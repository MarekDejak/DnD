#include "card.h"
#include "ui_card.h"
#include "mapwidget.h"
#include "lvl.h"

#include <QDebug>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QPalette>

Card::Card(QWidget* parent) : QDialog(parent), ui(new Ui::Card) {
    ui->setupUi(this);

    setStyleSheet("background-image: url(:/images/images/tlo1.jpg);");

    ui->closeButton->setStyleSheet(
        "font: 12pt "
        "Cooper Black"
        ";"
        "color: rgb(255, 255, 127);");
    ui->lvlUp->setStyleSheet(
        "font: 12pt "
        "Cooper Black"
        ";"
        "color: rgb(255, 255, 127);");

    connect(ui->closeButton, &QPushButton::clicked, this, &Card::onCloseClicked);
    connect(ui->lvlUp, &QPushButton::clicked, this, &Card::onLvlUpClicked);

    m_setNazwSkilli.insert("Atletyka");
    m_setNazwSkilli.insert("Akrobatyka");
    m_setNazwSkilli.insert("Blok");
    m_setNazwSkilli.insert("Brak munduru");
    m_setNazwSkilli.insert("Bron dwureczna");
    m_setNazwSkilli.insert("Celnosc");
    m_setNazwSkilli.insert("Ciezki mundur");
    m_setNazwSkilli.insert("Czytanie");
    m_setNazwSkilli.insert("Dlugie ostrza");
    m_setNazwSkilli.insert("Dzida");
    m_setNazwSkilli.insert("Handel");
    m_setNazwSkilli.insert("Iluzja");
    m_setNazwSkilli.insert("Kierowanie pojazdami");
    m_setNazwSkilli.insert("Kosmobiologia");
    m_setNazwSkilli.insert("Krotkie ostrza");
    m_setNazwSkilli.insert("Kutarate/chudo");
    m_setNazwSkilli.insert("Lekki mundur");
    m_setNazwSkilli.insert("Lepkie lapy");
    m_setNazwSkilli.insert("Medycyna");
    m_setNazwSkilli.insert("Obsluga ciezkiego sprzetu");
    m_setNazwSkilli.insert("Przyczajka");
    m_setNazwSkilli.insert("Przywracanie");
}

Card::~Card() {
    delete ui;
}

void Card::setName(QString imie) {
    m_name = imie;
}

