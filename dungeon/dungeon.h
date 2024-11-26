#ifndef DUNGEON_H
#define DUNGEON_H

#include "../entities/enemy.h"
#include "../entities/player.h" // TODO: Move items to item.h instead of player.h
#include <stdbool.h>

typedef enum EncounterType { MONSTER, TREASURE, SHOP, TRAP, BOSS, HEAL, EMPTY } EncounterType;

typedef struct Dungeon {
	struct DungeonRoom* entrance;
} Dungeon;

Dungeon* dg_create();
void dg_destroy(Dungeon* d);

typedef struct DungeonRoom {
	char* description;
	struct DungeonRoom* north;
	struct DungeonRoom* south;
	struct DungeonRoom* east;
	struct DungeonRoom* west;
	bool has_visited;
	bool interaction_completed;
	EncounterType encounter_type;
	Enemy* enemy;
	Item* item;
} DungeonRoom;

DungeonRoom* dr_create(const char* description, EncounterType encounter_type);
void dr_destroy(DungeonRoom* r);

#endif