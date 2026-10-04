/*
 * employee.c
 *
 *  Created on: Oct 3, 2026
 *      Author: Joel Lusilao
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employees.h"

/* This module keeps the actual employee list and the employee counter */
Employee employees[MAX_EMPLOYEES];
int count = 0;

static void trimWhitespace(char *text)
{
    size_t len;
    char *start;
    char *end;

    if (text == NULL) {
        return;
    }

    while (*text == ' ' || *text == '\t' || *text == '\r' || *text == '\n') {
        text++;
    }

    start = text;
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

static int readRequiredText(const char *prompt, char *buffer, size_t size)
{
    char line[200];

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            buffer[0] = '\0';
            return 0;
        }

        trimWhitespace(line);

        if (line[0] == '\0') {
            printf("This field cannot be empty. Please try again.\n");
            continue;
        }

        if (strlen(line) >= size) {
            printf("Input is too long. Please enter a shorter value.\n");
            continue;
        }

        strcpy(buffer, line);
        return 1;
    }
}

static int readIntegerValue(const char *prompt, int *value)
{
    char line[128];
    char *end;
    long result;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 0;
        }

        trimWhitespace(line);

        if (line[0] == '\0') {
            printf("This field cannot be empty. Please try again.\n");
            continue;
        }

        result = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t') {
            end++;
        }

        if (end == line || *end != '\0') {
            printf("Invalid number. Please enter a valid integer.\n");
            continue;
        }

        *value = (int)result;
        return 1;
    }
}

static int readDoubleValue(const char *prompt, double *value)
{
    char line[128];
    char *end;
    double result;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 0;
        }

        trimWhitespace(line);

        if (line[0] == '\0') {
            printf("This field cannot be empty. Please try again.\n");
            continue;
        }

        result = strtod(line, &end);
        while (*end == ' ' || *end == '\t') {
            end++;
        }

        if (end == line || *end != '\0') {
            printf("Invalid number. Please enter a valid decimal value.\n");
            continue;
        }

        *value = result;
        return 1;
    }
}

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

static int employeeIdExists(int id)
{
    int i;

    for (i = 0; i < count; i++) {
        if (employees[i].id == id) {
            return 1;
        }
    }

    return 0;
}

/* Function to add many employees */
char choice;
void addEmployees(void)
{
    char name[50];
    char department[50];
    char jobTitle[50];
    char contactNumber[20];
    int id;
    double housingAllowance;
    double transportAllowance;
    double basicSalary;

    do {
        if (count >= MAX_EMPLOYEES) {
            printf("\nEmployee storage is full.\n");
            break;
        }

        printf("\n========================================\n");
        printf("           ADD EMPLOYEE\n");
        printf("========================================\n");

        if (!readRequiredText("Name: ", name, sizeof(name))) {
            return;
        }

        if (!readRequiredText("Department: ", department, sizeof(department))) {
            return;
        }

        if (!readRequiredText("Job Title: ", jobTitle, sizeof(jobTitle))) {
            return;
        }

        if (!readRequiredText("Contact Number: ", contactNumber, sizeof(contactNumber))) {
            return;
        }

        if (!readIntegerValue("ID: ", &id) || id <= 0) {
            printf("Employee ID must be a positive number.\n");
            return;
        }

        if (employeeIdExists(id)) {
            printf("Employee ID %d already exists. Please use a unique ID.\n", id);
            return;
        }

        if (!readDoubleValue("Basic Salary: ", &basicSalary) || basicSalary < 0) {
            printf("Basic salary cannot be negative.\n");
            return;
        }

        if (!readDoubleValue("Housing Allowance: ", &housingAllowance) || housingAllowance < 0) {
            printf("Housing allowance cannot be negative.\n");
            return;
        }

        if (!readDoubleValue("Transport Allowance: ", &transportAllowance) || transportAllowance < 0) {
            printf("Transport allowance cannot be negative.\n");
            return;
        }

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
        if (scanf(" %c", &choice) != 1) {
            choice = 'N';
        }
        while (getchar() != '\n') {
        }

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

/* Employee submenu: simple navigation to the employee-related actions */
void employeeMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("           EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add employee\n");
        printf("2. Search employee\n");
        printf("3. Back to main menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployees();
                break;
            case 2:
                searchEmployee(employees);
                break;
            case 3:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);
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
    if (scanf("%d", &choice) != 1) {
        printf("Invalid option.\n");
        while (getchar() != '\n') {
        }
        return NULL;
    }
    while (getchar() != '\n') {
    }

    switch (choice) {
    case 1:
        if (!readIntegerValue("Enter the ID: ", &id) || id <= 0) {
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
        if (!readRequiredText("Enter the name: ", name, sizeof(name))) {
            return NULL;
        }

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



