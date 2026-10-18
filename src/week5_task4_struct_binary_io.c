/*
 * Name: Murad
 * Surname: Shikhmuradov
 * Student ID: 251ADB070
 */
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 50

typedef struct Student {
    char name[NAME_SIZE];
    int age;
    float gpa;
} Student;

int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening binary file for writing");
        return -1;
    }

    if (fwrite(s, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        perror("Error closing binary file");
        return -1;
    }
    return 0;
}

int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening binary file for reading");
        return -1;
    }

    size_t items = fread(out, sizeof(Student), 1, fp);
    fclose(fp);

    if (items != 1) {
        return -1;
    }
    out->name[NAME_SIZE - 1] = '\0';
    return 0;
}

static int save_student_text(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening text file for writing");
        return -1;
    }
    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        fclose(fp);
        return -1;
    }
    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

long file_size(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int main(void) {
    Student s = {0};
    strcpy(s.name, "Alice");
    s.age = 21;
    s.gpa = 3.75f;

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s, "student.bin") != 0) {
        printf("Error: could not save binary file.\n");
        return 1;
    }

    Student loaded = {0};
    printf("Loading student from binary file...\n");
    if (load_student_binary("student.bin", &loaded) != 0) {
        printf("Error: could not load binary file.\n");
        return 1;
    }
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    if (save_student_text(&s, "student.txt") != 0) {
        printf("Error: could not save text file.\n");
        return 1;
    }

    long text_size = file_size("student.txt");
    long bin_size = file_size("student.bin");
    if (text_size < 0 || bin_size < 0) {
        printf("Error: could not read file sizes.\n");
        return 1;
    }

    printf("Text file size: %ld bytes\n", text_size);
    printf("Binary file size: %ld bytes\n", bin_size);
    return 0;
}
