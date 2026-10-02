#include <stdio.h>
#include <string.h>

#define MAX 5   /* maximum number of suppliers */

/* Supplier data (one row per supplier) */
char names[MAX][100], emails[MAX][100], phones[MAX][30], towns[MAX][50];
int  count = 0;   /* suppliers stored so far */

/* Reads a line of text and removes the newline */
void readText(char text[], int size)
{
    fgets(text, size, stdin);
    text[strcspn(text, "\n")] = '\0';
}

void addSupplier()
{
    if (count >= MAX) {
        printf("Supplier list is full.\n");
        return;
    }
    printf("Enter supplier name: ");  readText(names[count], 100);
    printf("Enter email: ");          readText(emails[count], 100);
    printf("Enter phone: ");          readText(phones[count], 30);
    printf("Enter town: ");           readText(towns[count], 50);
    count++;
    printf("Supplier added.\n");
}

void displaySupplier()
{
    int i;
    if (count == 0) {
        printf("No suppliers yet.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        printf("\n--- SUPPLIER %d ---\n", i + 1);
        printf("Name : %s\nEmail: %s\nPhone: %s\nTown : %s\n",
               names[i], emails[i], phones[i], towns[i]);
    }
}

void searchSupplier()
{
    char search[100];
    int i;
    printf("Enter supplier name to search: ");
    readText(search, 100);
    for (i = 0; i < count; i++) {
        if (strcmp(names[i], search) == 0) {   /* 0 means equal */
            printf("Supplier found.\nEmail: %s\nPhone: %s\nTown : %s\n",
                   emails[i], phones[i], towns[i]);
            return;
        }
    }
    printf("Supplier not found.\n");
}

int main()
{
    char line[10];
    int choice;

    do {
        printf("\n=== SUPPLIER MANAGEMENT ===\n");
        printf("1. Add Supplier\n2. Display Supplier\n");
        printf("3. Search Supplier\n4. Exit\nEnter choice: ");
        readText(line, 10);

        /* one typed digit becomes a number; anything else is invalid (0) */
        choice = (strlen(line) == 1) ? line[0] - '0' : 0;

        switch (choice) {
            case 1: addSupplier();     break;
            case 2: displaySupplier(); break;
            case 3: searchSupplier();  break;
            case 4: printf("Goodbye.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
