#include <QtWidgets>
#include <QApplication>
#include <QVector>
#include <QDebug>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QImage>
#include <QGraphicsItemGroup>
#include <QPalette>

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

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}
void Mapa::createPin(QColor color, QString text) {
    auto pixmap = new QPixmap(":/images/images/map_pointer.png");
    QGraphicsPixmapItem* znacznik = m_scene->addPixmap(pixmap->scaledToHeight(30, Qt::SmoothTransformation));
    QFont font("Cooper Black", 15, QFont::Thin);
    font.setCapitalization(QFont::Capitalize);
    auto* tekst = new QGraphicsTextItem(text);
    tekst->setFont(font);
    tekst->setDefaultTextColor(color);

    auto* grupa = new QGraphicsItemGroup;
    grupa->addToGroup(znacznik);
    grupa->addToGroup(tekst);
    tekst->moveBy(20, -10);

    grupa->setFlags(QGraphicsItem::ItemIsMovable);
    grupa->setZValue(2);
    grupa->moveBy(10, 10);
    m_scene->addItem(grupa);
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
            m_pawns.push_back(pawn);
            amountOfPlayers++;
        }
    }
}
