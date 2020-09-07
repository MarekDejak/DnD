#pragma once

#include <QString>
#include <QVector>
#include <unordered_set>

class Player {
public:
    Player();

    bool isPicked = false;

    QString getName() { return name; }
    QString getZawod() { return zawod; }
    QString getRasa() { return rasa; }
    QVector<QString> getCzary() { return czary; }

    int getWiek() { return wiek; }
    int getSila() { return sila; }
    int getZwinnosc() { return zwinnosc; }
    int getSilaWoli() { return silaWoli; }
    int getSzybkosc() { return szybkosc; }
    int getWytrzymalosc() { return wytrzymalosc; }
    int getInteligencja() { return inteligencja; }
    int getOsobowosc() { return osobowosc; }
    int getSzczescie() { return szczescie; }
    int getHp() { return hp; }
    int getMana() { return mana; }
    int getAkrobatyka() { return akrobatyka; }
    int getAtletyka() { return atletyka; }
    int getBlok() { return blok; }
    int getBrakMun() { return brakMun; }
    int getBronDwu() { return bronDwu; }
    int getCelnosc() { return celnosc; }
    int getCiezkiMun() { return ciezkiMun; }
    int getCzytanie() { return czytanie; }
    int getDlugieOst() { return dlugieOst; }
    int getDzida() { return dzida; }
    int getHandel() { return handel; }
    int getIluzja() { return iluzja; }
    int getKierowanie() { return kierowanie; }
    int getKosmobiologia() { return kosmobiologia; }
    int getKrotkieOst() { return krotkieOst; }
    int getKuratare() { return kuratare; }
    int getLekkiMun() { return lekkiMun; }
    int getLepkieLapy() { return lepkieLapy; }
    int getMedycyna() { return medycyna; }
    int getObslugaCS() { return obslugaCS; }
    int getPrzyczajka() { return przyczajka; }
    int getPrzywracanie() { return przywracanie; }
    int getRozpierducha() { return rozpierducha; }
    int getSumo() { return sumo; }
    int getTransmutacja() { return transmutacja; }
    int getZabobony() { return zabobony; }
    int getZlotyJezyk() { return zlotyJezyk; }
    QString getPathPionek() { return pathPionek; }
    QString getPathPrzycisk() { return pathPrzycisk; }

    void setName(QString str) { name = str; }
    void setZawod(QString str) { zawod = str; }
    void setRasa(QString str) { rasa = str; }
    void setCzary(QVector<QString> vec) { czary = vec; }
    void setWiek(int a) { wiek = a; }
    void setSila(int a) { sila = a; }
    void setZwinnosc(int a) { zwinnosc = a; }
    void setSilaWoli(int a) { silaWoli = a; }
    void setSzybkosc(int a) { szybkosc = a; }
    void setWytrzymalosc(int a) { wytrzymalosc = a; }
    void setIngeligencja(int a) { inteligencja = a; }
    void setOsobowosc(int a) { osobowosc = a; }
    void setSzczescie(int a) { szczescie = a; }
    void setHp(int a) { hp = a; }
    void setMana(int a) { mana = a; }
    void setAkrobatyka(int a) { akrobatyka = a; }
    void setAtletyka(int a) { atletyka = a; }
    void setBlok(int a) { blok = a; }
    void setBrakMun(int a) { brakMun = a; }
    void setBronDwu(int a) { bronDwu = a; }
    void setCelnosc(int a) { celnosc = a; }
    void setCiezkiMun(int a) { ciezkiMun = a; }
    void setCzytanie(int a) { czytanie = a; }
    void setDlugieOst(int a) { dlugieOst = a; }
    void setDzida(int a) { dzida = a; }
    void setHandel(int a) { handel = a; }
    void setIluzja(int a) { iluzja = a; }
    void setKierowanie(int a) { kierowanie = a; }
    void setKosmobiologia(int a) { kosmobiologia = a; }
    void setKrotkieOst(int a) { krotkieOst = a; }
    void setKuratare(int a) { kuratare = a; }
    void setLekkiMun(int a) { lekkiMun = a; }
    void setLepkieLapy(int a) { lepkieLapy = a; }
    void setMedycyna(int a) { medycyna = a; }
    void setObslugaCS(int a) { obslugaCS = a; }
    void setPrzyczajka(int a) { przyczajka = a; }
    void setPrzywracanie(int a) { przywracanie = a; }
    void setRozpierducha(int a) { rozpierducha = a; }
    void setSumo(int a) { sumo = a; }
    void setTransmutacja(int a) { transmutacja = a; }
    void setZabobony(int a) { zabobony = a; }
    void setZlotyJezyk(int a) { zlotyJezyk = a; }
    void setPathPionek(QString str) { pathPionek = str; }
    void setPathPrzycisk(QString str) { pathPrzycisk = str; }

private:
    QString name{"default"};
    QString zawod{"default"};
    QString rasa{"default"};
    QVector<QString> czary;
    int wiek{0};
    int sila{0};
    int zwinnosc{0};
    int silaWoli{0};
    int szybkosc{0};
    int wytrzymalosc{0};
    int inteligencja{0};
    int osobowosc{0};
    int szczescie{0};
    int hp{0};
    int mana{0};
    int akrobatyka{10};
    int atletyka{10};
    int blok{10};
    int brakMun{10};
    int bronDwu{10};
    int celnosc{10};
    int ciezkiMun{10};
    int czytanie{10};
    int dlugieOst{10};
    int dzida{10};
    int handel{10};
    int iluzja{10};
    int kierowanie{10};
    int kosmobiologia{10};
    int krotkieOst{10};
    int kuratare{10};
    int lekkiMun{10};
    int lepkieLapy{10};
    int medycyna{10};
    int obslugaCS{10};
    int przyczajka{10};
    int przywracanie{10};
    int rozpierducha{10};
    int sumo{10};
    int transmutacja{10};
    int zabobony{10};
    int zlotyJezyk{10};
    QString pathPionek{"brak grafiki pionka"};
    QString pathPrzycisk{"brak grafiki przycisku"};
};
