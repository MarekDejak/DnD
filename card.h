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
    void manageOpenDialogs();
    void setupTitleAndGeometry();
    void populateSkillLayouts(QGridLayout* gridLayout, QFormLayout* attributesLayout);

    Character* m_character;
    QPixmap m_characterPortrait;
    static QVector<Character*> m_openCharacters;
};
