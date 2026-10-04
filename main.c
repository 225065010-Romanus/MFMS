#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

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

/* Ask until the user enters a whole number from min to max */
static int readMenuChoice(int min, int max)
{
    char line[64], *end;
    long value;
    int c;

    while (1) {
        printf("Enter your choice: ");
        if (fgets(line, sizeof line, stdin) == NULL)
            exit(0);
        if (strchr(line, '\n') == NULL)      /* line too long: discard rest */
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
            case 5: reportsMenu();  
            break;
            case 6: printf("Goodbye.\n"); 
            break;
        }
    } while (choice != 6);

    return 0;
}
