#include <stdio.h>
#include <string.h>


struct Book
{
    int id;
    int popularity;
    int lastAccessed;
};


struct Shelf
{
    struct Book books[100];
    int count;
    int capacity;
    int accessCounter;
};


void initShelf(struct Shelf *shelf, int capacity)
{
    shelf->count = 0;
    shelf->capacity = capacity;
    shelf->accessCounter = 0;
}


int findBook(struct Shelf *shelf, int id)
{
    int i;
    for (i = 0; i < shelf->count; i++)
    {
        if (shelf->books[i].id == id)
        {
            return i;
        }
    }
    return -1;
}


void removeLRU(struct Shelf *shelf)
{
    int minIndex = 0;
    int minAccess = shelf->books[0].lastAccessed;
    int i;

    for (i = 1; i < shelf->count; i++)
    {
        if (shelf->books[i].lastAccessed < minAccess)
        {
            minAccess = shelf->books[i].lastAccessed;
            minIndex = i;
        }
    }


    for (i = minIndex; i < shelf->count - 1; i++)
    {
        shelf->books[i] = shelf->books[i + 1];
    }
    shelf->count--;
}


void addBook(struct Shelf *shelf, int id, int popularity)
{
    int index = findBook(shelf, id);


    if (index != -1)
    {
        shelf->books[index].popularity = popularity;
        shelf->books[index].lastAccessed = shelf->accessCounter++;
        return;
    }


    if (shelf->count == shelf->capacity)
    {
        removeLRU(shelf);
    }


    shelf->books[shelf->count].id = id;
    shelf->books[shelf->count].popularity = popularity;
    shelf->books[shelf->count].lastAccessed = shelf->accessCounter++;
    shelf->count++;
}


int accessBook(struct Shelf *shelf, int id)
{
    int index = findBook(shelf, id);

    if (index == -1)
    {
        return -1;
    }


    shelf->books[index].lastAccessed = shelf->accessCounter++;
    return shelf->books[index].popularity;
}

int main()
{
    int capacity, q;
    struct Shelf shelf;

    printf("Enter capacity and number of operations: ");
    scanf("%d %d", &capacity, &q);

    initShelf(&shelf, capacity);

    int i;
    for (i = 0; i < q; i++)
    {
        char operation[10];
        scanf("%s", operation);

        if (strcmp(operation, "ADD") == 0)
        {
            int id, popularity;
            scanf("%d %d", &id, &popularity);
            addBook(&shelf, id, popularity);
        }
        else if (strcmp(operation, "ACCESS") == 0)
        {
            int id;
            scanf("%d", &id);
            int result = accessBook(&shelf, id);
            printf("%d\n", result);
        }
    }

    return 0;
}