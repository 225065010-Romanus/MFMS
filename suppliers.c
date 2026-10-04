
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "suppliers.h"

#define MAX_SUPPLIERS 5

char supEmail[MAX_SUPPLIERS][100];   
char supName[MAX_SUPPLIERS][100];
char supPhone[MAX_SUPPLIERS][30];
char supTown[MAX_SUPPLIERS][50];     
int  supCount = 0;                   /* suppliers stored so far */

static void trimText(char text[])
{
    size_t len;
    char *start = text;
    char *end;

    while (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
        start++;
    }

    len = strlen(start);
    end = start + len;

    while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t' || *(end - 1) == '\r' || *(end - 1) == '\n')) {
        end--;
    }
    *end = '\0';

    if (start != text) {
        memmove(text, start, (size_t)(end - start) + 1);
    }
}

static void readSupplierText(char text[], int size)
{
    char line[200];

    while (1) {
        printf("Enter value: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            text[0] = '\0';
            return;
        }

        trimText(line);

        if (line[0] == '\0') {
            printf("This field cannot be empty. Please try again.\n");
            continue;
        }

        if ((int)strlen(line) >= size) {
            printf("Input is too long. Please try again.\n");
            continue;
        }

        strcpy(text, line);
        return;
    }
}

static int supplierNameExists(const char *name)
{
    int i;

    for (i = 0; i < supCount; i++) {
        if (strcmp(supName[i], name) == 0) {
            return 1;
        }
    }

    return 0;
}

/* Adds one supplier */
void addSupplier(void)
{
    if (supCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    printf("Enter supplier name: ");
    readSupplierText(supName[supCount], 100);
    printf("Enter email: ");
    readSupplierText(supEmail[supCount], 100);
    printf("Enter phone: ");
    readSupplierText(supPhone[supCount], 30);
    printf("Enter town: ");
    readSupplierText(supTown[supCount], 50);

    if (supName[supCount][0] == '\0' || supEmail[supCount][0] == '\0' || supPhone[supCount][0] == '\0' || supTown[supCount][0] == '\0') {
        printf("Supplier registration cancelled because at least one required field was empty.\n");
        return;
    }

    if (supplierNameExists(supName[supCount])) {
        printf("A supplier with this name already exists. Please use a different name.\n");
        return;
    }

    supCount++;
    printf("Supplier added.\n");
}

/* Shows all suppliers */
void displaySupplier(void)
{
    int i;
    if (supCount == 0) {
        printf("No suppliers yet.\n");
        return;
    }
    for (i = 0; i < supCount; i++) {
        printf("\n--- SUPPLIER %d ---\n", i + 1);
        printf("Name : %s\nEmail: %s\nPhone: %s\nTown : %s\n",
               supName[i], supEmail[i], supPhone[i], supTown[i]);
    }
}

/* Return the number of suppliers currently stored */
int getSupplierCount(void)
{
    return supCount;
}

/* Finds a supplier by exact name */
void searchSupplier(void)
{
    char search[100];
    int i;
    printf("Enter supplier name to search: ");
    readSupplierText(search, 100);
    for (i = 0; i < supCount; i++) {
        if (strcmp(supName[i], search) == 0) {
            printf("Supplier found.\nEmail: %s\nPhone: %s\nTown : %s\n",
                   supEmail[i], supPhone[i], supTown[i]);
            return;
        }
    }
    printf("Supplier not found.\n");
}

/* Supplier sub-menu: call this from the main menu option "Supplier Management" */
void supplierMenu(void)
{
    char line[10];
    int choice;
    do {
        printf("\n1. Add Supplier\n2. Display Supplier\n");
        printf("3. Search Supplier\n4. Back\nEnter choice: ");
        readSupplierText(line, 10);
        choice = (strlen(line) == 1) ? line[0] - '0' : 0;
        if (choice == 1) addSupplier();
        else if (choice == 2) displaySupplier();
        else if (choice == 3) searchSupplier();
        else if (choice != 4) printf("Invalid choice.\n");
    } while (choice != 4);
}
