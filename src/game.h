#ifndef GAME_H
#define GAME_H

// window setting
#define GAME_TITLE "Battle Bridge"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// gameplay
#define NUMBER_OF_ENEMIES 3

// load game
void game();

// core concept
void initEngine();
void initVariable();
void setGameVariable();
void updateLogic();
void controlHandling(); 

#endif
