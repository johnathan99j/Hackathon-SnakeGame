/*
 * draw.c
 * Creates a Window, Layer and assigns an `update_proc` to draw 
 * the 'P' in the Pebble logo.
 */

#include <pebble.h>

static Window *s_main_window;
static Layer *s_canvas_layer;

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);

  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

  // Draw the 'loop' of the 'P'
  //graphics_context_set_fill_color(ctx, GColorBlack);
  //graphics_fill_rect(ctx, center, 40);
  //graphics_context_set_fill_color(ctx, GColorWhite);
  //graphics_fill_rect(ctx, center, 35);

  // Draw the 'stalk'
  //graphics_context_set_fill_color(ctx, GColorBlack);
  //graphics_fill_rect(ctx, GRect(32, 40, 5, 100), 0, GCornerNone);
  
  graphics_context_set_stroke_color(ctx, GColorBlack);
  //graphics_draw_pixel(ctx, GPoint(143, 167));
  /*
  graphics_fill_rect(ctx, GRect(6-6, 6-6, 6, 6), 0, GColorBlack);
  graphics_fill_rect(ctx, GRect(144-6, 6-6, 6, 6), 0, GColorBlack);
  graphics_fill_rect(ctx, GRect(6-6, 168-6, 6, 6), 0, GColorBlack);
  graphics_fill_rect(ctx, GRect(144-6, 168-6, 6, 6), 0, GColorBlack);
  */
  //x,y,width,height
  graphics_draw_rect(ctx, GRect(1, 22, 141, 144));    //TL
  graphics_draw_rect(ctx, GRect(2, 21, 139, 144));    //TL
  //graphics_draw_rect(ctx, GRect(2, 2, 144, 22));    //TL
  //graphics_draw_rect(ctx, GRect(138, 0, 6, 41));  //TR
  //graphics_fill_rect(ctx, GRect(0, 35, 6, 6), 0, GColorBlack);  //BL
  //graphics_fill_rect(ctx, GRect(138, 35, 6, 6), 0, GColorBlack);//BR 
  
  int grid[24][24];
  for(int row = 24; row < 160; row+=4+1) {
    for(int col = 5; col < 137; col+=4+1) {
      
      graphics_fill_rect(ctx, GRect(col, row, 4, 4), 0, GColorBlack);
    }
  }
  
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

  // Set the update_proc
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
}

static void main_window_unload(Window *window) {
  // Destroy Layer
  layer_destroy(s_canvas_layer);
}

static void init(void) {
  // Create main Window
  s_main_window = window_create();
  window_set_fullscreen(s_main_window, true);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit(void) {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
