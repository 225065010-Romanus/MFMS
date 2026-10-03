# MFMS Test Plan

Tester: [your name]
Build: gcc main.c employees.c budget.c suppliers.c assets.c reports.c -o mfms

## Main Menu
| # | Test | Input | Expected | Result |
|---|---|---|---|---|
| M1 | Valid choice | 1 to 5 | Opens the correct module | |
| M2 | Exit | 6 | Program exits cleanly | |
| M3 | Out of range | 0, 7, -1 | Invalid choice message, menu again | |
| M4 | Letter or empty | a, Enter | No crash or infinite loop | |

## Employees
| # | Test | Input | Expected | Result |
|---|---|---|---|---|
| E1 | Add valid employee | Valid data | Stored | |
| E2 | Negative salary | -5000 | Rejected | |
| E3 | Empty name | Enter | Rejected | |
| E4 | Letters as number | abc | Rejected | |
| E5 | Display when empty | None added | Clear message, no crash | |
| E6 | Search existing | Existing ID/name | Found | |
| E7 | Search missing | Unknown ID/name | "Not found" | |
| E8 | Salary calculation | Basic + housing + transport | Total correct (check by hand) | |

## Budget
| # | Test | Input | Expected | Result |
|---|---|---|---|---|
| B1 | Within budget | 500000 / 420000 | Remaining 80000, WITHIN BUDGET | |
| B2 | Over budget | 100000 / 120000 | EXCEEDED | |
| B3 | Equal | 100000 / 100000 | Remaining 0, status sensible | |
| B4 | Negative values | -1 | Rejected | |
| B5 | Over-budget list | Mixed departments | Only exceeded ones shown | |

## Suppliers
| # | Test | Input | Expected | Result |
|---|---|---|---|---|
| S1 | Add valid supplier | All fields | Stored | |
| S2 | Empty field | Enter | Handled | |
| S3 | Search existing | Existing ID/name | Found | |
| S4 | Search missing | Unknown | "Not found" | |
| S5 | Display when empty | None added | Clear message | |

## Assets
| # | Test | Input | Expected | Result |
|---|---|---|---|---|
| A1 | Add valid asset | All fields | Stored | |
| A2 | Negative value | -100 | Rejected | |
| A3 | Search existing | ID/name | Found | |
| A4 | Search missing | Unknown | "Not found" | |
| A5 | Display when empty | None added | Clear message | |

## Reports
| # | Test | Input | Expected | Result |
|---|---|---|---|---|
| R1 | Employee stats | Several employees | Total, average, highest, lowest correct | |
| R2 | Empty data | No records | No crash, no divide-by-zero | |
| R3 | Budget totals | Several departments | Totals add up | |
| R4 | Supplier/asset reports | Several records | All listed | |

## General
| # | Test | Expected | Result |
|---|---|---|---|
| G1 | Full compile | No errors | |
| G2 | 100-character name | No crash | |
| G3 | Return to main menu from every module | Works | |

## Bugs Found
| Bug | Module | Reported to | Fixed? |
|---|---|---|---|
| multiple definition of main (clashes with main.c) | Suppliers | Christian | No |
| Generic global names MAX and count may clash with other modules | Suppliers | Christian | No 