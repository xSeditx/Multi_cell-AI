
#include"window.h"
#include<iostream>
#include<vector>


WINDOW *SCREEN;
 
WINDOW::WINDOW(int x,int y,int width,int height,char *title){
        X = x;  Y = y;
        WIDTH  = width;
        HEIGHT = height;
        TITLE  = title;
                                                                                                            if(SDL_Init(SDL_INIT_VIDEO) !=0)std::cout << "Init Video Error" << std::endl;
        HWND = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0); if(!HWND)                       std::cout << "ERROR: Initializing SDL Window" << std::endl;
        RENDER = SDL_CreateRenderer(HWND, -1, SDL_RENDERER_ACCELERATED);                                                           if(!RENDER)                     std::cout << "ERROR: Initializing SDL Renderer" << std::endl;
            
        if(SDL_SetRenderDrawColor(RENDER, 0, 0, 0, 255) != 0)std::cout << "Set Color Error" << std::endl;
        
        BACK_BUFFER  = SDL_CreateTexture(RENDER, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
        
        SDL_SetRenderTarget(RENDER, BACK_BUFFER);
        SDL_SetWindowResizable(HWND, SDL_TRUE);
        
        WINDOW_SURFACE   = SDL_GetWindowSurface     (HWND);
        WINDOW_FORMAT    = SDL_GetWindowPixelFormat (HWND);
        
        WINDOW_PIXELS = new Uint32[WIDTH * (HEIGHT + 40) + 1];
        memset(WINDOW_PIXELS, 255, WIDTH * HEIGHT * sizeof(Uint32)); 
}

WINDOW::~WINDOW(){}


 bool LOOP_GAME()
 {
	    bool leftMouseButtonDown = false;
  		SDL_PollEvent(&SCREEN->EVENT);
        switch (SCREEN->EVENT.type)
        {
                case SDL_QUIT:
	          	        return 0;
                break;
	          
                case SDL_MOUSEBUTTONUP:
                        if (SCREEN->EVENT.button.button == SDL_BUTTON_LEFT)
                                leftMouseButtonDown = false;
                        break;
                case SDL_MOUSEBUTTONDOWN:
                        if (SCREEN->EVENT.button.button == SDL_BUTTON_LEFT)
                                leftMouseButtonDown = true;
                case SDL_MOUSEMOTION:
                        if (leftMouseButtonDown){
                                int mouseX = SCREEN->EVENT.motion.x;
                                int mouseY = SCREEN->EVENT.motion.y;
                        }
                break;
	          
        }
 return 1;
 }
 

void CLS(){
				SDL_UpdateTexture(SCREEN->BACK_BUFFER, NULL, SCREEN->WINDOW_PIXELS, SCREEN->WIDTH * sizeof(Uint32)); // SLOW
				memset(SCREEN->WINDOW_PIXELS, 0, SCREEN->WIDTH * SCREEN->HEIGHT * sizeof(Uint32)); 

}

void SYNC(){
	//    SDL_RenderClear(SCREEN->RENDER);
        SDL_RenderCopy(SCREEN->RENDER, SCREEN->BACK_BUFFER, NULL, NULL);
        SDL_RenderPresent(SCREEN->RENDER);
}



void SET_PIXEL(int x, int y, Uint32 COLOR)
{
	//((Uint32*)pixels)[ x + ( y * SCREEN_WIDTH ) ] = SDL_MapRGB(fmt, 255, 0, 0);
	SCREEN->WINDOW_PIXELS[(y * SCREEN->WIDTH) + x] = COLOR;
}
 
extern void SET_PIXELII   (int x, int y, Uint32 COLOR){
	if (x < 0)x += SCREENWIDTH;
	if (x >= SCREENWIDTH)x -= SCREENWIDTH;
	
	if (y > SCREENHEIGHT)y -= SCREENHEIGHT;
	if (y <= 0)y += SCREENHEIGHT;
		SCREEN->WINDOW_PIXELS[(y * SCREEN->WIDTH) + x] = COLOR;
}
 
bool SET_ACTIVE_WINDOW(WINDOW *active)
{
	SCREEN = active;
	return 1;
}

void LOCK_PIXELS(){
	int   PITCH;
	void *PIXELS;
	SDL_LockTexture(SCREEN->BACK_BUFFER, NULL, &PIXELS,  &PITCH);
}
void UNLOCK_PIXELS(){
	SDL_UnlockTexture(SCREEN->BACK_BUFFER);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// VECTOR MANIPULATION /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float NEWX(float x,float dist,float angle){
		return x + dist * cos(RADIANS(angle));
}

float NEWY(float y,float dist,float angle){
		return y + dist * sin(RADIANS(angle));
}




//void rotate(float& x, float& y, float angle) {
//          float nx = cos(angle) * x + sin(angle) * y;
//          float ny = cos(angle) * y - sin(angle) * x;
//          x = nx;
//          y = ny;
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//SDL_Color color = {0, 0, 0, 0}; // black
/// https://gamedev.stackexchange.com/questions/63617/altering-pixel-value-in-an-sdl2-texture
/// Why you are locking the texture? You shoudn't access texture memory directly, in general accessing GPU memory has low performance. 
///	You should work with SDL_Surface all time then use SDL_UpdateTexture(sdlTexture, NULL, pSurface->pixels, pSurface->pitch); 
/// when your drawing is done, and finally call SDL_RenderCopy(renderer, pTexture, NULL, NULL);

//void *pixels;
//int pitch;
//SDL_PixelFormat *fmt;
//Uint32 format = SDL_GetWindowPixelFormat(window);
//fmt = SDL_AllocFormat(format);

//SDL_LockTexture(pTexture, NULL, &pixels, &pitch);
//((Uint32*)pixels)[ x + ( y * SCREEN_WIDTH ) ] = SDL_MapRGB(fmt, 255, 0, 0);
//SDL_UnlockTexture(pTexture);
//SDL_FreeFormat(fmt);

//http://sdl.5483.n7.nabble.com/SDL-UpdateTexture-vs-Locking-td38080.html