#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[12];
    char dateOfBirth[12];
    char interest[20];
};

struct Student *students = NULL;
int studentCount = 0;
int capacity = 10;

void loadDatabase(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("No existing database found. Starting fresh.\n");
        students = (struct Student *)malloc(capacity * sizeof(struct Student));
        return;
    }

    students = (struct Student *)malloc(capacity * sizeof(struct Student));

    while (fread(&students[studentCount], sizeof(struct Student), 1, file) == 1)
    {
        studentCount++;

        if (studentCount >= capacity)
        {
            capacity = capacity * 2;
            students = (struct Student *)realloc(students, capacity * sizeof(struct Student));
        }
    }

    fclose(file);
    printf("Database loaded: %d students\n", studentCount);
}

void saveDatabase(const char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Error: Cannot save database!\n");
        return;
    }

    int i;
    for (i = 0; i < studentCount; i++)
    {
        fwrite(&students[i], sizeof(struct Student), 1, file);
    }

    fclose(file);
    printf("Database saved successfully!\n");
}

int findStudentByID(int id)
{
    int i;
    for (i = 0; i < studentCount; i++)
    {
        if (students[i].studentID == id)
        {
            return i;
        }
    }
    return -1;
}

void addStudent(const char *filename)
{
    struct Student newStudent;

    printf("\n=== Register New Student ===\n");
    printf("Student ID: ");
    scanf("%d", &newStudent.studentID);

    if (findStudentByID(newStudent.studentID) != -1)
    {
        printf("Error: Student ID already exists!\n");
        return;
    }

    getchar();
    printf("Full Name: ");
    fgets(newStudent.fullName, 100, stdin);
    newStudent.fullName[strcspn(newStudent.fullName, "\n")] = 0;

    printf("Batch (CS/SE/Cyber Security/AI): ");
    fgets(newStudent.batch, 20, stdin);
    newStudent.batch[strcspn(newStudent.batch, "\n")] = 0;

    printf("Membership Type (IEEE/ACM): ");
    fgets(newStudent.membershipType, 10, stdin);
    newStudent.membershipType[strcspn(newStudent.membershipType, "\n")] = 0;

    printf("Registration Date (YYYY-MM-DD): ");
    fgets(newStudent.registrationDate, 12, stdin);
    newStudent.registrationDate[strcspn(newStudent.registrationDate, "\n")] = 0;

    printf("Date of Birth (YYYY-MM-DD): ");
    fgets(newStudent.dateOfBirth, 12, stdin);
    newStudent.dateOfBirth[strcspn(newStudent.dateOfBirth, "\n")] = 0;

    printf("Interest (IEEE/ACM/Both): ");
    fgets(newStudent.interest, 20, stdin);
    newStudent.interest[strcspn(newStudent.interest, "\n")] = 0;

    if (studentCount >= capacity)
    {
        capacity = capacity * 2;
        students = (struct Student *)realloc(students, capacity * sizeof(struct Student));
    }

    students[studentCount] = newStudent;
    studentCount++;

    saveDatabase(filename);
    printf("Student registered successfully!\n");
}
void updateStudent(int studentID, const char *filename)
{
    int index = findStudentByID(studentID);

    if (index == -1)
    {
        printf("Student not found!\n");
        return;
    }

    int choice;
    printf("\nUpdate Student:\n");
    printf("1. Update Batch\n");
    printf("2. Update Membership Type\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("New Batch: ");
        fgets(students[index].batch, 20, stdin);
        students[index].batch[strcspn(students[index].batch, "\n")] = 0;
    }
    else if (choice == 2)
    {
        printf("New Membership Type: ");
        fgets(students[index].membershipType, 10, stdin);
        students[index].membershipType[strcspn(students[index].membershipType, "\n")] = 0;
    }

    saveDatabase(filename);
    printf("Student updated successfully!\n");
}
void deleteStudent(int studentID, const char *filename)
{
    int index = findStudentByID(studentID);

    if (index == -1)
    {
        printf("Student not found!\n");
        return;
    }

    int i;
    for (i = index; i < studentCount - 1; i++)
    {
        students[i] = students[i + 1];
    }

    studentCount--;
    saveDatabase(filename);
    printf("Student deleted successfully!\n");
}
void displayAllStudents()
{
    printf("\nAll Registered Students:\n");
    printf("%-10s %-25s %-15s %-10s %-12s %-12s %-10s\n",
           "ID", "Name", "Batch", "Type", "Reg Date", "DOB", "Interest");

    int i;
    for (i = 0; i < studentCount; i++)
    {
        printf("%-10d %-25s %-15s %-10s %-12s %-12s %-10s\n",
               students[i].studentID,
               students[i].fullName,
               students[i].batch,
               students[i].membershipType,
               students[i].registrationDate,
               students[i].dateOfBirth,
               students[i].interest);
    }
}

void generateBatchReport()
{
    char batch[20];
    char interest[20];

    getchar();
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    fgets(batch, 20, stdin);
    batch[strcspn(batch, "\n")] = 0;

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(interest, 20, stdin);
    interest[strcspn(interest, "\n")] = 0;

    printf("\nStudents in %s interested in %s:\n", batch, interest);

    int i;
    int count = 0;
    for (i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].batch, batch) == 0 && strcmp(students[i].interest, interest) == 0)
        {
            printf("%d. %s (ID: %d)\n", count + 1, students[i].fullName, students[i].studentID);
            count++;
        }
    }

    printf("Total: %d students\n", count);
}

int main()
{
    const char *filename = "members.dat";
    int choice;
    int id;

    loadDatabase(filename);

    while (1)
    {
        printf("\nIEEE/ACM Registration System:\n");
        printf("1. Register New Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Generate Batch Report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            addStudent(filename);
        }
        else if (choice == 2)
        {
            printf("Enter Student ID: ");
            scanf("%d", &id);
            updateStudent(id, filename);
        }
        else if (choice == 3)
        {
            printf("Enter Student ID: ");
            scanf("%d", &id);
            deleteStudent(id, filename);
        }
        else if (choice == 4)
        {
            displayAllStudents();
        }
        else if (choice == 5)
        {
            generateBatchReport();
        }
        else if (choice == 6)
        {
            free(students);
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}