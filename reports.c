#include <stdio.h>
#include "reports.h"
#include "assets.h"
#include "budget.h"
#include "suppliers.h"
#include "employees.h"

extern Employee employees[];

static double computeTotalSalary(void)
{
    double totalSalary = 0.0;
    int i;

    for (i = 0; i < count; i++) {
        totalSalary += computeSalary(&employees[i]);
    }

    return totalSalary;
}

double calculateAverageSalary(void)
{
    if (count <= 0) {
        return 0.0;
    }

    return computeTotalSalary() / count;
}

double findHighestSalary(void)
{
    double highestSalary = 0.0;
    int i;

    if (count <= 0) {
        return 0.0;
    }

    highestSalary = computeSalary(&employees[0]);
    for (i = 1; i < count; i++) {
        double salary = computeSalary(&employees[i]);
        if (salary > highestSalary) {
            highestSalary = salary;
        }
    }

    return highestSalary;
}

double findLowestSalary(void)
{
    double lowestSalary = 0.0;
    int i;

    if (count <= 0) {
        return 0.0;
    }

    lowestSalary = computeSalary(&employees[0]);
    for (i = 1; i < count; i++) {
        double salary = computeSalary(&employees[i]);
        if (salary < lowestSalary) {
            lowestSalary = salary;
        }
    }

    return lowestSalary;
}

void dashboardReport(void)
{
    double totalSalary = 0.0;
    double totalBudget = 0.0;
    double totalExpenditure = 0.0;
    double totalAssetValue = 0.0;
    int i;
    int overBudgetDepartments = 0;

    printf("\n========================================\n");
    printf("          MUNICIPAL FINANCIAL DASHBOARD\n");
    printf("========================================\n");

    printf("Employees registered: %d\n", count);
    if (count > 0) {
        for (i = 0; i < count; i++) {
            totalSalary += computeSalary(&employees[i]);
        }
        printf("Total payroll: N$%.2f\n", totalSalary);
    } else {
        printf("Total payroll: N$0.00\n");
    }

    totalBudget = getTotalAllocatedBudget();
    totalExpenditure = getTotalExpenditure();
    overBudgetDepartments = getOverBudgetDepartmentCount();
    printf("Total allocated budget: N$%.2f\n", totalBudget);
    printf("Total expenditure: N$%.2f\n", totalExpenditure);
    printf("Remaining budget: N$%.2f\n", totalBudget - totalExpenditure);
    printf("Departments over budget: %d\n", overBudgetDepartments);

    printf("Suppliers registered: %d\n", getSupplierCount());
    printf("Assets registered: %d\n", getAssetCount());
    totalAssetValue = getTotalAssetValue();
    printf("Total asset value: N$%.2f\n", totalAssetValue);

    if (overBudgetDepartments > 0) {
        printf("Financial status: NEEDS REVIEW\n");
    } else {
        printf("Financial status: HEALTHY\n");
    }

    printf("========================================\n");
}

void employeeReport(void)
{
    if (count == 0) {
        printf("\nNo employees have been registered yet.\n");
        return;
    }

    printf("\n========== EMPLOYEE REPORT ==========");
    printf("\nTotal employees: %d\n", count);
    printf("Average salary: N$%.2f\n", calculateAverageSalary());
    printf("Highest salary: N$%.2f\n", findHighestSalary());
    printf("Lowest salary: N$%.2f\n", findLowestSalary());
    printf("====================================\n");
}

void budgetReport(void)
{
    displayBudgets();
}

void supplierReport(void)
{
    displaySupplier();
}

void assetReport(void)
{
    displayAssetReport();
}

/* Reports submenu: a quick overview of the most important system summaries */
void reportsMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("                 REPORTS\n");
        printf("========================================\n");
        printf("1. Financial Dashboard\n");
        printf("2. Employee Summary\n");
        printf("3. Budget Summary\n");
        printf("4. Supplier Report\n");
        printf("5. Asset Report\n");
        printf("6. Back to main menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n') {
            }
            choice = 0;
        }

        switch (choice) {
            case 1:
                dashboardReport();
                break;
            case 2:
                employeeReport();
                break;
            case 3:
                budgetReport();
                break;
            case 4:
                supplierReport();
                break;
            case 5:
                assetReport();
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);
}