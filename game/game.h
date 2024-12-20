#ifndef GAME_H
#define GAME_H

#include "../dungeon/dungeon.h"
#include "../entities/player.h"

void g_start(Player* player);
void g_start_current_room();
void g_combat(Enemy* enemy);
void g_treasure();
void g_player();

#endif