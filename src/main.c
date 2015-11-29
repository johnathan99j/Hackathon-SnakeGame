#include <pebble.h>
#include "draw.h"
#include "fruit.h"

int main(void) {
	init();
  
	app_event_loop();

	deinit();
}

