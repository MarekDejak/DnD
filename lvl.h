#pragma once

#include <QDialog>
#include <QString>
#include <map>
#include <QSpinBox>
#include "player.h"

namespace Ui {
class Lvl;
}

class Lvl : public QDialog
{
    Q_OBJECT

public:
    explicit Lvl(std::map<QString, bool> coWeszlo, QVector<Player> characters, QString imie, QWidget *parent = nullptr);
    ~Lvl();
    QVector<Player> getCharacters(){return m_characters;}


signals:
    emit void saved();

private:
    Ui::Lvl *ui;
    std::map<QString, bool> m_skille;
    QVector<Player> m_characters;
    QVector<std::pair<QString, QSpinBox*>> m_skilleDodane;
    QString m_name;

    void onCloseClicked();
    void onZapiszClicked();


};


