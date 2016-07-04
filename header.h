#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "define.h"


TTF_Font* fontGame;
TTF_Font* fontMenu;

Mix_Music *music;
Mix_Chunk *soundGun, *soundExplosion;
Mix_Chunk *soundDeath;
Mix_Chunk *soundMenu;


SDL_Surface *screen;
SDL_Surface *surfaceBackground;
SDL_Surface *surfacePersonage;
SDL_Surface *surfaceBullet;
SDL_Surface *surfaceFireball;

SDL_Event event;

int keyMenu; //entrar e sair do menu para o jogo
int optionMenu;
int keyIntro; //chave para animacao de entrada inimigo
int pauseGame;

//int timeIN;
//int timeOUT;

//estrutura dos elementos tela (personagem, armas, inimigos, etc)
typedef struct OBJECT {
    int x, y; //posicao na tela
    int w, h; //largura e altura
    int v; //velocidade - constate p cada objeto
    int vx, vy; //sentido (-1 ou 1) do objeto. uso para velocidade
    int sx, sy; //selecionar sprite na imagem
    int dx, dy; //sentido do objeto. uso para disparos qd objeto parado
    int type; //tipo do objeto: 0 - player; 1 - bullet; 2 - enemy
    int status; //numero de vidas; 0 = morto
} Object;



// ======= WARNING ===== retirar variavel nB strutura STACK, criar uma variavel na estrutura GUNS

//estrutura da pilha de objetos
//status - 0: indisponível, 1: em uso, 2: disparo
typedef struct STACK {
    int nB; //numero de objetos
    int st; //status
    int width;
    int height;
    int speed;
    int life;
    char img[text];
    Object setup[nObject];
} Stack;


typedef struct GUNS {
    int index;
    Stack gun[nGuns];
} Guns;


typedef struct ENEMIES {
    int index;
    SDL_Surface *surface[nEnemy];
    Stack enemy[nEnemy];
} Enemies;


typedef struct STAGE {
    int nS; //numero da fase
    int nT; //numero de tipos de inimigos
    int nE; //numero de inimigos
    int nD; //numero de inimigos mortos
    //int pts; //pontos
    char img[text];   
} Stage;


typedef struct STAGES {
    int index;
    int status; //chave p produção de inimigos
    int pts;
    char imgbegin[nStage][text];
    Stage stage[nStage]; 
} Stages;



//Criando arma
Guns guns;

//poder 3º inimigo
Stack fireBall;

//Criando inimigos
Enemies enemies;

//Criando personagem
Object hunter;

//criando fases
Stages stages;

//Prototipos das funcoes
void Load(void);
void CreateStage(int, int);
void Create(void);
void CreateEnemy(void);
SDL_Surface* Sprite (char*, int, int, int, int);
void DrawBullet(SDL_Surface*, SDL_Surface*, Stack*);
void DrawEnemy(SDL_Surface*);
void DrawPersonage(Object*, SDL_Surface*, SDL_Surface*);
void Shooting(Stack*, Object*, int);
void Enemy();
int EventKeyboard(SDL_Event);
int EventMenu(SDL_Event);
int EventPause(SDL_Event);
SDL_Surface* Collision(Object*, SDL_Surface*, SDL_Surface*);
void Clear(void);

void CollisionType22(Object* object, SDL_Surface*);

void Texto(SDL_Surface*);
int Menu (void);
void Intro (void);