Ptaszki Card::getPtaszki() {
    for (int i = 0; i < m_characters.size(); i++) {
        if (m_name == m_characters[i].getName()) {
            if (m_ptaszki.size() != 0) {
                if (ui->atletykaB->isChecked()) {
                    m_ptaszki[i]["Atletyka"] = true;
                }  // zapamietanie ptaszkow QCheckBox
                else {
                    m_ptaszki[i]["Atletyka"] = false;
                }
                if (ui->akrobatykaB->isChecked()) {
                    m_ptaszki[i]["Akrobatyka"] = true;
                } else {
                    m_ptaszki[i]["Akrobatyka"] = false;
                }
                if (ui->blokB->isChecked()) {
                    m_ptaszki[i]["Blok"] = true;
                } else {
                    m_ptaszki[i]["Blok"] = false;
                }
                if (ui->brakMunB->isChecked()) {
                    m_ptaszki[i]["Brak munduru"] = true;
                } else {
                    m_ptaszki[i]["Brak munduru"] = false;
                }
                if (ui->bronDwuB->isChecked()) {
                    m_ptaszki[i]["Bron dwureczna"] = true;
                } else {
                    m_ptaszki[i]["Bron dwureczna"] = false;
                }
                if (ui->celnoscB->isChecked()) {
                    m_ptaszki[i]["Celnosc"] = true;
                } else {
                    m_ptaszki[i]["Celnosc"] = false;
                }
                if (ui->ciezkiMunB->isChecked()) {
                    m_ptaszki[i]["Ciezki mundur"] = true;
                } else {
                    m_ptaszki[i]["Ciezki mundur"] = false;
                }
                if (ui->czytanieB->isChecked()) {
                    m_ptaszki[i]["Czytanie"] = true;
                } else {
                    m_ptaszki[i]["Czytanie"] = false;
                }
                if (ui->dlugieOstB->isChecked()) {
                    m_ptaszki[i]["Dlugie ostrza"] = true;
                } else {
                    m_ptaszki[i]["Dlugie ostrza"] = false;
                }
                if (ui->dzidaB->isChecked()) {
                    m_ptaszki[i]["Dzida"] = true;
                } else {
                    m_ptaszki[i]["Dzida"] = false;
                }
                if (ui->handelB->isChecked()) {
                    m_ptaszki[i]["Handel"] = true;
                } else {
                    m_ptaszki[i]["Handel"] = false;
                }
                if (ui->iluzjaB->isChecked()) {
                    m_ptaszki[i]["Iluzja"] = true;
                } else {
                    m_ptaszki[i]["Iluzja"] = false;
                }
                if (ui->kierowanieB->isChecked()) {
                    m_ptaszki[i]["Kierowanie pojazdami"] = true;
                } else {
                    m_ptaszki[i]["Kierowanie pojazdami"] = false;
                }
                if (ui->kosmobiologiaB->isChecked()) {
                    m_ptaszki[i]["Kosmobiologia"] = true;
                } else {
                    m_ptaszki[i]["Kosmobiologia"] = false;
                }
                if (ui->krotkieOstB->isChecked()) {
                    m_ptaszki[i]["Krotkie ostrza"] = true;
                } else {
                    m_ptaszki[i]["Krotkie ostrza"] = false;
                }
                if (ui->kutarateB->isChecked()) {
                    m_ptaszki[i]["Kutarate/chudo"] = true;
                } else {
                    m_ptaszki[i]["Kutarate/chudo"] = false;
                }
                if (ui->lekkiMunB->isChecked()) {
                    m_ptaszki[i]["Lekki mundur"] = true;
                } else {
                    m_ptaszki[i]["Lekki mundur"] = false;
                }
                if (ui->lepkieB->isChecked()) {
                    m_ptaszki[i]["Lepkie lapy"] = true;
                } else {
                    m_ptaszki[i]["Lepkie lapy"] = false;
                }
                if (ui->medycynaB->isChecked()) {
                    m_ptaszki[i]["Medycyna"] = true;
                } else {
                    m_ptaszki[i]["Medycyna"] = false;
                }
                if (ui->obslugaCSB->isChecked()) {
                    m_ptaszki[i]["Obsluga ciezkiego sprzetu"] = true;
                } else {
                    m_ptaszki[i]["Obsluga ciezkiego sprzetu"] = false;
                }
                if (ui->przyczajkaB->isChecked()) {
                    m_ptaszki[i]["Przyczajka"] = true;
                } else {
                    m_ptaszki[i]["Przyczajka"] = false;
                }
                if (ui->przywracanieB->isChecked()) {
                    m_ptaszki[i]["Przywracanie"] = true;
                } else {
                    m_ptaszki[i]["Przywracanie"] = false;
                }
                if (ui->rozpierduchaB->isChecked()) {
                    m_ptaszki[i]["Rozpierducha"] = true;
                } else {
                    m_ptaszki[i]["Rozpierducha"] = false;
                }
                if (ui->sumoB->isChecked()) {
                    m_ptaszki[i]["Sumo"] = true;
                } else {
                    m_ptaszki[i]["Sumo"] = false;
                }
                if (ui->transmutacjaB->isChecked()) {
                    m_ptaszki[i]["Transmutacja"] = true;
                } else {
                    m_ptaszki[i]["Transmutacja"] = false;
                }
                if (ui->zabobonyB->isChecked()) {
                    m_ptaszki[i]["Zabobony"] = true;
                } else {
                    m_ptaszki[i]["Zabobony"] = false;
                }
                if (ui->zlotyJezykB->isChecked()) {
                    m_ptaszki[i]["Zloty jezyk"] = true;
                } else {
                    m_ptaszki[i]["Zloty jezyk"] = false;
                }
            }
        }
    }

    return m_ptaszki;
}

