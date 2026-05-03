#include <stdio.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write(), close(), unlink()
#include <string.h>     // strlen()
#include <dirent.h>     // opendir(), readdir(), closedir()
#include <sys/stat.h>   // stat()
#include <time.h>       // ctime()
#include "file_manager.h"

#define STORAGE_DIR "storage/"
#define BUFFER_SIZE 1024

// Creates a new file inside the storage directory
void createFile() {
    char fileName[100];
    char path[150];

    printf("Enter file name to create: ");
    scanf("%s", fileName);

    // Build full path: storage/filename
    snprintf(path, sizeof(path), "%s%s", STORAGE_DIR, fileName);

    /*
       open() is a system call.
       O_CREAT creates the file.
       O_EXCL prevents overwriting an existing file.
       O_WRONLY opens the file for writing only.
       0644 gives read/write permission to owner and read permission to others.
    */
    int fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);

    if (fd == -1) {
        perror("Error creating file");
        return;
    }

    printf("File '%s' created successfully.\n", fileName);

    // close() releases the file descriptor
    close(fd);
}

// Writes content into an existing file
void writeToFile() {
    char fileName[100];
    char path[150];
    char content[BUFFER_SIZE];

    printf("Enter file name to write to: ");
    scanf("%s", fileName);

    snprintf(path, sizeof(path), "%s%s", STORAGE_DIR, fileName);

    /*
       O_WRONLY opens file for writing.
       O_APPEND adds new content at the end of the file.
    */
    int fd = open(path, O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("Error opening file for writing");
        return;
    }

    printf("Enter content to write: ");
    getchar(); // removes leftover newline from scanf
    fgets(content, BUFFER_SIZE, stdin);

    // write() writes bytes from memory into the file
    if (write(fd, content, strlen(content)) == -1) {
        perror("Error writing to file");
        close(fd);
        return;
    }

    printf("Content written successfully.\n");

    close(fd);
}

// Opens and reads a file
void readFile() {
    char fileName[100];
    char path[150];
    char buffer[BUFFER_SIZE];

    printf("Enter file name to read: ");
    scanf("%s", fileName);

    snprintf(path, sizeof(path), "%s%s", STORAGE_DIR, fileName);

    // O_RDONLY opens the file for reading only
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    // read() reads data from file into buffer
    int bytesRead = read(fd, buffer, BUFFER_SIZE - 1);

    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        return;
    }

    buffer[bytesRead] = '\0';

    printf("\n----- File Content -----\n");

    if (bytesRead == 0) {
        printf("File is empty.\n");
    } else {
        printf("%s\n", buffer);
    }

    close(fd);
}

// Lists all files inside the storage directory
void listFiles() {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(STORAGE_DIR);

    if (dir == NULL) {
        perror("Error opening storage directory");
        return;
    }

    printf("\nFiles in storage directory:\n");

    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden entries like . and ..
        if (entry->d_name[0] != '.') {
            printf("- %s\n", entry->d_name);
            count++;
        }
    }

    if (count == 0) {
        printf("No files found.\n");
    }

    closedir(dir);
}

// Shows file attributes such as size, permissions, and last modified time
void showFileDetails() {
    char fileName[100];
    char path[150];
    struct stat fileStat;

    printf("Enter file name to show details: ");
    scanf("%s", fileName);

    snprintf(path, sizeof(path), "%s%s", STORAGE_DIR, fileName);

    /*
       stat() gets file metadata.
       Metadata means information about the file, not the file content.
    */
    if (stat(path, &fileStat) == -1) {
        perror("Error getting file details");
        return;
    }

    printf("\n----- File Details -----\n");
    printf("File Name: %s\n", fileName);
    printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Permissions: %o\n", fileStat.st_mode & 0777);
    printf("Last Modified: %s", ctime(&fileStat.st_mtime));
}

// Deletes a file from the storage directory
void deleteFile() {
    char fileName[100];
    char path[150];

    printf("Enter file name to delete: ");
    scanf("%s", fileName);

    snprintf(path, sizeof(path), "%s%s", STORAGE_DIR, fileName);

    /*
       unlink() removes the file name from the directory.
       If no process is using the file, the file is deleted.
    */
    if (unlink(path) == -1) {
        perror("Error deleting file");
        return;
    }

    printf("File '%s' deleted successfully.\n", fileName);
}