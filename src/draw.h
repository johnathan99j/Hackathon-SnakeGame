/*
 * draw.c
 * Creates a Window, Layer and assigns an `update_proc` to draw 
 * the 'P' in the Pebble logo.
 */

#include <pebble.h>

#define ROW 28
#define COL 27

GContext *G_ctx;
int G_P = 0;
int G_LastX, G_LastY = 0;

int G_Score = 0;

static Window *s_main_window;
static Layer *s_canvas_layer;
static TextLayer *s_output_layer;

struct snake{
  int life;
  int size;
  int score;
  int x;
  int y;
  int dir;
};

void set_draw(int R, int C, int S);
void draw();
void updateScore(int score);
void rndPosition(int *x, int *y);
int random(int min, int max);
void drawFruit();
void reset();
void create_snake(int lif, int siz, int xpos, int ypos, int sdir);
void move_snake(struct snake *s,int dir);


short state[ROW][COL];

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
static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);
	
	graphics_context_set_stroke_color(ctx, GColorBlack);
	graphics_context_set_text_color(ctx, GColorBlack);  
	
	G_ctx = ctx;
	
	//Draws score text
	
	updateScore(G_Score);
	
	//This draws new fruit with each canvas re-draw, only needed when canvas is initially drawn
	//otherwise, the function should only be called once the snake collides w/ the snake
	//hope this helps lool
	
	drawFruit();
	
	//create_snake(3, 4, random(0,120), random(0,140), 0);
	
  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));
  //x,y,width,height
  
	//Draws border
  graphics_draw_rect(ctx, GRect(1, 22, 142, 144));
  graphics_draw_rect(ctx, GRect(2, 21, 140, 144));
	
	while (G_P == 0){
		create_snake(3, 4, random(0,120), random(0,140), 0);
	}
	
}
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
  text_layer_set_text(s_output_layer, "Tom's 1");
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
  text_layer_set_text(s_output_layer, "Tom's 2");
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
  s_output_layer = text_layer_create(GRect(0, 65, 141, 151));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text(s_output_layer, "");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));	//Adds pause text
	//layer_remove_from_parent(text_layer_get_layer(s_output_layer));		//Removes pause text
	
  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

  // Set the update_proc
	if(G_LastX==0){
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
	}
}

static void main_window_unload(Window *window) {
  // Destroy Layer
  layer_destroy(s_canvas_layer);
	text_layer_destroy(s_output_layer);
}

static void init(void) {
  // Create main Window
  s_main_window = window_create();
  window_set_fullscreen(s_main_window, true);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
	
	window_set_click_config_provider(s_main_window, click_config_provider);

  window_stack_push(s_main_window, true);
}

static void deinit(void) {
  // Destroy main Window
  window_destroy(s_main_window);
}


void move_snake(struct snake *s,int dir){
	int i=0;
	for(i=0;i<s->size;++i){
		
	}
}

void create_snake(int lif, int siz, int xpos, int ypos, int sdir){
	struct snake *create_snake = (struct snake *) malloc (sizeof(struct snake));
	
  if( lif == 0 || siz == 0 ){
    //text_layer_set_text(s_output_layer, "GAMEOVER");
  }else{
    create_snake->life = lif;
    create_snake->size = siz;
    create_snake->score = 0;
    create_snake->x = xpos;
    create_snake->y = ypos;
    create_snake->dir = sdir;
    /*
		int i =0;
		
		for(i=0;i<create_snake->size*4;i+=4){
			graphics_draw_rect(G_ctx, GRect(2+create_snake->x+i,21+create_snake->y, 5, 5));
		}
		*/
	//state[create_snake->x][create_snake->y] = 1;
				/*int i=0;
				for(i=0;i>create_snake->size;++i){
					state[create_snake->x+i][create_snake->y] = 1;
					printf("i:%d",i);
				}
				draw();
			*/
		}
		
    if( create_snake->x > 0 && create_snake->x < 27 ){
      if( create_snake->y > 0 && create_snake->y < 26 ){
        
				
        
      }
    }
    /*
    if( create_snake->dir >= 0 ){
      while(1){
        if( create_snake->dir == 1 ){
          //state[create_snake->x+1][create_snake->y];
          create_snake->x+=1;
         // graphics_fill_rect(G_ctx, GRect(create_snake->x, create_snake->y, 4, 4), 0, GColorBlack);
        }
      }
      
    }*/
		
  }


/*
int *change_snake_dir(int bpress, int cdir){
  struct snake * curr_snake = (struct snake *) malloc (sizeof(struct snake));
  
  if ( *bpress == NULL ){    //ERROR
    return -1;
  }else if( bpress == 1 ){ //left (UP BUTTON)
    if( cdir == 0 ){
      
      curr_snake->x -= state[][];
      cdir = 3;
      return cdir;
      
    }else if () {
      
    }
  }else if( bpress == 2 ){ //right (DOWN BUTTON)
    
  }else{    //ERROR
    return -1;
  }
}
*/