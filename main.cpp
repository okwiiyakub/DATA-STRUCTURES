#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_DATE_LENGTH 10
#define MAX_REG_NUM_LENGTH 6
#define MAX_PROGRAM_CODE_LENGTH 4
#define MAX_STUDENTS 100

struct Student {
    char name[MAX_NAME_LENGTH];
    char dateOfBirth[MAX_DATE_LENGTH];
    char regNumber[MAX_REG_NUM_LENGTH];
    char programCode[MAX_PROGRAM_CODE_LENGTH];
    float annualTuition;
};

struct Student students[MAX_STUDENTS];
int numStudents = 0;

void addStudent();
void displayStudents();
void updateStudent();
void deleteStudent();
void searchByRegNumber();
void sortByField(char field);
void exportToCSV();
void swap(struct Student *a, struct Student *b);

int main() {

    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Search by Registration Number\n");
        printf("6. Sort Students\n");
        printf("7. Export to CSV\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchByRegNumber();
                break;
            case 6: {
                char field;
                printf("Enter field to sort by ('n' for name, 'r' for registration number): ");
                scanf(" %c", &field);
                sortByField(field);
                break;
            }
            case 7:
                exportToCSV();
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 8.\n");
        }
    } while (choice != 8);

    return 0;
}

//first  commit (joshua)

void addStudent() {
    if (numStudents < MAX_STUDENTS) {
        printf("Enter student's name: ");
        scanf(" %[^\n]", students[numStudents].name);
        printf("Enter student's date of birth (YYYY-MM-DD): ");
        scanf("%s", students[numStudents].dateOfBirth);
        printf("Enter student's registration number: ");
        scanf("%s", students[numStudents].regNumber);
        printf("Enter student's program code: ");
        scanf("%s", students[numStudents].programCode);
        printf("Enter student's annual tuition: ");
        scanf("%f", &students[numStudents].annualTuition);
        while (students[numStudents].annualTuition==0){
            printf("Tuition can't be zero, Re-enter value.");
            scanf("%f", &students[numStudents].annualTuition);
        }
        numStudents++;
    } else {
        printf("Maximum number of students reached.\n");
    }
}

void displayStudents() {
    if (numStudents == 0) {
        printf("No students to display.\n");
    } else {
        printf("List of students:\n");
        for (int i = 0; i < numStudents; i++) {
            printf("Name: %s\n", students[i].name);
            printf("Date of Birth: %s\n", students[i].dateOfBirth);
            printf("Registration Number: %s\n", students[i].regNumber);
            printf("Program Code: %s\n", students[i].programCode);
            printf("Annual Tuition: %.2f\n", students[i].annualTuition);
            printf("\n");
        }
    }
}

void updateStudent() {
    if (numStudents == 0) {
        printf("No students to update.\n");
        return;
    }

    char regNum[MAX_REG_NUM_LENGTH];
    printf("Enter registration number of student to update: ");
    scanf("%s", regNum);

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].regNumber, regNum) == 0) {
            printf("Enter new student's name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new student's date of birth (YYYY-MM-DD): ");
            scanf("%s", students[i].dateOfBirth);
            printf("Enter new student's program code: ");
            scanf("%s", students[i].programCode);
            printf("Enter new student's annual tuition: ");
            scanf("%f", &students[i].annualTuition);
            printf("Student information updated successfully.\n");
            return;
        }
    }

    printf("Student with registration number %s not found.\n", regNum);
}

//second commit(wilfred)

void deleteStudent() {
    if (numStudents == 0) {
        printf("No students to delete.\n");
        return;
    }

    char regNum[MAX_REG_NUM_LENGTH];
    printf("Enter registration number of student to delete: ");
    scanf("%s", regNum);

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].regNumber, regNum) == 0) {
            // Shift elements to fill the gap
            for (int j = i; j < numStudents - 1; j++) {
                strcpy(students[j].name, students[j + 1].name);
                strcpy(students[j].dateOfBirth, students[j + 1].dateOfBirth);
                strcpy(students[j].regNumber, students[j + 1].regNumber);
                strcpy(students[j].programCode, students[j + 1].programCode);
                students[j].annualTuition = students[j + 1].annualTuition;
            }
            numStudents--;
            printf("Student deleted successfully.\n");
            return;
        }
    }

    printf("Student with registration number %s not found.\n", regNum);
}

void searchByRegNumber() {
    if (numStudents == 0) {
        printf("No students to search.\n");
        return;
    }

    char regNum[MAX_REG_NUM_LENGTH];
    printf("Enter registration number of student to search: ");
    scanf("%s", regNum);

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].regNumber, regNum) == 0) {
            printf("Student found:\n");
            printf("Name: %s\n", students[i].name);
            printf("Date of Birth: %s\n", students[i].dateOfBirth);
            printf("Registration Number: %s\n", students[i].regNumber);
            printf("Program Code: %s\n", students[i].programCode);
            printf("Annual Tuition: %.2f\n", students[i].annualTuition);
            return;
        }
    }

    printf("Student with registration number %s not found.\n", regNum);
}
//third commit (yakub)

void sortByField(char field) {
    // Bubble sort
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if ((field == 'n' && strcmp(students[j].name, students[j + 1].name) > 0) ||
                (field == 'r' && strcmp(students[j].regNumber, students[j + 1].regNumber) > 0)) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }

    printf("Students sorted successfully.\n");
}

void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

void exportToCSV() {
    FILE *file = fopen("students.csv", "a"); // Open file in append mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s,%s,%s,%s,%.2f\n", students[i].name, students[i].dateOfBirth, students[i].regNumber, students[i].programCode, students[i].annualTuition);

    }

    fclose(file);
    printf("Records exported to students.csv successfully.\n");
}
// last commit(ananda)