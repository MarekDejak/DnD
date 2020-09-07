#include "mainwindow.h"

#include "loadiconfromfiles.h"
#include "selectcharacter.h"
#include "mapwidget.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupWindow();
    QStackedWidget* stackedWidget = new QStackedWidget(this);

    SelectCharacter* selectChar = new SelectCharacter(this);
    MapWidget* mapa = new MapWidget(this);

    setCentralWidget(stackedWidget);
    stackedWidget->addWidget(selectChar);
    stackedWidget->addWidget(mapa);

    connect(selectChar, &SelectCharacter::startPressed, this, [=]() { stackedWidget->setCurrentIndex(Map); });
    //    connect(selectChar, &SelectCharacter::closeApplication, this, [=]() { exit(0); });

    //    connect(selectChar, &SelectCharacter::selectCharacterFinished, this, [=]() {
    //        mapa->setCharacterInfo(selectChar->charInfo());
    //        stackedWidget->setCurrentIndex(1);
    //    });
}

void MainWindow::setupWindow() {
    setWindowTitle("DnD");
    setWindowIcon(loadIconFromFiles(":/icons/task_list_edit_%1_%2.png"));
}
