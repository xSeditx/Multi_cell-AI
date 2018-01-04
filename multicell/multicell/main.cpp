#include"Window.h"
#include<iostream>
#include"cell.h"
#include"main.h"
//extern double COS[360],SIN[360];
using namespace std;


vector<multi_cell>CREATURES;


void main()
{
	WINDOW main(0,0,SCREENWIDTH,SCREENHEIGHT,"NEW WINDOW");
	SET_ACTIVE_WINDOW(&main);
	srand(RANDOM(10000));

	LOOP(10000){
		CREATURES.push_back(multi_cell(RANDOM(10)));
    }

	float TIMER =0;
	while(_LOOP_GAME){
	  _CLS;
       TIMER = SDL_GetTicks();

	   for(int count = 0;count < CREATURES.size();count++){
	          CREATURES[count].ROTATE(RANDOM(30) - 15);//RANDOM(360));//;
	          CREATURES[count].MOVE(1);
			  //if(CREATURES[count].HIT()!=0)
			   //DRAW_WORLD();
			  CREATURES[count].SIGHT();
	          CREATURES[count].DRAW();
	   }
	   			 for(int Y = 0;Y < SCREENHEIGHT; Y++){
		        for(int X = 0;X < SCREENWIDTH; X++){
					if (WORLD[X][Y] != 0)SET_PIXEL(X,Y,RGB(255,255,255));
				}
				}
	  Print(SDL_GetTicks() - TIMER);
	 _SYNC;
	}
	return;
}




void DRAW_WORLD()
{
	for(int Y = 0;Y < SCREENHEIGHT; Y++){
		for(int X = 0;X < SCREENWIDTH; X++){
			int *V = &WORLD[(int)X][(int)Y];
			switch(*V){
			    case  0:break;
				case -1:
				    SET_PIXEL(X,Y  ,RGB(100,100,100));
				break;
				case -2:
					SET_PIXEL(X,Y-1,RGB(  0,155,  0)) ; 
				break;
				default:
					if (SHOW_COLLISION == 1)    SET_PIXEL(X,Y-1,RGB(255,0,0));
                    else if  (SHOW_SEX == 1) if (CREATURES[*V].GENDER == male) 
						                        SET_PIXEL(X,Y-1,RGB(255,0,0)); 
					                       else SET_PIXEL(X,Y-1,RGB(0,0,255));
					else SET_PIXEL(X,Y-1,CREATURES[*V].COLOR) ;
				break;
			}
		}
	}

}

















///float X = 100,Y = 100,DIST = 10;
///		for (float angle = 0; angle < 360;angle++){
///			float XX = NEWX(X,10,angle); //X + DIST *cos(RADIANS(angle));
///			float YY = Y + DIST *sin(RADIANS(angle));
///			SET_PIXEL(XX,YY,RGB(255,255,255));
///		}






