#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "header.h"
#include "define.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>



void CreateStage(int beginStage, int pts) {
    //carregando fase
    stages.index = beginStage - 1;
    stages.status = 1;
    stages.pts = pts;
    Stage *p = &stages.stage[stages.index];

    p->nS = beginStage;
    p->nD = 0;


    soundExplosion = Mix_LoadWAV("music/explosao.wav");
    soundGun = Mix_LoadWAV("music/gun.wav");
    soundDeath = Mix_LoadWAV("music/morte.wav");
    soundMenu = Mix_LoadWAV("music/menu.wav");

}


void CreateEnemy() {
    for (enemies.index = 0; enemies.index < nEnemy; enemies.index++) {
        //carregando inimigo
        enemies.surface[enemies.index] = Sprite(enemies.enemy[enemies.index].img, 0, colorR, colorG, colorB);
        enemies.enemy[enemies.index].nB = nObject; //numero de inimigos padrao
        //enemies.enemy[enemies.index].st = 1; //status do inimigo
    }
}



void Create() {
    //carregando personagem
    surfacePersonage = Sprite(imgPersonage, 0, 0, 0, 0); //cor fundo (255, 0, 255) - 0 sem background, 1 com background
    hunter.x = posBeginX;
    hunter.y = posBeginY;
    hunter.w = wHunter;
    hunter.h = hHunter;
    hunter.v = vHunter;
    hunter.vx = 0;
    hunter.vy = 0;
    hunter.sx = 0;
    hunter.sy = hHunter * right;
    hunter.dx = 1;
    hunter.dy = 0;
    hunter.type = 0;
    hunter.status = nHunterLife;

    //carregando armamento
    guns.index = 0; //tipo da arma selecionada - primeira arma.
    surfaceBullet = Sprite(guns.gun[guns.index].img, 0, colorR, colorG, colorB);
    guns.gun[guns.index].nB = nObject; //numero de municoes padrao
    guns.gun[guns.index].st = 1; //status da arma - selecionada

    //carregando "arma" inimigo
    fireBall.nB = nObject;
    fireBall.st = 1;
    fireBall.width = wFireBall;
    fireBall.height = hFireBall;
    fireBall.speed = vFireBall;
    fireBall.life = nLifeFireBall;
    strcpy(fireBall.img, imgFireBall);
    surfaceFireball = Sprite(fireBall.img, 0, colorR, colorG, colorB);
}




SDL_Surface* Sprite (char *file, int background, int r, int g, int b) {
    SDL_Surface *surface = NULL;
    if (background) {
        //carregando surface
        int colorkey;
        SDL_Surface *temp;


        temp = IMG_Load(file);
        if (temp == NULL) {
            temp = SDL_LoadBMP(file);
            if(temp == NULL) {
                printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
                exit(0);
            }
        }
        surface = SDL_DisplayFormat(temp);
        SDL_FreeSurface(temp);

        /* setup surface colorkey and turn on RLE */
        colorkey = SDL_MapRGB(screen->format, r, g, b);
        SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    }

    else {
        surface = IMG_Load(file);
        if (surface == NULL) {
            surface = SDL_LoadBMP(file);
            if(surface == NULL) {
                printf("Erro ao carregar a imagem: %s  - name: %s\n", IMG_GetError(), file);
                exit(0);
            }
        }
    }

    return surface;
}



void Clear() {
    //liberando superficies
    int index;
    for (index = 0; index < nEnemy; index++) 
        SDL_FreeSurface(enemies.surface[index]);
    SDL_FreeSurface(surfaceFireball);
    SDL_FreeSurface(surfaceBullet);
    SDL_FreeSurface(surfacePersonage);
    SDL_FreeSurface(surfaceBackground);
    SDL_FreeSurface(screen);
    Mix_FreeMusic(music);
    Mix_FreeChunk(soundExplosion);
    Mix_FreeChunk(soundGun);
    Mix_FreeChunk(soundDeath);
    Mix_FreeChunk(soundMenu);
    TTF_CloseFont(fontMenu);
    TTF_CloseFont(fontGame);
}