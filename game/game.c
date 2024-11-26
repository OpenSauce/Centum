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
	current_room->has_visited = true;

	switch (current_room->encounter_type) {
	case TREASURE:
		type("1. Open Chest\t");
		break;
	case MONSTER:
		type("1. Attack enemy\t");
		break;
	}
	type("2. Go North\t");
	type("3. Go West\t");
	type("4. Go East\t");
	type("5. Go South\n");

	int choice = get_input_int(5);

	switch (choice) {
	case 1:
		switch (current_room->encounter_type) {
		case TREASURE:
			if (current_room->interaction_completed) {
				type("The chest is empty.\n");
				break;
			}
			g_treasure();
			break;
		case MONSTER:
			if (current_room->interaction_completed) {
				type("The bones of the slayed rest there peacefully.\n");
				break;
			}
			g_combat(current_room->enemy);
			break;
		}
		break;
	case 2:
		if (current_room->north) {
			current_room = current_room->north;
			break;
		} else {
			type("You can't go that way.\n");
			break;
		}
	case 3:
		if (current_room->west) {
			current_room = current_room->west;
			break;
		} else {
			type("You can't go that way.\n");
			break;
		}
	case 4:
		if (current_room->east) {
			current_room = current_room->east;
			break;
		} else {
			type("You can't go that way.\n");
			break;
		}
	case 5:
		if (current_room->south) {
			current_room = current_room->south;
			break;
		} else {
			type("You can't go that way.\n");
			break;
		}
	}

	g_start_current_room();
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
					current_room->interaction_completed = true;
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
			break;
		case 2:
			type("You attempt to run away from the %s!\n", enemy->name);
			return;
		}
	}

	if (current_player->stats->hp <= 0) {
		type("You were defeated by the %s...\n", enemy->name);
	} else {
		type("You defeated the %s!\n", enemy->name);
		current_room->interaction_completed = true;
	}
}

void g_treasure()
{
	type_with_color(COLOR_GREEN, "You open the chest and find 20 gold!\n");
	current_player->gold += 20;
	type("You now have %d gold.\n", current_player->gold);
	current_room->interaction_completed = true;
	return;
}