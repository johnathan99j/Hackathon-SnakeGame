#include <pebble.h>
#include "draw.h"

struct snake{
  int life;
  int size;
  int score;
  int x;
  int y;
  int dir;
};

struct *create_snake(int lif, int siz, int xpos, int ypos, int sdir){
	struct snake * create_snake = (struct snake *) malloc (sizeof(struct snake));
	
  if( lif == 0 || size == 0 ){
    //death
  }else if( *create_snake = NULL ){
    //malloc fail
  }else{
    create_snake->life = lif;
    create_snake->size = siz;
    create_snake->score = 0;
    create_snake->x = xpos;
    create_snake->y = ypos;
    create_snake->dir = sdir; 
  }
}

int *move_snake(int bpress){
  struct snake * curr_snake = (struct snake *) malloc (sizeof(struct snake));
  
  if( bpress == NULL ){
    //error
  }else if( bpress == 0 ){ //-X
    if( curr_snake->x == state[0][] ){ //touches left border?
      curr_snake->x = 27;//change x to right
    }else{
      curr_snake->x -= 1;//decrament x
    }
  }else if( bpress == 1 ){ //-Y
    if( curr_snake->y == 0 ){//touches top border?
      curr_snake->y = 26;//change y to bottom
    }else{
      curr_snake->y -= 1;//decrament y
    }
  }else if( bpress == 2 ){ //X++
    if( curr_snake->x == 27 ){ //touches left border?
      curr_snake->x = 0;//change x to right
    }else{
      curr_snake->x += 1;//incrament x
    }
  }else if( bpress == 3 ){
    if( curr_snake->y == 26 ){//touches top border?
      curr_snake->y = 0;//change y to bottom
    }else{
      curr_snake->y += 1;//decrament y
    }
  }
}