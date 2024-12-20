#include "../entities/player.h"
#include "../util/util.h"

void play()
{
	typeln("You step into the small and dark grotto, wet soil squishes between your toes.");
	typeln("The strong swamp air starts to thin out and the smell of spring draws near.");
	typeln("A voice waves through the air.");
	typeln("\"Tell me your name:\"");
	char* name = get_input_string(10);
	typeln("Hello %s", name);
	Player* player = pl_create(name);
	pl_pretty_print(player);
	pl_destroy(player);
}