#pragma once

#include "mapa.h"
#include "card.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QMap>
#include <unordered_map>


class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr);
    void setCharacterInfo(CharacterInfo info);
    void setPtaszki(Ptaszki input);


private:

private:

    std::map<QString, QPushButton*> buttonMap;
    QVBoxLayout *verticalLayout;
    Mapa* m_mapa;
    CharacterInfo m_info;
    Ptaszki m_ptaszki;
    QVector<QString> m_openCards;

private slots:
    void onPrzyciskClicked(QString imie);


};

