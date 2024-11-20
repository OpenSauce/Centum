#include "dungeon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dungeon* dg_create()
{
	Dungeon* d = (Dungeon*)malloc(sizeof(Dungeon));
	DungeonRoom* dr = dr_create("A little room, with a nice shining chest in the middle");
	d->entrance = dr;
	return d;
}

void dg_destroy(Dungeon* d)
{
	dr_destroy(d->entrance);
	free(d);
}

DungeonRoom* dr_create(const char* description)
{
	DungeonRoom* r = (DungeonRoom*)malloc(sizeof(DungeonRoom));
	if (!r) {
		printf("Memory allocation failed for DungeonRoom.\n");
		exit(1);
	}

	r->description = (char*)malloc(strlen(description) + 1);
	if (!r->description) {
		printf("Memory allocation failed for description.\n");
		free(r);
		exit(1);
	}
	strcpy(r->description, description);

	r->north = NULL;
	r->south = NULL;
	r->east = NULL;
	r->west = NULL;

	return r;
}

void dr_destroy(DungeonRoom* r)
{
	if (r) {
		if (r->north)
			dr_destroy(r->north);
		if (r->south)
			dr_destroy(r->south);
		if (r->east)
			dr_destroy(r->east);
		if (r->west)
			dr_destroy(r->west);

		free(r->description);

		free(r);
	}
}