#include "selectcharacter.h"

#include "ui_selectcharacter.h"

#include "charactermodel.h"
#include "editabilitiesdialog.h"
#include "editcharacterdialog.h"
#include "loadiconfromfiles.h"
#include "usedfiltermodel.h"

#include <QDebug>
#include <QMessageBox>

static const QString confirmDeletion = "Do you really want to delete '%1'?";

SelectCharacter::SelectCharacter(CharacterModel* model, QWidget* parent)
    : QWidget(parent), m_ui(new Ui::SelectCharacter), m_model(model) {
    m_ui->setupUi(this);
    setupProxyModels();
    setupViews();
    setupButtons();
}

void SelectCharacter::setupProxyModels() {
    m_usedCharactersModel = new UsedFilterModel(this);
    m_usedCharactersModel->setSourceModel(m_model);

    m_availableCharactersModel = new UsedFilterModel(this);
    m_availableCharactersModel->setSourceModel(m_model);
    m_availableCharactersModel->setAcceptOnFound(false);
}

void SelectCharacter::setupViews() {
    m_ui->availableCharactersListView->setModel(m_availableCharactersModel);
    m_ui->usedCharactersListView->setModel(m_usedCharactersModel);
    m_ui->availableCharactersListView->setFocusPolicy(Qt::ClickFocus);
    m_ui->usedCharactersListView->setFocusPolicy(Qt::ClickFocus);

    m_currentListView = m_ui->availableCharactersListView;
    connect(m_ui->availableCharactersListView, &QListView::clicked, this,
            [=]() { m_currentListView = m_ui->availableCharactersListView; });
    connect(m_ui->usedCharactersListView, &QListView::clicked, this,
            [=]() { m_currentListView = m_ui->usedCharactersListView; });

    connect(m_ui->availableCharactersListView, &QListView::doubleClicked, this, &SelectCharacter::editCharacter);
    connect(m_ui->usedCharactersListView, &QListView::doubleClicked, this, &SelectCharacter::editCharacter);
}

void SelectCharacter::setupButtons() {
    connect(m_ui->rightArrow, &QPushButton::pressed, this, &SelectCharacter::addCharacterToUsed);
    connect(m_ui->leftArrow, &QPushButton::pressed, this, &SelectCharacter::removeCharacterFromUsed);
    connect(m_ui->editCharacterButton, &QPushButton::pressed, this, &SelectCharacter::editCharacter);
    connect(m_ui->addCharacterButton, &QPushButton::pressed, this, &SelectCharacter::addNewCharacter);
    connect(m_ui->removeCharacterButton, &QPushButton::pressed, this, &SelectCharacter::deleteCharacter);
    connect(m_ui->saveButton, &QPushButton::pressed, this, &SelectCharacter::writeToFile);
    connect(m_ui->editAbilitiesButton, &QPushButton::pressed, this, &SelectCharacter::editAbilities);
    connect(m_ui->startButton, &QPushButton::pressed, this, &SelectCharacter::startPressed);

    loadButtonIcons();
}

void SelectCharacter::writeToFile() {
    m_model->writeDataFile();
}

void SelectCharacter::editAbilities() {
    EditAbilitiesDialog dialog(m_model, this);
    dialog.exec();
}

void SelectCharacter::deleteCharacter() {
    const auto selection = m_currentListView->selectionModel()->selection();
    if (selection.count() == 1) {
        const QString name = selection.indexes().first().data().toString();
        if (QMessageBox::Yes == QMessageBox::question(this, "Question", confirmDeletion.arg(name))) {
            m_currentListView->model()->removeRow(selection.indexes().first().row());
        }
    }
}

void SelectCharacter::addNewCharacter() {
    m_model->insertRow(m_model->rowCount());
}

void SelectCharacter::editCharacter() {
    const auto selection = m_currentListView->selectionModel()->selection();
    if (selection.count() == 1) {
        new EditCharacterDialog(
            true, selection.indexes().first().data(CharacterModel::CharacterRole).value<Character*>(), this);
    }
}

void SelectCharacter::addCharacterToUsed() {
    const auto selection = m_ui->availableCharactersListView->selectionModel()->selection();
    if (selection.count() == 1) {
        m_availableCharactersModel->setData(selection.indexes().first(), true, CharacterModel::UsedRole);
    }
}

void SelectCharacter::removeCharacterFromUsed() {
    const auto selection = m_ui->usedCharactersListView->selectionModel()->selection();
    if (selection.count() == 1) {
        m_usedCharactersModel->setData(selection.indexes().first(), false, CharacterModel::UsedRole);
    }
}

void SelectCharacter::loadButtonIcons() {
    m_ui->leftArrow->setIcon(loadIconFromFiles(":/icons/simple_arrow_left_green_%1_%2.png"));
    m_ui->rightArrow->setIcon(loadIconFromFiles(":/icons/simple_arrow_right_green_%1_%2.png"));
    m_ui->addCharacterButton->setIcon(loadIconFromFiles(":/icons/plus_green_%1_%2.png"));
    m_ui->removeCharacterButton->setIcon(loadIconFromFiles(":/icons/delete_red_%1_%2.png"));
    m_ui->editCharacterButton->setIcon(loadIconFromFiles(":/icons/properties_edit_%1_%2.png"));
    m_ui->saveButton->setIcon(loadIconFromFiles(":/icons/save_%1_%2.png"));
    m_ui->startButton->setIcon(loadIconFromFiles(":/icons/checkmark_green_%1_%2.png"));
    m_ui->editAbilitiesButton->setIcon(loadIconFromFiles(":/icons/task_list_properties_%1_%2.png"));
}

SelectCharacter::~SelectCharacter() {
    delete m_ui;
}
