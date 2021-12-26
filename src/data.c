#include "data.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void getData(const char* path, char* data, int row)
{
    FILE *file = fopen(path, "r");
    char buff[1024];
    if(file){
        strcpy(data,"");
        for(int i = 0;  i < row; i++){
            strcpy(buff,"");
            fgets(buff, sizeof(buff), file);
            strcat(data, buff);
        }
    } else
        printf("error can't load file");
    fclose(file);
}

void insert(const char* path, char* data)
{
    FILE *file = fopen(path, "a");
    if(file){
        fprintf(file, "%s\n", data); 
    } else
        printf("error can't load file");
    fclose(file);
}

void sortChamp(const char* source, const char* destination){
    FILE *srcFile = fopen(source, "r");
    FILE *dstFile = fopen(destination, "w");
    char x_buff[255];
    char y_buff[255];
    char z_buff[255];
    char result[512];
    char chmp[3][255];
    int changedRank = 0;

    if(srcFile && dstFile){
        for(int i = 0; i < 3; i++) strcpy(chmp[i], "");
        while(fgets(x_buff, sizeof(x_buff), srcFile)){
            changedRank = 0;
            if(strcmp(chmp[0], "") == 0)
                strcpy(chmp[0], x_buff);
            else if(strcmp(chmp[1], "") == 0)  
                strcpy(chmp[1], x_buff);
            else if(strcmp(chmp[2], "") == 0)
                strcpy(chmp[2], x_buff);
            else{
                printf("0 %d\n 1 %d\n 2 %d\n", atoi(chmp[0]), atoi(chmp[1]), atoi(chmp[2]));
                if(atoi(chmp[0]) < atoi(x_buff) && changedRank == 0){
                    strcpy(y_buff, chmp[0]);
                    strcpy(chmp[0], x_buff);
                    changedRank = 1;
                }

                if(atoi(chmp[1]) < atoi(x_buff)  && changedRank == 0){
                    strcpy(y_buff, chmp[1]);
                    strcpy(chmp[1], x_buff);
                    changedRank = 2;
                }

                if(atoi(chmp[2]) < atoi(x_buff) && changedRank == 0){
                    strcpy(chmp[2], x_buff);
                }

                if(atoi(chmp[1]) < atoi(y_buff) && changedRank == 1){
                    strcpy(z_buff, chmp[1]);
                    strcpy(chmp[1], y_buff);
                    changedRank = 1;
                }

                if(atoi(chmp[2]) < atoi(z_buff) && changedRank == 1){
                    strcpy(chmp[2], z_buff);
                }

                if(atoi(chmp[2]) < atoi(y_buff) && changedRank == 2){
                    strcpy(chmp[2], y_buff);
                }
            }
        }
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3-1; j++){
                if(atoi(chmp[i]) < atoi(chmp[i+1])){
                    strcpy(x_buff, chmp[i]);
                    strcpy(chmp[i], chmp[i+1]);
                    strcpy(chmp[i+1], x_buff);
                }
            }
        }
        for(int i = 0; i < 3; i++){
            if(chmp[i]){
                strcat(result, chmp[i]);
            }
        }

        fprintf(dstFile, "%s", result);
    } else
        printf("error can't load file");
    fclose(srcFile);
    fclose(dstFile);
}
