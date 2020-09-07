#pragma once

#include <QDialog>
#include "player.h"

namespace Ui {
class CreateCharacter;
}

class CreateCharacter : public QDialog {
    Q_OBJECT

public:
    static QString filepath;
    explicit CreateCharacter(QVector<Player> characters, QWidget* parent = nullptr);
    ~CreateCharacter();

private:
    Ui::CreateCharacter* ui;
    QVector<Player> m_characters;

    void onSpellAddClicked();
    void onSpellRemoveClicked();
    void onCloseClicked();
    void onSaveClicked();
};
