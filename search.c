#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "file_manager.h"

#define STORAGE_DIR "storage/"
#define BUFFER_SIZE 1024

/*
 * searchFile() - Search the storage directory in two modes:
 *   1. Search by file name  – scans directory entries with strcmp().
 *   2. Search by content    – reads each file and checks for a substring
 *                             with strstr(), printing every file that matches.
 *
 * The user selects the mode interactively.
 */
void searchFile() {
    int mode;

    printf("\nSearch options:\n");
    printf("  1. Search by file name\n");
    printf("  2. Search by content (keyword)\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    if (mode == 1) {
        /* ---- Name search ---- */
        char fileName[100];
        printf("Enter file name to search: ");
        scanf("%s", fileName);

        DIR *dir = opendir(STORAGE_DIR);
        if (dir == NULL) {
            perror("Error opening storage directory");
            return;
        }

        int found = 0;
        struct dirent *entry;

        /*
         * readdir() reads each directory entry.
         * strcmp() compares the entry name to the user's input exactly.
         */
        while ((entry = readdir(dir)) != NULL) {
            /* Skip hidden entries and lock markers. */
            if (entry->d_name[0] == '.') continue;
            size_t len = strlen(entry->d_name);
            if (len > 5 && strcmp(entry->d_name + len - 5, ".open") == 0) continue;

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

    } else if (mode == 2) {
        /* ---- Content search ---- */
        char keyword[200];
        printf("Enter keyword to search inside files: ");
        getchar(); /* clear leftover newline from scanf */
        fgets(keyword, sizeof(keyword), stdin);

        /* Strip trailing newline from fgets. */
        size_t klen = strlen(keyword);
        if (klen > 0 && keyword[klen - 1] == '\n') {
            keyword[klen - 1] = '\0';
            klen--;
        }

        if (klen == 0) {
            printf("Keyword cannot be empty.\n");
            return;
        }

        DIR *dir = opendir(STORAGE_DIR);
        if (dir == NULL) {
            perror("Error opening storage directory");
            return;
        }

        int matches = 0;
        struct dirent *entry;

        printf("\nFiles containing \"%s\":\n", keyword);

        while ((entry = readdir(dir)) != NULL) {
            /* Skip hidden entries and lock markers. */
            if (entry->d_name[0] == '.') continue;
            size_t len = strlen(entry->d_name);
            if (len > 5 && strcmp(entry->d_name + len - 5, ".open") == 0) continue;

            /* Build full path and open for reading. */
            char path[300];
            snprintf(path, sizeof(path), "%s%s", STORAGE_DIR, entry->d_name);

            int fd = open(path, O_RDONLY);
            if (fd == -1) continue; /* skip unreadable files */

            char buffer[BUFFER_SIZE];
            int bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
            close(fd);

            if (bytesRead <= 0) continue;
            buffer[bytesRead] = '\0';

            /*
             * strstr() scans the buffer for the first occurrence of keyword.
             * Returns NULL if not found.
             */
            if (strstr(buffer, keyword) != NULL) {
                printf("  - %s\n", entry->d_name);
                matches++;
            }
        }

        closedir(dir);

        if (matches == 0) {
            printf("  No files found containing \"%s\".\n", keyword);
        } else {
            printf("Found %d file(s) matching the keyword.\n", matches);
        }

    } else {
        printf("Invalid choice.\n");
    }
}
