#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    setupWindow();
    setupModel();
    setupViews();
    setupButtons();
}

void MainWindow::setupModel() {
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

void MainWindow::generateCSV() {
    auto file = QFile(defaultfileName);
    file.resize(0);
    file.open(QIODevice::WriteOnly);
    file.write(baseAbilities.toUtf8());
    file.close();
    m_model->setFile(defaultfileName);
}

void MainWindow::setupViews() {
    m_ui->availableCharactersListView->setModel(m_availableCharactersModel);
    m_ui->usedCharactersListView->setModel(m_usedCharactersModel);
    m_ui->availableCharactersListView->setFocusPolicy(Qt::ClickFocus);
    m_ui->usedCharactersListView->setFocusPolicy(Qt::ClickFocus);

    m_currentListView = m_ui->availableCharactersListView;
    connect(m_ui->availableCharactersListView, &QListView::clicked, this,
            [=]() { m_currentListView = m_ui->availableCharactersListView; });
    connect(m_ui->usedCharactersListView, &QListView::clicked, this,
            [=]() { m_currentListView = m_ui->usedCharactersListView; });

    connect(m_ui->availableCharactersListView, &QListView::doubleClicked, this, &MainWindow::editCharacter);
    connect(m_ui->usedCharactersListView, &QListView::doubleClicked, this, &MainWindow::editCharacter);
}

void MainWindow::setupWindow() {
    m_ui->setupUi(this);
    setWindowTitle("DnD");
    setWindowIcon(loadIconFromFiles(":/icons/task_list_edit_%1_%2.png"));
}

void MainWindow::setupButtons() {
    connect(m_ui->rightArrow, &QPushButton::pressed, this, &MainWindow::addCharacterToUsed);
    connect(m_ui->leftArrow, &QPushButton::pressed, this, &MainWindow::removeCharacterFromUsed);
    connect(m_ui->editCharacterButton, &QPushButton::pressed, this, &MainWindow::editCharacter);
    connect(m_ui->addCharacterButton, &QPushButton::pressed, this, &MainWindow::addNewCharacter);
    connect(m_ui->removeCharacterButton, &QPushButton::pressed, this, &MainWindow::deleteCharacter);
    connect(m_ui->saveButton, &QPushButton::pressed, this, &MainWindow::writeToFile);
    connect(m_ui->editAbilitiesButton, &QPushButton::pressed, this, &MainWindow::editAbilities);

    loadButtonIcons();
}

void MainWindow::writeToFile() {
    m_model->writeDataFile();
}

void MainWindow::editAbilities(){
    qDebug()<<"editing abilities";
}

void MainWindow::deleteCharacter() {
    const auto selection = m_currentListView->selectionModel()->selection();
    if (selection.count() == 1) {
        const QString name = selection.indexes().first().data().toString();
        if (QMessageBox::Yes == QMessageBox::question(this, "Question", confirmDeletion.arg(name))) {
            m_currentListView->model()->removeRow(selection.indexes().first().row());
        }
    }
}

void MainWindow::addNewCharacter() {
    m_model->insertRow(m_model->rowCount());
}

void MainWindow::editCharacter() {
    const auto selection = m_currentListView->selectionModel()->selection();
    if (selection.count() == 1) {
        new EditCharacterDialog(selection.indexes().first().data(Qt::UserRole).value<Character*>(), this);
    }
}

void MainWindow::addCharacterToUsed() {
    const auto selection = m_ui->availableCharactersListView->selectionModel()->selection();
    if (selection.count() == 1) {
        m_usedCharacters.push_back(selection.indexes().first().data().toString());
    }
    updateFilterModels();
}

void MainWindow::removeCharacterFromUsed() {
    const auto selection = m_ui->usedCharactersListView->selectionModel()->selection();
    if (selection.count() == 1) {
        m_usedCharacters.removeOne(selection.indexes().first().data().toString());
    }
    updateFilterModels();
}

void MainWindow::updateFilterModels() {
    m_usedCharactersModel->setFilterStringList(m_usedCharacters);
    m_availableCharactersModel->setFilterStringList(m_usedCharacters);
}

void MainWindow::loadButtonIcons() {
    m_ui->leftArrow->setIcon(loadIconFromFiles(":/icons/simple_arrow_left_green_%1_%2.png"));
    m_ui->rightArrow->setIcon(loadIconFromFiles(":/icons/simple_arrow_right_green_%1_%2.png"));
    m_ui->addCharacterButton->setIcon(loadIconFromFiles(":/icons/plus_green_%1_%2.png"));
    m_ui->removeCharacterButton->setIcon(loadIconFromFiles(":/icons/delete_red_%1_%2.png"));
    m_ui->editCharacterButton->setIcon(loadIconFromFiles(":/icons/properties_edit_%1_%2.png"));
    m_ui->saveButton->setIcon(loadIconFromFiles(":/icons/save_%1_%2.png"));
    m_ui->cancelButton->setIcon(loadIconFromFiles(":/icons/forbidden_%1_%2.png"));
    m_ui->editAbilitiesButton->setIcon(loadIconFromFiles(":/icons/task_list_properties_%1_%2.png"));
}

MainWindow::~MainWindow() {
    delete m_ui;
}
