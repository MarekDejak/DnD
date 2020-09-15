#include "card.h"

#include <QDialogButtonBox>
#include <QLabel>

#include "charactermodel.h"

QVector<Character*> Card::m_openCharacters = {};

Card::Card(Character* character, QWidget* parent) : QDialog(parent), m_character(character) {
    manageOpenDialogs();
    setupTitleAndGeometry();
    populateLayout();
    show();
}

void Card::generateFixedLayout(QFormLayout* formLayout) {
    auto* nameEdit = new QLabel(this);
    nameEdit->setText(m_character->name());
    formLayout->addRow(nameLabel, nameEdit);

    auto* raceEdit = new QLabel(this);
    raceEdit->setText(m_character->getRace());
    formLayout->addRow(raceLabel, raceEdit);

    auto* professionEdit = new QLabel(this);
    professionEdit->setText(m_character->getProfession());
    formLayout->addRow(professionLabel, professionEdit);
}

void Card::populateLayout() {
    auto* formLayout = new QFormLayout(this);

    generateFixedLayout(formLayout);
    for (const auto [ability, value] : m_character->getAllAbilities()) {
        auto* abilityNameLabel = new QLabel(this);
        abilityNameLabel->setStyleSheet(
            "color: rgb(255, 255, 127); font: 12pt "
            "Cooper Black");
        abilityNameLabel->setText(ability);

        auto* valueLabel = new QLabel(this);
        valueLabel->setStyleSheet(
            "color: rgb(255, 255, 127); font: 12pt "
            "Cooper Black");
        valueLabel->setText(QString::number(value));

        formLayout->addRow(abilityNameLabel, valueLabel);
    }

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    formLayout->addWidget(buttonBox);

    setLayout(formLayout);
}

void Card::setupTitleAndGeometry() {
    setWindowTitle(m_character->name());
    QFontMetrics metrics(font(), this);
    setMinimumWidth(metrics.horizontalAdvance(m_character->name()) + 10);
}

void Card::manageOpenDialogs() {
    if (m_openCharacters.contains(m_character)) {
        deleteLater();
        return;
    }
    connect(this, &QDialog::finished, this, [=]() { m_openCharacters.removeOne(m_character); });
    m_openCharacters.push_back(m_character);
}
