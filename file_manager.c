#include <stdio.h>
#include <string.h>
#include "file_manager.h"

File files[MAX_FILES];
int fileCount = 0;

void createFile(char name[]) {
    strcpy(files[fileCount].name, name);
    files[fileCount].content[0] = '\0';
    files[fileCount].isOpen = 0;

    fileCount++;

    printf("File '%s' created.\n", name);
}

void openFile(char name[]) {
    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i].name, name) == 0) {
            files[i].isOpen = 1;
            printf("File '%s' opened.\n", name);
            return;
        }
    }

    printf("File not found.\n");
}

void closeFile(char name[]) {
    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i].name, name) == 0) {
            files[i].isOpen = 0;
            printf("File '%s' closed.\n", name);
            return;
        }
    }

    printf("File not found.\n");
}

void writeToFile(char name[], char text[]) {
    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i].name, name) == 0) {

            if(files[i].isOpen == 0) {
                printf("Cannot write. File is closed.\n");
                return;
            }

            strcat(files[i].content, text);
            printf("Written to '%s'.\n", name);
            return;
        }
    }

    printf("File not found.\n");
}

void readFile(char name[]) {
    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i].name, name) == 0) {

            if(files[i].isOpen == 0) {
                printf("Cannot read. File is closed.\n");
                return;
            }

            printf("Content of '%s':\n%s\n", name, files[i].content);
            return;
        }
    }

    printf("File not found.\n");
}

int searchFile(char name[]) {
    for(int i = 0; i < fileCount; i++) {
        if(strcmp(files[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

void listFiles() {
    printf("\nFiles:\n");

    for(int i = 0; i < fileCount; i++) {
        printf("%s [%s]\n",
               files[i].name,
               files[i].isOpen ? "Open" : "Closed");
    }
}
