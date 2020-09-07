#include "createcharacter.h"
#include "ui_createcharacter.h"
#include "selectcharacter.h"

#include <QPixmap>
#include <QFile>
//#include <sstream>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QMovie>

QString CreateCharacter::filepath{"D:/Programy/Programare/Bomba/BombaCharactersSave.txt"};

CreateCharacter::CreateCharacter(QVector<Player> characters, QWidget* parent)
    : QDialog(parent), ui(new Ui::CreateCharacter), m_characters(characters) {
    ui->setupUi(this);

    QMovie* mv = new QMovie(":/gifs/images/bombapluje.gif");  // gif
    mv->start();
    ui->labelObrazek->setMovie(mv);

    connect(ui->buttonSpellAdd, &QPushButton::clicked, this, &CreateCharacter::onSpellAddClicked);
    connect(ui->buttonSpellRemove, &QPushButton::clicked, this, &CreateCharacter::onSpellRemoveClicked);
    connect(ui->buttonZapisz, &QPushButton::clicked, this, &CreateCharacter::onSaveClicked);
    connect(ui->buttonAnuluj, &QPushButton::clicked, this, &CreateCharacter::onCloseClicked);
}

CreateCharacter::~CreateCharacter() {
    delete ui;
}

void CreateCharacter::onSaveClicked() {
    if (ui->imie->text().size() == 0) {
        QMessageBox::warning(this, "Uwaga", "Podaj imie");
    } else {
        Player player1;
        player1.setName(ui->imie->text());
        player1.setZawod(ui->zawodL->text());
        player1.setRasa(ui->rasaL->text());
        player1.setWiek(ui->wiekS->value());
        player1.setSila(ui->silaS->value());
        player1.setZwinnosc(ui->zwinnoscS->value());
        player1.setSilaWoli(ui->silaWoliS->value());
        player1.setSzybkosc(ui->szybkoscS->value());
        player1.setWytrzymalosc(ui->wytrzymaloscS->value());
        player1.setIngeligencja(ui->inteligencjaS->value());
        player1.setOsobowosc(ui->osobowoscS->value());
        player1.setSzczescie(ui->szczescieS->value());
        player1.setAkrobatyka(ui->akrobatykaS->value());
        player1.setAtletyka(ui->atletykaS->value());
        player1.setBlok(ui->blokS->value());
        player1.setBrakMun(ui->brakMunS->value());
        player1.setBronDwu(ui->bronDwuS->value());
        player1.setCelnosc(ui->celnoscS->value());
        player1.setCiezkiMun(ui->ciezkiMunS->value());
        player1.setCzytanie(ui->czytanieS->value());
        player1.setDlugieOst(ui->dlugieOstS->value());
        player1.setDzida(ui->dzidaS->value());
        player1.setHandel(ui->handelS->value());
        player1.setIluzja(ui->iluzjaS->value());
        player1.setKierowanie(ui->kierowanieS->value());
        player1.setKosmobiologia(ui->kosmobiologiaS->value());
        player1.setKrotkieOst(ui->krotkieOstS->value());
        player1.setKuratare(ui->kutarateS->value());
        player1.setLekkiMun(ui->lekkiMunS->value());
        player1.setLepkieLapy(ui->lepkieS->value());
        player1.setMedycyna(ui->medycynaS->value());
        player1.setObslugaCS(ui->obslugaCSS->value());
        player1.setPrzyczajka(ui->przyczajkaS->value());
        player1.setPrzywracanie(ui->przywracanieS->value());
        player1.setRozpierducha(ui->rozpierduchaS->value());
        player1.setSumo(ui->sumoS->value());
        player1.setTransmutacja(ui->transmutacjaS->value());
        player1.setZabobony(ui->zabobonyS->value());
        player1.setZlotyJezyk(ui->zlotyJezykS->value());

        QVector<QString> spells;
        for (int i = 0; i < ui->spellView->count(); i++) {
            spells.push_back(ui->spellView->item(i)->text());
        }
        player1.setCzary(spells);

        m_characters.push_back(player1);

        QFile file(CreateCharacter::filepath);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Could not save file");
            return;
        }
        QTextStream out(&file);
        QString text = "";
        for (auto x : m_characters) {
            out << x.getName() + "\n";
            out << x.getZawod() + "\n";
            out << x.getRasa() + "\n";

            QString czaryZapis;
            for (auto spell : x.getCzary()) {
                czaryZapis += spell + "$";
            }
            out << czaryZapis.toUpper() + "\n";

            out << QString::number(x.getWiek()) + "\n";
            out << QString::number(x.getSila()) + "\n";
            out << QString::number(x.getZwinnosc()) + "\n";
            out << QString::number(x.getSilaWoli()) + "\n";
            out << QString::number(x.getSzybkosc()) + "\n";
            out << QString::number(x.getWytrzymalosc()) + "\n";
            out << QString::number(x.getInteligencja()) + "\n";
            out << QString::number(x.getOsobowosc()) + "\n";
            out << QString::number(x.getSzczescie()) + "\n";
            out << QString::number(x.getHp()) + "\n";
            out << QString::number(x.getMana()) + "\n";
            out << QString::number(x.getAkrobatyka()) + "\n";
            out << QString::number(x.getAtletyka()) + "\n";
            out << QString::number(x.getBlok()) + "\n";
            out << QString::number(x.getBrakMun()) + "\n";
            out << QString::number(x.getBronDwu()) + "\n";
            out << QString::number(x.getCelnosc()) + "\n";
            out << QString::number(x.getCiezkiMun()) + "\n";
            out << QString::number(x.getCzytanie()) + "\n";
            out << QString::number(x.getDlugieOst()) + "\n";
            out << QString::number(x.getDzida()) + "\n";
            out << QString::number(x.getHandel()) + "\n";
            out << QString::number(x.getIluzja()) + "\n";
            out << QString::number(x.getKierowanie()) + "\n";
            out << QString::number(x.getKosmobiologia()) + "\n";
            out << QString::number(x.getKrotkieOst()) + "\n";
            out << QString::number(x.getKuratare()) + "\n";
            out << QString::number(x.getLekkiMun()) + "\n";
            out << QString::number(x.getLepkieLapy()) + "\n";
            out << QString::number(x.getMedycyna()) + "\n";
            out << QString::number(x.getObslugaCS()) + "\n";
            out << QString::number(x.getPrzyczajka()) + "\n";
            out << QString::number(x.getPrzywracanie()) + "\n";
            out << QString::number(x.getRozpierducha()) + "\n";
            out << QString::number(x.getSumo()) + "\n";
            out << QString::number(x.getTransmutacja()) + "\n";
            out << QString::number(x.getZabobony()) + "\n";
            out << QString::number(x.getZlotyJezyk()) + "\n";
            out << x.getPathPionek() + "\n";
            out << x.getPathPrzycisk() + "\n";
        }
        file.close();
        QMessageBox::information(this, "Sukces", "Postac zapisana\nZrestartuj program");

        close();
    }
}

void CreateCharacter::onSpellAddClicked() {
    if (ui->spellEnter->text().size() > 0) {
        QString spell = ui->spellEnter->text();
        ui->spellView->addItem(spell);
        ui->spellEnter->setText("");
    }
}
void CreateCharacter::onSpellRemoveClicked() {
    ui->spellView->takeItem(ui->spellView->currentRow());
}

void CreateCharacter::onCloseClicked() {
    hide();
}
