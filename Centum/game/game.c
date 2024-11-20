#include "game.h"
#include "../util/util.h"

DungeonRoom* current_room;

void g_start(Player* player)
{

	type("%s walks into the dungeon, opening the first door. What awaits!\n", player->name);
	Dungeon* d = dg_create();
	current_room = d->entrance;
	g_start_current_room();
}

void g_start_current_room()
{
	type("%s\n", current_room->description);
	type("1. Open Chest\n");
	type("2. Go North\n");
	type("3. Go West\n");
	type("4. Go East\n");
	type("5. Go South\n");

	int choice = get_input_int(4);

	switch (choice) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}