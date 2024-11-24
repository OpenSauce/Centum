#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>

Enemy* e_create(char* name, int health, int speed, int damage)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->name = name;
	CombatStats* stats = (CombatStats*)malloc(sizeof(CombatStats));
	stats->hp = health;
	stats->speed = speed;
	stats->damage = damage;
	enemy->stats = stats;
	return enemy;
}

void e_pretty_print(const Enemy* enemy)
{
	printf("Enemy Stats:\n");
	printf("Health: %d\n", enemy->stats->hp);
	printf("Speed: %d\n", enemy->stats->speed);
	printf("Damage: %d\n", enemy->stats->damage);
}