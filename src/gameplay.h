#ifndef GAMEPLAY_H
#define GAMEPLAY_H

struct enemy{
    int status;
    int speed;
};

struct player{
    int speed;
};

struct bullet{
    int speed;
    int status;
};

void setGameplayVariable();
void gameplay();
void updateGameplayVariable();

#endif
