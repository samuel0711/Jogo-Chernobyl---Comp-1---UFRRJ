#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "header.h"
#include "define.h"
#include <SDL/SDL_ttf.h>


//definicoes do usuarios
void Load() {
	int i;


	//definicoes armas
	int vecWidth[nGuns] = {wBullet1, wBullet2, wBullet3};
	int vecHeight[nGuns] = {hBullet1,hBullet2, hBullet3};
	int vecSpeed[nGuns] = {vBullet1,vBullet2, vBullet3};
	int vecLife[nGuns] = {nBulletLife1, nBulletLife2, nBulletLife3};

	char vecImg[nGuns][text];
	strcpy(vecImg[0], imgBullet1);
	strcpy(vecImg[1], imgBullet2);
	strcpy(vecImg[2], imgBullet3);




	//definicoes inimigos
	int vecWidth2[nGuns] = {wEnemy1, wEnemy2, wEnemy3};
	int vecHeight2[nGuns] = {hEnemy1,hEnemy2, hEnemy3};
	int vecSpeed2[nGuns] = {vEnemy1,vEnemy2, vEnemy3};
	int vecLife2[nGuns] = {nEnemyLife1, nEnemyLife2, nEnemyLife3};
	
	char vecImg2[nGuns][text];
	strcpy(vecImg2[0], imgEnemy1);
	strcpy(vecImg2[1], imgEnemy2);
	strcpy(vecImg2[2], imgEnemy3);




	//definicoes fases
	char vecImg3[nStage][text];
	strcpy(vecImg3[0], imgBack1);
	strcpy(vecImg3[1], imgBack2);
	strcpy(vecImg3[2], imgBack3);	

	char vecImg4[nStage][text];
	strcpy(vecImg4[0], imgBegin1);
	strcpy(vecImg4[1], imgBegin2);
	strcpy(vecImg4[2], imgBegin3);

    int vecNT[nStage] = {nTf1, nTf2, nTf3};
    int vecNE[nStage] = {nEf1, nEf2, nEf3};










	for (i = 0; i < nGuns; i++) {
		guns.gun[i].width = vecWidth[i];
		guns.gun[i].height = vecHeight[i];
		guns.gun[i].speed = vecSpeed[i];
		guns.gun[i].life = vecLife[i];
		strcpy(guns.gun[i].img, vecImg[i]); 
	}


	for (i = 0; i < nEnemy; i++) {
		enemies.enemy[i].width = vecWidth2[i];
		enemies.enemy[i].height = vecHeight2[i];
		enemies.enemy[i].speed = vecSpeed2[i];
		enemies.enemy[i].life = vecLife2[i];
		strcpy(enemies.enemy[i].img, vecImg2[i]); 
		//enemies.surface[i] = vecSurface[i];
	}


	for (i = 0; i < nStage; i++) {
		stages.stage[i].nT = vecNT[i];
    	stages.stage[i].nE = vecNE[i];
		strcpy(stages.stage[i].img, vecImg3[i]); 
		strcpy(stages.imgbegin[i], vecImg4[i]); 
	}

}