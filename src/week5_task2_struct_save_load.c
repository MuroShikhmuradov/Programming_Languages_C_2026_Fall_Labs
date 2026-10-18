/*
 * Name: Murad
 * Surname: Shikhmuradov
 * Student ID: 251ADB070
 */
#include <stdio.h>

#define NAME_SIZE 50

typedef struct Student {
    char name[NAME_SIZE];
    int age;
    float gpa;
} Student;

int save_student(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        perror("Error closing file");
        return -1;
    }
    return 0;
}

int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return -1;
    }

    int fields = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);
    fclose(fp);

    if (fields != 3) {
        return -1;
    }
    return 0;
}

int main(void) {
    Student original = {"Alice", 21, 3.75f};
    Student loaded = {0};

    printf("Saving student to file...\n");
    if (save_student(&original, "student.txt") != 0) {
        printf("Error: could not save student.\n");
        return 1;
    }

    printf("Loading student from file...\n");
    if (load_student("student.txt", &loaded) != 0) {
        printf("Error: could not load student.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return 0;
}
