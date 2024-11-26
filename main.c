#include "entities/player.h"
#include "game/game.h"
#include "util/util.h"
#include <stdlib.h>

void start_game();
void load_game();
void show_instructions();
void quit_game();

int main()
{
menu:
	type_with_color(COLOR_RED, "=== Welcome to %d Centum ===\n", 100);
	type("1. Start Game\t");
	type("2. Continue\t");
	type("3. Instructions\t");
	type("4. Quit\n");

	int choice = get_input_int(4);

	switch (choice) {
	case 1:
		start_game();
		break;
	case 2:
		load_game();
		break;
	case 3:
		show_instructions();
		goto menu;
		break;
	case 4:
		quit_game();
		break;
	}

	return 0;
}

void start_game()
{
	type("\nStarting the game...\n");
	type("Prepare for adventure!\n\n");
	Player* p = pl_create("Leigh");
	g_start(p);
}

void load_game() { type("\nLoading game unavailable\n"); }

void show_instructions()
{
	type("\n=== Instructions ===\n");
	type("1. Navigate the dungeon using menu choices.\n");
	type("2. Fight enemies and solve puzzles.\n");
	type("3. Manage your inventory and survive.\n\n");
}

void quit_game()
{
	type("\nThank you for playing! Goodbye!\n");
	exit(0);
}