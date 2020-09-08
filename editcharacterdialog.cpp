#include "editcharacterdialog.h"

#include <QDialogButtonBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

QVector<Character*> EditCharacterDialog::m_openCharacters = {};

EditCharacterDialog::EditCharacterDialog(bool editable, Character* character, QWidget* parent)
    : QDialog(parent), m_character(character), m_editable(editable) {
    manageOpenDialogs();
    setupTitleAndGeometry();
    populateLayout();
    show();
}

void EditCharacterDialog::populateLayout() {
    auto* formLayout = new QFormLayout(this);

    if (m_editable) {
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
    } else {
        auto* label = new QLabel(this);
        label->setText(m_character->name());
        formLayout->addRow(label);

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
