#include "../build/cJSON.h"
#include "../entities/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_player(const char* filename, Player* player)
{
	cJSON* root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "name", player->name);
	cJSON_AddNumberToObject(root, "level", player->level);
	cJSON_AddNumberToObject(root, "health", player->stats->hp);
	cJSON_AddNumberToObject(root, "experience", player->experience);

	char* json_string = cJSON_Print(root);
	FILE* file = fopen(filename, "w");
	if (file) {
		fputs(json_string, file);
		fclose(file);
	}

	cJSON_Delete(root);
	free(json_string);
}

int load_player(const char* filename, Player* player)
{
	FILE* file = fopen(filename, "r");
	if (!file) {
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* json_string = malloc(length + 1);
	fread(json_string, 1, length, file);
	fclose(file);
	json_string[length] = '\0';

	cJSON* root = cJSON_Parse(json_string);
	if (!root) {
		free(json_string);
		return 0;
	}

	cJSON* name = cJSON_GetObjectItem(root, "name");
	cJSON* level = cJSON_GetObjectItem(root, "level");
	cJSON* health = cJSON_GetObjectItem(root, "health");
	cJSON* experience = cJSON_GetObjectItem(root, "experience");

	if (cJSON_IsString(name) && cJSON_IsNumber(level) && cJSON_IsNumber(health)
		&& cJSON_IsNumber(experience)) {
		strcpy(player->name, name->valuestring);
		player->level = level->valueint;
		player->stats->hp = health->valueint;
		player->experience = experience->valueint;
	}

	cJSON_Delete(root);
	free(json_string);
	return 1;
}