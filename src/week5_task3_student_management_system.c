/*
 * Name: Murad
 * Surname: Shikhmuradov
 * Student ID: 251ADB070
 */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_SIZE 50
#define LINE_SIZE 256
#define FILENAME "students.txt"

typedef struct Student {
    char name[NAME_SIZE];
    int id;
    float gpa;
} Student;

int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);

static int read_line(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL) {
        return 0;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }
    return 1;
}

static int is_blank(const char *s) {
    for (; *s != '\0'; s++) {
        if (*s != ' ' && *s != '\t') {
            return 0;
        }
    }
    return 1;
}

static int parse_int(const char *s, int *out) {
    char *end;
    errno = 0;
    long value = strtol(s, &end, 10);
    if (end == s) {
        return 0;
    }
    while (*end == ' ' || *end == '\t') {
        end++;
    }
    if (*end != '\0' || errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        return 0;
    }
    *out = (int)value;
    return 1;
}

static int parse_float(const char *s, float *out) {
    char *end;
    errno = 0;
    double value = strtod(s, &end);
    if (end == s) {
        return 0;
    }
    while (*end == ' ' || *end == '\t') {
        end++;
    }
    if (*end != '\0' || errno == ERANGE) {
        return 0;
    }
    *out = (float)value;
    return 1;
}

int load_students(Student arr[], int max) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        return 0;
    }

    char line[LINE_SIZE];
    int count = 0;
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        Student s;
        if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
            arr[count] = s;
            count++;
        }
    }

    fclose(fp);
    return count;
}

int save_students(const Student arr[], int count) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        perror("Error opening " FILENAME " for writing");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) != 0) {
        perror("Error closing " FILENAME);
        return -1;
    }
    return 0;
}

void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name[LINE_SIZE];
    char id_text[LINE_SIZE];
    char gpa_text[LINE_SIZE];

    printf("Enter name: ");
    if (!read_line(name, sizeof name)) {
        return;
    }
    printf("Enter ID: ");
    if (!read_line(id_text, sizeof id_text)) {
        return;
    }
    printf("Enter GPA: ");
    if (!read_line(gpa_text, sizeof gpa_text)) {
        return;
    }

    int id;
    float gpa;
    int valid = 1;

    if (is_blank(name) || strchr(name, ',') != NULL || strlen(name) >= NAME_SIZE) {
        valid = 0;
    }
    if (!parse_int(id_text, &id)) {
        valid = 0;
    }
    if (!parse_float(gpa_text, &gpa) || gpa < 0.0f || gpa > 4.0f) {
        valid = 0;
    }

    if (!valid) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    memcpy(arr[*count].name, name, strlen(name) + 1);
    arr[*count].id = id;
    arr[*count].gpa = gpa;
    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, FILENAME);

    char choice[LINE_SIZE];
    for (;;) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");

        if (!read_line(choice, sizeof choice)) {
            printf("\n");
            break;
        }

        int option;
        if (!parse_int(choice, &option)) {
            option = 0;
        }

        if (option == 1) {
            list_students(students, count);
        } else if (option == 2) {
            add_student(students, &count);
        } else if (option == 3) {
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    if (save_students(students, count) != 0) {
        printf("Error: could not save data to %s\n", FILENAME);
        return 1;
    }
    printf("Data saved. Goodbye!\n");
    return 0;
}
