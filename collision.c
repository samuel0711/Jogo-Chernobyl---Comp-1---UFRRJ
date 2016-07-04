#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
#include "define.h"

//prototipo da funcao
void Kill(Object*);
void CollisionType0(Object* object, SDL_Surface*);
SDL_Surface* CollisionType1(Object* object, SDL_Surface*, SDL_Surface*, int);
void CollisionType21(Object* object, SDL_Surface*);
int CollisionObjects (Object*, Object*);
void Score (int);


int borderRight = BORDERRIGHT;
int borderLeft = BORDERLEFT;
int borderUp = BORDERUP;
int borderDown = BORDERDOWN;



SDL_Surface* Collision(Object *object, SDL_Surface *surface, SDL_Surface *screen) {
    //limites da tela
    if (object->type == 0) //personagens pricipais
    	CollisionType0(object, screen);

    else if (object->type == 1 || object->type == 12) //bullet or fireball
		surface = CollisionType1(object, surface, screen, object->type);

    else if (object->type == 2) //inimigos
    	CollisionType21(object, screen);

    return surface;
}



//pode retirar o ponteiro screen
void CollisionType0(Object *object, SDL_Surface *screen) {
    if ((object->x + object->w) > borderRight) {
        object->vx = 0;
        object->x = borderRight - object->w;        
    }

    else if (object->x < borderLeft) {
        object->vx = 0;
        object->x = borderLeft;
    }

    if ((object->y + object->h) > borderDown) {
        object->vy = 0;
        object->y = borderDown - object->h; 
    }

    else if (object->y < borderUp) {
        object->vy = 0;
        object->y = borderUp;         
    }


    int i, j;
    for (j = 0; j < stages.stage[stages.index].nT; j++) {
	    for (i = 0; i < nObject; i++) {
	    	Object *p = &enemies.enemy[j].setup[i];
	    	if(CollisionObjects(object, p)) {
	    		object->status--;
	    		object->x = 0;
	    		object->y = 0;
        		Mix_PlayChannel(-1,soundDeath,0);
	    		break;
	    	}
	    }
	}
    //printf("%d\n", object->status);
    if (object->status == 0)
    	pauseGame = 2; //bloqueia todas as atualizacoes
}






SDL_Surface* CollisionType1(Object *object, SDL_Surface *surface, SDL_Surface *screen, int type) {
    if (object->status == 1) {
        if ((object->x + object->w) > borderRight) {
            Kill(object);
            object->x = borderRight - object->w;        
        }

        else if (object->x < borderLeft) {
            Kill(object);
            object->x = borderLeft;
        }

        if ((object->y + object->h) > borderDown) {
            Kill(object);
            object->y = borderDown - object->h; 
        }

        else if (object->y < borderUp) {
            Kill(object);
            object->y = borderUp;         
        }


        int i, j;
        if (type == 1)
	        for (j = 0; j < stages.stage[stages.index].nT; j++) { //j - tipo de inimigo
		        for (i = 0; i < nObject; i++) {
		        	Object *p = &enemies.enemy[j].setup[i];
		        	if(CollisionObjects(object, p)) {
			            Kill(object);
			            p->status--;
			            if (p->status == 0) {
				            Kill(p);
				            p->v = 0; //impede atualizacao do objeto na funcao DrawEnemy
				            p->x = screen->w + 1; //retirando da tela
			                p->y = screen->h + 1; //retirando da tela
			                stages.stage[stages.index].nD++; //diminui o numero de inimigo da fase
			                Score(j);

			                if (stages.stage[stages.index].nD == nObject/(3 - nrow)) {
			                	stages.stage[stages.index].nD = 0;
			                	stages.status = 1;
			                }
			                //printf("%d %d \n", stages.stage[stages.index].nD, stages.status);

			            }
		        		break;
		        	}
		        }
	    	}
    }

    else if (object->status == 0){
        int vExpl = 4; //velocidade explosao
        surface = Sprite(imgExplosion, 0, 0, 0, 0);
        object->sx += vExpl * explW;
        if (object->sx >= explW * explRow) {
            object->sx = 0;
            object->sy += explH;
            if (object->sy == explH * explCol) {
                object->v = 0; //na funcao DrawBullet bloqueia a atualizacao do objeto
                object->sy = (explCol - 1) * explH;

                object->x = screen->w + 1; //retirando da tela
                object->y = screen->h + 1; //retirando da tela
            }
        }
    }
    return surface;
}


void Kill(Object *object) {
    object->vx = object->vy = 0;
    object->status = 0;
    object->sx = object->sy = 0;
    object->w = explW;
    object->h = explH;
    Mix_PlayChannel(-1,soundExplosion,0);

}



void CollisionType21(Object *object, SDL_Surface *screen) {
	if ((object->x + object->w) > borderRight) {
	    object->vx = -object->vx;
	    object->x = borderRight - object->w;        
	}

	else if (object->x < borderLeft) {
	    object->vx = -object->vx;
	    object->x = borderLeft;
	}

	if ((object->y + object->h) > borderDown) {
	    object->vy = -object->vy;
	    object->y = borderDown - object->h; 
	}

	else if (object->y < borderUp) {
	    object->vy = -object->vy;
	    object->y = borderUp;         
	}

	int i, j;
	for (j = 0; j < stages.stage[stages.index].nT; j++) {
	    for (i = 0; i < nObject; i++) {
	    	Object *p = &enemies.enemy[j].setup[i];
	    	if(CollisionObjects(object, p) && (object->x != p->x || object->y != p->y)) { //dei uma roubada p garantir que um objeto nao colida com "ele mesmo"
				object->vx = -object->vx;
				object->vy = -object->vy;
	    		break;
	    	}
	    }
	}


}


void CollisionType22(Object *object, SDL_Surface *screen) {
	if ((object->x + object->w) > borderRight) {
	    object->vx = -object->vx;
	    object->x = borderRight - object->w;        
	}

	else if (object->x < borderLeft) {
	    object->vx = -object->vx;
	    object->x = borderLeft;
	}

	if ((object->y + object->h) > borderDown) {
	    object->vy = -object->vy;
	    object->y = borderDown - object->h; 
	}

	else if (object->y < borderUp) {
	    object->vy = -object->vy;
	    object->y = borderUp;         
	}

	int i, j;
	for (j = 0; j < stages.stage[stages.index].nT; j++) {
	    for (i = 0; i < nObject; i++) {
	    	Object *p = &enemies.enemy[j].setup[i];
	    	if(CollisionObjects(object, p) && (object->x != p->x || object->y != p->y)) { //dei uma roubada p garantir que um objeto nao colida com "ele mesmo"
		
				p->vx = -p->vx;
				p->vy = -p->vy;
				// object->vx = 0; //-object->vx;
				// object->vy = 0; //-object->vy;
				object->vx = -1 + rand()%3; //-object->vx;
				object->vy = -1 + rand()%3; //-object->vy;	    		

				while (object->vx == 0 && object->vy == 0) {
					object->vx = -1 + rand()%3; //-object->vx;
					object->vy = -1 + rand()%3; //-object->vy;
				}
	    	}
	    }
	}


}




int CollisionObjects (Object *obj1, Object *obj2) {
    if ((obj1->x + obj1->w > obj2->x && obj1->x < obj2->x + obj2->w) &&
        (obj1->y + obj1->h > obj2->y && obj1->y < obj2->y + obj2->h)) {
    	return 1;
	}

	return 0;
}





void Score (int type) {
	stages.pts += (type+1) * 10;
}