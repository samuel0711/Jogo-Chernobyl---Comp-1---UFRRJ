#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "header.h"
#include "define.h"


int EventKeyboardGame(SDL_Event); 
void EventKeyboardHunter(SDL_Event); 
void KeyState(void);
void Update(int, int, int);// primeiro argumento: coluna do sprite, segundo e terceiro argumentos: direcao do movimento (vx e vy)


int EventKeyboard(SDL_Event event) {
    int quit = 0;

    if (SDL_PollEvent(&event)) {
        quit = EventKeyboardGame(event); //eventos do teclado controle do jogo
        if (!quit)
            EventKeyboardHunter(event); //eventos do teclado para personagem
    }

    else 
        KeyState();

    return quit;
}



int EventKeyboardGame(SDL_Event event) {
    int quit = 0;

    if (event.type == SDL_QUIT)
        quit = 1;

    //add demais teclas para controle do jogo
    else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit = 1;
                break;

            case SDLK_RETURN:
                pauseGame++;
                pauseGame = pauseGame % 2;
                break;

            default: break;
        }
    }
    return quit;
}


//       WARNING: ADD SPRITE DIAGONAL

void EventKeyboardHunter(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                if (guns.gun[guns.index].st != 0 && guns.gun[guns.index].nB > 0)
                    guns.gun[guns.index].st++;
                    Mix_PlayChannel(-1,soundGun,0);
                break;

            case SDLK_UP:
                Update(up, hunter.vx, -1);
                break;

            case SDLK_DOWN:
                Update(down, hunter.vx, 1);
                break;

            case SDLK_RIGHT:
                Update(right, 1, hunter.vy);
                break;

            case SDLK_LEFT:
                Update(left, -1, hunter.vy);
                break;

            default: break;
        }
    }

    else if (event.type == SDL_KEYUP) {
        SDLKey key = event.key.keysym.sym;

        if (key == SDLK_UP || key == SDLK_DOWN)
            hunter.vy = 0;

        else if (key == SDLK_RIGHT || key == SDLK_LEFT)
            hunter.vx = 0;
    }
}



void KeyState() {
    int i = 2;
    Uint8 *keystate = SDL_GetKeyState(&i);
 
    if (keystate[SDLK_RIGHT] && keystate[SDLK_LEFT]) {
        Update(right, 1, 0);
        hunter.vx = 0; 
        hunter.sx = 0;
    }

    else if (keystate[SDLK_UP] && keystate[SDLK_DOWN]) {
        Update(down, 0, 1);
        hunter.vy = 0;
        hunter.sx = 0;
    }

    else if (keystate[SDLK_UP] && keystate[SDLK_RIGHT])
        Update(up, 1, -1);

    else if (keystate[SDLK_UP] && keystate[SDLK_LEFT]) 
        Update(up, -1, -1);
    
    else if (keystate[SDLK_DOWN] && keystate[SDLK_RIGHT])
        Update(down, 1, 1);
    
    else if (keystate[SDLK_DOWN] && keystate[SDLK_LEFT])
        Update(down, -1, 1); 
    
    else if (keystate[SDLK_UP])
        Update(up, hunter.vx, -1);
    
    else if (keystate[SDLK_DOWN])
        Update(down, hunter.vx, 1);
    
    else if (keystate[SDLK_RIGHT])
        Update(right, 1, hunter.vy);
    
    else if (keystate[SDLK_LEFT])
        Update(left, -1, hunter.vy);
}




void Update(int index, int dirx, int diry) {
    hunter.sy = hHunter * index;
    hunter.sx += wHunter;
    if (hunter.sx == (nSprites - 1) * wHunter) //resetando a imagem p movimento
        hunter.sx = 0;

    hunter.vx = dirx;
    hunter.vy = diry;
    hunter.dx = dirx;
    hunter.dy = diry;
}





int EventMenu(SDL_Event event) {
    int quit = 0;
    static int option = 1;
    int nButton = 4;
    char image[4][20] = {"sprite/menu1.jpg", "sprite/menu2.jpg", "sprite/menu3.jpg", "sprite/menu4.jpg"};
    surfaceBackground = Sprite(image[option-1], 0, 0, 0, 0);
    SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            quit = 1;

        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RETURN:
                    optionMenu = option;
                    break;

                case SDLK_UP:
                    option--;
                    Mix_PlayChannel(-1,soundMenu,0);
                    break;

                case SDLK_DOWN:
                    option++;
                    Mix_PlayChannel(-1,soundMenu,0);
                    break;

                default: break;
            }
        }
        if (option < 1)
            option = nButton;

        else if (option > nButton)
            option = 1;
        //printf("%d\n", option);
        surfaceBackground = Sprite(image[option-1], 0, 0, 0, 0);
        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
    }

    return quit;
}




int EventPause (SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                exit(1);
                break;

            case SDLK_RETURN:
                pauseGame = 0;
                break;

            default: break;
        }
    }
    return 0;
}