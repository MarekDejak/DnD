#include "card.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QFormLayout>
#include <map>

#include "charactermodel.h"

QVector<Character*> Card::m_openCharacters = {};

Card::Card(QPixmap* pixmap, Character* character, QWidget* parent)
    : QDialog(parent), m_character(character), m_characterPortrait(pixmap) {
    setStyleSheet(
        "color: black; font: 12pt "
        "Cooper Black");
    manageOpenDialogs();
    setupTitleAndGeometry();
    generateFixedLayout();
    show();
}

void Card::generateFixedLayout() {
    auto* gridLayout = new QGridLayout(this);

    auto* nameEdit = new QLabel;
    nameEdit->setText(m_character->name());
    nameEdit->setStyleSheet(
        "color: black; font: 20pt "
        "Showcard Gothic");
    gridLayout->addWidget(nameEdit, 0, 0, 1, 3, Qt::AlignHCenter);

    auto* verticalLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout(this);

    auto* raceEdit = new QLabel(this);
    raceEdit->setText(m_character->getRace());
    formLayout->addRow(raceLabel, raceEdit);

    auto* professionEdit = new QLabel(this);
    professionEdit->setText(m_character->getProfession());
    formLayout->addRow(professionLabel, professionEdit);
    verticalLayout->addLayout(formLayout);

    auto* attributesL = new QLabel;
    attributesL->setText(attributesLabel);
    attributesL->setStyleSheet(
        "color: black; font: 16pt "
        "Showcard Gothic");
    verticalLayout->addWidget(attributesL);

    gridLayout->addLayout(verticalLayout, 1, 0);
    auto* characterImage = new QLabel(this);
    characterImage->setPixmap(*m_characterPortrait);  //
    gridLayout->addWidget(characterImage, 1, 1, 1, 2, Qt::AlignCenter);

    auto* skillsL = new QLabel;
    skillsL->setText(skillsLabel);
    skillsL->setStyleSheet(
        "color: black; font: 16pt "
        "Showcard Gothic");
    gridLayout->addWidget(skillsL, 2, 0);

    auto* skillsLayoutFirst = new QFormLayout(this);
    auto allAbilities = m_character->getAllAbilities();

    int skillsRowsInForm = allAbilities.size() / 2 + 1;

    auto it = allAbilities.begin();
    for (int i = 0; i < skillsRowsInForm; i++) {
        auto* abilityNameLabel = new QLabel(this);
        abilityNameLabel->setText(it->first);
        auto* valueLabel = new QLabel(this);
        valueLabel->setText(QString::number(it->second));
        skillsLayoutFirst->addRow(abilityNameLabel, valueLabel);
        it++;
    }
    gridLayout->addLayout(skillsLayoutFirst, 3, 0);

    auto* skillsLayoutSecond = new QFormLayout(this);
    do {
        auto* abilityNameLabel = new QLabel(this);
        abilityNameLabel->setText(it->first);
        auto* valueLabel = new QLabel(this);
        valueLabel->setText(QString::number(it->second));
        skillsLayoutSecond->addRow(abilityNameLabel, valueLabel);
        it++;
    } while (it != allAbilities.end());
    gridLayout->addLayout(skillsLayoutSecond, 3, 1);

    setLayout(gridLayout);
}

void Card::populateLayout() {
    auto* formLayout = new QFormLayout(this);

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
