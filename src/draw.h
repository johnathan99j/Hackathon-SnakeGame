/*
 * draw.c
 * Creates a Window, Layer and assigns an `update_proc` to draw 
 * the 'P' in the Pebble logo.
 */

#include <pebble.h>
#include <stdio.h>
#define ROW 28
#define COL 27

GContext *G_ctx;

short state[ROW][COL];

void reset() {
  for (short i = 0; i < ROW; i++) {
    for (short j = 0; j < COL; j++) {
      state[i][j] = 0;
    }
  }
}

static Window *s_main_window;
static Layer *s_canvas_layer;

void updateScore(int score);

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);
	
	G_ctx = ctx;

  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));
  
  graphics_context_set_stroke_color(ctx, GColorBlack);
	graphics_context_set_text_color(ctx, GColorBlack);  
	
  //x,y,width,height
  
	//Draws border
  graphics_draw_rect(ctx, GRect(1, 22, 142, 144));
  graphics_draw_rect(ctx, GRect(2, 21, 140, 144));
	 
  //Draws grid
  
  /* STATE
    0 - NULL
    1 - graphics_fill_rect
    2 - graphics_draw_circle
  */
  
  int r = 0;
  for(int row = 24; row < 160; row+=4+1) {
    int c = 0;
    for(int col = 5; col < 137; col+=4+1) {
      if (state[r][c] == 1) {
        graphics_fill_rect(ctx, GRect(col, row, 4, 4), 0, GColorBlack);
      } else if (state[r][c] == 2) {
        graphics_draw_circle(ctx, GPoint(col+2, row+1), 2);
      } 
      c++;
    }
      r++;
  }
	
	//Draws score text
	updateScore(123456789);  
}

char *itoa(int num){
	static char buff[20] = {};
	int i = 0, temp_num = num, length = 0;
	char *string = buff;
	if(num >= 0) {
		while(temp_num) {
			temp_num /= 10;
			length++;
		}
		for(i = 0; i < length; i++) {
			buff[(length-1)-i] = '0' + (num % 10);
			num /= 10;
		}
		buff[i] = '\0';
	}
	else
	return "Unsupported Number";
	return string;
}

void updateScore(int scoreInt){
	char scoreStr[32];
	char Int2Str[20];
	strcpy(Int2Str,itoa(scoreInt));
	strcpy(scoreStr,"Score: ");
	strcat(scoreStr, Int2Str);
	graphics_draw_text(G_ctx, scoreStr, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(1, 0, 141, 21), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
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