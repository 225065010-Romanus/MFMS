//author: 226141608 Samy Mujinga Wa Pelekoni//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

/* Show the main menu to the user. This is the central navigation point of the app. */
static void displayMenu(void)
{
    printf("\n========================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

/* Read a valid whole number in a safe way. This prevents crashes from bad user input. */
static int readMenuChoice(int min, int max)
{
    char line[64], *end;
    long value;
    int c;

    while (1) {
        printf("Enter your choice: ");
        if (fgets(line, sizeof line, stdin) == NULL)
            exit(0);
        if (strchr(line, '\n') == NULL)      /* line too long: discard the rest */
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        value = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t')
            end++;
        if (end == line || (*end != '\n' && *end != '\0'))
            printf("Invalid input. Please enter a number.\n");
        else if (value < min || value > max)
            printf("Please enter a number from %d to %d.\n", min, max);
        else
            return (int)value;
    }
}

/* The main program loop. It keeps the system alive until the user chooses Exit. */
int main(void)
{
    int choice;

    do {
        displayMenu();
        choice = readMenuChoice(1, 6);

        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                supplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                printf("Goodbye.\n");
                break;
            default:
                printf("Unexpected menu selection.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
