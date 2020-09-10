#pragma once

#include "character.h"

#include <QDialog>
#include <QFormLayout>

class EditCharacterDialog : public QDialog {
public:
    EditCharacterDialog(bool editable, Character* character, QWidget* parent);

private:
    template<class Editor>
    void generateFixedLayout(QFormLayout* layout);
    void populateLayout();
    void manageOpenDialogs();
    void setupTitleAndGeometry();

    bool m_editable;
    Character* m_character;
    static QVector<Character*> m_openCharacters;
};
