#include "auth.h"
#include "helper.h"
#include "game.h"
#include "data.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Renderer* renderer;
extern int doesInput;
extern int currentPage;
static TTF_Font* font;
static SDL_Color color;
static SDL_Texture* background;
static SDL_Texture* gameTitle;
static SDL_Texture* loginOption;
static SDL_Texture* registerOption;
static SDL_Texture* usernameForm;
static SDL_Texture* passwordForm;
static SDL_Texture* loginLabelForm;
static SDL_Texture* registerLabelForm;
static SDL_Texture* errorMessage;
static SDL_Rect srcGameTitle;
static SDL_Rect dstGameTitle;
static SDL_Rect dstLoginOption;
static SDL_Rect dstRegisterOption;
static SDL_Rect dstUsernameForm;
static SDL_Rect dstPasswordForm;
static SDL_Rect dstErrorMessage;
static SDL_Rect dstLabelForm;

int displayIt = 1;
int selectedOption = 0;
int selectedForm   = 0;
char usernameFormContent[100];
char passwordFormContent[100];
char inputUsername[50];
char inputPassword[50];
char authError[255];
char buffer[525];
int currentProcess;

void setAuthVariable()
{
    font        = TTF_OpenFont("res/font/UbuntuMono-Regular.ttf", 24);
    color.r     = 0;
    color.g     = 20;
    color.b     = 190;
    background  = loadTexture(loadSurface("res/image/background.jpg")); 
    gameTitle   = loadTexture(loadSurface("res/image/game_title.png"));
    loginLabelForm = loadTexture(loadTextSurface(font,"Login", &color));
    registerLabelForm = loadTexture(loadTextSurface(font,"Register", &color));
    srcGameTitle.x = 0;
    srcGameTitle.y = 0;
    srcGameTitle.w = 500;
    srcGameTitle.h = 108;
    dstGameTitle.x = (WINDOW_WIDTH - 500)/2;
    dstGameTitle.y = 20;
    dstGameTitle.w = 500;
    dstGameTitle.h = 108;
    dstLoginOption.x = (WINDOW_WIDTH - 200)/2;
    dstLoginOption.y = (WINDOW_HEIGHT - 300);
    dstLoginOption.w = 200;
    dstLoginOption.h = 32;
    dstRegisterOption.x = (WINDOW_WIDTH - 200)/2;
    dstRegisterOption.y = (WINDOW_HEIGHT - 200);
    dstRegisterOption.w = 200;
    dstRegisterOption.h = 32;
    dstUsernameForm.x = (WINDOW_WIDTH - 500)/2;
    dstUsernameForm.y = (WINDOW_HEIGHT - 200);
    dstUsernameForm.w = 500;
    dstUsernameForm.h = 32;
    dstPasswordForm.x = (WINDOW_WIDTH - 500)/2;
    dstPasswordForm.y = (WINDOW_HEIGHT - 100);
    dstPasswordForm.w = 500;
    dstPasswordForm.h = 32;
    dstLabelForm.x = (WINDOW_WIDTH - 500)/2;
    dstLabelForm.y = (WINDOW_HEIGHT - 400);
    dstLabelForm.w = 500;
    dstLabelForm.h = 32;
    dstErrorMessage.x = (WINDOW_WIDTH - 500)/2;
    dstErrorMessage.y = (WINDOW_HEIGHT - 300);
    dstErrorMessage.w = 500;
    dstErrorMessage.h = 32;
    currentProcess = 0;
    authError[0] = '\0';
}

void auth()
{
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, gameTitle, &srcGameTitle, &dstGameTitle);
    printf("%d", currentProcess);
    switch(currentProcess){
        case 0:
            authOption();
            break;
        case 1:
            form();
            break;
        default:
            break;
    }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
}

void authOption()
{ 
    if(doesInput || displayIt){
        loginOption = loadTexture(loadTextSurface(font,((selectedOption == 0) ? "Login <<" : "Login"), &color)); 
        registerOption = loadTexture(loadTextSurface(font,((selectedOption == 1) ? "Register <<" : "Register"), &color)); 
        doesInput = 0;
        displayIt = 0;
    }
    SDL_RenderCopy(renderer, loginOption, NULL, &dstLoginOption);
    SDL_RenderCopy(renderer, registerOption, NULL, &dstRegisterOption);
}

void form()
{
    SDL_RenderCopy(renderer, ((selectedOption)?registerLabelForm:loginLabelForm), NULL, &dstLabelForm);

    if(strlen(authError) > 0){
        errorMessage = loadTexture(loadTextSurface(font, authError, &color));
        SDL_RenderCopy(renderer, errorMessage, NULL, &dstErrorMessage);
    }
    if(doesInput || displayIt){      
        sprintf(usernameFormContent, "Username : %s", inputUsername);
        sprintf(passwordFormContent, "Password : %s", inputPassword);
        usernameForm = loadTexture(loadTextSurface(font, usernameFormContent, &color));
        passwordForm = loadTexture(loadTextSurface(font, passwordFormContent, &color));
        doesInput = 0;
        displayIt = 0;
    }

    SDL_RenderCopy(renderer, usernameForm, NULL, &dstUsernameForm);
    SDL_RenderCopy(renderer, passwordForm, NULL, &dstPasswordForm);
}

void login()
{
    form();
}

void registration()
{
    form(); 
}

void authProcess()
{
    authError[0] = '\0';
    if(strlen(inputUsername) <= 0)
        strcpy(authError, "Username is empty");
    else
    if(strlen(inputPassword) <= 0)
        strcpy(authError, "Password is empty");
    else
    if(selectedOption == 0 && !(strtok(getSpecificData("data/user.txt", inputUsername), ":")))
        strcpy(authError, "Your account is not registered");
    else
    if(selectedOption == 0 && strcmp(getAnotherSide(getSpecificData("data/user.txt", inputUsername), ":"), strcat(inputPassword,"\n")) != 0)
        strcpy(authError, "Your password don't match with our record");
    else{
        if(selectedOption == 0)
            currentPage++;
        if(selectedOption == 1){
            sprintf(buffer, "%s:%s", inputUsername, inputPassword);
            insert("data/user.txt", buffer);
            selectedOption--;
        }
    }
    inputUsername[0] = '\0';
    inputPassword[0] = '\0';
}
