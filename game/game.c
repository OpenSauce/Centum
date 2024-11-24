#include "game.h"
#include "../util/util.h"
#include <unistd.h>

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
	type("%s\n", current_room->description);

	switch (current_room->encounter_type) {
	case TREASURE:
		type("1. Open Chest\n");
		break;
	case MONSTER:
		type("1. Attack enemy\n");
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
		switch (current_room->encounter_type) {
		case TREASURE:
			g_treasure();
			break;
		case MONSTER:
			g_combat(current_room->enemy);
			break;
		}
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

void g_combat(Enemy* enemy)
{
	type("A wild %s appears!\n", enemy->name);

	while (current_player->stats->hp > 0 && enemy->stats->hp > 0) {
		type("1. Attack\n");
		type("2. Run\n");

		int choice = get_input_int(2);

		switch (choice) {
		case 1:
			if (current_player->stats->speed >= enemy->stats->speed) {
				type("You attack the %s!\n", enemy->name);
				enemy->stats->hp -= current_player->stats->attack;
				type("The %s has %d HP left.\n", enemy->name, enemy->stats->hp);
				if (enemy->stats->hp <= 0) {
					type("You defeated the %s!\n", enemy->name);
					current_room->has_visited = true;
					return;
				}
				type("The %s attacks you!\n", enemy->name);
				current_player->stats->hp -= enemy->stats->attack;
				type("You have %d HP left.\n", current_player->stats->hp);
			} else {
				type("The %s attacks you!\n", enemy->name);
				current_player->stats->hp -= enemy->stats->attack;
				type("You have %d HP left.\n", current_player->stats->hp);
				if (current_player->stats->hp <= 0) {
					type("You were defeated by the %s...\n", enemy->name);
					return;
				}
				type("You attack the %s!\n", enemy->name);
				enemy->stats->hp -= current_player->stats->attack;
				type("The %s has %d HP left.\n", enemy->name, enemy->stats->hp);
			}
			usleep(500000);
		case 2:
			type("You attempt to run away from the %s!\n", enemy->name);
			current_room->has_visited = true;
			return;
		}
	}

	if (current_player->stats->hp <= 0) {
		type("You were defeated by the %s...\n", enemy->name);
	} else {
		type("You defeated the %s!\n", enemy->name);
		current_room->has_visited = true;
	}
}

void g_treasure()
{
	type_with_color(COLOR_GREEN, "You open the chest and find 20 gold!\n");
	current_player->gold += 20;
	type("You now have %d gold.\n", current_player->gold);
	current_room->has_visited = true;
	return;
}