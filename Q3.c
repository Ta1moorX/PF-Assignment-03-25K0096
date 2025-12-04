#include <stdio.h>
#include <string.h>

struct Employee
{
    int id;
    char name[100];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee emp[], int n)
{
    printf("\nEmployee Records:\n");
    printf("%-10s %-25s %-25s %-15s\n", "ID", "Name", "Designation", "Salary");

    int i;
    for (i = 0; i < n; i++)
    {
        printf("%-10d %-25s %-25s %-15.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

void findHighestSalary(struct Employee emp[], int n)
{
    int i;
    int maxIndex = 0;
    float maxSalary = emp[0].salary;

    for (i = 1; i < n; i++)
    {
        if (emp[i].salary > maxSalary)
        {
            maxSalary = emp[i].salary;
            maxIndex = i;
        }
    }

    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\n", emp[maxIndex].id);
    printf("Name: %s\n", emp[maxIndex].name);
    printf("Designation: %s\n", emp[maxIndex].designation);
    printf("Salary: %.2f\n", emp[maxIndex].salary);
}


void searchEmployee(struct Employee emp[], int n, int searchType)
{
    int searchId;
    char searchName[100];
    int found = 0;
    int i;

    if (searchType == 1)
    {
        printf("Enter Employee ID to search: ");
        scanf("%d", &searchId);

        for (i = 0; i < n; i++)
        {
            if (emp[i].id == searchId)
            {
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", emp[i].id);
                printf("Name: %s\n", emp[i].name);
                printf("Designation: %s\n", emp[i].designation);
                printf("Salary: %.2f\n", emp[i].salary);
                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("Enter Employee Name to search: ");
        getchar();
        fgets(searchName, 100, stdin);
        searchName[strcspn(searchName, "\n")] = 0;

        for (i = 0; i < n; i++)
        {
            if (strcmp(emp[i].name, searchName) == 0)
            {
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", emp[i].id);
                printf("Name: %s\n", emp[i].name);
                printf("Designation: %s\n", emp[i].designation);
                printf("Salary: %.2f\n", emp[i].salary);
                found = 1;
                break;
            }
        }
    }

    if (found == 0)
    {
        printf("\nEmployee not found!\n");
    }
}

//byref 
void updateSalaries(struct Employee *emp, int n, float threshold, float bonusPercent)
{
    int i;
    int count = 0;

    printf("\n=== Updating Salaries Below %.2f ===\n", threshold);

    for (i = 0; i < n; i++)
    {
        if (emp[i].salary < threshold)
        {
            float oldSalary = emp[i].salary;
            emp[i].salary = emp[i].salary + (emp[i].salary * bonusPercent / 100.0);
            printf("Employee %s: %.2f -> %.2f\n", emp[i].name, oldSalary, emp[i].salary);
            count++;
        }
    }

    printf("Total employees updated: %d\n", count);
}

int main()
{
    int n;
    int i;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];

    for (i = 0; i < n; i++)
    {
        printf("\nEnter details for Employee %d\n:", i + 1);
        printf("Employee ID: ");
        scanf("%d", &emp[i].id);

        printf("Name: ");
        getchar();
        fgets(emp[i].name, 100, stdin);
        emp[i].name[strcspn(emp[i].name, "\n")] = 0;

        printf("Designation: ");
        fgets(emp[i].designation, 50, stdin);
        emp[i].designation[strcspn(emp[i].designation, "\n")] = 0;

        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }

    displayEmployees(emp, n);
    findHighestSalary(emp, n);
    int choice;
    printf("\n\nSearch Employee:\n1. By ID\n2. By Name\nEnter choice: ");
    scanf("%d", &choice);
    searchEmployee(emp, n, choice);
    updateSalaries(emp, n, 50000, 10);
    printf("\nUpdated Employee Records:\n");
    displayEmployees(emp, n);

    return 0;
}