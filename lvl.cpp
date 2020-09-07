#include "lvl.h"
#include "ui_lvl.h"
#include "createcharacter.h"
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QFile>

#include <QLabel>

Lvl::Lvl(std::map<QString, bool> coWeszlo, QVector<Player> characters, QString imie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lvl), m_skille(coWeszlo), m_characters(characters), m_name(imie)
{
    ui->setupUi(this);

    setStyleSheet("background-image: url(:/images/images/tlo1.jpg);");
    resize(100, 100);
    ui->zapiszButton->setStyleSheet("font: 12pt ""Cooper Black"";"
                                    "color: rgb(255, 255, 127);");
    ui->closeButton->setStyleSheet("font: 12pt ""Cooper Black"";"
                                    "color: rgb(255, 255, 127);");
    QVBoxLayout *verticalLayout = new QVBoxLayout;



    for(auto x:m_skille){
        if(x.second == true){

            QHBoxLayout *horizontalLayout = new QHBoxLayout;
            QLabel *label = new QLabel;
            label->setText(x.first);
            label->setStyleSheet("font: 12pt ""Cooper Black""; color: rgb(255, 255, 127);");

            QSpinBox *spinbox = new QSpinBox;
//            QSpinBox spinbox;
            spinbox->setStyleSheet("font: 12pt ""Cooper Black""; color: rgb(255, 255, 127); background-color: rgb(0, 0, 0);");
            spinbox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

            horizontalLayout->addWidget(label);
            horizontalLayout->addWidget(spinbox);

            std::pair<QString, QSpinBox*> para;
            para.first = x.first;
            para.second = spinbox;
            m_skilleDodane.push_back(para);


            verticalLayout->addLayout(horizontalLayout);
        }
    }
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(ui->zapiszButton);
    horizontalLayout->addWidget(ui->closeButton);
    verticalLayout->addLayout(horizontalLayout);

    setLayout(verticalLayout);

    connect(ui->closeButton, &QPushButton::clicked, this, &Lvl::onCloseClicked);
    connect(ui->zapiszButton, &QPushButton::clicked, this, &Lvl::onZapiszClicked);


}

