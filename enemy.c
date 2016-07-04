#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "header.h"
#include "define.h"


int gate = 1;

void InstanceEnemy(Object*, int, int);

void Enemy() {
    Object *p;
    int sum = 0;
    int i, j;

    

    while (gate <= ngates) {
        //printf("%d\n", stages.stage[stages.index].nE);

        for (i = 0; i < nrow; i++) {
            for (j = 0; j < ncol; j++) {
                enemies.index = rand()%stages.stage[stages.index].nT;
                if (enemies.enemy[enemies.index].nB > 0) { //&& p->status == 0
                    enemies.enemy[enemies.index].nB--;

                    p = &(enemies.enemy[enemies.index].setup[enemies.enemy[enemies.index].nB]);

                    InstanceEnemy(p, i, j);

                    stages.stage[stages.index].nE--;
                    sum++;
                }
            }
        }
        gate++;
    }
    gate = 1;
    stages.status = 0;
}


void InstanceEnemy(Object *object, int row, int col) {

    object->w = enemies.enemy[enemies.index].width; //wEnemy;
    object->h = enemies.enemy[enemies.index].height; //hEnemy;
    object->v = enemies.enemy[enemies.index].speed; //vEnemy;

    int gap = 70;
    int begin = 100;
    switch(gate) {
        case 1: //left
            object->x = begin - row * gap;
            object->y = (screen->h)/2 - (object->h)/2 - (object->h + 5) * (1 - col);

            object->vx = 1 - nrow * row;
            object->vy = -1 + col;

            break;


        case 2: //rigth
            object->x = screen->w - begin - row * gap;
            object->y = (screen->h)/2 - (object->h)/2 - (object->h + 5) * (1 - col);

            object->vx = 1 - nrow * row;
            object->vy = -1 + col;

            break;


        case 3: //up
            object->y = begin - row * gap;
            object->x = (screen->w)/2 - (object->w)/2 - (object->w + 5) * (1 - col);

            object->vy = 1 - nrow * row;
            object->vx = -1 + col;

            break;


        case 4: //down
            object->y = screen-> h - begin - row * gap;
            object->x = (screen->w)/2 - (object->w)/2 - (object->w + 5) * (1 - col);

            object->vy = 1 - nrow * row;
            object->vx = -1 + col;

            break;        
    }

    object->sx = 0;
    object->sy = 0;
    object->type = 2; //tipo - inimigo
    object->status = enemies.enemy[enemies.index].life; //vivo
}