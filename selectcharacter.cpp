#include "selectcharacter.h"

#include "ui_selectcharacter.h"

#include "charactermodel.h"
#include "editcharacterdialog.h"
#include "loadiconfromfiles.h"
#include "stringfiltermodel.h"

#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

static const QString baseAbilities =
    "Name,Kutarate,Chudo,Gimnastyka korekcyjna,Polewanie,Praca na wysokosciach,Paszport polsatu";
static const QString confirmDeletion = "Do you really want to delete '%1'?";
static const QString defaultfileName = "CharacterSheet.csv";
static const QString errorMessage =
    "The following error occured: %1. Do you want to generate an empty 'CharacterSheet.csv'?";

SelectCharacter::SelectCharacter(QWidget* parent) : QWidget(parent), m_ui(new Ui::SelectCharacter) {
    m_ui->setupUi(this);
    setupModel();
    setupViews();
    setupButtons();
}

void SelectCharacter::setupModel() {
    m_model = new CharacterModel(this);
    connect(m_model, &CharacterModel::fatal, this, [=](QString fatal) {
        QMessageBox::warning(this, "Fatal error", fatal);
        exit(0);
    });
    connect(m_model, &CharacterModel::error, this, [=](QString error) {
        if (QMessageBox::Yes == QMessageBox::question(this, "Error", errorMessage.arg(error))) {
            generateCSV();
        } else {
            exit(0);
        }
    });
    connect(m_model, &CharacterModel::warning, this,
            [=](QString warning) { QMessageBox::warning(this, "Warning", warning); });
    m_model->setFile(defaultfileName);

    m_availableCharactersModel = new StringFilterModel(this);
    m_usedCharactersModel = new StringFilterModel(this);
    m_availableCharactersModel->setSourceModel(m_model);
    m_usedCharactersModel->setSourceModel(m_model);

    m_availableCharactersModel->setAcceptOnFound(false);
}

void SelectCharacter::generateCSV() {
    auto file = QFile(defaultfileName);
    file.resize(0);
    file.open(QIODevice::WriteOnly);
    file.write(baseAbilities.toUtf8());
    file.close();
    m_model->setFile(defaultfileName);
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
    qDebug() << "editing abilities";
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
        new EditCharacterDialog(selection.indexes().first().data(Qt::UserRole).value<Character*>(), this);
    }
}

void SelectCharacter::addCharacterToUsed() {
    const auto selection = m_ui->availableCharactersListView->selectionModel()->selection();
    if (selection.count() == 1) {
        m_usedCharacters.push_back(selection.indexes().first().data().toString());
    }
    updateFilterModels();
}

void SelectCharacter::removeCharacterFromUsed() {
    const auto selection = m_ui->usedCharactersListView->selectionModel()->selection();
    if (selection.count() == 1) {
        m_usedCharacters.removeOne(selection.indexes().first().data().toString());
    }
    updateFilterModels();
}

void SelectCharacter::updateFilterModels() {
    m_usedCharactersModel->setFilterStringList(m_usedCharacters);
    m_availableCharactersModel->setFilterStringList(m_usedCharacters);
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
