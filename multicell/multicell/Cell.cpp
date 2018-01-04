
#include"cell.h"
#include"window.h"
using namespace std;


int WORLD[SCREENWIDTH][SCREENHEIGHT] ={0};
bool SHOW_VISION    = true;
bool SHOW_SEX       = false;
bool SHOW_COLLISION = false;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// MULTIcell CLASS ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

multi_cell::multi_cell(){} 
multi_cell::~multi_cell(){}

void multi_cell::WRAP(){
	if (POSITION.X < 0)             POSITION.X  +=  SCREENWIDTH;
	if (POSITION.X >= SCREENWIDTH)  POSITION.X  -=  SCREENWIDTH;
	if (POSITION.Y < 0)             POSITION.Y  +=  SCREENHEIGHT;
	if (POSITION.Y >= SCREENHEIGHT) POSITION.Y  -=  SCREENHEIGHT;

	if(ANGLE<  0) ANGLE += 360;
	if(ANGLE>360) ANGLE -= 360;
}

void multi_cell::DRAW(){
 
	   for(int count = 0;count < CELLS.size(); count++){
		       //CELLS[count].ROTATE(CELLS[count].POSITION.X, CELLS[count].POSITION.Y, ANGLE);
			   SET_PIXELII(CELLS[count].POSITION.X + POSITION.X,  CELLS[count].POSITION.Y + POSITION.Y,   CELLS[count].COLOR);
	   }
}

void multi_cell::MOVE(float speed){
	    //POTENTIAL.X += cos(RADIANS(ANGLE));
	    //POTENTIAL.Y += sin(RADIANS(ANGLE));
		POSITION.X += cos(RADIANS(ANGLE));
	    POSITION.Y += sin(RADIANS(ANGLE));
	    WRAP();
}

double COS[360],SIN[360];


void multi_cell::ROTATE(float angle){
	ANGLE += angle;
	
	for(int count = 0;count < CELLS.size();count ++){
		  float nx = (cos(RADIANS(angle)) * CELLS[count].POSITION.X) + (sin(RADIANS(angle)) * CELLS[count].POSITION.Y);
          float ny = (cos(RADIANS(angle)) * CELLS[count].POSITION.Y) - (sin(RADIANS(angle)) * CELLS[count].POSITION.X);
                CELLS[count].POSITION.X = nx;
                CELLS[count].POSITION.Y = ny;
		
	}

}






multi_cell::multi_cell(int numcells){
	    
		POSITION.X = (SCREENWIDTH) / 2;
		POSITION.Y = (SCREENHEIGHT) / 2;
		ANGLE =  RANDOM(360);
		NUMBER_OF_CELLS = numcells;
		COLOR = RGB(rand()%255,rand()%255,rand()%255);
		VISION.DISTANCE = RANDOM(10);
		VISION.FOV =      RANDOM(30);
		for(float y = 0; y < numcells; y++){
	        	 
	        				cell n = cell(this);
	        				n.POSITION.X = RANDOM(6)-3;
	        				n.POSITION.Y = RANDOM(6)-3;
	        		        CELLS.push_back(n);
	            
		}
		ALIVE = true;
}

void multi_cell::KILL(){
        ALIVE = false;
}


int multi_cell::HIT(){

	LOOP(NUMBER_OF_CELLS){
	
         int VALUE = WORLD[int(POTENTIAL.X)][int(POTENTIAL.Y)];

	      if(VALUE != 0 && VALUE != ID){
		         if (VALUE == -2){
			     WORLD[int(POTENTIAL.X)][int(POTENTIAL.Y)] = 0;
TryAgain:
			     int *V = &WORLD[int(rand()%WORLD_WIDTH)][int(rand()%WORLD_HEIGHT)];
			     if(*V == 0){
				       *V = -2;
			     }else{
				       goto TryAgain;
			     }
			     HEALTH += 100;
			    //LAST_MEAL = 0;
		}
		else{
			return VALUE;
		}
	}
return 0;



	}
}

int multi_cell::SIGHT(){
	float XX,YY,x1,y1;
	float ANG;
	 x1=POSITION.X;
	 y1=POSITION.Y;
	 float Theta;
	
    	for(float  DIST = 2; DIST < (float)VISION.DISTANCE; DIST++ ){
			Theta = (360 / ( 8 * DIST));
			for(float A  = -VISION.FOV; A < VISION.FOV; A+=Theta){	
    	            ANG = WRAP_ANGLE(ANGLE + A);
			        XX = x1 + DIST * cos(RADIANS(ANG));
			        YY = y1 + DIST * sin(RADIANS(ANG));
			        XX = WRAPX(XX);
			        YY = WRAPY(YY);
			        if(SHOW_VISION == true)SET_PIXELII(XX, YY, RGB(77,77,77));;
			        int VALUE = WORLD[(int)XX][(int)YY];
			        //if(VALUE !=  0)return VALUE;
			}
		}
return 0;
}

float   multi_cell::WRAPX(float x){
	if (x < 0)            return x + SCREENWIDTH;
	if (x >= SCREENWIDTH) return x - SCREENWIDTH;
return x;
}

float   multi_cell::WRAPY(float y){
	if (y > SCREENHEIGHT) return y - SCREENHEIGHT;
	if (y <= 0)           return y + SCREENHEIGHT;
return y;
}

float   multi_cell::WRAP_ANGLE(float angle){
	if (angle > 360) return angle - 360;
	if (angle <= 0)  return angle + 360;
return angle;
}

void multi_cell::SET_POSITION(){
    POSITION.X = POTENTIAL.X;
	POSITION.Y = POTENTIAL.Y;
	ANGLE = WRAP_ANGLE(ANGLE);
	int *W = &WORLD[(int)POSITION.X][(int)POSITION.Y]; // Confused as to why I have it setup this way as I believe 
	 if (W == 0)*W = ID;                               // my runtime checks should have already been performed
	                                                   // Plus being after my setting of position it nullify the very purpose to WTF! Fix this shit
	//if(WORLD[(int)X][(int)Y]==0)BUFFER[(int)X][(int)Y] = ID;
return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// cell CLASS ///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cell::~cell(){}

cell::cell(){
	    	POSITION.X = rand()%11 - 5;
			POSITION.Y = rand()%11 - 5;
			COLOR = RGB(RANDOM(255),RANDOM(255),RANDOM(255));
			WRAP();
}


cell::cell(multi_cell *Parent){
		    POSITION.X = Parent->POSITION.X + (RANDOM(20)-10);
			POSITION.Y = Parent->POSITION.Y + (RANDOM(20)-10);
			HEALTH = Parent->HEALTH;
			COLOR = Parent->COLOR;
			COLOR = Parent->COLOR;//RGB(RANDOM(255),RANDOM(255),RANDOM(255));
			WRAP();
}


void cell::DRAW(float x,float y,float angle){}
void cell::WRAP(){}
void cell::ROTATE(float &X, float &Y, float angle) {}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










