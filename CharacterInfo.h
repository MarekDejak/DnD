#pragma once

#include <QVector>
#include "player.h"

struct CharacterInfo {
    int amtOfPlayers = 0;
    int amtOfCharacters = 0;

    QVector<Player> characters;
    QVector<QString> chosenCharacters;
};
