#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "header.h"
#include "define.h"


int main(int argc, char** argv) {
    int quit = 0;
    int beginTime, endTime;
    int beginStage = 1, pts = 0;
    int permission = 1;
    keyMenu = 0; //definido no header
    optionMenu = 0;
    keyIntro = 0;
    pauseGame = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) return -1;
    if(TTF_Init() == -1) return -1;
    screen = SDL_SetVideoMode(WSCREEN, HSCREEN, BPP, SDL_SWSURFACE);// | SDL_ANYFORMAT | SDL_FULLSCREEN);
    SDL_WM_SetCaption("Chernobyl", "Jogo");
    //SDL_WM_GrabInput(!SDL_WM_GrabInput(SDL_GRAB_QUERY));  //segura o mouse

    fontGame = TTF_OpenFont("fonts/font2.ttf", FONTSIZE);
    TTF_SetFontStyle(fontGame, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);

    //Inicializando SDL_mixer
    if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        return 0;    

    //Mix_AllocateChannels(5);

    Intro(); //abertura do jogo - logo da empresa e história.

    //carregando elementos do jogo - definicoes do usuario
    Load();

    //iniciando fase
    CreateStage(beginStage, pts); //argumentos: num da fase, pontuacao e background

    //criando elementos do jogo
    Create();

    while(!quit) {
        beginTime = SDL_GetTicks(); //retorna a quantidade de milissegundos decorridos desde a inicialização da biblioteca.

        if (keyMenu == 0) {
            quit = Menu();
        }
            

        else if (keyMenu == 1) {
            //verificando eventos teclado
            quit = EventKeyboard(event);



            if (pauseGame == 1) { //pause
                surfaceBackground = Sprite("sprite/pause.jpg", 0, 0, 0, 0);
                SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
            }



            else if (pauseGame == 0) { //jogando
                //atualizando cenario
                surfaceBackground = Sprite(stages.stage[stages.index].img, 0, 0, 0, 0);
                SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
                Texto(screen);           

                if (stages.stage[stages.index].nE > 0 && stages.status == 1) {
                    //Intro();
                    CreateEnemy();
                    Enemy();
                }

                else if (stages.stage[stages.index].nE <= 0 && stages.status == 1) {
                    stages.index++;
                    //printf("%d\n", stages.index);
                    if (stages.index == nStage) { //verificando fim do jogo
                        quit = 1;
                        keyMenu = -1;
                        surfaceBackground = Sprite("sprite/fim.jpg", 0, 0, 0, 0);
                        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
                        Mix_PauseMusic();
                        SDL_Delay(3000);
                    }
                    else { //carregando imagem do numero da fase
                        surfaceBackground = Sprite(stages.imgbegin[stages.index], 0, 0, 0, 0);
                        SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
                        SDL_Flip(screen);
                        SDL_Delay(1000);
                        permission = 0;
                    }
                }

                if (stages.index < nStage && permission) {
                    //printf("%d\n", stages.index);
                    //atualizando elementos do jogo
                    if (guns.gun[guns.index].st == 2)
                        Shooting(&guns.gun[guns.index], &hunter, 1);
                    
                    DrawEnemy(screen);  
                    DrawBullet(surfaceFireball, screen, &fireBall); 
                    DrawBullet(surfaceBullet, screen, &guns.gun[guns.index]);
                    DrawPersonage(&hunter, surfacePersonage, screen);
                }
                permission = 1;
            }




            else if (pauseGame == 2) { //game over
                surfaceBackground = Sprite("sprite/gameover.jpg", 0, 0, 0, 0);
                SDL_BlitSurface(surfaceBackground, NULL, screen, NULL);
                Mix_PauseMusic();
                SDL_Delay(3000);
                keyMenu = -1;
                quit = 0;
            }
        }


        //atualizando tela
        SDL_Flip(screen);

        //Vefiricando e atualizando FPS
        endTime = SDL_GetTicks();
        if ((endTime - beginTime)*FPS < 1000) {
            SDL_Delay(1000/FPS - (endTime - beginTime));
            //printf("%d fps\n", 1000/(SDL_GetTicks() - beginTime));
        }
    }

    Clear();
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
