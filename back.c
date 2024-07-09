#include "back.h"
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
void main.enemy(int *argc, char *argv[])
{
	  while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
		    if (e.type == SDL_QUIT) {
		        SDL_Quit();
		        return 0;
		    }
		}

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Rect mouseRect = { mouseX, mouseY, 1, 1 };

		// Check for collision between mouse and enemy hitbox
		SDL_Rect enemyHitbox = { enemyX, enemyY, SPRITE_WIDTH_ENEMY1, SPRITE_HEIGHT_ENEMY1 };
		if (checkCollision(enemyHitbox, mouseRect)) {
		    enemyStopped = 1;
		} else {
		    enemyStopped = 0;
		}

		// Handle coin collision
		for (int i = 0; i < SCREEN_WIDTH / (SPRITE_WIDTH_ENEMY1 + COIN_DISTANCE); ++i) {
		    if (coins[i].exists && checkCollision(coins[i].hitbox, mouseRect)) {
		        coins[i].exists = 0;
		    }
		}

		// Move the enemy horizontally if it's not stopped
		if (!enemyStopped) {
		    enemyX += ENEMY_SPEED * enemyDirection;
		    if (enemyX <= 0) {
		        enemyDirection = 1; // Change direction to right when reaching the left edge
		        frame = 0; // Reset animation frame
		    } else if (enemyX >= SCREEN_WIDTH - SPRITE_WIDTH_ENEMY1) {
		        enemyDirection = -1; // Change direction to left when reaching the right edge
		        frame = 0; // Reset animation frame
		    }
		}

		// Update the enemy's animation based on its direction and mouse collision
		if (enemyDirection == 1) {
		    if (enemyStopped) {
		        applySurface(enemyX, enemyY, spriteSheet, screen, &enemyClips3[frame]); // Third line animation
		    } else {
		        applySurface(enemyX, enemyY, spriteSheet, screen, &enemyClips1[frame]); // First line animation
		    }
		} else {
		    if (enemyStopped) {
		        applySurface(enemyX, enemyY, spriteSheet, screen, &enemyClips3[frame]); // Third line animation
		    } else {
		        applySurface(enemyX, enemyY, spriteSheet, screen, &enemyClips2[frame]); // Second line animation
		    }
		}

		// Render coins
		for (int i = 0; i < SCREEN_WIDTH / (SPRITE_WIDTH_ENEMY1 + COIN_DISTANCE); ++i) {
		    if (coins[i].exists) {
		        applySurface(coins[i].x, coins[i].y, coinSpriteSheet, screen, &coinClips[frame]);
		    }
		}

		if (SDL_Flip(screen) == -1) {
		    printf("SDL could not flip screen! SDL Error: %s\n", SDL_GetError());
		    return 1;
		}

		if (SDL_GetTicks() - startTime >= FRAME_DURATION) {
		    frame++;

		    if (frame >= NUM_FRAMES_ENEMY1) {
		        frame = 0;
		    }

		    startTime = SDL_GetTicks();
		}

		SDL_Delay(10);
	    }

void initBackground(background *b)
{


b->img_back=IMG_Load("back_lvl1.png");
b->pos_back.x=0;
b->pos_back.y=0;



b->camera.x=0;
b->camera.y=250;
b->camera.w=SCREEN_W; 
b->camera.h=SCREEN_H;



         b->music2=Mix_LoadMUS("music2.mp3"); 
	 b->bref1 = Mix_LoadWAV("bref1.wav"); //
 	b->bref2 = Mix_LoadWAV("bref2.wav");

	b->img_anim=IMG_Load("animation.png");  

	b->pos_img_anim.x=125; 
	b->pos_img_anim.y=100;

	b->one_img.x=0;
	b->one_img.y=0;

	b->one_img.w=116;  
	b->one_img.h=140;  

	b->nb_img=0;  



TTF_Init();
b->s.font=TTF_OpenFont("angelina.TTF",50);

b->s.color=(SDL_Color) {0,0,0};
b->s.text=TTF_RenderText_Blended(b->s.font,"score1: 0",b->s.color);

b->s.postext.x=100;
b->s.postext.y=10;

b->score=0;

Mix_PlayMusic(b->music2, -1); 

}

void initBackground2(background *b)
{


b->img_back=IMG_Load("back_lvl1.png");
b->pos_back2.x=907;
b->pos_back2.y=0;



b->camera2.x=0;
b->camera2.y=250;
b->camera2.w=SCREEN_W; 
b->camera2.h=SCREEN_H;


	b->img_anim=IMG_Load("animation.png"); 
	b->pos_img_anim.x=1000;
	b->pos_img_anim.y=100;

	b->one_img.x=0;
	b->one_img.y=0;

	b->one_img.w=116;  
	b->one_img.h=140;  

	b->nb_img=0;  



TTF_Init();
b->s.font=TTF_OpenFont("angelina.TTF",50);

b->s.color=(SDL_Color) {0,0,0};
b->s.text=TTF_RenderText_Blended(b->s.font,"score2: 0",b->s.color); 

b->s.postext.x=1000;
b->s.postext.y=10;

b->score=0;


}

void afficheBackground (background b, SDL_Surface *screen)
{

	char sc[12];
	sprintf(sc,"score 1: %d",b.score);
	b.s.text=TTF_RenderText_Blended(b.s.font,sc,b.s.color);


	SDL_BlitSurface(b.img_back,&b.camera,screen,&b.pos_back);
	affiche_anim_back(b,screen); 
	SDL_BlitSurface(b.s.text,NULL,screen,&b.s.postext);


}
void afficheBackground2 (background b, SDL_Surface *screen)
{

	char sc[12];
	sprintf(sc,"score 2: %d",b.score);
	b.s.text=TTF_RenderText_Blended(b.s.font,sc,b.s.color);


	SDL_BlitSurface(b.img_back,&b.camera2,screen,&b.pos_back2);
	affiche_anim_back(b,screen); 
	SDL_BlitSurface(b.s.text,NULL,screen,&b.s.postext);

}

void scrolling (background *b,int direction,int pas)
{

if (direction ==0){   


	b->camera.x+= pas;
        b->score+=1;          
	
        }
else if (direction ==1){          


	b->camera.x-=pas; 
        b->score+=1;
	}
 
else if (direction ==2){


         b->camera.y-= pas;
         b->score+=1;
	}
else if (direction ==3){         


	 b->camera.y+= pas;
         b->score+=1;
	 }

}

void scrolling2 (background *b,int direction,int pas)
{

if (direction ==0){   


	b->camera2.x+= pas;
        b->score+=1;          
	
        }
else if (direction ==1){          


	b->camera2.x-=pas; 
        b->score+=1;
	}
 
else if (direction ==2){


         b->camera2.y-= pas;
         b->score+=1;
	}
else if (direction ==3){       


	 b->camera2.y+= pas;
         b->score+=1;
	 }

}

void animerBackground(background *b)
{
	if (b->nb_img >=0 && b->nb_img <9) {
	b->one_img.x=b->nb_img * b->one_img.w;
	b->nb_img++;
	}
	
	if ( b->nb_img == 9) { 
	b->one_img.x=b->nb_img * b->one_img.w;
	b->nb_img=0;
	}

}

void affiche_anim_back(background b,SDL_Surface *screen)
{
	SDL_BlitSurface(b.img_anim,&(b.one_img), screen, &b.pos_img_anim);
}