void Card::setPtaszki(Ptaszki input) {
    m_ptaszki = input;

    m_setPtaszkow.insert(ui->atletykaB);
    m_setPtaszkow.insert(ui->akrobatykaB);
    m_setPtaszkow.insert(ui->blokB);
    m_setPtaszkow.insert(ui->bronDwuB);
    m_setPtaszkow.insert(ui->celnoscB);
    m_setPtaszkow.insert(ui->ciezkiMunB);
    m_setPtaszkow.insert(ui->czytanieB);
    m_setPtaszkow.insert(ui->dlugieOstB);
    m_setPtaszkow.insert(ui->dzidaB);
    m_setPtaszkow.insert(ui->handelB);
    m_setPtaszkow.insert(ui->iluzjaB);
    m_setPtaszkow.insert(ui->kierowanieB);
    m_setPtaszkow.insert(ui->kosmobiologiaB);
    m_setPtaszkow.insert(ui->krotkieOstB);
    m_setPtaszkow.insert(ui->kutarateB);
    m_setPtaszkow.insert(ui->lekkiMunB);
    m_setPtaszkow.insert(ui->lepkieB);
    m_setPtaszkow.insert(ui->medycynaB);
    m_setPtaszkow.insert(ui->obslugaCSB);
    m_setPtaszkow.insert(ui->przyczajkaB);
    m_setPtaszkow.insert(ui->przywracanieB);
    m_setPtaszkow.insert(ui->rozpierduchaB);
    m_setPtaszkow.insert(ui->sumoB);
    m_setPtaszkow.insert(ui->transmutacjaB);
    m_setPtaszkow.insert(ui->zabobonyB);
    m_setPtaszkow.insert(ui->zlotyJezykB);

    for (int i = 0; i < m_characters.size(); i++) {
        if (m_name == m_characters[i].getName()) {
            if (m_ptaszki[i]["Atletyka"] == true) {
                ui->atletykaB->setChecked(true);
            } else {
                ui->atletykaB->setChecked(false);
            }
            if (m_ptaszki[i]["Akrobatyka"] == true) {
                ui->akrobatykaB->setChecked(true);
            } else {
                ui->akrobatykaB->setChecked(false);
            }
            if (m_ptaszki[i]["Blok"] == true) {
                ui->blokB->setChecked(true);
            } else {
                ui->blokB->setChecked(false);
            }
            if (m_ptaszki[i]["Brak munduru"] == true) {
                ui->brakMunB->setChecked(true);
            } else {
                ui->brakMunB->setChecked(false);
            }
            if (m_ptaszki[i]["Bron dwureczna"] == true) {
                ui->bronDwuB->setChecked(true);
            } else {
                ui->bronDwuB->setChecked(false);
            }
            if (m_ptaszki[i]["Celnosc"] == true) {
                ui->celnoscB->setChecked(true);
            } else {
                ui->celnoscB->setChecked(false);
            }
            if (m_ptaszki[i]["Ciezki mundur"] == true) {
                ui->ciezkiMunB->setChecked(true);
            } else {
                ui->ciezkiMunB->setChecked(false);
            }
            if (m_ptaszki[i]["Czytanie"] == true) {
                ui->czytanieB->setChecked(true);
            } else {
                ui->czytanieB->setChecked(false);
            }
            if (m_ptaszki[i]["Dlugie ostrza"] == true) {
                ui->dlugieOstB->setChecked(true);
            } else {
                ui->dlugieOstB->setChecked(false);
            }
            if (m_ptaszki[i]["Dzida"] == true) {
                ui->dzidaB->setChecked(true);
            } else {
                ui->dzidaB->setChecked(false);
            }
            if (m_ptaszki[i]["Handel"] == true) {
                ui->handelB->setChecked(true);
            } else {
                ui->handelB->setChecked(false);
            }
            if (m_ptaszki[i]["Iluzja"] == true) {
                ui->iluzjaB->setChecked(true);
            } else {
                ui->iluzjaB->setChecked(false);
            }
            if (m_ptaszki[i]["Kierowanie pojazdami"] == true) {
                ui->kierowanieB->setChecked(true);
            } else {
                ui->kierowanieB->setChecked(false);
            }
            if (m_ptaszki[i]["Kosmobiologia"] == true) {
                ui->kosmobiologiaB->setChecked(true);
            } else {
                ui->kosmobiologiaB->setChecked(false);
            }
            if (m_ptaszki[i]["Krotkie ostrza"] == true) {
                ui->krotkieOstB->setChecked(true);
            } else {
                ui->krotkieOstB->setChecked(false);
            }
            if (m_ptaszki[i]["Kutarate/chudo"] == true) {
                ui->kutarateB->setChecked(true);
            } else {
                ui->kutarateB->setChecked(false);
            }
            if (m_ptaszki[i]["Lekki mundur"] == true) {
                ui->lekkiMunB->setChecked(true);
            } else {
                ui->lekkiMunB->setChecked(false);
            }
            if (m_ptaszki[i]["Lepkie lapy"] == true) {
                ui->lepkieB->setChecked(true);
            } else {
                ui->lepkieB->setChecked(false);
            }
            if (m_ptaszki[i]["Medycyna"] == true) {
                ui->medycynaB->setChecked(true);
            } else {
                ui->medycynaB->setChecked(false);
            }
            if (m_ptaszki[i]["Obsluga ciezkiego sprzetu"] == true) {
                ui->obslugaCSB->setChecked(true);
            } else {
                ui->obslugaCSB->setChecked(false);
            }
            if (m_ptaszki[i]["Przyczajka"] == true) {
                ui->przyczajkaB->setChecked(true);
            } else {
                ui->przyczajkaB->setChecked(false);
            }
            if (m_ptaszki[i]["Przywracanie"] == true) {
                ui->przywracanieB->setChecked(true);
            } else {
                ui->przywracanieB->setChecked(false);
            }
            if (m_ptaszki[i]["Rozpierducha"] == true) {
                ui->rozpierduchaB->setChecked(true);
            } else {
                ui->rozpierduchaB->setChecked(false);
            }
            if (m_ptaszki[i]["Sumo"] == true) {
                ui->sumoB->setChecked(true);
            } else {
                ui->sumoB->setChecked(false);
            }
            if (m_ptaszki[i]["Transmutacja"] == true) {
                ui->transmutacjaB->setChecked(true);
            } else {
                ui->transmutacjaB->setChecked(false);
            }
            if (m_ptaszki[i]["Zabobony"] == true) {
                ui->zabobonyB->setChecked(true);
            } else {
                ui->zabobonyB->setChecked(false);
            }
            if (m_ptaszki[i]["Zloty jezyk"] == true) {
                ui->zlotyJezykB->setChecked(true);
            } else {
                ui->zlotyJezykB->setChecked(false);
            }
        }
    }
}

