#include "player.h"
#include "../util/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int inventory_capacity = 28;

Inventory* inv_create()
{
	Inventory* inv = (Inventory*)malloc(sizeof(Inventory));
	if (!inv) {
		fprintf(stderr, "Memory allocation failed for Inventory\n");
		exit(EXIT_FAILURE);
	}

	inv->items = (Item**)malloc(inventory_capacity * sizeof(Item*));
	if (!inv->items) {
		fprintf(stderr, "Memory allocation failed for Inventory items\n");
		free(inv);
		exit(EXIT_FAILURE);
	}

	inv->item_count = 0;
	inv->capacity = inventory_capacity;

	return inv;
}

void inv_destroy(Inventory* inv)
{
	if (inv) {
		for (int i = 0; i < inv->item_count; i++) {
			free(inv->items[i]->name);
			free(inv->items[i]->description);
			free(inv->items[i]);
		}
		free(inv->items);
		free(inv);
	}
}

bool inv_add_item(Inventory* inv, Item* item)
{
	if (inv->item_count < inv->capacity) {
		inv->items[inv->item_count] = item;
		inv->item_count++;
		return true;
	}
	return false;
}

Player* pl_create(const char* name)
{
	Player* p = (Player*)malloc(sizeof(Player));
	if (!p) {
		fprintf(stderr, "Memory allocation failed for Player\n");
		exit(EXIT_FAILURE);
	}

	p->name = strdup(name);
	if (!p->name) {
		fprintf(stderr, "Memory allocation failed for Player name\n");
		free(p);
		exit(EXIT_FAILURE);
	}

	CombatStats* stats = (CombatStats*)malloc(sizeof(CombatStats));
	p->stats = stats;
	p->stats->attack = 1;
	p->stats->hp = 10;
	p->stats->speed = 1;
	p->level = 1;
	p->experience = 0;
	p->gold = 0;
	p->inventory = inv_create();

	return p;
}

void pl_destroy(Player* self)
{
	if (self) {
		free(self->name);
		free(self);
	}
}

void pl_pretty_print(Player* self)
{
	if (self) {
		type("Player name: %s, Level: %d, Experience: %d, Gold: %d\n", self->name, self->level,
			self->experience, self->gold);
		type("HP: %d, Attack: %d, Speed: %d\n", self->stats->hp, self->stats->attack,
			self->stats->speed);

		type("Inventory (%d/%d):\n", self->inventory->item_count, self->inventory->capacity);
		for (int i = 0; i < self->inventory->item_count; i++) {
			Item* item = self->inventory->items[i];
			type("  - %s: %s (Value: %d)\t", item->name, item->description, item->value);
		}

		type("\n\n");
	}
}