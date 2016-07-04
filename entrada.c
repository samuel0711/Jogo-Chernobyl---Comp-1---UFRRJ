#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
#include "define.h"

/*
void WalkEnemy(SDL_Surface*);
void Draw (Object*, SDL_Surface*, SDL_Surface*);
void UpSprite (Object*, int, int);

void Intro (void) {
	int beginTime, endTime;
    beginTime = SDL_GetTicks(); //retorna a quantidade de milissegundos decorridos desde a inicialização da biblioteca.

    SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);

    Texto("SCORE: 0000", screen, 10, 10);


    
    WalkEnemy(screen);  
    DrawPersonage(&hunter, surfacePersonage, screen);

	//atualizando tela
	SDL_Flip(screen);


    //Vefiricando e atualizando FPS
    endTime = SDL_GetTicks();
    if ((endTime - beginTime)*FPS < 1000) {
        SDL_Delay(1000/FPS - (endTime - beginTime));
        //printf("%d fps\n", 1000/(SDL_GetTicks() - beginTime));
    }
}



void WalkEnemy(SDL_Surface *screen) {
    int i, j;
    Object *p;

    for (j = 0; j < stages.stage[stages.index].nT; j++) {
        for (i = nObject-1; i >= enemies.enemy[j].nB; i--) {
            p = &(enemies.enemy[j].setup[i]);

            if (p->v != 0) {
                if (j == 0)
                    UpSprite(p, wEnemy1, hEnemy1);
                
                else if (j == 1)
                    UpSprite(p, wEnemy2, hEnemy2);

                else
                    UpSprite(p, wEnemy3, hEnemy3);

                Draw(p, enemies.surface[j], screen);
            }
        }
    }
}



void Draw (Object *object, SDL_Surface *surface, SDL_Surface *screen) {
    SDL_Rect pos1; //posicao no sprite ("recortar imagem")
    SDL_Rect pos2; //posicao no espaco apos movimento

    pos1.x = object->sx;
    pos1.y = object->sy;
    pos1.w = object->w;
    pos1.h = object->h;

    //nova posicao
    object->x += object->vx * object->v;
    object->y += object->vy * object->v;

    pos2.x = object->x;
    pos2.y = object->y;
    pos2.w = object->w;
    pos2.h = object->h;

    //atualizar tela
    SDL_BlitSurface(surface, &pos1, screen, &pos2);
}



void UpSprite (Object *object, int w, int h) {
    int dir;

    if (object->vx == 1 && object->vy == 1) //Sudeste
        dir = DE;

    else if (object->vx == 1 && object->vy == 0) //Leste
        dir = RE;

    else if (object->vx == 1 && object->vy == -1) //Nordeste
        dir = UE;    

    else if (object->vx == 0 && object->vy == 1) //Sul
        dir = DE;

    else if (object->vx == 0 && object->vy == -1) //Norte
        dir = UE;

    else if (object->vx == -1 && object->vy == 1) //Sudoeste
        dir = DE;

    else if (object->vx == -1 && object->vy == 0) //Oeste
        dir = LE;

    else if (object->vx == -1 && object->vy == -1) //Noroeste
        dir = UE;

    object->sy = h * dir;
    object->sx += w;
    if (object->sx == (nSE - 1) * w) //resetando a imagem p movimento
        object->sx = 0;
}
*/