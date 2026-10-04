#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

#define MAX_REPORT_DEPTS 50

/* ---------- private helpers ---------- */

/* Total monthly pay = basic + housing + transport. */
static double getSalary(const Employee *e)
{
    return e->basicSalary + e->housingAllowance + e->transportAllowance;
}

static void printLine(void)
{
    printf("------------------------------------------------------------\n");
}

static void printHeader(const char *title)
{
    printf("\n========================================\n");
    printf("%s\n", title);
    printf("========================================\n");
}

/* Reads a menu choice safely; returns -1 if the input is not a number. */
static int readChoice(void)
{
    char line[64];
    char *end;
    long value;

    if (fgets(line, sizeof(line), stdin) == NULL)
        return 5;                       /* input closed: leave the menu */
    value = strtol(line, &end, 10);
    while (*end == ' ' || *end == '\t')
        end++;
    if (end == line || (*end != '\n' && *end != '\0'))
        return -1;
    return (int)value;
}

/* ---------- salary helpers ---------- */

double calculateAverageSalary(void)
{
    int count = getEmployeeCount();
    double total = 0.0;
    int i;

    if (count <= 0)
        return 0.0;

    for (i = 0; i < count; i++)
        total += getSalary(getEmployeeByIndex(i));

    return total / count;
}

double findHighestSalary(void)
{
    int count = getEmployeeCount();
    double highest;
    int i;

    if (count <= 0)
        return 0.0;

    highest = getSalary(getEmployeeByIndex(0));     /* start from record 1 */
    for (i = 1; i < count; i++)
        if (getSalary(getEmployeeByIndex(i)) > highest)
            highest = getSalary(getEmployeeByIndex(i));

    return highest;
}

double findLowestSalary(void)
{
    int count = getEmployeeCount();
    double lowest;
    int i;

    if (count <= 0)
        return 0.0;

    lowest = getSalary(getEmployeeByIndex(0));      /* NOT 0 */
    for (i = 1; i < count; i++)
        if (getSalary(getEmployeeByIndex(i)) < lowest)
            lowest = getSalary(getEmployeeByIndex(i));

    return lowest;
}

/* ---------- 1. Employee report ---------- */

void employeeReport(void)
{
    int count = getEmployeeCount();
    char deptNames[MAX_REPORT_DEPTS][CHAR_LENGTH];
    int deptCounts[MAX_REPORT_DEPTS];
    int deptTotal = 0;
    char highestName[CHAR_LENGTH];
    char lowestName[CHAR_LENGTH];
    double highest, lowest;
    int i, j, found;

    printHeader("EMPLOYEE REPORT");

    if (count <= 0) {
        printf("No employees registered.\n");
        return;
    }

    highest = lowest = getSalary(getEmployeeByIndex(0));
    strcpy(highestName, getEmployeeByIndex(0)->name);
    strcpy(lowestName, getEmployeeByIndex(0)->name);

    for (i = 0; i < count; i++) {
        const Employee *e = getEmployeeByIndex(i);
        double s = getSalary(e);

        if (s > highest) {
            highest = s;
            strcpy(highestName, e->name);
        }
        if (s < lowest) {
            lowest = s;
            strcpy(lowestName, e->name);
        }

        /* count employees per department using strcmp */
        found = 0;
        for (j = 0; j < deptTotal; j++) {
            if (strcmp(deptNames[j], e->department) == 0) {
                deptCounts[j]++;
                found = 1;
                break;
            }
        }
        if (!found && deptTotal < MAX_REPORT_DEPTS) {
            strcpy(deptNames[deptTotal], e->department);
            deptCounts[deptTotal] = 1;
            deptTotal++;
        }
    }

    printf("Total Employees : %d\n", count);
    printf("Average Salary  : N$%.2f\n", calculateAverageSalary());
    printf("Highest Salary  : N$%.2f (%s)\n", highest, highestName);
    printf("Lowest Salary   : N$%.2f (%s)\n", lowest, lowestName);

    printf("\nEmployees per department:\n");
    printLine();
    for (j = 0; j < deptTotal; j++)
        printf("%-30s %d\n", deptNames[j], deptCounts[j]);
    printLine();
}

/* ---------- 2. Budget report ---------- */

void budgetReport(void)
{
    int count = getBudgetCount();
    double totalAllocated = 0.0, totalSpent = 0.0;
    int overCount = 0;
    int i;

    printHeader("BUDGET REPORT");

    if (count <= 0) {
        printf("No department budgets registered.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        const Budget *b = getBudgetByIndex(i);
        totalAllocated += b->allocatedBudget;
        totalSpent += b->expenditure;
    }

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Total Remaining Budget : N$%.2f\n", totalAllocated - totalSpent);

    printf("\nDepartments exceeding budget:\n");
    printLine();
    for (i = 0; i < count; i++) {
        const Budget *b = getBudgetByIndex(i);
        if (b->expenditure > b->allocatedBudget) {
            printf("%-30s over by N$%.2f\n", b->department,
                   b->expenditure - b->allocatedBudget);
            overCount++;
        }
    }
    if (overCount == 0)
        printf("None - all departments are within budget.\n");
    printLine();
}

/* ---------- 3. Supplier report ---------- */

void supplierReport(void)
{
    int count = getSupplierCount();
    int i;

    printHeader("SUPPLIER REPORT");

    if (count <= 0) {
        printf("No suppliers registered.\n");
        return;
    }

    printf("%-6s %-20s %-24s %-12s %s\n",
           "ID", "Name", "Email", "Telephone", "Town");
    printLine();
    for (i = 0; i < count; i++) {
        const Supplier *s = getSupplierByIndex(i);
        printf("%-6d %-20s %-24s %-12s %s\n", s->id, s->name,
               s->email, s->phone, s->town);
    }
    printLine();
    printf("Total suppliers: %d\n", count);
}

/* ---------- 4. Asset report ---------- */

void assetReport(void)
{
    int count = getAssetCount();
    int i;

    printHeader("ASSET REPORT");

    if (count <= 0) {
        printf("No assets registered.\n");
        return;
    }

    printf("%-8s %-18s %-10s %-12s %-12s %s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine();
    for (i = 0; i < count; i++) {
        const Asset *a = getAssetByIndex(i);
        printf("%-8s %-18s %-10s %-12.2f %-12s %s\n", a->id, a->name,
               a->type, a->purchaseValue, a->department, a->condition);
    }
    printLine();
    printf("Total assets: %d\n", count);
    printf("Total purchase value: N$%.2f\n", getTotalAssetValue());
}

/* ---------- Reports sub-menu ---------- */

void reportsMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("REPORTS\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");

        choice = readChoice();

        switch (choice) {
        case 1: employeeReport(); break;
        case 2: budgetReport();   break;
        case 3: supplierReport(); break;
        case 4: assetReport();    break;
        case 5: break;
        default: printf("Invalid choice. Please enter 1-5.\n");
        }
    } while (choice != 5);
}