Lvl::~Lvl()
{
    delete ui;
}
void Lvl::onCloseClicked(){

    close();
}
void Lvl::onZapiszClicked(){

    for(int i=0; i<m_characters.size(); i++){
        if(m_name == m_characters[i].getName()){

            for(auto x : m_skilleDodane){
                if(x.first == "Akrobatyka"){m_characters[i].setAkrobatyka(m_characters[i].getAkrobatyka()+x.second->value());}
                if(x.first == "Atletyka"){m_characters[i].setAtletyka(m_characters[i].getAtletyka()+x.second->value());}
                if(x.first == "Blok"){m_characters[i].setBlok(m_characters[i].getBlok()+x.second->value());}
                if(x.first == "Brak munduru"){m_characters[i].setBrakMun(m_characters[i].getBrakMun()+x.second->value());}
                if(x.first == "Bron dwureczna"){m_characters[i].setBronDwu(m_characters[i].getBronDwu()+x.second->value());}
                if(x.first == "Celnosc"){m_characters[i].setCelnosc(m_characters[i].getCelnosc()+x.second->value());}
                if(x.first == "Ciezki mundur"){m_characters[i].setCiezkiMun(m_characters[i].getCiezkiMun()+x.second->value());}
                if(x.first == "Czytanie"){m_characters[i].setCzytanie(m_characters[i].getCzytanie()+x.second->value());}
                if(x.first == "Dlugie ostrza"){m_characters[i].setDlugieOst(m_characters[i].getDlugieOst()+x.second->value());}
                if(x.first == "Dzida"){m_characters[i].setDzida(m_characters[i].getDzida()+x.second->value());}
                if(x.first == "Handel"){m_characters[i].setHandel(m_characters[i].getHandel()+x.second->value());}
                if(x.first == "Iluzja"){m_characters[i].setIluzja(m_characters[i].getIluzja()+x.second->value());}
                if(x.first == "Kierowanie pojazdami"){m_characters[i].setKierowanie(m_characters[i].getKierowanie()+x.second->value());}
                if(x.first == "Kosmobiologia"){m_characters[i].setKosmobiologia(m_characters[i].getKosmobiologia()+x.second->value());}
                if(x.first == "Krotkie ostrza"){m_characters[i].setKrotkieOst(m_characters[i].getKrotkieOst()+x.second->value());}
                if(x.first == "Kutarate/chudo"){m_characters[i].setKuratare(m_characters[i].getKuratare()+x.second->value());}
                if(x.first == "Lekki mundur"){m_characters[i].setLekkiMun(m_characters[i].getLekkiMun()+x.second->value());}
                if(x.first == "Lepkie lapy"){m_characters[i].setLepkieLapy(m_characters[i].getLepkieLapy()+x.second->value());}
                if(x.first == "Medycyna"){m_characters[i].setMedycyna(m_characters[i].getMedycyna()+x.second->value());}
                if(x.first == "Obsluga ciezkiego sprzetu"){m_characters[i].setObslugaCS(m_characters[i].getObslugaCS()+x.second->value());}
                if(x.first == "Przyczajka"){m_characters[i].setPrzyczajka(m_characters[i].getPrzyczajka()+x.second->value());}
                if(x.first == "Przywracanie"){m_characters[i].setPrzywracanie(m_characters[i].getPrzywracanie()+x.second->value());}
                if(x.first == "Rozpierducha"){m_characters[i].setRozpierducha(m_characters[i].getRozpierducha()+x.second->value());}
                if(x.first == "Sumo"){m_characters[i].setSumo(m_characters[i].getSumo()+x.second->value());}
                if(x.first == "Transmutacja"){m_characters[i].setTransmutacja(m_characters[i].getTransmutacja()+x.second->value());}
                if(x.first == "Zabobony"){m_characters[i].setZabobony(m_characters[i].getZabobony()+x.second->value());}
                if(x.first == "Zloty jezyk"){m_characters[i].setZlotyJezyk(m_characters[i].getZlotyJezyk()+x.second->value());}
            }
        }
    }



    QFile file(CreateCharacter::filepath);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Could not save file");
        return;
    }
    QTextStream out(&file);
    QString text = "";
    for(auto x: m_characters){

        out << x.getName()+"\n";
        out << x.getZawod()+"\n";
        out << x.getRasa()+"\n";

        QString czaryZapis;
        for(auto spell:x.getCzary()){
            czaryZapis += spell + "$";
        }
        out << czaryZapis.toUpper()+"\n";

        out << QString::number(x.getWiek())+"\n";
        out << QString::number(x.getSila())+"\n";
        out << QString::number(x.getZwinnosc())+"\n";
        out << QString::number(x.getSilaWoli())+"\n";
        out << QString::number(x.getSzybkosc())+"\n";
        out << QString::number(x.getWytrzymalosc())+"\n";
        out << QString::number(x.getInteligencja())+"\n";
        out << QString::number(x.getOsobowosc())+"\n";
        out << QString::number(x.getSzczescie())+"\n";
        out << QString::number(x.getHp())+"\n";
        out << QString::number(x.getMana())+"\n";
        out << QString::number(x.getAkrobatyka())+"\n";
        out << QString::number(x.getAtletyka())+"\n";
        out << QString::number(x.getBlok())+"\n";
        out << QString::number(x.getBrakMun())+"\n";
        out << QString::number(x.getBronDwu())+"\n";
        out << QString::number(x.getCelnosc())+"\n";
        out << QString::number(x.getCiezkiMun())+"\n";
        out << QString::number(x.getCzytanie())+"\n";
        out << QString::number(x.getDlugieOst())+"\n";
        out << QString::number(x.getDzida())+"\n";
        out << QString::number(x.getHandel())+"\n";
        out << QString::number(x.getIluzja())+"\n";
        out << QString::number(x.getKierowanie())+"\n";
        out << QString::number(x.getKosmobiologia())+"\n";
        out << QString::number(x.getKrotkieOst())+"\n";
        out << QString::number(x.getKuratare())+"\n";
        out << QString::number(x.getLekkiMun())+"\n";
        out << QString::number(x.getLepkieLapy())+"\n";
        out << QString::number(x.getMedycyna())+"\n";
        out << QString::number(x.getObslugaCS())+"\n";
        out << QString::number(x.getPrzyczajka())+"\n";
        out << QString::number(x.getPrzywracanie())+"\n";
        out << QString::number(x.getRozpierducha())+"\n";
        out << QString::number(x.getSumo())+"\n";
        out << QString::number(x.getTransmutacja())+"\n";
        out << QString::number(x.getZabobony())+"\n";
        out << QString::number(x.getZlotyJezyk())+"\n";
        out << x.getPathPionek()+"\n";
        out << x.getPathPrzycisk()+"\n";
    }
    file.close();
    QMessageBox msgSaved;
    msgSaved.setStyleSheet("background-image: url(:/images/images/tlo1.jpg);"
                           "font: 12pt ""Cooper Black"";"
                           "color: rgb(255, 255, 127);");

    msgSaved.setButtonText(1, "OK");
    msgSaved.setText("Podniesiono poziom atrybutow");

    msgSaved.setModal(true);
    msgSaved.exec();
    emit saved();


    close();
}


