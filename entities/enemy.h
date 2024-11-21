#ifndef ENEMY_H
#define ENEMY_H

#include "combat_stats.h"

typedef struct {
	char* name;
	CombatStats* stats;
} Enemy;

Enemy* e_create(char* name, int hp, int speed, int damage);
void e_pretty_print(const Enemy* enemy);

#endif