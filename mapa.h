#pragma once

#include "Charactermodel.h"
#include <QFrame>
#include <QVector>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Mapa : public QFrame {
public:
    explicit Mapa(CharacterModel* model, QWidget* parent = nullptr);
    int getBackgroundHeight() { return m_backgroundImageHeight; }

signals:
    void clicked();

private:
    void onDataChanged();
    int m_backgroundImageHeight;
    QGraphicsScene* m_scene;
    QVector<QGraphicsPixmapItem*> m_pawns;

protected:
    CharacterModel* m_model;
};
