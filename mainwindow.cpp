#include "mainwindow.h"

#include "loadiconfromfiles.h"
#include "selectcharacter.h"
#include "mapwidget.h"

#include <QMessageBox>
#include <QStackedWidget>

static const QString errorMessage =
    "The following error occured: %1. Do you want to generate an empty 'CharacterSheet.csv'?";
static const QString defaultAbilities =
    "Name,Race,Profession,Kutarate,Chudo,Gimnastyka korekcyjna,Polewanie,Praca na wysokosciach,Paszport polsatu";
static const QString defaultfileName = "CharacterSheet.csv";

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupWindow();
    setupModel();
    setupUI();
    setupStyleSheets();
}

void MainWindow::setupStyleSheets() {
    setStyleSheet(
        "QPushButton {color: rgb(0, 0, 0);font: 75 9pt Berlin Sans FB; background-color: rgb(150, 150, 150);}");
}

void MainWindow::setupUI() {
    QStackedWidget* stackedWidget = new QStackedWidget(this);

    SelectCharacter* selectChar = new SelectCharacter(m_model, this);
    MapWidget* map = new MapWidget(m_model, this);

    setCentralWidget(stackedWidget);
    stackedWidget->addWidget(selectChar);
    stackedWidget->addWidget(map);

    connect(selectChar, &SelectCharacter::startPressed, this, [=]() { stackedWidget->setCurrentIndex(Map); });
    connect(map, &MapWidget::stopPressed, this, [=]() { stackedWidget->setCurrentIndex(SelectChar); });
}

void MainWindow::setupWindow() {
    setWindowTitle("DnD");
    setWindowIcon(loadIconFromFiles(":/icons/task_list_edit_%1_%2.png"));
}

void MainWindow::generateCSV() {
    auto file = QFile(defaultfileName);
    file.resize(0);
    file.open(QIODevice::WriteOnly);
    file.write(defaultAbilities.toUtf8());
    file.close();
    m_model->setFile(defaultfileName);
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
}
