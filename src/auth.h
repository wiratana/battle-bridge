#ifndef AUTH_H
#define AUTH_H

struct user{
    char username[100];
};

void setAuthVariable();    
void auth();
void authOption();
void form();
void authProcess();
#endif 
