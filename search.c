#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "file_manager.h"

#define STORAGE_DIR "storage/"

// Searches for a file by checking directory entries
void searchFile() {
    char fileName[100];
    DIR *dir;
    struct dirent *entry;
    int found = 0;

    printf("Enter file name to search: ");
    scanf("%s", fileName);

    dir = opendir(STORAGE_DIR);

    if (dir == NULL) {
        perror("Error opening storage directory");
        return;
    }

    /*
       readdir() reads each file name inside the directory.
       strcmp() compares the user input with each file name.
    */
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, fileName) == 0) {
            found = 1;
            break;
        }
    }

    closedir(dir);

    if (found) {
        printf("File '%s' found in storage directory.\n", fileName);
    } else {
        printf("File '%s' not found.\n", fileName);
    }
}