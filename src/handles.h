#include <pebble.h>
#include "draw.h"

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Up pressed!");
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Select pressed!");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Down pressed!");
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}