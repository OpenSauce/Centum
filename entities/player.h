#ifndef PLAYER_H
#define PLAYER_H

#include "combat_stats.h"
#include <stdbool.h>

typedef struct Item {
	char* name;
	char* description;
	int value;
} Item;

typedef struct Inventory {
	Item** items;
	int item_count;
	int capacity;
} Inventory;

Inventory* inv_create();
void inv_destroy(Inventory* inv);
bool inv_add_item(Inventory* inv, Item* item);
void inv_remove_item(Inventory* inv, Item* item);

typedef struct Player {
	char* name;
	int level;
	int experience;
	int gold;
	CombatStats* stats;
	Inventory* inventory;
} Player;

Player* pl_create(const char* name);
void pl_destroy(Player* self);
void pl_pretty_print(Player* self);

#endif