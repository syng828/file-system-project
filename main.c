#include <stdio.h>
#include <string.h>

#define MAX_FILES 1000

struct File {
    char name[100];
    char content[1000];
    int isOpen; //0 for closed, 1 for open
};

struct File files[MAX_FILES];
int fileCount = 0;

int createFile(const char *name) {
    if (fileCount >= MAX_FILES) {
        printf("Error: Reached max file limit.\n");
        return -1;
    }
    strncpy(files[fileCount].name, name, sizeof(files[fileCount].name) - 1); // strncpy (destination, source, size) copies from source to destination 
    files[fileCount].content[0] = '\0'; 
    files[fileCount].isOpen = 0; 
    fileCount++;
    return fileCount - 1;  //returns the index of created file
}

int main() { 
    int fileIndex = createFile("example.txt");
    if (fileIndex != -1) {
        printf("File '%s' created successfully.\n", files[fileIndex].name);
    }
    return 0;
}