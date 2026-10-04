#ifndef REPORTS_H
#define REPORTS_H

/* Member 5 - Reports module.
 * Reports read data from the other modules ONLY through their accessor
 * functions (getXCount / getXByIndex), so no module's data is shared directly. */

/* Reports sub-menu - called from main.c (case 5) */
void reportsMenu(void);

/* Individual reports */
void employeeReport(void);
void budgetReport(void);
void supplierReport(void);
void assetReport(void);

/* Helpers that return values */
double calculateAverageSalary(void);
double findHighestSalary(void);
double findLowestSalary(void);

void reportsMenu(void);

#endif