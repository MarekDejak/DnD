#include <QtWidgets>
#include <QApplication>
#include <QVector>
#include <QDebug>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QImage>

#include "mapa.h"
#include "selectcharacter.h"


static int pawnHeight = 50;

Mapa::Mapa(CharacterModel* model, QWidget* parent) : QFrame(parent), m_model(model) {
    connect(m_model, &QAbstractItemModel::dataChanged, this, &Mapa::onDataChanged);

    m_scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(m_scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap backgroundPix(":/images/images/background.png");
    setMinimumSize(backgroundPix.width() + 20, backgroundPix.height() + 20);
    m_backgroundImageHeight = backgroundPix.height();
    QGraphicsPixmapItem* background = m_scene->addPixmap(backgroundPix);
    background->setZValue(0);
    m_scene->addItem(background);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}

void Mapa::onDataChanged() {
    for (auto* pawn : m_pawns) {
        delete pawn;
    }
    m_pawns.clear();

    int amountOfPlayers = 0;
    for (int i = 0; i < m_model->rowCount(); i++) {
        if (m_model->data(m_model->index(i, 0), CharacterModel::UsedRole).toBool()) {
            const auto pixmap = m_model->data(m_model->index(i, 0), CharacterModel::PawnImageRole)
                                    .value<QPixmap>()
                                    .scaledToHeight(pawnHeight, Qt::SmoothTransformation);
            QGraphicsPixmapItem* pawn = m_scene->addPixmap(pixmap);
            pawn->setY(amountOfPlayers * pawnHeight);
            pawn->setFlags(QGraphicsItem::ItemIsMovable);
            pawn->setZValue(1);
            m_scene->addItem(pawn);
>>>>>>> d60e639... rewrite mapa.cpp to use QGraphicsView, remove unused .cpp and .h files, add pawns and buttons to resources
            m_pawns.push_back(pawn);
            amountOfPlayers++;
        }
    }
}
