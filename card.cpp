#include "card.h"
#include "ui_card.h"

#include <QDialog>

Card::Card(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Card)
{



}

Card::~Card()
{
    delete ui;
}


