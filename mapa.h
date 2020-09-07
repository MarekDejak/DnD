#pragma once

#include "CharacterInfo.h"
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Mapa : public QFrame {
public:
    explicit Mapa(QWidget* parent = nullptr);
    void makePionki();
    void setCharacterInfo(CharacterInfo info);

signals:
    void clicked();  //

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    CharacterInfo m_info;
};
