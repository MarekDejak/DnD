#include "waypointdialog.h"
#include "ui_waypointdialog.h"
#include "mapa.h"

#include <QColorDialog>
#include <QDebug>

WaypointDialog::WaypointDialog(QWidget* parent) : QDialog(parent), ui(new Ui::WaypointDialog) {
    ui->setupUi(this);

    connect(ui->colorButton, &QPushButton::pressed, this, &WaypointDialog::onColorClicked);
    connect(ui->acceptButton, &QPushButton::pressed, this, &WaypointDialog::onAcceptClicked);
    connect(ui->cancelButton, &QPushButton::pressed, this, &WaypointDialog::reject);

    m_color = QColor(Qt::black);
}

WaypointDialog::~WaypointDialog() {
    delete ui;
}

void WaypointDialog::onColorClicked() {
    m_color = QColorDialog::getColor(m_color, this, "Kolor tekstu");
}

void WaypointDialog::onAcceptClicked() {
    m_text = ui->pinName->text();
    emit accept();
}