void Card::setCharacterInfo(CharacterInfo info) {
    m_characters = info.characters;
    m_chosenCharacters = info.chosenCharacters;

    for (int i = 0; i < m_characters.size(); i++) {
        if (m_name == m_characters[i].getName()) {
            QPixmap pixmap1(m_characters[i].getPathPrzycisk());  // zdjecie
            ui->zdjecieL->setPixmap(pixmap1.scaledToHeight(200, Qt::SmoothTransformation));
            ui->zdjecieL->show();
            ui->zdjecieL->setAttribute(Qt::WA_DeleteOnClose);

            ui->imieL->setText(m_name);  // wyswietlenie statow
            ui->rasaL->setText("RASA: " + m_characters[i].getRasa());
            ui->zawodL->setText("ZAWOD: " + m_characters[i].getZawod());
            ui->wiekL->setText("WIEK: " + QString::number(m_characters[i].getWiek()));
            ui->silaL->setText("SILA: " + QString::number(m_characters[i].getSila()));
            ui->zwinnoscL->setText("ZWINNOSC: " + QString::number(m_characters[i].getZwinnosc()));
            ui->szybkoscL->setText("SZYBKOSC: " + QString::number(m_characters[i].getSzybkosc()));
            ui->wytrzymaloscL->setText("WYTRZYMALOSC: " + QString::number(m_characters[i].getWytrzymalosc()));
            ui->inteligencjaL->setText("INTELIGENCJA: " + QString::number(m_characters[i].getInteligencja()));
            ui->osobowoscL->setText("OSOBOWOSC: " + QString::number(m_characters[i].getOsobowosc()));
            ui->szczescieL->setText("SZCZESCIE: " + QString::number(m_characters[i].getSzczescie()));

            for (int j = 0; j < m_characters[i].getCzary().count(); j++) {
                QString czar = m_characters[i].getCzary()[j];
                ui->czaryL->addItem(czar);
            }

            ui->akrobatykaL->setText("Akrobatyka: : " + QString::number(m_characters[i].getAkrobatyka()));
            ui->atletykaL->setText("Atletyka: " + QString::number(m_characters[i].getAtletyka()));
            ui->blokL->setText("Blok: " + QString::number(m_characters[i].getBlok()));
            ui->brakMunL->setText("Brak munduru: " + QString::number(m_characters[i].getBrakMun()));
            ui->bronDwuL->setText("Bron dwurczna: " + QString::number(m_characters[i].getBronDwu()));
            ui->celnoscL->setText("Celnosc: " + QString::number(m_characters[i].getCelnosc()));
            ui->ciezkiMunL->setText("Ciezki mundur: " + QString::number(m_characters[i].getCiezkiMun()));
            ui->czytanieL->setText("Czytanie: " + QString::number(m_characters[i].getCzytanie()));
            ui->dlugieOstL->setText("Dlugie ostrza: " + QString::number(m_characters[i].getDlugieOst()));
            ui->dzidaL->setText("Dzida: " + QString::number(m_characters[i].getDzida()));
            ui->handelL->setText("Handel: " + QString::number(m_characters[i].getHandel()));
            ui->iluzjaL->setText("Iluzja: " + QString::number(m_characters[i].getIluzja()));
            ui->kierowanieL->setText("Kierowanie pojazdami: " + QString::number(m_characters[i].getKierowanie()));
            ui->kosmobiologiaL->setText("Kosmobiologia: " + QString::number(m_characters[i].getKosmobiologia()));
            ui->krotkieOstL->setText("Krotkie ostrza: " + QString::number(m_characters[i].getKrotkieOst()));
            ui->kutarateL->setText("Kutarate/chudo: " + QString::number(m_characters[i].getKuratare()));
            ui->lekkiMunL->setText("Lekki mundur: " + QString::number(m_characters[i].getLekkiMun()));
            ui->lepkieL->setText("Lepkie lapy: " + QString::number(m_characters[i].getLepkieLapy()));
            ui->medycynaL->setText("Medycyna: " + QString::number(m_characters[i].getMedycyna()));
            ui->obslugaCSL->setText("Obsluga ciezkiego sprzetu: " + QString::number(m_characters[i].getObslugaCS()));
            ui->przyczajkaL->setText("Przyczajka: " + QString::number(m_characters[i].getPrzyczajka()));
            ui->przywracanieL->setText("Przywracanie: " + QString::number(m_characters[i].getPrzywracanie()));
            ui->rozpierduchaL->setText("Rozpierducha: " + QString::number(m_characters[i].getRozpierducha()));
            ui->sumoL->setText("Sumo: " + QString::number(m_characters[i].getSumo()));
            ui->transmutacjaL->setText("Transmutacja: " + QString::number(m_characters[i].getTransmutacja()));
            ui->zabobonyL->setText("Zabobony: " + QString::number(m_characters[i].getZabobony()));
            ui->zlotyJezykL->setText("Zloty jezyk: " + QString::number(m_characters[i].getZlotyJezyk()));
        }
    }
}

