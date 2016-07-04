#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
#include "define.h"


void InstanceGun(Object*, Stack*, Object*, int);


void Shooting(Stack *stack, Object *generator, int type) { //recebe gun ou fireball
    Object *p;

    if (stack->st != 0) {
        stack->st--;
    	stack->nB--;

        p = &(stack->setup[stack->nB]);

        InstanceGun(p, stack, generator, type);

    	//DrawPersonage(p, surface, screen);

    	//tipo de arma 1 - disparo infinito
    	if (stack->nB == 0)
    		stack->nB = nObject;
	}

}


void InstanceGun(Object *object, Stack *stack, Object *generator, int type) {
	object->x = generator->x + (generator->w)/2;
    object->y = generator->y + (generator->h)/2;
    object->w = stack->width; //wBullet;
    object->h = stack->height; //hBullet;
	object->v = stack->speed; //vBullet;

    if (generator->vx == 0)
        object->vx = generator->dx;

    else
        object->vx = generator->vx;


    if (generator->vy == 0)
        object->vy = generator->dy;

    else
        object->vy = generator->vy;

    object->sx = 0;
    object->sy = 0;
    object->type = type;
    object->status = 1;
}
