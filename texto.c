#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
#include "define.h"



void Texto(SDL_Surface* dst) {
    SDL_Color cor = {255, 0, 0}; //preto

    char texto [30];
    sprintf(texto,"SCORE: %d", stages.pts);

    SDL_Surface *src = TTF_RenderText_Blended(fontGame, texto, cor);
    SDL_Rect dst_rect = {10, 10, 0, 0};

    SDL_BlitSurface(src, NULL, dst, &dst_rect);


    //imagem hp
    SDL_Surface *src2 = Sprite(imgLife, 0, 0, 0, 0);
    SDL_Rect dst_rect2 = {200, 10, 0, 0};

    SDL_BlitSurface(src2, NULL, dst, &dst_rect2);


    char texto2 [5];
    sprintf(texto2,"%d", hunter.status);

    SDL_Surface *src3 = TTF_RenderText_Blended(fontGame, texto2, cor);
    SDL_Rect dst_rect3 = {235, 10, 0, 0};

    SDL_BlitSurface(src3, NULL, dst, &dst_rect3);

    SDL_FreeSurface(src);
    SDL_FreeSurface(src2);
    SDL_FreeSurface(src3);
}



