#include "mapwidget.h"

#include "loadiconfromfiles.h"
#include "editcharacterdialog.h"
#include <waypointdialog.h>

#include <QVBoxLayout>
#include <QDebug>
#include <QVector>
#include <QListView>
#include <QPixmap>

static const int buttonImageHeight = 100;

MapWidget::MapWidget(CharacterModel* model, QWidget* parent) : QWidget(parent), m_model(model) {
    connect(m_model, &QAbstractItemModel::dataChanged, this, &MapWidget::onDataChanged);

    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    m_verticalLayout = new QVBoxLayout(this);

    QPushButton* waypoint = new QPushButton("Znacznik", this);
    QPushButton* stopGame = new QPushButton("Stop game", this);
    stopGame->setIcon(loadIconFromFiles(":/icons/stop_%1_%2.png"));

    connect(stopGame, &QPushButton::pressed, this, &MapWidget::stopPressed);
    connect(waypoint, &QPushButton::pressed, this, &MapWidget::waypointClicked);

    m_verticalLayout->addWidget(waypoint);
    m_verticalLayout->addWidget(stopGame);

    m_mapa = new Mapa(this);
    m_mapa->setCharacterModel(m_model);
    horizontalLayout->addWidget(m_mapa);
    horizontalLayout->addLayout(m_verticalLayout);
    setLayout(horizontalLayout);

    this->setWindowTitle("Mapa");
}

void MapWidget::waypointClicked() {
    WaypointDialog waypointDialog(this);
    waypointDialog.setWindowTitle("Znacznik");
    if (waypointDialog.exec() == QDialog::Accepted) {
        m_mapa->createPin(waypointDialog.color(), waypointDialog.text());
    }
}

void MapWidget::onPrzyciskClicked(const QModelIndex& index) {
    auto* character = m_model->data(index, CharacterModel::CharacterRole).value<Character*>();
    auto image = m_model->data(index, CharacterModel::ButtonImageRole).value<QPixmap>();

    new Card(image, character, this);
}

void MapWidget::onDataChanged() {
    for (auto* button : m_buttons) {
        m_verticalLayout->removeWidget(button);
        delete button;
    }
    m_buttons.clear();
    for (int i = 0; i < m_model->rowCount(); i++) {
        if (m_model->data(m_model->index(i, 0), CharacterModel::UsedRole).toBool()) {
            const QString name = m_model->data(m_model->index(i, 0)).toString();
            QPushButton* button = new QPushButton(this);
            const auto pixmap = m_model->data(m_model->index(i, 0), CharacterModel::ButtonImageRole)
                                    .value<QPixmap>()
                                    .scaledToHeight(buttonImageHeight, Qt::SmoothTransformation);
            if (!pixmap.isNull()) {
                button->setIconSize(pixmap.rect().size());
                button->setIcon(pixmap);
            } else {
                button->setText(name);
            }
            button->setStyleSheet("border: 1px solid black; border-radius: 25px;");
            connect(button, &QPushButton::clicked, this, [=]() { onPrzyciskClicked(m_model->index(i, 0)); });
            m_buttons.push_back(button);
            m_verticalLayout->addWidget(button);
        }
    }
}
