#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "header.h"
#include "define.h"




void DrawEnemy1 (Object*, SDL_Surface*, SDL_Surface*);
void DrawEnemy2 (Object*, SDL_Surface*, SDL_Surface*);
void DrawEnemy3 (Object*, SDL_Surface*, SDL_Surface*);
void Direction (Object*);
void UpdateSprite (Object*, int, int);


void DrawPersonage (Object *object, SDL_Surface *surface, SDL_Surface *screen) {
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

    surface = Collision(object, surface, screen);

    //atualizar tela
    SDL_BlitSurface(surface, &pos1, screen, &pos2);
}



//podemos fundir as duas funcoes abaixo
void DrawBullet(SDL_Surface *surface, SDL_Surface *screen, Stack *stack) {
    int count;
    Object *p;

    for (count = nObject-1; count >= stack->nB; count--) {
        p = &(stack->setup[count]);

        if (p->v != 0) {
            DrawPersonage(p, surface, screen);
        }
    }
}










//====== INIMIGO ==========


void DrawEnemy(SDL_Surface *screen) {
    int i, j;
    Object *p;

    for (j = 0; j < stages.stage[stages.index].nT; j++) {
        for (i = nObject-1; i >= enemies.enemy[j].nB; i--) {
            p = &(enemies.enemy[j].setup[i]);

            if (p->v != 0) {
                if (j == 0) {
                    UpdateSprite(p, wEnemy1, hEnemy1);
                    DrawEnemy1(p, enemies.surface[j], screen);
                }
                
                else if (j == 1) {
                    UpdateSprite(p, wEnemy2, hEnemy2);
                    DrawEnemy2(p, enemies.surface[j], screen);
                }

                else {
                    UpdateSprite(p, wEnemy3, hEnemy3);
                    DrawEnemy3(p, enemies.surface[j], screen);
                }
            }
        }
    }
}




void DrawEnemy1 (Object *object, SDL_Surface *surface, SDL_Surface *screen) {
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

    surface = Collision(object, surface, screen);
    //sy = 21 * h - sprite para morte
    
    //atualizar tela
    SDL_BlitSurface(surface, &pos1, screen, &pos2);
}




void DrawEnemy2 (Object *object, SDL_Surface *surface, SDL_Surface *screen) {
    SDL_Rect pos1; //posicao no sprite ("recortar imagem")
    SDL_Rect pos2; //posicao no espaco apos movimento

    pos1.x = object->sx;
    pos1.y = object->sy;
    pos1.w = object->w;
    pos1.h = object->h;


    //verificando posicao do inimigo em relacao ao personagem
    if (hunter.x - object->x > 0)
        object->vx = 1;

    else if (hunter.x - object->x < 0)
        object->vx = -1;

    else
        object->vx = 0;


    if (hunter.y - object->y > 0)
        object->vy = 1;

    else if (hunter.y - object->y < 0)
        object->vy = -1;

    else
        object->vy = 0;

    CollisionType22(object, screen);    

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



void DrawEnemy3 (Object *object, SDL_Surface *surface, SDL_Surface *screen) {
    SDL_Rect pos1; //posicao no sprite ("recortar imagem")
    SDL_Rect pos2; //posicao no espaco apos movimento

    pos1.x = object->sx;
    pos1.y = object->sy;
    pos1.w = object->w;
    pos1.h = object->h;


    int numRad = rand()%100;
    if (numRad  == 1)
        if (fireBall.st != 0 && fireBall.nB > 0)
            fireBall.st++;

    if (fireBall.st == 2) { //arrumar essa parte - o inimigo nao esta produzindo fireBall
        Shooting(&fireBall, object, 12);
        Direction(object);
    }

    else {
        //nova posicao
        object->x += object->vx * object->v;
        object->y += object->vy * object->v;
    }

    pos2.x = object->x;
    pos2.y = object->y;
    pos2.w = object->w;
    pos2.h = object->h;

    surface = Collision(object, surface, screen);


    //atualizar tela
    SDL_BlitSurface(surface, &pos1, screen, &pos2);
}



void Direction (Object *object) {
    int dir;
    int N = 2, NE = 3, E = 4, SE = 5, S = 6, SO = 7, O = 0, NO = 1;

    if (object->vx == 1 && object->vy == 1) //Sudeste
        dir = SE;

    else if (object->vx == 1 && object->vy == 0) //Leste
        dir = E;

    else if (object->vx == 1 && object->vy == -1) //Nordeste
        dir = NE;    

    else if (object->vx == 0 && object->vy == 1) //Sul
        dir = S;

    else if (object->vx == 0 && object->vy == -1) //Norte
        dir = N;

    else if (object->vx == -1 && object->vy == 1) //Sudoeste
        dir = SO;

    else if (object->vx == -1 && object->vy == 0) //Oeste
        dir = O;

    else if (object->vx == -1 && object->vy == -1) //Noroeste
        dir = NO;


    int k = fireBall.nB;
    if (k == nObject)
        k = 0;

    fireBall.setup[k].sy = dir * hFireBall;
}




void UpdateSprite (Object *object, int w, int h) {
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