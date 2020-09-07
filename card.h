#pragma once
#include "CharacterInfo.h"
#include "Ptaszki.h"

#include <QDialog>
#include <QVector>
#include <QCheckBox>
#include <unordered_set>
#include <set>


namespace Ui {
class Card;
}

class Card : public QDialog
{
    Q_OBJECT

public:
    explicit Card(QWidget *parent = nullptr);
    void setCharacterInfo(CharacterInfo info);
    void setName(QString imie);
    void setPtaszki(Ptaszki ptaszki);

    Ptaszki getPtaszki();//bylo na koncu const

    ~Card();

private:
    Ui::Card *ui;
    QVector<Player> m_characters;
    QVector<QString> m_chosenCharacters;
    QString m_name;
    Ptaszki m_ptaszki;

    std::set<QCheckBox*> m_setPtaszkow;
    std::set<QString> m_setNazwSkilli;

    void reloadCardInfo(QVector<Player> cardInfo);




    void onCloseClicked();
    void onLvlUpClicked();
};

