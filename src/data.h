#ifndef DATA_H
#define DATA_H

void getData(const char *path, char *data, int row);
void insert(const char *path, char *data);
void sortChamp(const char* source, const char* destination);
char* getSpecificData(const char *path, char *comparator);
char* getAnotherSide(char *data, char *separator);

#endif
