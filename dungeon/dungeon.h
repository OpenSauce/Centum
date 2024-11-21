#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>

typedef enum EncounterType { MONSTER, TREASURE, BOSS } EncounterType;

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
	EncounterType encounter_type;
} DungeonRoom;

DungeonRoom* dr_create(const char* description, EncounterType encounter_type);
void dr_destroy(DungeonRoom* r);

#endif