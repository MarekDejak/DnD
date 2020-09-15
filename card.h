#pragma once

#include "character.h"

#include <QDialog>
#include <QFormLayout>
#include <QPixmap>

class Card : public QDialog {
public:
    Card(QPixmap* pixmap, Character* character, QWidget* parent);

private:
    void generateFixedLayout();
    void populateLayout();
    void manageOpenDialogs();
    void setupTitleAndGeometry();

    Character* m_character;
    QPixmap* m_characterPortrait;
    static QVector<Character*> m_openCharacters;
};
