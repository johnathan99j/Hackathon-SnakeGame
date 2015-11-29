#include <pebble.h>

#define WIDTH 4
#define HEIGHT 4

struct fruit{
	int x,y;
	int W,H;
};




struct fruit *createFruit(int x, int y){
	struct fruit *newFruit = (struct fruit *) malloc (sizeof(struct fruit));
	
	if(newFruit == NULL){
		printf("malloc fail");
		exit(-1);
	}
	
	newFruit->x = x;
	newFruit->y = y;
	newFruit->W = WIDTH;
	newFruit->H = HEIGHT;
	
	return newFruit;	
}

