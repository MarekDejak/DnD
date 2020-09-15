#pragma once

#include "character.h"

#include <QDialog>
#include <QFormLayout>

class Card : public QDialog {
public:
    Card(Character* character, QWidget* parent);

private:
    void generateFixedLayout(QFormLayout* layout);
    void populateLayout();
    void manageOpenDialogs();
    void setupTitleAndGeometry();

    bool m_editable;
    Character* m_character;
    static QVector<Character*> m_openCharacters;
};
