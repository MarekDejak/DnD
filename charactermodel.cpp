#include "charactermodel.h"

#include <QTextStream>
#include <QWidget>

static const QString nameLabel = "Name";
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

void CharacterModel::parseDataFile() {
    beginResetModel();
    QTextStream in(&m_dataFile);
    const QString headerLine = in.readLine();
    if (headerLine.isNull()) {
        emit error(incorrectFileFormat);
    }
    QStringList skills = headerLine.split(",");
    if (skills.takeFirst() != nameLabel) {
        emit error(incorrectFileFormat);
    }
    m_skills = skills;

    QString line = in.readLine();
    while (!line.isNull()) {
        auto values = line.split(",");
        auto* character = new Character(values.takeFirst());
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
    output.push_back("Name,");
    output.append(m_skills.join(","));
    output.push_back("\n");
    for (const auto character : m_characters) {
        output.push_back(character->name() + ",");
        for (const auto skill : m_skills) {
            output.push_back(QString::number(character->getAbility(skill)) + ",");
        }
        output.chop(1);
        output.push_back("\n");
    }

    m_dataFile.resize(0);
    m_dataFile.write(output.toUtf8());
}

int CharacterModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_characters.count();
}

int CharacterModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_skills.count() + 1;
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
        if (index.column() == 0) {
            return m_characters.at(index.row())->name();
        } else {
            return m_characters.at(index.row())->getAbility(m_skills.at(index.column() - 1));
        }
    } else if (role == CharacterRole) {
        return QVariant::fromValue(m_characters.at(index.row()));
    } else if (role == UsedRole) {
        return m_characters.at(index.row())->used();
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
