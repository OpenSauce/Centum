#include "dungeon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Dungeon* dg_create()
{
	srand(time(NULL)); // Seed the random number generator

	Dungeon* d = malloc(sizeof(Dungeon));

	// Create rooms
	DungeonRoom* entrance = dr_create("The door creaks open, the smell of dust hits your nose, you "
									  "find a nice shining chest in the middle.",
		TREASURE);
	DungeonRoom* room1 = dr_create("As you open the door you hear the scurry of rats, you see a "
								   "small rat in the center of the room poised to attack.",
		MONSTER);
	room1->enemy = e_create("Rat", 10, 5, 2);
	DungeonRoom* room2
		= dr_create("You enter a dimly lit room with cobwebs hanging from the ceiling.", TREASURE);
	DungeonRoom* room3 = dr_create("A cold breeze hits you as you step into this room, and you see "
								   "a skeleton warrior ready to fight.",
		MONSTER);
	room3->enemy = e_create("Skeleton Warrior", 20, 3, 5);
	DungeonRoom* room4 = dr_create(
		"The room is filled with the smell of sulfur, and you see a treasure chest in the corner.",
		TREASURE);

	// Array of rooms
	DungeonRoom* rooms[] = { room1, room2, room3, room4 };
	int num_rooms = sizeof(rooms) / sizeof(rooms[0]);

	DungeonRoom* head = entrance;

	int i = 0;
	while (i < num_rooms) {
		int direction = rand() % 4;
		switch (direction) {
		case 0:
			if (head->north == NULL) {
				head->north = rooms[i];
				rooms[i]->south = head;
				head = rooms[i];
				i++;
			}
			break;
		case 1:
			if (head->south == NULL) {
				head->south = rooms[i];
				rooms[i]->north = head;
				head = rooms[i];
				i++;
			}
			break;
		case 2:
			if (head->east == NULL) {
				head->east = rooms[i];
				rooms[i]->west = head;
				head = rooms[i];
				i++;
			}
			break;
		case 3:
			if (head->west == NULL) {
				head->west = rooms[i];
				rooms[i]->east = head;
				head = rooms[i];
				i++;
			}
			break;
		}
	}

	d->entrance = entrance;
	return d;
}

void dg_destroy(Dungeon* d)
{
	dr_destroy(d->entrance);
	free(d);
}

DungeonRoom* dr_create(const char* description, EncounterType encounter_type)
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

	r->encounter_type = encounter_type;

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