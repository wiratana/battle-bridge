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
static SDL_Texture* bulletG;
static SDL_Texture* score;
static SDL_Rect dstBackground;
static SDL_Rect dstBridge;
static SDL_Rect dstShip[3];
static SDL_Rect dstBullet;
static SDL_Rect dstScore;
static char buffForPath[512];

SDL_Rect dstTank;
int lastScore = 0;
char buffForScore[11];
char buffForLog[512];
struct enemy enemies[3];
struct player player;
struct bullet bullet;
int isFire;
int gameOver;
int randSpeed[2] = {1, 2};
time_t now;

void setGameplayVariable(){
    lastScore = 0;
    isFire = 0;
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
    bulletG = loadTexture(clearBackground(loadSurface("res/image/bullet.png"),&white));
    sprintf(buffForScore, "%d", lastScore);
    score = loadTexture(loadTextSurface(font,buffForScore,&color));
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
    dstScore.w = 75;
    dstScore.h = 50;
    int enemyDistance = 125;
    for(int i = 0; i < 3; i++){
        dstShip[i].x = 220+i*enemyDistance;
        dstShip[i].y = 0;
        dstShip[i].w = 50;
        dstShip[i].h = 75;
        enemies[i].status = 1;
        enemies[i].speed = 1;
    }
    player.speed = 4;
    bullet.status = 0;
    bullet.speed = 7;
}

void gameplay()
{
    SDL_RenderCopy(renderer, background, NULL, &dstBackground); 
    SDL_RenderCopy(renderer, bridge, NULL, &dstBridge); 
    SDL_RenderCopy(renderer, tank, NULL, &dstTank); 
    SDL_RenderCopy(renderer, score, NULL, &dstScore);
    for(int i = 0; i < 3; i++){
        SDL_RenderCopy(renderer, ship, NULL, &dstShip[i]); 
    } 
    if(bullet.status)
        SDL_RenderCopy(renderer, bulletG, NULL, &dstBullet); 
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
               ((dstBullet.y + dstBullet.h/2) <= (dstShip[i].y + dstShip[i].h))){
                bullet.status = 0;
                dstShip[i].y = -dstShip[i].h;
                enemies[i].speed = randSpeed[rand()%2];
                lastScore += 1;
                sprintf(buffForScore, "%d", lastScore);
                score = loadTexture(loadTextSurface(font,buffForScore,&color));
            }
        }
 
        if(isFire == 1){
            dstBullet.x = dstTank.x + dstTank.w;
            dstBullet.y = dstTank.y + (dstTank.w-dstBullet.w)/2;
            isFire = 0;
        }
 
        if(bullet.status)
            dstBullet.x += bullet.speed;
 
        if(dstBullet.x >= WINDOW_WIDTH-dstBullet.w)
            bullet.status = 0;
 
        if(gameOver){
            currentPage++;
	    time(&now);
	    sprintf(buffForLog, "%s | %d | %s", playerInfo.username, lastScore, ctime(&now));
	    sprintf(buffForPath, "data/%d.txt", getID("data/user.txt",playerInfo.username));
	    insert(buffForPath, buffForLog);
	    prepareData(); 
	    setGameplayVariable();
	}
    }
}
