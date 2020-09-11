#include "editabilitiesdialog.h"

#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>

static QString dialogTitle = "Edit abilities";

EditAbilitiesDialog::EditAbilitiesDialog(CharacterModel* model, QWidget* parent) : QDialog(parent), m_model(model) {
    setupTitleAndGeometry();
    setupModel(model);
    populateLayout();
}

void EditAbilitiesDialog::setupTitleAndGeometry() {
    setWindowTitle(dialogTitle);
    QFontMetrics metrics(font(), this);
    setMinimumWidth(metrics.horizontalAdvance(dialogTitle) + 512);
}

void EditAbilitiesDialog::populateLayout() {
    auto* layout = new QVBoxLayout(this);
    auto* skillsView = new QListView(this);
    skillsView->setModel(m_skillsModel);
    skillsView->setEditTriggers(QAbstractItemView::EditKeyPressed | QAbstractItemView::DoubleClicked);
    layout->addWidget(skillsView);

    auto* okButton = new QPushButton("OK", this);
    auto* removeAbilityButton = new QPushButton("Remove ability", this);
    auto* addAbilityButton = new QPushButton("Add ability", this);

    connect(okButton, &QPushButton::pressed, this, &QDialog::accept);
    connect(removeAbilityButton, &QPushButton::pressed, this, &EditAbilitiesDialog::removeAbility);
    connect(addAbilityButton, &QPushButton::pressed, this, &EditAbilitiesDialog::addAbility);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(removeAbilityButton);
    buttonLayout->addWidget(addAbilityButton);

    layout->addItem(buttonLayout);
    setLayout(layout);
}

void EditAbilitiesDialog::removeAbility() {}

void EditAbilitiesDialog::addAbility() {}

void EditAbilitiesDialog::setupModel(CharacterModel* model) {
    m_skillsModel = new SkillsProxyModel(model, this);
}