void Card::onCloseClicked() {
    reject();
}

void Card::onLvlUpClicked() {
    getPtaszki();

    int ileSkilliWeszlo = 0;

    std::map<QString, bool> coWeszlo;

    for (int i = 0; i < m_characters.size(); i++) {
        if (m_name == m_characters[i].getName()) {
            coWeszlo = m_ptaszki[i];

            for (auto x : coWeszlo) {
                if (x.second == true)
                    ileSkilliWeszlo++;
            }
        }
    }
    if (ileSkilliWeszlo != 0) {
        auto* lvl = new Lvl(coWeszlo, m_characters, m_name, this);
        connect(lvl, &Lvl::saved, this, [=]() { reloadCardInfo(lvl->getCharacters()); });
        //         connect(lvl, &Lvl::saved, this, &Card::close); // zamkniecie karty gdy lvl sie zamknie

        lvl->setWindowTitle("Lvl up");
        lvl->setModal(true);
        lvl->show();
    } else {
        QMessageBox nothingLvled;
        nothingLvled.setStyleSheet(
            "background-image: url(:/images/images/tlo1.jpg);"
            "font: 12pt "
            "Cooper Black"
            ";"
            "color: rgb(255, 255, 127);");

        nothingLvled.setButtonText(1, "OK");
        nothingLvled.setText("Nic nie weszlo      ");

        nothingLvled.setModal(true);
        nothingLvled.exec();
    }
}

