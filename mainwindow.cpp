#include "mainwindow.h"

#include "selectcharacter.h"
#include "mapwidget.h"

#include <QStackedWidget>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    SelectCharacter *selectChar = new SelectCharacter(this);

    MapWidget *mapa = new MapWidget(this);

    setCentralWidget(stackedWidget);
    stackedWidget->addWidget(selectChar);
    stackedWidget->addWidget(mapa);


    connect(selectChar, &SelectCharacter::closeApplication, this, [=](){exit(0);});

    connect(selectChar, &SelectCharacter::selectCharacterFinished, this, [=](){
        mapa->setCharacterInfo(selectChar->charInfo());
        stackedWidget->setCurrentIndex(1);} );



}

MainWindow::~MainWindow()
{
}

