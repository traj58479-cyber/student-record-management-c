#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student {
    int rollNo;
    char name[50];
    char course[30];
    float cgpa;
};

void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n============================================\n");
        printf("     STUDENT RECORD MANAGEMENT SYSTEM\n");
        printf("============================================\n");
        printf("1. Add New Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please select between 1 and 6.\n");
        }
    }
    return 0;
}

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    printf("\n--- Add Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);
    while (getchar() != '\n');

    printf("Enter Full Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Course (e.g., B.Tech CSE): ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);

    fprintf(fp, "%d|%s|%s|%.2f\n", s.rollNo, s.name, s.course, s.cgpa);
    fclose(fp);
    printf("Student record saved to %s!\n", FILE_NAME);
}

void viewAllStudents() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("\nNo records found yet. Add a student first.\n");
        return;
    }

    struct Student s;
    int count = 0;
    printf("\n-----------------------------------------------------------------\n");
    printf("%-10s %-25s %-18s %-6s\n", "Roll No", "Name", "Course", "CGPA");
    printf("-----------------------------------------------------------------\n");

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%f\n", &s.rollNo, s.name, s.course, &s.cgpa) == 4) {
        printf("%-10d %-25s %-18s %.2f\n", s.rollNo, s.name, s.course, s.cgpa);
        count++;
    }
    printf("-----------------------------------------------------------------\n");
    if (count == 0) {
        printf("No student records available.\n");
    } else {
        printf("Total Students: %d\n", count);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    int roll, found = 0;
    struct Student s;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%f\n", &s.rollNo, s.name, s.course, &s.cgpa) == 4) {
        if (s.rollNo == roll) {
            printf("\n--- Student Found ---\n");
            printf("Roll No : %d\n", s.rollNo);
            printf("Name    : %s\n", s.name);
            printf("Course  : %s\n", s.course);
            printf("CGPA    : %.2f\n", s.cgpa);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student with Roll No %d not found.\n", roll);
    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    int roll, found = 0;
    struct Student s;
    printf("\nEnter Roll Number to update: ");
    scanf("%d", &roll);
    while (getchar() != '\n');

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%f\n", &s.rollNo, s.name, s.course, &s.cgpa) == 4) {
        if (s.rollNo == roll) {
            printf("Current: %s | %s | %.2f\n", s.name, s.course, s.cgpa);
            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Enter New Course: ");
            fgets(s.course, sizeof(s.course), stdin);
            s.course[strcspn(s.course, "\n")] = '\0';

            printf("Enter New CGPA: ");
            scanf("%f", &s.cgpa);
            found = 1;
        }
        fprintf(temp, "%d|%s|%s|%.2f\n", s.rollNo, s.name, s.course, s.cgpa);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) printf("Record updated successfully!\n");
    else printf("Student with Roll No %d not found.\n", roll);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    int roll, found = 0;
    struct Student s;
    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%f\n", &s.rollNo, s.name, s.course, &s.cgpa) == 4) {
        if (s.rollNo == roll) {
            found = 1;
        } else {
            fprintf(temp, "%d|%s|%s|%.2f\n", s.rollNo, s.name, s.course, s.cgpa);
        }
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) printf("Student record deleted successfully!\n");
    else printf("Student with Roll No %d not found.\n", roll);
}