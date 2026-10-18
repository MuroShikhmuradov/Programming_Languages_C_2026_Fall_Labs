/*
 * Name: Murad
 * Surname: Shikhmuradov
 * Student ID: 251ADB070
 */
#include <stdio.h>

#define LINE_SIZE 256

int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : "data.txt";

    printf("Writing lines to %s...\n", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");

    if (fclose(fp) != 0) {
        perror("Error closing file after writing");
        return 1;
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    printf("Reading contents:\n");
    char line[LINE_SIZE];
    int lines_read = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
        lines_read++;
    }

    fclose(fp);

    printf("Lines read: %d\n", lines_read);
    return 0;
}