void Card::reloadCardInfo(QVector<Player> cardInfo) {
    for (int i = 0; i < m_characters.size(); i++) {
        if (m_name == m_characters[i].getName()) {
            m_characters = cardInfo;

            ui->akrobatykaL->setText("Akrobatyka: : " + QString::number(m_characters[i].getAkrobatyka()));
            ui->atletykaL->setText("Atletyka: " + QString::number(m_characters[i].getAtletyka()));
            ui->blokL->setText("Blok: " + QString::number(m_characters[i].getBlok()));
            ui->brakMunL->setText("Brak munduru: " + QString::number(m_characters[i].getBrakMun()));
            ui->bronDwuL->setText("Bron dwurczna: " + QString::number(m_characters[i].getBronDwu()));
            ui->celnoscL->setText("Celnosc: " + QString::number(m_characters[i].getCelnosc()));
            ui->ciezkiMunL->setText("Ciezki mundur: " + QString::number(m_characters[i].getCiezkiMun()));
            ui->czytanieL->setText("Czytanie: " + QString::number(m_characters[i].getCzytanie()));
            ui->dlugieOstL->setText("Dlugie ostrza: " + QString::number(m_characters[i].getDlugieOst()));
            ui->dzidaL->setText("Dzida: " + QString::number(m_characters[i].getDzida()));
            ui->handelL->setText("Handel: " + QString::number(m_characters[i].getHandel()));
            ui->iluzjaL->setText("Iluzja: " + QString::number(m_characters[i].getIluzja()));
            ui->kierowanieL->setText("Kierowanie pojazdami: " + QString::number(m_characters[i].getKierowanie()));
            ui->kosmobiologiaL->setText("Kosmobiologia: " + QString::number(m_characters[i].getKosmobiologia()));
            ui->krotkieOstL->setText("Krotkie ostrza: " + QString::number(m_characters[i].getKrotkieOst()));
            ui->kutarateL->setText("Kutarate/chudo: " + QString::number(m_characters[i].getKuratare()));
            ui->lekkiMunL->setText("Lekki mundur: " + QString::number(m_characters[i].getLekkiMun()));
            ui->lepkieL->setText("Lepkie lapy: " + QString::number(m_characters[i].getLepkieLapy()));
            ui->medycynaL->setText("Medycyna: " + QString::number(m_characters[i].getMedycyna()));
            ui->obslugaCSL->setText("Obsluga ciezkiego sprzetu: " + QString::number(m_characters[i].getObslugaCS()));
            ui->przyczajkaL->setText("Przyczajka: " + QString::number(m_characters[i].getPrzyczajka()));
            ui->przywracanieL->setText("Przywracanie: " + QString::number(m_characters[i].getPrzywracanie()));
            ui->rozpierduchaL->setText("Rozpierducha: " + QString::number(m_characters[i].getRozpierducha()));
            ui->sumoL->setText("Sumo: " + QString::number(m_characters[i].getSumo()));
            ui->transmutacjaL->setText("Transmutacja: " + QString::number(m_characters[i].getTransmutacja()));
            ui->zabobonyL->setText("Zabobony: " + QString::number(m_characters[i].getZabobony()));
            ui->zlotyJezykL->setText("Zloty jezyk: " + QString::number(m_characters[i].getZlotyJezyk()));

            for (auto* elem : m_setPtaszkow) {
                elem->setChecked(false);
            }
        }
    }
}
