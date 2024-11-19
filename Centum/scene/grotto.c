#include <stdio.h>
#include "../player/player.h"
#include "../util/util.h"

void play() {
    typeln("You step into the small and dark grotto, wet soil squishes between your toes.");
    typeln("The strong swamp air starts to thin out and the smell of spring draws near.");
    typeln("A voice waves through the air.");
    typeln("\"Tell me your name:\"");
    char *name = get_input_string(10);
    typeln("And hello, to %s", name);
    Player *player = create_player(name);
    pretty_print_player(player);
    destroy_player(player);
}