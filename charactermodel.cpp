#include "charactermodel.h"

#include <QTextStream>
#include <QWidget>

static const QString buttonImagePath = "images/%1_button.png";
static const QString pawnImagePath = "images/%1_pawn.png";
static const QString incorrectFileFormat = "Incorrect file format";
static const QString fileNotFound = "'CharacterSheet.csv' does not exist";
static const QString fileUsed = "'CharacterSheet.csv' is currently being used by another program";
static const QString corruptedCharacter = "'Character %1' entry corrupted, skipping";

CharacterModel::CharacterModel(QWidget* parent) : QAbstractTableModel(parent) {}

void CharacterModel::setFile(QString fileName) {
    m_dataFile.setFileName(fileName);
    if (openFile()) {
        parseDataFile();
    }
}

bool CharacterModel::openFile() {
    if (m_dataFile.exists()) {
        if (m_dataFile.open(QIODevice::ReadWrite)) {
            return true;
        } else {
            emit fatal(fileUsed);
        }
    } else {
        emit error(fileNotFound);
    }
    return false;
}

CharacterModel::~CharacterModel() {
    writeDataFile();
    for (auto* character : m_characters) {
        delete character;
    }
    m_dataFile.close();
}

void CharacterModel::emitWarningAndDeleteCharacter(Character* character) {
    emit warning(corruptedCharacter.arg(character->name()));
    delete character;
}

std::tuple<QString, QString, QString> CharacterModel::parseFixedColumns(QStringList& values) {
    if (values.count() < FixedColumnCount) {
        emit error(incorrectFileFormat);
    }
    const QString name = values.takeFirst();
    const QString race = values.takeFirst();
    const QString profession = values.takeFirst();
    return {name, race, profession};
}

void CharacterModel::parseDataFile() {
    beginResetModel();
    QTextStream in(&m_dataFile);
    const QString headerLine = in.readLine();
    if (headerLine.isNull()) {
        emit error(incorrectFileFormat);
    }
    QStringList skills = headerLine.split(",");
    const auto [name, race, profession] = parseFixedColumns(skills);
    if (name != nameLabel || race != raceLabel || profession != professionLabel) {
        emit error(incorrectFileFormat);
    }
    m_skills = skills;

    QString line = in.readLine();
    while (!line.isNull()) {
        auto values = line.split(",");
        const auto [name, race, profession] = parseFixedColumns(values);
        auto* character = new Character(name, race, profession);
        if (values.count() != skills.count()) {
            emitWarningAndDeleteCharacter(character);
            line = in.readLine();
            continue;
        }
        for (int i = 0; i < values.count(); i++) {
            bool ok = false;
            character->setAbility(skills[i], values[i].toInt(&ok));
            if (!ok) {
                emitWarningAndDeleteCharacter(character);
                line = in.readLine();
                continue;
            }
        }
        m_characters.push_back(character);
        line = in.readLine();
    }
    endResetModel();
}

void CharacterModel::writeDataFile() {
    QString output;
    output.push_back(QString("%1,").arg(nameLabel));
    output.push_back(QString("%1,").arg(raceLabel));
    output.push_back(QString("%1,").arg(professionLabel));
    output.append(m_skills.join(","));
    output.push_back("\n");
    for (const auto character : m_characters) {
        output.push_back(character->name() + ",");
        output.push_back(character->getRace() + ",");
        output.push_back(character->getProfession() + ",");
        for (const auto skill : m_skills) {
            output.push_back(QString::number(character->getAbility(skill)) + ",");
        }
        output.chop(1);
        output.push_back("\n");
    }

    m_dataFile.resize(0);
    m_dataFile.write(output.toUtf8());
    m_dataFile.close();
    openFile();
}

int CharacterModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_characters.count();
}

int CharacterModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_skills.count() + FixedColumnCount;
}

QString CharacterModel::getUniqueCharacterName() {
    QString suggestedName = "Character";
    for (const auto character : m_characters) {
        if (character->name() == suggestedName) {
            suggestedName += "1";
        }
    }
    return suggestedName;
}

QString CharacterModel::getUniqueSkillName() {
    QString suggestedName = "Skill";
    for (const auto skill : m_skills) {
        if (skill == suggestedName) {
            suggestedName += "1";
        }
    }
    return suggestedName;
}

bool CharacterModel::removeRows(int row, int count, const QModelIndex& parent) {
    beginResetModel();
    Q_UNUSED(parent);
    Q_UNUSED(count);
    m_characters.remove(row);
    endResetModel();
    return true;
}

bool CharacterModel::insertRows(int row, int count, const QModelIndex& parent) {
    beginResetModel();
    Q_UNUSED(parent);
    Q_UNUSED(count);
    auto* character = new Character(getUniqueCharacterName());
    for (const auto skill : m_skills) {
        character->setAbility(skill, 0);
    }
    m_characters.insert(row, character);
    endResetModel();
    return true;
}

QVariant CharacterModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.column() == NameColumn) {
            return m_characters.at(index.row())->name();
        } else if (index.column() == RaceColumn) {
            return m_characters.at(index.row())->getRace();
        } else if (index.column() == ProfColumn) {
            return m_characters.at(index.row())->getProfession();
        } else {
            return m_characters.at(index.row())->getAbility(m_skills.at(index.column() - FixedColumnCount));
        }
    } else if (role == CharacterRole) {
        return QVariant::fromValue(m_characters.at(index.row()));
    } else if (role == UsedRole) {
        return m_characters.at(index.row())->used();
    } else if (role ==
               ButtonImageRole) {  // zebrac w PortraitImageRole, wyrzucic skalowanie, zastowowac do Button i Card
        const QString name = m_characters.at(index.row())->name().replace(" ", "");
        return QPixmap(buttonImagePath.arg(name));
    } else if (role == PawnImageRole) {
        const QString name = m_characters.at(index.row())->name().replace(" ", "");
        return QPixmap(pawnImagePath.arg(name)).scaledToHeight(70, Qt::SmoothTransformation);
    } else if (role == SkillsRole) {
        return m_skills;
    }
    return QVariant();
}

bool CharacterModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == UsedRole) {
        m_characters.at(index.row())->setUsed(value.toBool());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void CharacterModel::editSkill(QString from, QString to) {
    m_skills.replace(m_skills.indexOf(from), to);
    for (auto* character : m_characters) {
        character->editAbility(from, to);
    }
}

void CharacterModel::removeSkill(QString skill) {
    m_skills.removeOne(skill);
    for (auto* character : m_characters) {
        character->removeAbility(skill);
    }
}

void CharacterModel::addSkill() {
    const auto name = getUniqueSkillName();
    m_skills.push_back(name);
    for (auto* character : m_characters) {
        character->addAbility(name);
    }
}
