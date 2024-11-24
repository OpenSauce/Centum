#ifndef SAVE_H
#define SAVE_H

#include "../entities/player.h"

void save_player(const char* filename, Player* player);
int load_player(const char* filename, Player* player);

#endif