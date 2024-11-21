#ifndef GAME_H
#define GAME_H

#include "../dungeon/dungeon.h"
#include "../entities/player.h"

void g_start(Player* player);
Dungeon* generate_dungeon();
void g_start_current_room();

#endif