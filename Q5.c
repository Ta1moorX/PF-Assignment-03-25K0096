#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initEditor(char ***lines, int *numLines, int *capacity)
{
    *capacity = 10;
    *numLines = 0;


    *lines = (char **)malloc((*capacity) * sizeof(char *));

    if (*lines == NULL)
    {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
}


void insertLine(char ***lines, int *numLines, int *capacity, int index, char *text)
{

    if (index < 0 || index > *numLines)
    {
        printf("Error: Invalid index!\n");
        return;
    }

   
    if (*numLines >= *capacity)
    {
        *capacity = *capacity * 2;
        *lines = (char **)realloc(*lines, (*capacity) * sizeof(char *));

        if (*lines == NULL)
        {
            printf("Error: Memory reallocation failed!\n");
            exit(1);
        }
    }

   
    int len = strlen(text);
    char *newLine = (char *)malloc((len + 1) * sizeof(char));

    if (newLine == NULL)
    {
        printf("Error: Memory allocation for line failed!\n");
        exit(1);
    }

    strcpy(newLine, text);

  
    int i;
    for (i = *numLines; i > index; i--)
    {
        (*lines)[i] = (*lines)[i - 1];
    }


    (*lines)[index] = newLine;
    (*numLines)++;
}


void deleteLine(char ***lines, int *numLines, int index)
{
    if (index < 0 || index >= *numLines)
    {
        printf("Error: Invalid index!\n");
        return;
    }


    free((*lines)[index]);


    int i;
    for (i = index; i < *numLines - 1; i++)
    {
        (*lines)[i] = (*lines)[i + 1];
    }

    (*numLines)--;
}


void printAllLines(char **lines, int numLines)
{
    printf("\nText Editor Content:\n");
    int i;
    for (i = 0; i < numLines; i++)
    {
        printf("%d: %s\n", i + 1, lines[i]);
    }

}


void freeAll(char ***lines, int numLines)
{
    int i;
    for (i = 0; i < numLines; i++)
    {
        free((*lines)[i]);
    }
    free(*lines);
    *lines = NULL;
}


void shrinkToFit(char ***lines, int *numLines, int *capacity)
{
    if (*numLines == 0)
        return;

    *capacity = *numLines;
    *lines = (char **)realloc(*lines, (*capacity) * sizeof(char *));

    if (*lines == NULL)
    {
        printf("Error: Shrink failed!\n");
        exit(1);
    }

    printf("Memory optimized! Capacity: %d\n", *capacity);
}


void saveToFile(char **lines, int numLines, char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    int i;
    for (i = 0; i < numLines; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
    printf("File saved successfully!\n");
}


void loadFromFile(char ***lines, int *numLines, int *capacity, char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Cannot open file for reading!\n");
        return;
    }

    char buffer[1000];
    while (fgets(buffer, 1000, file) != NULL)
    {

        buffer[strcspn(buffer, "\n")] = 0;
        insertLine(lines, numLines, capacity, *numLines, buffer);
    }

    fclose(file);
    printf("File loaded successfully!\n");
}

int main()
{
    char **lines;
    int numLines;
    int capacity;
    int choice;
    char buffer[1000];
    int index;
    char filename[100];

    initEditor(&lines, &numLines, &capacity);

    while (1)
    {
        printf("\nText Editor Menu:\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Shrink to Fit\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            printf("Enter index (0 to %d): ", numLines);
            scanf("%d", &index);
            getchar();
            printf("Enter text: ");
            fgets(buffer, 1000, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            insertLine(&lines, &numLines, &capacity, index, buffer);
        }
        else if (choice == 2)
        {
            printf("Enter index to delete (0 to %d): ", numLines - 1);
            scanf("%d", &index);
            deleteLine(&lines, &numLines, index);
        }
        else if (choice == 3)
        {
            printAllLines(lines, numLines);
        }
        else if (choice == 4)
        {
            printf("Enter filename: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = 0;
            saveToFile(lines, numLines, filename);
        }
        else if (choice == 5)
        {
            printf("Enter filename: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = 0;
            loadFromFile(&lines, &numLines, &capacity, filename);
        }
        else if (choice == 6)
        {
            shrinkToFit(&lines, &numLines, &capacity);
        }
        else if (choice == 7)
        {
            freeAll(&lines, numLines);
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