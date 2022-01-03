#include "gameplay.h"
#include "helper.h" 
#include "game.h" 
#include "board.h"
#include "auth.h"
#include "data.h"

#include <stdio.h>
#include <SDL.h>
#include <time.h>

extern SDL_Renderer* renderer;
extern int currentPage;
extern struct user playerInfo;
static TTF_Font* font;
static SDL_Color color; 
static SDL_Color white; 
static SDL_Texture* background;
static SDL_Texture* bridge;
static SDL_Texture* tank;
static SDL_Texture* ship;
static SDL_Texture* playerBullet;
static SDL_Texture* enemyBullet;
static SDL_Texture* score;
static SDL_Texture* wave;
static SDL_Rect dstBackground;
static SDL_Rect dstBridge;
static SDL_Rect dstShip[3];
static SDL_Rect dstBullet;
static SDL_Rect dstEnemyBullet[3];
static SDL_Rect dstScore;
static SDL_Rect dstWave;
static char buffForPath[512];

SDL_Rect dstTank;
int lastScore;
int lastWave;
int waveCounter;
char buffForScore[11];
char buffForWave[11];
char buffForLog[512];
struct enemy enemies[3];
struct player player;
struct bullet bullet;
int gameOver;
int randSpeed[2] = {1, 2};
time_t now;

void setGameplayVariable(){
    lastScore = 0;
    lastWave = 0;
    waveCounter = 0;
    player.pbullet.isFire = 0;
    gameOver = 0;
    font = TTF_OpenFont("res/font/UbuntuMono-Regular.ttf", 24);
    color.r = 255;
    color.g = 255;
    color.b = 0;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    background = loadTexture(loadSurface("res/image/background_gameplay.jpg"));
    bridge = loadTexture(loadSurface("res/image/bridge.png"));
    tank = loadTexture(clearBackground(loadSurface("res/image/tank.png"),&white));
    ship = loadTexture(clearBackground(loadSurface("res/image/ship.png"),&white));
    playerBullet = loadTexture(clearBackground(loadSurface("res/image/bullet.png"),&white));
    enemyBullet = loadTexture(clearBackground(loadSurface("res/image/enemy_bullet.png"),&white));
    sprintf(buffForScore, "%d", lastScore);
    sprintf(buffForWave, "%d", lastWave);
    score = loadTexture(loadTextSurface(font,buffForScore,&color));
    wave = loadTexture(loadTextSurface(font,buffForWave,&color));
    dstBackground.x = 140;
    dstBackground.y = 0;
    dstBackground.w = 500;
    dstBackground.h = 480;
    dstBridge.x = 0;
    dstBridge.y = 0;
    dstBridge.w = 140;
    dstBridge.h = 480;
    dstTank.x = (140-75)/2;
    dstTank.y = 0;
    dstTank.w = 75;
    dstTank.h = 75;
    dstBullet.x = 0;
    dstBullet.y = 0;
    dstBullet.w = 25;
    dstBullet.h = 25; 
    dstScore.x = WINDOW_WIDTH-120;
    dstScore.y = 20;
    dstScore.w = 50;
    dstScore.h = 25;
    dstWave.x = WINDOW_WIDTH-120;
    dstWave.y = 50;
    dstWave.w = 50;
    dstWave.h = 25;
    int enemyDistance = 125;
    for(int i = 0; i < 3; i++){
        dstShip[i].x = 220+i*enemyDistance;
        dstShip[i].y = 0;
        dstShip[i].w = 50;
        dstShip[i].h = 75;
        enemies[i].status = 1;
        enemies[i].speed = 1;
        enemies[i].ebullet.status = 0;
        enemies[i].ebullet.speed = 4;
	dstEnemyBullet[i].x = 0;
	dstEnemyBullet[i].y = 0;
	dstEnemyBullet[i].w = 25;
	dstEnemyBullet[i].h = 25;
    }
    player.speed = 4;
    player.pbullet.status = 0;
    player.pbullet.speed = 7;
}

