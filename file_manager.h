#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#define MAX_FILES 100
#define MAX_NAME 100
#define MAX_CONTENT 1000

typedef struct {
    char name[MAX_NAME];
    char content[MAX_CONTENT];
    int isOpen;
} File;

extern File files[MAX_FILES];
extern int fileCount;

void createFile(char name[]);
void openFile(char name[]);
void closeFile(char name[]);
void writeToFile(char name[], char text[]);
void readFile(char name[]);
void listFiles();
int searchFile(char name[]);

#endif
