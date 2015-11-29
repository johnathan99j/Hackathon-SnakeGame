#include <pebble.h>

#define WIDTH 4
#define HEIGHT 4

struct fruit{
	int x,y;
	int W,H;
};

void rndPosition(int *x, int *y);
int random(int min, int max);


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

int random(int min, int max)
{
    int range, result, cutoff;
 
    if (min >= max)
        return min; // only one outcome possible, or invalid parameters
    range = max-min+1;
    cutoff = (RAND_MAX / range) * range;
 
    // Rejection method, to be statistically unbiased.
    do {
        result = rand();
    } while (result >= cutoff);
 
    return result % range + min;
}

void rndPosition(int *x, int *y){
	
	int NewX, NewY =0;
	
	time_t t;
	srand((unsigned) time(&t));
  
  /* Intializes random number generator */
  NewX = random(0,27);
	NewY = random(0,27);
	
	int rnd = rand();
	
	printf("X:%d Y:%d\n",NewX,NewY);
	
	*x= NewX;
	*y= NewY;
	
}