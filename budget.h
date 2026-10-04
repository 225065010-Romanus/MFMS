#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 100
#define NAME_LENGTH 100

typedef struct {
    char department[NAME_LENGTH];
    double allocatedBudget;
    double expenditure;
} Budget;

/* Function declarations */
void budgetMenu(void);
void addBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void displayOverBudget(void);
double calculateBudget(double allocated, double expenditure);
int findDepartment(const char name[]);

#endif