# MFMS
# Municipal Financial Management System (MFMS)

**Course:** PAP521S - Programming in Practice
**Group number:** [10]
**Repository:** https://github.com/225065010-Romanus/MFMS.git

## Group Members

| Student | Student No. | Responsibility |
|---|---|---|
| [Joel Lusilao] | [226028704] | Employee Management |
| [Immanuel louw] | [226034755] | Budget Management |
| [Christian Mutenzwa] | [225173131] | Supplier Management |
| [Fredy Annanias] | [226142493] | Asset Management |
| [Oscar Myumbelo] | [226] | Reports |
| [Sammy] | [Number] | Functions, integration and validation |
| [Romanus Johannes] | [225065010] | Testing, documentation and Git coordination |

## Project Description

MFMS is a menu-driven console application written in ANSI C (C99) for managing a municipality's finances. It is the foundation version of the system (Project A) and will be extended and refactored in Project B.

## System Features

- Main menu with clear navigation and handling of invalid choices
- Employee management: add, display, search, salary calculation
- Budget management: departmental budgets, expenditure, remaining balance, within/exceeded status, over-budget departments
- Supplier management: add, display, search
- Asset management: asset register, display, search
- Reports: employee, budget, supplier and asset reports
- Input validation (negative values, empty names, invalid numbers and menu choices)

## Project Structure

    MFMS/
    |-- main.c          Main menu and navigation
    |-- employees.c/.h  Employee management
    |-- budget.c/.h     Budget management
    |-- suppliers.c/.h  Supplier management
    |-- assets.c/.h     Asset management
    |-- reports.c/.h    Reports
    |-- TESTING.md      Test plan and bug log
    |-- README.md

## Compilation Instructions

Requires GCC. In the project folder, run:

    gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms

## How to Run

Windows (PowerShell):

    .\mfms



## Individual Responsibilities

Member 1 Joel Lusilao;
I wrote code about employee management where I created a .h file in order to have permanent variables and declare static functions.In the  code i made and implement functions for adding the employees and calculating salaries,setting departments,adding job titles transport allowance and so forth.I had some errors such as putting wrong function names and not putting everything in order.

Member 2 Immanuel louw:
I was responsible for developing the *Budget Management module* for the MFMS project.
I created the budget.c and budget.h files for my assigned module.
The module allows users to add and store departmental budgets.
It allows users to record and manage departmental expenditure.
I implemented calculations for the remaining budget and budget status.
The system identifies departments that have exceeded their allocated budgets.
I used structures, arrays, functions, conditions, loops, strings, and input validation.
I also compiled and tested the module using GCC to ensure that it worked correctly.

Member 3 Christian Mutenzwa
Store each supplier's ID, name, email, telephone number and town/location.
Add suppliers, display them, search for them, and compare/search supplier information.
Supply supplierMenu() so main.c can reach the module.

Member 4 Fredy Annanias;
I developed the Asset Management module (assets.c and assets.h). It stores municipal assets in an array of structs (ID, name, type, purchase value, department, condition). Features: add asset with auto-generated IDs (AST001, AST002...), display all assets in a formatted table, and search by ID, name, type or department (case-insensitive, using strcmp and strstr). Input is validated with loops: empty names, negative or non-numeric values and invalid menu choices are rejected. I also wrote an asset report function (displayAssetReport) plus getAssetCount, getTotalAssetValue and getAssetByIndex for the Reports module, and an assetMenu() submenu for main.c. I tested it by adding multiple assets, searching, and entering invalid input. My work was committed to the group GitHub repository under my account (226142493-Annanias): 'Add Asset struct and function declarations' and 'Add asset register with add, display, search and validation'.

Member 5 Oscar Myumbelo 226133745
Employee report: total employees, average, highest and lowest salary.
Budget report: total allocated budget, total expenditure, remaining budget, and departments over budget.
Supplier report: list the registered suppliers.
Asset report: list the registered assets.
Supply reportsMenu(), and ask the other modules for the data it needs.

Member 6 Samy Mujinga 

This file is the program’s controller. It is supposed to do only three things:

1. show the menu
2. read a valid choice
3. send the user to the correct module

That part is now structured correctly.

What was wrong in the main file
The main issues were:

- weak menu validation
  - it could accept non-numeric input, extra garbage, or out-of-range values
- bad input handling
  - long input lines needed to be cleaned up so the next prompt still works
- weak central routing
  - the app depends on the correct module names and correct headers being linked from here

 What is fixed now
In `main.c`:

- `displayMenu()` cleanly shows the available choices
- `readMenuChoice()` validates:
  - only numbers are accepted
  - the number must be between 1 and 6
  - invalid input is rejected without crashing
- `main()` loops correctly until the user exits
- each menu option calls the right function:
  - `employeeMenu()`
  - `budgetMenu()`
  - `supplierMenu()`
  - `assetMenu()`
  - `reportsMenu()`

 What I changed in the main file logic
The real improvement was making the entrypoint behave like a proper controller:

- it does not let bad choices pass
- it does not crash on garbage input
- it exits cleanly when the user selects 6
And I ran data validation on all the files.


Member 7 Romanus Johannes:
Assigned responsibility: Testing, documentation and Git coordination
(also wrote main.c, normally Student 6's part, and handed the test runs to him)

GitHub contribution
- Created the MFMS repository, .gitignore and starter project structure
  (main.c and a .c/.h pair per module) and invited the group as collaborators
- Removed a stray temp file and updated .gitignore to keep temp files and .exe out
- Wrote and committed README.md and the TESTING.md test plan template
- Fixed a missing #include "reports.h" in reports.c
- Fixed a missing/misspelled #include "suppliers.h" in suppliers.c
- Wrote main.c (main menu, input validation for the menu choice, calls to
  each module's menu function) and fixed its first compile errors


Functions/modules developed
- main.c: displayMenu(), readMenuChoice(), main()

Testing performed
- Compiled the full project with gcc and found errors:
  - "multiple definition of main" (suppliers.c)
  - implicit declarations: employeeMenu, reportsMenu, assetMenu name mismatch
  - supplier.h vs suppliers.h include typo
- Reported each bug to the module owner
- Student 6 is carrying out the test plan runs in TESTING.md 
-

Team coordination
- Explained the Git routine (pull, commit small, pull, push) and the .h/.c
  split to the group