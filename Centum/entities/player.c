#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	p->level = 0;
	p->gold = 0;

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
		printf("Player name: %s, Level: %d\n", self->name, self->level);
	}
}