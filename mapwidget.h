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

class MapWidget : public QWidget {
    Q_OBJECT

public:
    explicit MapWidget(CharacterModel* model, QWidget* parent = nullptr);
    void setCharacterInfo(CharacterInfo info);
    void setPtaszki(Ptaszki input);

signals:
    void stopPressed();

private:
    void onDataChanged();

    QVector<QPushButton*> m_buttons;
    CharacterModel* m_model;
    QVBoxLayout* m_verticalLayout;
    Mapa* m_mapa;
    CharacterInfo m_info;
    Ptaszki m_ptaszki;
    QVector<QString> m_openCards;

private slots:
    void onPrzyciskClicked(QString imie);
};
