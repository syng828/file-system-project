#include <stdio.h>
<<<<<<< HEAD
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
=======
#include "file_manager.h"

int main() {
    int choice;

    while (1) {
        printf("\n===== File Management System =====\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Search File\n");
        printf("5. List Files\n");
        printf("6. Show File Details\n");
        printf("7. Delete File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
    
         // Clear input buffer
        while (getchar() != '\n');

        continue;
        }


        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                writeToFile();
                break;
            case 3:
                readFile();
                break;
            case 4:
                searchFile();
                break;
            case 5:
                listFiles();
                break;
            case 6:
                showFileDetails();
                break;
            case 7:
                deleteFile();
                break;
            case 8:
                printf("Exiting File Management System.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

>>>>>>> 4071e4a (Added file management system project (multi-file version))
    return 0;
}