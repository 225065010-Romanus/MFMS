/*
 * employee.c
 *
 *  Created on: Oct 3, 2026
 *      Author: Joel Lusilao
 */

#include <stdio.h>
#include <string.h>
#include "employees.h"

/* Function to create an Employee */
void createEmployee(Employee *employee, const char *name, const char *department,
                        const char *jobTitle, const char *contactNumber, int id, 
                        double housingAllowance, double transportAllowance, double basicSalary)
{
   

    
    printf("\n========== ADD EMPLOYEE ==========\n");

    printf("Name: ");
    strcpy(employee->name, name);
    printf("Department: ");
    strcpy(employee->department, department);
    printf("Job Title: ");
    strcpy(employee->jobTitle, jobTitle);
    printf("Contact Number: ");
    strcpy(employee->contactNumber, contactNumber);
    employee->id = id;
    printf("ID: %d\n", employee->id);
    employee->housingAllowance = housingAllowance;
    printf("Housing Allowance: %.2f\n", employee->housingAllowance);
    employee->transportAllowance = transportAllowance;
    printf("Transport Allowance: %.2f\n", employee->transportAllowance);
    employee->basicSalary = basicSalary;
  
}

/* Function to add many employees */

    char choice;
void addEmployees(void)
{
    do {
        if (count >= MAX_EMPLOYEES) {
            printf("\nEmployee storage is full.\n");
            break;
        }

        char name[50];
        char department[50];
        char jobTitle[50];
        char contactNumber[20];
        int id;
        double housingAllowance;
        double transportAllowance;
        double basicSalary;

        printf("\n========================================\n");
        printf("           ADD EMPLOYEE\n");
        printf("========================================\n");

        printf("Name: ");
        scanf(" %49[^\n]", name);

        printf("Department: ");
        scanf(" %49[^\n]", department);

        printf("Job Title: ");
        scanf(" %49[^\n]", jobTitle);

        printf("Contact Number: ");
        scanf(" %19s", contactNumber);

        printf("ID: ");
        scanf("%d", &id);

        printf("Basic Salary: ");
        scanf("%lf", &basicSalary);

        printf("Housing Allowance: ");
        scanf("%lf", &housingAllowance);

        printf("Transport Allowance: ");
        scanf("%lf", &transportAllowance);

        createEmployee(
            &employees[count],
            name,
            department,
            jobTitle,
            contactNumber,
            id,
            housingAllowance,
            transportAllowance,
            basicSalary
        );
        count++;
        printf("\nEmployee added successfully!\n");

        printf("\nDo you want to add another employee? (Y/N): ");
        scanf(" %c", &choice);

    } while (choice == 'Y' || choice == 'y');
}

/* Function to retrieve the employee name */
const char* getName(const Employee *employee)
{
    return employee->name;
}


/* Function to set the employee name */
void setName(Employee *employee, const char *name)
{
    strcpy(employee->name, name);
}

/* Function to retrieve the employee department */
const char* getDepartment(const Employee *employee)
{
    return employee->department;
}


/* Function to set the department name */
void setDepartment(Employee *employee, const char *department)
{
    strcpy(employee->department, department);
}

/* Function to retrieve the job title */
const char* getJobTitle(const Employee *employee)
{
    return employee->jobTitle;
}

/* Function to set the job title */
void setJobTitle(Employee *employee, const char *jobTitle)
{
    strcpy(employee->jobTitle, jobTitle);
}
/* Function to retrieve the contact number */
const char* getContactNumber(const Employee *employee)
{
    return employee->contactNumber;
}

/* Function to set the contact number */
void setContactNumber(Employee *employee, const char *contactNumber)
{
    strcpy(employee->contactNumber, contactNumber);
}
/* Function to retrieve the ID */
int getID(const Employee *employee)
{
    return employee->id;
}


/* Function to set the ID */
void setID(Employee *employee, int id)
{
    employee->id = id;
}


/* Function to set the housing allowance */
void setHousingAllowance(Employee *employee, double housingAllowance)
{
    employee->housingAllowance = housingAllowance;
}

/* Function to retrieve the housing allowance */
double getHousingAllowance(const Employee *employee)
{
    return employee->housingAllowance;
}

/* Function to set the transport allowance */
void setTransportAllowance(Employee *employee, double transportAllowance)
{
    employee->transportAllowance = transportAllowance;
}

/* Function to retrieve the transport allowance */
double getTransportAllowance(const Employee *employee)
{
    return employee->transportAllowance;
}

/* Function to retrieve the basic salary */
double getBasicSalary(const Employee *employee)
{
    return employee->basicSalary;
}

/* Function to set the basic salary */
void setBasicSalary(Employee *employee, double basicSalary)
{
    employee->basicSalary = basicSalary;
}


/* Function to compute  the salary from the  salary and allowances */
double computeSalary(Employee *employee)
{
    double salary =
        employee->basicSalary + 
        employee->housingAllowance+
        employee->transportAllowance;
    return salary;
}


/* Function to print employee details */
void printEmployeeDetails(const Employee *employee)
{
    printf("Name: %s\n", employee->name);
    printf("Department: %s\n", employee->department);
    printf("Job Title: %s\n", employee->jobTitle);
    printf("Contact Number: %s\n", employee->contactNumber);
    printf("ID: %d\n", employee->id);
    printf("Basic Salary: %.2f\n", employee->basicSalary);
    printf("Housing Allowance: %.2f\n", employee->housingAllowance);
    printf("Transport Allowance: %.2f\n", employee->transportAllowance);
}

/* Function to search an Employee */
Employee* searchEmployee(Employee *employees)
{
    int id;
    char name[CHAR_LENGTH];
    int choice;

    printf("\n");
    printf("Do you want to search for an employee?\n");
    printf("1. Search by ID\n");
    printf("2. Search by name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Enter the ID: ");
        scanf("%d", &id);
        if ((id <= 0)) {
            printf("Invalid employee ID.\n");
            return NULL;
        }

        for (int i = 0; i < MAX_EMPLOYEES; i++) {
            if (employees[i].id == id) {
                printEmployeeDetails(&employees[i]);
                return &employees[i];
            }
        }

        printf("Employee not found.\n");
        return NULL;

    case 2:
        printf("Enter the name: ");
        scanf("%s", name);

        for (int i = 0; i < MAX_EMPLOYEES; i++) {
            if (strcmp(name, employees[i].name) == 0) {
                printf("Found: %s\n", employees[i].name);
                printEmployeeDetails(&employees[i]);
                return &employees[i];
            }
        }

        printf("Employee not found.\n");
        return NULL;

    default:
        printf("Invalid option.\n");
        return NULL;
    }
}



