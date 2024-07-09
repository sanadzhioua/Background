#include<stdio.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "back.h"



int main(void)
{
	int pas=50;
	int continuer=1;
	SDL_Surface *screen=NULL;
	background b;
        background b2;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	screen=SDL_SetVideoMode(1850,350,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(screen==NULL)
	{
		printf("unable to set video mode:%s\n",SDL_GetError());
		return 1;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	initBackground(&b); 
	initBackground2(&b2);

	while (continuer)
	{		
		SDL_PollEvent(&event);
     		switch(event.type)
        	{
			case SDL_QUIT:
                		continuer = 0;
                	break;
			case SDL_KEYDOWN:
                		switch(event.key.keysym.sym)
                		{
					case SDLK_ESCAPE:
                        			continuer = 0;
                        		break;
					case SDLK_RIGHT:
 						if(b.camera.x<12750)
						{
			                		
							scrolling(&b,0,pas);
						}			
                        		break;
                        		case SDLK_LEFT:
           					if(b.camera.x>0)
						{
							scrolling(&b,1,pas);
						} 
                        		break;
			 		case SDLK_UP:
                            			Mix_FadeInChannel(-1,b.bref1,0,0);
 						if(b.camera.y>0)
						{
							scrolling(&b,2,pas);
							
						}
                        		break;
 			 		case SDLK_DOWN:
 			  			if(b.camera.y<250)
						{
							scrolling(&b,3,pas);
						}		
                        		break;
					case SDLK_d:
 						if(b2.camera2.x<12750) //6050
						{
			                		
							scrolling2(&b2,0,pas);
						}				
                        		break;
                        		case SDLK_q:
           					if(b2.camera2.x>0)
						{
							scrolling2(&b2,1,pas);
						} 
                        		break;
			 		case SDLK_z:
                            			
 						if(b2.camera2.y>0)
						{
							scrolling2(&b2,2,pas);
						}
                        		break;
 			 		case SDLK_s:
 			  			if(b2.camera2.y<250)
						{
							scrolling2(&b2,3,pas);
						}		
                        		break;

				}
			break;
		}

		animerBackground(&b2);
		animerBackground(&b);
		
		afficheBackground (b,screen);
		afficheBackground2 (b2,screen);
		SDL_Flip(screen);

	}
	SDL_Quit();
        Mix_FreeMusic (b.music1);
        Mix_FreeMusic (b.music2);
        Mix_CloseAudio();

        return 1;
}

