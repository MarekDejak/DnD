#pragma once

#include <QDialog>

#include "charactermodel.h"
#include "skillsproxymodel.h"

class EditAbilitiesDialog : public QDialog {
public:
    EditAbilitiesDialog(CharacterModel* model, QWidget* parent);

private slots:
    void removeAbility();
    void addAbility();

private:
    void setupTitleAndGeometry();
    void populateLayout();
    void setupModel(CharacterModel* model);

    SkillsProxyModel* m_skillsModel;
    CharacterModel* m_model;
};
