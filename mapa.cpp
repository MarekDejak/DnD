#include <QtWidgets>
#include <QApplication>
#include <QDebug>

#include "mapa.h"
#include "selectcharacter.h"

Mapa::Mapa(QWidget* parent) : QFrame(parent) {
    setStyleSheet("background-image: url(:/images/images/background.png);");

    QPixmap background(":/images/images/background.png");  // wczytane tylko do ustalenia wymiarow okna
    setMinimumSize(background.width(), background.height());
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
}

void Mapa::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Mapa::dragMoveEvent(QDragMoveEvent* event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Mapa::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        QString text;
        dataStream >> pixmap >> offset;

        QLabel* newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void Mapa::mousePressEvent(QMouseEvent* event) {
    QLabel* child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *(child->pixmap());

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData* mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

void Mapa::setCharacterModel(CharacterModel* model) {
    m_model = model;
    connect(m_model, &QAbstractItemModel::dataChanged, this, &Mapa::onDataChanged);

    createPawns();
}
void Mapa::onDataChanged() {
    for (auto* pawn : m_pawns) {
        //            m_verticalLayout->removeWidget(button);
        pawn->hide();
        delete pawn;
    }
    m_pawns.clear();

    int numOfPlayers = 0;
    for (int i = 0; i < m_model->rowCount(); i++) {
        if (m_model->data(m_model->index(i, 0), CharacterModel::UsedRole).toBool()) {
            QPixmap pixmap = m_model->data(m_model->index(i, 0), CharacterModel::PawnImageRole).value<QPixmap>();
            auto* pawn = new QLabel(this);
            pawn->setPixmap(pixmap.scaledToHeight(50, Qt::SmoothTransformation));
            pawn->move(10, 10 + 55 * numOfPlayers);
            pawn->show();
            //            pawn->setAttribute(Qt::WA_DeleteOnClose);
            m_pawns.push_back(pawn);
            numOfPlayers++;
            qDebug() << "oj tak, +1 byczq";
        }
    }
}

void Mapa::createPawns() {
    qDebug() << "createPawns()";
}
