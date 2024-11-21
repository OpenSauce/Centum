#include "enemy.h"
#include <stdio.h>
#include <stdlib.h>

Enemy* e_create(char* name, int health, int speed, int damage)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	enemy->name = name;
	CombatStats* stats = (CombatStats*)malloc(sizeof(CombatStats));
	enemy->stats = stats;
	enemy->stats->hp = health;
	enemy->stats->speed = speed;
	enemy->stats->damage = damage;
	return enemy;
}

void e_pretty_print(const Enemy* enemy)
{
	printf("Enemy Stats:\n");
	printf("Health: %d\n", enemy->stats->hp);
	printf("Speed: %d\n", enemy->stats->speed);
	printf("Damage: %d\n", enemy->stats->damage);
}