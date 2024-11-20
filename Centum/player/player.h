#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
	char* name;
	int level;
	int gold;
} Player;

Player* pl_create(const char* name);
void pl_destroy(Player* self);
void pl_pretty_print(Player* self);

#endif