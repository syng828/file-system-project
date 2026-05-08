#include <stdio.h>
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

    return 0;
}