#pragma once

#include "Charactermodel.h"
#include <QFrame>
#include <QVector>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Mapa : public QFrame {
public:
    explicit Mapa(QWidget* parent = nullptr);
    void setCharacterModel(CharacterModel* model);
    int getBackgroundHeight() { return backgroundImageHeight; }

signals:
    void clicked();

private:
    void onDataChanged();
    QVector<QLabel*> m_pawns;
    int backgroundImageHeight;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    CharacterModel* m_model;
};
