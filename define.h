#define WSCREEN 800 //640
#define HSCREEN 600 //480
#define BPP 16
#define FPS 24

#define FONTSIZE 24

#define BORDERRIGHT 800 //748
#define BORDERLEFT 0 //52
#define BORDERUP 0 //70
#define BORDERDOWN 600 //585

//comprimento vetor caminho sprites
#define text 30
#define imgLife "sprite/hp.png"


//Personagem principal
#define wHunter 60 //largura personagem
#define hHunter 55 //altura personagem
#define vHunter 5 //velocidade personagem
#define posBeginX 0
#define posBeginY 0
#define nHunterLife 10
#define imgPersonage "sprite/doc.png"



//definicoes imagem contendo os sprites personagejm principal
#define down 0//10 //numero da linha de cada posicao
#define up 1//8
#define left 2//9
#define right 3//11
#define nSprites 5//9 //numero de sprites por posicao



//definicoes imagem contendo os sprites explosao
#define explRow 5 
#define explCol 5
#define explW 64
#define explH 64
#define imgExplosion "sprite/explosion17.png" 



//cor de fundo - padrao RGB
#define colorR 255
#define colorG 0
#define colorB 255



//numero de fases
#define nStage 3

//FASE 1
#define nEf1 12 //numero de inimigos na fase - deve ser multiplo do numero de elementos na pilha
#define nTf1 1 //numero de tipos de inimigos
#define imgBack1 "sprite/back1.jpg"
#define imgBegin1 "sprite/round1.jpg"

//FASE 2
#define nEf2 12 //numero de inimigos na fase
#define nTf2 2 //numero de tipos de inimigos
#define imgBack2 "sprite/back2.jpg"
#define imgBegin2 "sprite/round2.jpg"

//FASE 3
#define nEf3 12 //numero de inimigos na fase
#define nTf3 3 //numero de tipos de inimigos
#define imgBack3 "sprite/back3.jpg"
#define imgBegin3 "sprite/round3.jpg"




//numeros de objetos na pilha
#define nObject 24



//para adicionar uma arma, alterar arquivo load.c
//numero de armas
#define nGuns 3

//conf do projetil
#define wBullet1 7 //largura
#define hBullet1 16 //altura
#define vBullet1 15 //velocidade
#define nBulletLife1 1
#define imgBullet1 "sprite/pilula.png"

//conf do projetil
#define wBullet2 7 //largura
#define hBullet2 16 //altura
#define vBullet2 15 //velocidade
#define nBulletLife2 1
#define imgBullet2 "sprite/pilula.png"

//conf do projetil
#define wBullet3 7 //largura
#define hBullet3 16 //altura
#define vBullet3 15 //velocidade
#define nBulletLife3 1
#define imgBullet3 "sprite/pilula.png"




//para adicionar um inimigo, alterar arquivo load.c
//numero de inimigos
#define nEnemy 3

//definicoes imagem contendo os sprites inimmigos
#define DE 10 //numero da linha de cada posicao
#define UE 8
#define LE 9
#define RE 11
#define nSE 9 //numero de sprites por posicao


//conf do inimigo 1
#define wEnemy1 64 //largura
#define hEnemy1 64 //altura
#define vEnemy1 3 //velocidade
#define nEnemyLife1 1 //numero de vidas
#define imgEnemy1 "sprite/enemy1.png"


//conf do inimigo 2
#define wEnemy2 64//48 //largura
#define hEnemy2 64 //75 //altura
#define vEnemy2 2 //velocidade
#define nEnemyLife2 2 //numero de vidas
#define imgEnemy2 "sprite/enemy2.png"


//conf do inimigo 3
#define wEnemy3 64 //largura
#define hEnemy3 64 //altura
#define vEnemy3 2 //velocidade
#define nEnemyLife3 1 //numero de vidas
#define imgEnemy3 "sprite/enemy3.png"



//GATE - WARNIN
#define nrow 2 //1 ou 2
#define ncol 3 //valor fixo
#define ngates 4 //valor fixo


//"Arma" inimigo
#define wFireBall 64 //largura
#define hFireBall 64 //altura
#define vFireBall 5 //velocidade
#define nLifeFireBall 1
#define imgFireBall "sprite/fireball.png"