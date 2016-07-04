#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
#include "define.h"



void Intro (void) {
    int i;
    const int dim = 5;
    int nlogo = 2;
    char image[5][30] = {"sprite/logo1.jpg", "sprite/logo2.jpg", "sprite/history1.jpg", "sprite/history2.jpg", "sprite/history3.jpg"};
    for (i = 0; i < nlogo; i++) {
        SDL_Rect pos = {screen->w/4, screen->h/4, screen->w/2, screen->h/2};
        SDL_Rect drect = {0, 0, screen->w, screen->h};
        SDL_FillRect(screen, &drect, SDL_MapRGB(screen->format, 255, 255, 255));

        surfaceBackground = Sprite(image[i], 0, 0, 0, 0);
        SDL_BlitSurface(surfaceBackground, NULL, screen, &pos);
        SDL_Flip(screen);

        SDL_Delay(1000);
    }

    music = Mix_LoadMUS("music/tema5.wav");
    if (music == NULL)
        printf("Mus: SDL error=%s\n", SDL_GetError());
    Mix_PlayMusic(music, -1);


    for (i = nlogo; i < dim; i++) {
        surfaceBackground = Sprite(image[i], 0, 0, 0, 0);
        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
        SDL_Flip(screen);

        SDL_Delay(2000);
    }

}




int Menu (void) {
    int quit = 0;
    quit = EventMenu(event);

    if (optionMenu == 1) {
        keyMenu = 1;
        surfaceBackground = Sprite("sprite/help.jpg", 0, 0, 0, 0);
        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(1000);

        //Carregando musica
        music = Mix_LoadMUS("music/tema.wav");
        if (music == NULL)
            printf("Mus: SDL error=%s\n", SDL_GetError());
        Mix_PlayMusic(music, -1);

        surfaceBackground = Sprite(stages.imgbegin[stages.index], 0, 0, 0, 0);
        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(1000);
    }
    if( optionMenu == 3)
    {
        surfaceBackground = Sprite("sprite/creditos.jpeg", 0, 0, 0, 0);
        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(2000);
        quit = 1;
        return quit;
    }

    else if (optionMenu == 4)
        quit = 1;

    return quit;
}

// void Menutop(char* texto, SDL_Surface* dst, int x, int y) {
//   SDL_Color cor = {0, 0, 0}; //preto
//   SDL_Surface* src = TTF_RenderText_Blended(fontMenu, texto, cor);
//   SDL_Rect dst_rect = {x, y, 0, 0};

//   SDL_BlitSurface(src, NULL, dst, &dst_rect);

//   SDL_FreeSurface(src);
// }2
