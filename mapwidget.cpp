#include "mapwidget.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QVector>

MapWidget::MapWidget(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    verticalLayout = new QVBoxLayout(this);

    QPushButton* buttonPoint = new QPushButton(this);  //
    buttonPoint->setText("Znacznik");
    buttonPoint->setStyleSheet(
        "color: rgb(0, 0, 0);font: 75 9pt "
        "Berlin Sans FB"
        "; background-color: rgb(150, 150, 150);");

    verticalLayout->addWidget(buttonPoint);

    m_mapa = new Mapa(this);
    horizontalLayout->addWidget(m_mapa);  // layout glowny (poziomy)
    horizontalLayout->addLayout(verticalLayout);
    setLayout(horizontalLayout);

    this->setWindowTitle("Mapa");
}

void MapWidget::onPrzyciskClicked(QString imie) {
    if (!m_openCards.contains(imie)) {  // otwiera sie tylko jesli nie jest juz otwarte
        auto card = new Card(this);

        std::map<QString, bool> ptak;
        while (m_ptaszki.size() < m_info.characters.size()) {  // zeby wektor nie byl pusty
            m_ptaszki.push_back(ptak);
        }
        connect(card, &QDialog::finished, this, [=]() {
            m_openCards.removeOne(imie);
            setPtaszki(card->getPtaszki());
        });

        card->setWindowTitle(imie);
        card->setName(imie);
        card->setCharacterInfo(m_info);
        card->setPtaszki(m_ptaszki);
        card->show();
        m_openCards.push_back(imie);
    }
}

void MapWidget::setPtaszki(Ptaszki input) {
    m_ptaszki = input;
}

void MapWidget::setCharacterInfo(CharacterInfo info) {
    m_mapa->setCharacterInfo(info);
    m_info = info;
    for (int i = 0; i < info.amtOfPlayers; i++) {
        QString imie = info.chosenCharacters[i];

        for (int j = 0; j < info.amtOfCharacters; j++) {
            if (imie == info.characters[j].getName()) {  ////////////////////////////////// tworzenie przycisku postaci
                QPushButton* button = new QPushButton(this);  //
                QPixmap pixmap(info.characters[j].getPathPrzycisk());
                QPixmap pixmapScaled = pixmap.scaledToHeight(70, Qt::SmoothTransformation);
                QIcon ButtonIcon(pixmapScaled);                   //
                button->setIcon(ButtonIcon);                      //
                button->setIconSize(pixmapScaled.rect().size());  //
                button->setStyleSheet("border: 1px solid black; border-radius: 25px;");
                verticalLayout->addWidget(button);

                buttonMap[imie] = button;
                connect(button, &QPushButton::clicked, this, [=]() { onPrzyciskClicked(imie); });  // lambda
            }
        }
    }
}
