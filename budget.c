
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "budget.h"

static Budget budgets[MAX_DEPARTMENTS];
static int budgetCount = 0;

/* Read a line of text safely */
static void readLine(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }
}

/* Read a valid non-negative monetary amount */
static double readAmount(const char prompt[])
{
    char input[100];
    char *end;
    double amount;

    while (1) {
        printf("%s", prompt);
        readLine(input, sizeof(input));

        amount = strtod(input, &end);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (input[0] != '\0' &&
            end != input &&
            *end == '\0' &&
            amount >= 0) {
            return amount;
        }

        printf("Invalid amount. Enter a non-negative number.\n");
    }
}

/* Calculate the remaining budget */
double calculateBudget(double allocated, double expenditure)
{
    return allocated - expenditure;
}

/* Find a department by name */
int findDepartment(const char name[])
{
    int i;

    for (i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].department, name) == 0) {
            return i;
        }
    }

    return -1;
}

/* Add a new departmental budget */
void addBudget(void)
{
    char name[NAME_LENGTH];
    int index;

    if (budgetCount >= MAX_DEPARTMENTS) {
        printf("Department limit reached.\n");
        return;
    }

    printf("Enter department name: ");
    readLine(name, sizeof(name));

    if (name[0] == '\0') {
        printf("Department name cannot be empty.\n");
        return;
    }

    index = findDepartment(name);

    if (index != -1) {
        printf("Department already exists.\n");
        return;
    }

    strcpy(budgets[budgetCount].department, name);

    budgets[budgetCount].allocatedBudget =
        readAmount("Enter allocated budget (N$): ");

    budgets[budgetCount].expenditure = 0;

    budgetCount++;

    printf("Department budget added successfully!\n");
}

/* Record expenditure for an existing department */
void recordExpenditure(void)
{
    char name[NAME_LENGTH];
    int index;
    double amount;

    printf("Enter department name: ");
    readLine(name, sizeof(name));

    index = findDepartment(name);

    if (index == -1) {
        printf("Department not found.\n");
        return;
    }

    amount = readAmount("Enter expenditure (N$): ");

    budgets[index].expenditure += amount;

    printf("Expenditure recorded successfully!\n");
}

/* Display all departmental budgets */
void displayBudgets(void)
{
    int i;
    double remaining;

    if (budgetCount == 0) {
        printf("No departmental budgets registered.\n");
        return;
    }

    printf("\n========== BUDGET REPORT ==========\n");

    for (i = 0; i < budgetCount; i++) {
        remaining = calculateBudget(
            budgets[i].allocatedBudget,
            budgets[i].expenditure
        );

        printf("\nDepartment: %s\n",
               budgets[i].department);
        printf("Allocated Budget: N$%.2f\n",
               budgets[i].allocatedBudget);
        printf("Expenditure: N$%.2f\n",
               budgets[i].expenditure);
        printf("Remaining Budget: N$%.2f\n",
               remaining);

        if (remaining < 0) {
            printf("Status: OVER BUDGET\n");
        } else {
            printf("Status: WITHIN BUDGET\n");
        }
    }

    printf("\n===================================\n");
}

/* Display departments that exceeded their budgets */
void displayOverBudget(void)
{
    int i;
    int found = 0;

    printf("\n===== DEPARTMENTS OVER BUDGET =====\n");

    for (i = 0; i < budgetCount; i++) {
        if (budgets[i].expenditure >
            budgets[i].allocatedBudget) {

            printf("Department: %s\n",
                   budgets[i].department);
            printf("Allocated: N$%.2f\n",
                   budgets[i].allocatedBudget);
            printf("Expenditure: N$%.2f\n",
                   budgets[i].expenditure);
            printf("Exceeded by: N$%.2f\n\n",
                   budgets[i].expenditure -
                   budgets[i].allocatedBudget);

            found = 1;
        }
    }

    if (!found) {
        printf("No departments have exceeded "
               "their budgets.\n");
    }
}

/* Budget management menu */
void budgetMenu(void)
{
    int choice;
    char input[100];
    char *end;

    do {
        printf("\n================================\n");
        printf("       BUDGET MANAGEMENT\n");
        printf("================================\n");
        printf("1. Add Departmental Budget\n");
        printf("2. Record Expenditure\n");
        printf("3. Display All Budgets\n");
        printf("4. Show Departments Over Budget\n");
        printf("5. Return to Main Menu\n");
        printf("================================\n");

        printf("Enter your choice: ");
        readLine(input, sizeof(input));

        choice = (int)strtol(input, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (input[0] == '\0' || end == input || *end != '\0') {
            choice = 0;
        }

        switch (choice) {
            case 1:
                addBudget();
                break;

            case 2:
                recordExpenditure();
                break;

            case 3:
                displayBudgets();
                break;

            case 4:
                displayOverBudget();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);
}