#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 1000

struct File {
    char name[100];
    char content[1000];
    int isOpen;           // 0 for closed, 1 for open
    int size;             // number of bytes of content
    time_t modified_time; // last modified timestamp
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
    files[fileCount].size = 0;
    files[fileCount].modified_time = time(NULL);
    fileCount++;
    return fileCount - 1; // returns the index of created file
}

// Opens a file by setting isOpen to 1
void openFile() {
    char name[100];
    printf("Enter file name to open: ");
    scanf("%s", name);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].name, name) == 0) {
            if (files[i].isOpen == 1) {
                printf("File '%s' is already open.\n", name);
            } else {
                files[i].isOpen = 1;
                printf("File '%s' opened successfully.\n", name);
            }
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

// Closes a file by setting isOpen to 0
void closeFile() {
    char name[100];
    printf("Enter file name to close: ");
    scanf("%s", name);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].name, name) == 0) {
            if (files[i].isOpen == 0) {
                printf("File '%s' is already closed.\n", name);
            } else {
                files[i].isOpen = 0;
                printf("File '%s' closed successfully.\n", name);
            }
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

// Writes content to an open file
void writeToFile() {
    char name[100];
    char newContent[1000];

    printf("Enter file name to write to: ");
    scanf("%s", name);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].name, name) == 0) {
            if (files[i].isOpen == 0) {
                printf("Error: File '%s' is not open. Please open it first.\n", name);
                return;
            }
            printf("Enter content to write: ");
            getchar(); // clear leftover newline from scanf
            fgets(newContent, sizeof(newContent), stdin);

            // Check if appending would overflow the content buffer
            if (files[i].size + (int)strlen(newContent) >= 1000) {
                printf("Error: Not enough space in file.\n");
                return;
            }

            strncat(files[i].content, newContent, sizeof(files[i].content) - files[i].size - 1);
            files[i].size += strlen(newContent);
            files[i].modified_time = time(NULL);
            printf("Content written successfully.\n");
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

// Reads and prints the content of a file
void readFile() {
    char name[100];

    printf("Enter file name to read: ");
    scanf("%s", name);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].name, name) == 0) {
            if (files[i].isOpen == 0) {
                printf("Error: File '%s' is not open. Please open it first.\n", name);
                return;
            }
            printf("\n----- File Content -----\n");
            if (files[i].size == 0) {
                printf("File is empty.\n");
            } else {
                printf("%s\n", files[i].content);
            }
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

// Searches for a file by name
void searchFile() {
    char name[100];

    printf("Enter file name to search: ");
    scanf("%s", name);

    /*
       strcmp() compares the user input with each file name.
    */
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i].name, name) == 0) {
            printf("File '%s' found. Status: %s\n", name, files[i].isOpen ? "Open" : "Closed");
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

// Lists all files in the system
void listFiles() {
    if (fileCount == 0) {
        printf("No files found.\n");
        return;
    }
    printf("\nFiles in storage:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("- %s [%s]\n", files[i].name, files[i].isOpen ? "Open" : "Closed");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== File Management System =====\n");
        printf("1. Create File\n");
        printf("2. Open File\n");
        printf("3. Close File\n");
        printf("4. Write to File\n");
        printf("5. Read File\n");
        printf("6. Search File\n");
        printf("7. List Files\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                char fileName[100];
                printf("Enter file name to create: ");
                scanf("%s", fileName);
                int idx = createFile(fileName);
                if (idx != -1) {
                    printf("File '%s' created successfully.\n", files[idx].name);
                }
                break;
            }
            case 2: openFile();    break;
            case 3: closeFile();   break;
            case 4: writeToFile(); break;
            case 5: readFile();    break;
            case 6: searchFile();  break;
            case 7: listFiles();   break;
            case 8:
                printf("Exiting File Management System.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}