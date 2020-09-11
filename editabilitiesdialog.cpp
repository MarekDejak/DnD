#include "editabilitiesdialog.h"

#include <QMessageBox>
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
    m_skillsView = new QListView(this);
    m_skillsView->setModel(m_skillsModel);
    m_skillsView->setEditTriggers(QAbstractItemView::EditKeyPressed | QAbstractItemView::DoubleClicked);
    layout->addWidget(m_skillsView);

    auto* okButton = new QPushButton("OK", this);
    auto* removeAbilityButton = new QPushButton("Remove ability", this);
    auto* addAbilityButton = new QPushButton("Add ability", this);

    connect(okButton, &QPushButton::pressed, this, &QDialog::accept);
    connect(removeAbilityButton, &QPushButton::pressed, this, &EditAbilitiesDialog::removeAbility);
    connect(addAbilityButton, &QPushButton::pressed, this, &EditAbilitiesDialog::addAbility);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(addAbilityButton);
    buttonLayout->addWidget(removeAbilityButton);

    layout->addItem(buttonLayout);
    setLayout(layout);
}

void EditAbilitiesDialog::removeAbility() {
    const auto selection = m_skillsView->selectionModel()->selection();
    if (selection.count() == 1) {
        const auto name = selection.indexes().first().data().toString();
        if (QMessageBox::Yes ==
            QMessageBox::question(this, "Confirmation", QString("Do you really want to delete '%1'?").arg(name))) {
            m_skillsModel->removeSkill(name);
        }
    }
}

void EditAbilitiesDialog::addAbility() {
    m_skillsModel->addSkill();
}

void EditAbilitiesDialog::setupModel(CharacterModel* model) {
    m_skillsModel = new SkillsProxyModel(model, this);
}
