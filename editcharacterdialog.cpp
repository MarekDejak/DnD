#include "editcharacterdialog.h"

#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

#include "charactermodel.h"

QVector<Character*> EditCharacterDialog::m_openCharacters = {};

EditCharacterDialog::EditCharacterDialog(bool editable, Character* character, QWidget* parent)
    : QDialog(parent), m_editable(editable), m_character(character) {
    manageOpenDialogs();
    setupTitleAndGeometry();
    populateLayout();
    show();
}

template<class Editor>
void EditCharacterDialog::generateFixedLayout(QFormLayout* formLayout) {
    auto* nameEdit = new Editor(this);
    nameEdit->setText(m_character->name());
    formLayout->addRow(nameLabel, nameEdit);

    auto* raceEdit = new Editor(this);
    raceEdit->setText(m_character->getRace());
    formLayout->addRow(raceLabel, raceEdit);

    auto* professionEdit = new Editor(this);
    professionEdit->setText(m_character->getProfession());
    formLayout->addRow(professionLabel, professionEdit);

    if constexpr (std::is_same_v<QLineEdit, Editor>) {
        connect(nameEdit, &Editor::editingFinished, this, [=]() { m_character->setName(nameEdit->text()); });
        connect(professionEdit, &Editor::editingFinished, this,
                [=]() { m_character->setProfession(professionEdit->text()); });
        connect(raceEdit, &Editor::editingFinished, this, [=]() { m_character->setRace(raceEdit->text()); });
    }
}

void EditCharacterDialog::populateLayout() {
    auto* formLayout = new QFormLayout(this);

    if (m_editable) {
        generateFixedLayout<QLineEdit>(formLayout);
        for (const auto [ability, value] : m_character->getAllAbilities()) {
            auto* spinBox = new QSpinBox(this);
            spinBox->setValue(value);
            const auto abilityName = ability;
            connect(spinBox, &QSpinBox::editingFinished, this,
                    [=]() { m_character->setAbility(abilityName, spinBox->value()); });
            formLayout->addRow(ability, spinBox);
        }
    } else {
        generateFixedLayout<QLabel>(formLayout);
        for (const auto [ability, value] : m_character->getAllAbilities()) {
            auto* label = new QLabel(this);
            label->setText(QString::number(value));
            formLayout->addRow(ability, label);
        }
    }

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);
}

void EditCharacterDialog::setupTitleAndGeometry() {
    setWindowTitle(m_character->name());
    QFontMetrics metrics(font(), this);
    setMinimumWidth(metrics.horizontalAdvance(m_character->name()) + 512);
}

void EditCharacterDialog::manageOpenDialogs() {
    if (m_openCharacters.contains(m_character)) {
        deleteLater();
        return;
    }
    connect(this, &QDialog::finished, this, [=]() { m_openCharacters.removeOne(m_character); });
    m_openCharacters.push_back(m_character);
}
