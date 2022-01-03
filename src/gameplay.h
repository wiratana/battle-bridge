#ifndef GAMEPLAY_H
#define GAMEPLAY_H

struct bullet{
    int speed;
    int status;
    int isFire;
};

struct enemy{
    int status;
    int speed;
    struct bullet ebullet;
};

struct player{
    int speed;
    struct bullet pbullet;
};

void setGameplayVariable();
void gameplay();
void updateGameplayVariable();

#endif
