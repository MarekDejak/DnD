#include "editcharacterdialog.h"

#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>

QVector<Character*> EditCharacterDialog::m_openCharacters = {};

EditCharacterDialog::EditCharacterDialog(Character* character, QWidget* parent)
    : QDialog(parent), m_character(character) {
    manageOpenDialogs();
    setupTitleAndGeometry();
    populateLayout();
    show();
}

void EditCharacterDialog::populateLayout() {
    auto* formLayout = new QFormLayout(this);

    auto* nameEdit = new QLineEdit(this);
    nameEdit->setText(m_character->name());
    formLayout->addRow("Name", nameEdit);
    connect(nameEdit, &QLineEdit::editingFinished, this, [=]() { m_character->setName(nameEdit->text()); });

    for (const auto [ability, value] : m_character->getAllAbilities()) {
        auto* spinBox = new QSpinBox(this);
        spinBox->setValue(value);
        const auto abilityName = ability;
        connect(spinBox, &QSpinBox::editingFinished, this,
                [=]() { m_character->setAbility(abilityName, spinBox->value()); });
        formLayout->addRow(ability, spinBox);
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
