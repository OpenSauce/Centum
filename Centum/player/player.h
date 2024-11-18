#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
    char *name;
    int level;
    int gold;
} Player;

Player *create_player(const char *name);
void destroy_player(Player *self);
void pretty_print_player(Player *self);

#endif