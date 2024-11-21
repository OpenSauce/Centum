#include "game.h"
#include "../util/util.h"

DungeonRoom* current_room;
Player* current_player;

void g_start(Player* player)
{
	current_player = player;
	type("%s walks into the dungeon, opening the first door. What awaits!\n", player->name);
	Dungeon* d = dg_create();
	current_room = d->entrance;
	g_start_current_room();
}

void g_start_current_room()
{
	if (!current_room->has_visited) {
		type("%s\n", current_room->description);
	}

	switch (current_room->encounter_type) {
	case TREASURE:
		type("1. Open Chest\n");
		break;
	case MONSTER:
		type("1. Attack Monster\n");
		break;
	}
	type("2. Go North\n");
	type("3. Go West\n");
	type("4. Go East\n");
	type("5. Go South\n");

	int choice = get_input_int(5);

	switch (choice) {
	case 1:
		if (current_room->has_visited) {
			type("The chest is empty.\n");
			g_start_current_room();
			return;
		}
		type_with_color(COLOR_GREEN, "You open the chest and find 20 gold!\n");
		current_player->gold += 20;
		type("You now have %d gold.\n", current_player->gold);
		current_room->has_visited = true;
		g_start_current_room();
		break;
	case 2:
		if (current_room->north) {
			current_room = current_room->north;
			g_start_current_room();
		} else {
			type("You can't go that way.\n");
			g_start_current_room();
		}
		break;
	case 3:
		if (current_room->west) {
			current_room = current_room->west;
			g_start_current_room();
		} else {
			type("You can't go that way.\n");
			g_start_current_room();
		}
		break;
	case 4:
		if (current_room->east) {
			current_room = current_room->east;
			g_start_current_room();
		} else {
			type("You can't go that way.\n");
			g_start_current_room();
		}
		break;
	case 5:
		if (current_room->south) {
			current_room = current_room->south;
			g_start_current_room();
		} else {
			type("You can't go that way.\n");
			g_start_current_room();
		}
		break;
	}
}