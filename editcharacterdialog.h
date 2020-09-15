#pragma once

#include "character.h"

#include <QDialog>
#include <QFormLayout>

class EditCharacterDialog : public QDialog {
public:
    EditCharacterDialog(Character* character, QWidget* parent);

private:
    void generateFixedLayout(QFormLayout* layout);
    void populateLayout();
    void manageOpenDialogs();
    void setupTitleAndGeometry();

    Character* m_character;
    static QVector<Character*> m_openCharacters;
};
