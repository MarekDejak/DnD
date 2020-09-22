#pragma once

#include "CharacterInfo.h"
#include "charactermodel.h"
#include "mapa.h"
#include "card.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QMap>
#include <unordered_map>
#include <QPixmap>

class MapWidget : public QWidget {
    Q_OBJECT

public:
    explicit MapWidget(CharacterModel* model, QWidget* parent = nullptr);

signals:
    void stopPressed();

private:
    void onDataChanged();
    void waypointClicked();
    int calculateButtonImageHeight();

    QVector<QPushButton*> m_buttons;
    CharacterModel* m_model;
    QVBoxLayout* m_verticalLayout;
    Mapa* m_mapa;
    CharacterInfo m_info;
    QVector<QString> m_openCards;
    QPixmap* m_pawnImage;

private slots:
    void onPrzyciskClicked(const QModelIndex& imie);
};