void gameplay()
{
    SDL_RenderCopy(renderer, background, NULL, &dstBackground); 
    SDL_RenderCopy(renderer, bridge, NULL, &dstBridge); 
    SDL_RenderCopy(renderer, tank, NULL, &dstTank); 
    SDL_RenderCopy(renderer, score, NULL, &dstScore);
    SDL_RenderCopy(renderer, wave, NULL, &dstWave);
    for(int i = 0; i < 3; i++){
        SDL_RenderCopy(renderer, ship, NULL, &dstShip[i]); 
    } 
    if(player.pbullet.status)
        SDL_RenderCopy(renderer, playerBullet, NULL, &dstBullet); 
    for(int i = 0; i < 3; i++){
	if(enemies[i].ebullet.status)
	    SDL_RenderCopy(renderer, enemyBullet, NULL, &dstEnemyBullet[i]); 
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/24);
}

void updateGameplayVariable()
{
    if(currentPage == 2){
        for(int i = 0; i < 3; i++){
            dstShip[i].y += enemies[i].speed;
 
            if(dstShip[i].y >= WINDOW_HEIGHT-dstShip[i].h/2)
                gameOver = 1;
 
            if(((dstBullet.x + dstBullet.w/2) >= (dstShip[i].x)) &&
               ((dstBullet.x + dstBullet.w/2) <= (dstShip[i].x + dstShip[i].w)) &&
               ((dstBullet.y + dstBullet.h/2) >= (dstShip[i].y)) &&
               ((dstBullet.y + dstBullet.h/2) <= (dstShip[i].y + dstShip[i].h)) && 
		player.pbullet.status == 1){
                player.pbullet.status = 0;
                dstShip[i].y = -dstShip[i].h;
                enemies[i].speed = randSpeed[rand()%2];
                lastScore += 1;
                sprintf(buffForScore, "%d", lastScore);
                score = loadTexture(loadTextSurface(font,buffForScore,&color));
            }

	    if(dstShip[i].y >= dstTank.y && dstShip[i].y <= (dstTank.y + dstTank.h) &&
		enemies[i].ebullet.status == 0){
		enemies[i].ebullet.isFire = 1;
		enemies[i].ebullet.status = 1;
	    }

	    if(enemies[i].ebullet.isFire){
		dstEnemyBullet[i].x = dstShip[i].x;
		dstEnemyBullet[i].y = dstShip[i].y + (dstShip[i].w-dstEnemyBullet[i].w)/2;
		enemies[i].ebullet.isFire = 0;
	    } 

	    if(enemies[i].ebullet.status)
		dstEnemyBullet[i].x -= enemies[i].ebullet.speed;

	    if(dstEnemyBullet[i].x <= 0)
		enemies[i].ebullet.status = 0;

	    if(((dstEnemyBullet[i].x + dstEnemyBullet[i].w/2) >= (dstTank.x)) &&
               ((dstEnemyBullet[i].x + dstEnemyBullet[i].w/2) <= (dstTank.x + dstTank.w/2)) &&
               ((dstEnemyBullet[i].y + dstEnemyBullet[i].h/2) >= (dstTank.y)) &&
               ((dstEnemyBullet[i].y + dstEnemyBullet[i].h/2) <= (dstTank.y + dstTank.h)) && 
		enemies[i].ebullet.status == 1){
		enemies[i].ebullet.status = 0;
		gameOver = 1;
            }
        }
 
        if(player.pbullet.isFire == 1){
            dstBullet.x = dstTank.x + dstTank.w;
            dstBullet.y = dstTank.y + (dstTank.w-dstBullet.w)/2;
            player.pbullet.isFire = 0;
        }
 
        if(player.pbullet.status)
            dstBullet.x += player.pbullet.speed;
 
        if(dstBullet.x >= WINDOW_WIDTH-dstBullet.w)
            player.pbullet.status = 0;
 
        if(gameOver){
            currentPage++;
	    time(&now);
	    sprintf(buffForLog, "%s | %d | %d | %s", playerInfo.username, lastScore, lastWave, ctime(&now));
	    sprintf(buffForPath, "data/%d.txt", getID("data/user.txt",playerInfo.username));
	    insert(buffForPath, buffForLog);
	    prepareData(); 
	    setGameplayVariable();
	}
	
	if((waveCounter%1000)==0){
	    lastWave = waveCounter/1000;
	    sprintf(buffForWave, "%d", lastWave);
	    wave = loadTexture(loadTextSurface(font,buffForWave,&color));
	}
	waveCounter++;
    }
}
