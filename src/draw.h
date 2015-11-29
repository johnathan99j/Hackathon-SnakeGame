/*
 * draw.c
 * Creates a Window, Layer and assigns an `update_proc` to draw 
 * the 'P' in the Pebble logo.
 */

#include <pebble.h>

#define ROW 28
#define COL 27

static Window *s_main_window;
static Layer *s_canvas_layer;
static TextLayer *s_output_layer;

GContext *G_ctx;
int G_P = 0;
int G_LastX, G_LastY = 0;
int ii = 0;
int jj = 0;
int dire = 0;

void set_draw(int R, int C, int S);
void draw();
void updateScore(int score);
void rndPosition(int *x, int *y);
int random(int min, int max);
void drawFruit();
void reset();
static void updateGame(Layer *layer, GContext *ctx);
static void timer_handler(void *context);
static void click_config_provider(void *context);

short state[ROW][COL];

static void updateGame(Layer *layer, GContext *ctx) {
  //game
  int i = 0;
	int j = 0;
	
  GRect bounds = layer_get_bounds(layer);
	
	graphics_context_set_stroke_color(ctx, GColorBlack);
	graphics_context_set_text_color(ctx, GColorBlack);
  
  //Draws border
  graphics_draw_rect(ctx, GRect(1, 22, 142, 144));
  graphics_draw_rect(ctx, GRect(2, 21, 140, 144));
	
	G_ctx = ctx;
	
	//Draws score text
	updateScore(0);
	
	//Draws cube things
	if(G_P==0){
		if(dire==0 || dire==4){		//RIGHT
			if(jj == 27) {
				jj = 0;
			}
			set_draw(ii,jj,1);
			jj++;
			set_draw(ii-i, jj-1, 0);
		}else if(dire==2){		//LEFT
			if(jj == 00) {
				jj = 27;
			}
			set_draw(ii,jj,1);

			jj--;
			set_draw(ii+i, jj+1, 0);
		}else if(dire==1){	//DOWN
			if(ii == 27) {
				ii = 0;
			}
			set_draw(ii,jj,1);
			ii++;
			set_draw(ii-1, jj-j, 0);
		}else if(dire ==3){		//UP
			if(ii == 00) {
				ii = 27;
			}
			set_draw(ii,jj,1);

			ii--;
			set_draw(ii+1, jj+j, 0);
		}
	}
}

/* 
		STATE
    0 - NULL
    1 - graphics_fill_rect
    2 - graphics_draw_circle
*/

void reset() {
  for (short i = 0; i < ROW; i++) {
    for (short j = 0; j < COL; j++) {
      state[i][j] = 0;
    }
  }
}

void set_draw(int R, int C, int S) {
  state[R][C] = S;
  
  int r = 0;
  for(int row = 24; row < 160; row+=4+1) {
    int c = 0;
    for(int col = 5; col < 137; col+=4+1) {
      if (state[r][c] == 1) {
        graphics_fill_rect(G_ctx, GRect(col, row, 4, 4), 0, GColorBlack);
      } else if (state[r][c] == 2) {
        graphics_draw_circle(G_ctx, GPoint(col+2, row+1), 2);
      } 
      c++;
    }
      r++;
  }
}

void draw() {
  
  int r = 0;
  for(int row = 24; row < 160; row+=4+1) {
    int c = 0;
    for(int col = 5; col < 137; col+=4+1) {
      if (state[r][c] == 1) {
        graphics_fill_rect(G_ctx, GRect(col, row, 4, 4), 0, GColorBlack);
      } else if (state[r][c] == 2) {
        graphics_draw_circle(G_ctx, GPoint(col+2, row+1), 2);
      } 
      c++;
    }
      r++;
  }
}


int random(int min, int max){
    int range, result, cutoff;
 
    if (min >= max)
        return min;
    range = max-min+1;
    cutoff = (RAND_MAX / range) * range;
    do {
        result = rand();
    } while (result >= cutoff);
    return result % range + min;
}

void rndPosition(int *x, int *y){
	int NewX, NewY =0;
	
	time_t t;
	srand((unsigned) time(&t));
  
  NewX = random(1,27);
	NewY = random(1,27);
	
	*x= NewX;
	*y= NewY;
}

void drawFruit(){
	
	if(G_LastX==0){
		int x,y =0;
		rndPosition(&x, &y);

		G_LastX=x;
		G_LastY=y;

		set_draw(x,y,2);
	}else{
		set_draw(G_LastX, G_LastY, 2);
	}
	
	
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------


  

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	if(scoreInt==0){
		strcpy(Int2Str,"0");
	}else{
		strcpy(Int2Str,itoa(scoreInt));
	}
	strcpy(scoreStr,"Score: ");
	strcat(scoreStr, Int2Str);
	graphics_draw_text(G_ctx, scoreStr, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(1, 0, 141, 21), GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(s_output_layer, "Tom's 1");
	dire -= 1;
	if(dire<0){
		dire=3;
	}
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	
	if(G_P==0){
			text_layer_set_text(s_output_layer, "PAUSE");
		G_P = 1;		
	}else{
		text_layer_set_text(s_output_layer, "");
		G_P = 0;
	}
	
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(s_output_layer, "Tom's 2");
	dire += 1;
	if(dire>4){
		dire=1;
	}
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
	
// Create output TextLayer
  
	//layer_remove_from_parent(text_layer_get_layer(s_output_layer));		//Removes pause text
	
  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

  // Set the update_proc
	if(G_LastX==0){
    //canvas_update_proc
	}
  
}

static void main_window_unload(Window *window) {
  // Destroy Layer
  layer_destroy(s_canvas_layer);
	text_layer_destroy(s_output_layer);
}

static void timer_handler(void *context) {
   layer_mark_dirty(s_canvas_layer);
   app_timer_register(150, timer_handler, NULL);
}

static void init() {
  // Create main Window
  s_main_window = window_create();
  window_set_fullscreen(s_main_window, true);
  window_set_click_config_provider(s_main_window, click_config_provider);
  s_canvas_layer = layer_create(GRect(0,0,144,168));
  window_stack_push(s_main_window, false);
	
	Layer *window_layer = window_get_root_layer(s_main_window);
	s_output_layer = text_layer_create(GRect(0, 65, 141, 151));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text(s_output_layer, "");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));	//Adds pause text
	
  Layer* motherLayer = window_get_root_layer(s_main_window);
  layer_add_child(motherLayer, s_canvas_layer);


  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  layer_set_update_proc(s_canvas_layer, updateGame);
  app_timer_register(150, timer_handler, NULL);
  
}

static void deinit(void) {
  // Destroy main Window
  window_destroy(s_main_window);
}