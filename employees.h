#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES      100
#define CHAR_LENGTH        100
#define PHONE_LENGTH       20

/* Shared employee state across the employee module */
extern int count;

/* Define the Employee structure */
typedef struct {
    char name[CHAR_LENGTH];
    char department[CHAR_LENGTH];
    char jobTitle[CHAR_LENGTH];
    char contactNumber[PHONE_LENGTH];
    int id;
    double housingAllowance;
    double transportAllowance;
    double basicSalary;
} Employee;

/* Function to create an Employee */
void createEmployee(Employee *, const char *, const char *,
                    const char *, const char *contactNumber, int , double, double, double );
/* Function to add one or more employees from the employee submenu */
void addEmployees(void);
/* Function to show the employee management menu */
void employeeMenu(void);
/* Function to retrieve the employee name */
const char* getName(const Employee *);
/* Function to set the employee department */
void setName(Employee *, const char *);
/* Function to retrieve the employee department */
const char* getDepartment(const Employee *);
/* Function to set the employee department */
void setDepartment(Employee *, const char *);
/* Function to retrieve the employee job title */
const char* getJobTitle(const Employee *);
/* Function to set the employee job title */
void setJobTitle(Employee *, const char *);
/* Function to retrieve the employee contact number */
const char* getContactNumber(const Employee *);
/* Function to set the employee contact number */
void setContactNumber(Employee *, const char *);
/* Function to retrieve the employee ID */
int getID(const Employee *);
/* Function to set the employee ID */
void setID(Employee *employee, int );
/* Function to set the employee housing allowance */
void setHousingAllowance(Employee *, double );
/* Function to retrieve the employee housing allowance */
double getHousingAllowance(const Employee *employee);
/* Function to set the employee transport allowance */
void setTransportAllowance(Employee *, double );
/* Function to retrieve the employee transport allowance */
double getTransportAllowance(const Employee *);
/* Function to retrieve the employee basic salary */
double getBasicSalary(const Employee *);
/* Function to set the employee basic salary */
void setBasicSalary(Employee *, double);
/* Function to compute  the salary from basic salary and allowances */
double computeSalary(Employee *);
/* Function to display employee details */
void printEmployeeDetails(const Employee *);
/* Function to search an Employee */
Employee* searchEmployee(Employee *);

#endif