#ifndef GAME_H
#define GAME_H

// window setting
#define GAME_TITLE "Battle Bridge"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// load game
void game();

// core concept
void initEngine();
void initVariable();
void updateLogic();
void controlHandling(); 

#endif
