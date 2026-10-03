/*
 * assets.c - Asset Management module (I am Student 4 Fredy 226142493)
 * Stores a basic municipal asset register in an array of structs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "assets.h"

#define LINE_LEN 128

static Asset assets[MAX_ASSETS];
static int   assetCount = 0;

static const char *ASSET_TYPES[] = {
    "Vehicle", "Computer", "Building", "Equipment", "Office Furniture", "Other"
};
static const char *ASSET_CONDITIONS[] = { "Excellent", "Good", "Fair", "Poor" };

static int readLine(const char *prompt, char *buf, int size)
{
    int len, start, i;

    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        return 0;
    }
    len = (int)strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else {
        int c;                      /* line too long: discard the rest */
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    while (len > 0 && isspace((unsigned char)buf[len - 1])) {
        buf[--len] = '\0';
    }
    start = 0;
    while (buf[start] != '\0' && isspace((unsigned char)buf[start])) {
        start++;
    }
    if (start > 0) {
        for (i = 0; buf[start + i] != '\0'; i++) {
            buf[i] = buf[start + i];
        }
        buf[i] = '\0';
    }
    return 1;
}

static void readNonEmpty(const char *prompt, char *buf, int size)
{
    while (1) {
        if (!readLine(prompt, buf, size)) {
            buf[0] = '\0';
            return;                 /* end of input */
        }
        if (strlen(buf) > 0) {
            return;
        }
        printf("  Error: this field cannot be empty.\n");
    }
}

static int readIntInRange(const char *prompt, int min, int max)
{
    char line[LINE_LEN];
    char *end;
    long value;

    while (1) {
        if (!readLine(prompt, line, sizeof(line))) {
            return -1;
        }
        value = strtol(line, &end, 10);
        if (line[0] == '\0' || *end != '\0' || value < min || value > max) {
            printf("  Error: enter a whole number from %d to %d.\n", min, max);
        } else {
            return (int)value;
        }
    }
}

/* Reads a non-negative decimal number; repeats until valid. */
static double readNonNegativeDouble(const char *prompt)
{
    char line[LINE_LEN];
    char *end;
    double value;

    while (1) {
        if (!readLine(prompt, line, sizeof(line))) {
            return 0.0;
        }
        value = strtod(line, &end);
        if (line[0] == '\0' || *end != '\0' || !isfinite(value)) {
            printf("  Error: enter a valid number.\n");
        } else if (value < 0) {
            printf("  Error: value cannot be negative.\n");
        } else {
            return value;
        }
    }
}


/* Copies src to dest in lower case. */
static void toLowerCopy(char *dest, const char *src)
{
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

/* Returns 1 if text contains keyword (case-insensitive). */
static int containsIgnoreCase(const char *text, const char *keyword)
{
    char t[LINE_LEN], k[LINE_LEN];

    if (strlen(text) >= sizeof(t) || strlen(keyword) >= sizeof(k)) {
        return 0;
    }
    toLowerCopy(t, text);
    toLowerCopy(k, keyword);
    return strstr(t, k) != NULL;
}

/* Returns 1 if two strings are equal, ignoring case. */
static int equalsIgnoreCase(const char *a, const char *b)
{
    char la[LINE_LEN], lb[LINE_LEN];

    if (strlen(a) >= sizeof(la) || strlen(b) >= sizeof(lb)) {
        return 0;
    }
    toLowerCopy(la, a);
    toLowerCopy(lb, b);
    return strcmp(la, lb) == 0;
}


static void printAssetHeader(void)
{
    printf("\n%-8s %-22s %-17s %-14s %-16s %-10s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("------------------------------------------------------------"
           "-------------------\n");
}

static void printAssetRow(const Asset *a)
{
    printf("%-8s %-22s %-17s %-14.2f %-16s %-10s\n",
           a->id, a->name, a->type, a->purchaseValue,
           a->department, a->condition);
}

/* Lets the user pick one option from a list; copies it into dest. */
static void chooseFromList(const char *title, const char *options[],
                           int count, char *dest)
{
    int i, choice;

    printf("%s\n", title);
    for (i = 0; i < count; i++) {
        printf("  %d. %s\n", i + 1, options[i]);
    }
    choice = readIntInRange("Select option: ", 1, count);
    if (choice < 1) {
        choice = count;             /* EOF fallback */
    }
    strcpy(dest, options[choice - 1]);
}


void addAsset(void)
{
    Asset a;

    printf("\n--- ADD ASSET ---\n");
    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full (%d assets).\n", MAX_ASSETS);
        return;
    }

    snprintf(a.id, sizeof(a.id), "AST%03d", assetCount + 1);
    readNonEmpty("Asset name: ", a.name, sizeof(a.name));
    chooseFromList("Asset type:", ASSET_TYPES, 6, a.type);
    a.purchaseValue = readNonNegativeDouble("Purchase value (N$): ");
    readNonEmpty("Department: ", a.department, sizeof(a.department));
    chooseFromList("Condition:", ASSET_CONDITIONS, 4, a.condition);

    assets[assetCount] = a;
    assetCount++;
    printf("\nAsset added successfully. Assigned ID: %s\n", a.id);
}

void displayAssets(void)
{
    int i;

    printf("\n--- REGISTERED ASSETS ---\n");
    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
    printAssetHeader();
    for (i = 0; i < assetCount; i++) {
        printAssetRow(&assets[i]);
    }
    printf("\nTotal assets: %d\n", assetCount);
}

void searchAsset(void)
{
    char keyword[LINE_LEN];
    int option, i, found = 0;

    printf("\n--- SEARCH ASSETS ---\n");
    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
    printf("Search by:\n  1. Asset ID\n  2. Asset name\n"
           "  3. Asset type\n  4. Department\n");
    option = readIntInRange("Select option: ", 1, 4);
    if (option < 1) {
        return;
    }
    readNonEmpty("Enter search text: ", keyword, sizeof(keyword));

    for (i = 0; i < assetCount; i++) {
        int match = 0;
        switch (option) {
            case 1: match = equalsIgnoreCase(assets[i].id, keyword); break;
            case 2: match = containsIgnoreCase(assets[i].name, keyword); break;
            case 3: match = containsIgnoreCase(assets[i].type, keyword); break;
            case 4: match = containsIgnoreCase(assets[i].department, keyword); break;
        }
        if (match) {
            if (!found) {
                printAssetHeader();
            }
            printAssetRow(&assets[i]);
            found++;
        }
    }
    if (found == 0) {
        printf("No matching assets found.\n");
    } else {
        printf("\n%d asset(s) found.\n", found);
    }
}

int getAssetCount(void)
{
    return assetCount;
}

double getTotalAssetValue(void)
{
    double total = 0.0;
    int i;

    for (i = 0; i < assetCount; i++) {
        total += assets[i].purchaseValue;
    }
    return total;
}

const Asset *getAssetByIndex(int index)
{
    if (index < 0 || index >= assetCount) {
        return NULL;
    }
    return &assets[index];
}

void displayAssetReport(void)
{
    int i, poor = 0;

    printf("\n========== ASSET REPORT ==========\n");
    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
    printAssetHeader();
    for (i = 0; i < assetCount; i++) {
        printAssetRow(&assets[i]);
        if (strcmp(assets[i].condition, "Poor") == 0) {
            poor++;
        }
    }
    printf("\nTotal assets         : %d\n", assetCount);
    printf("Total purchase value : N$%.2f\n", getTotalAssetValue());
    printf("Assets in poor condition: %d\n", poor);
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("           ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add asset\n2. Display assets\n3. Search assets\n"
               "4. Back to main menu\n");
        choice = readIntInRange("Enter your choice: ", 1, 4);
        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            default: break;          /* 4 or EOF: return */
        }
    } while (choice >= 1 && choice != 4);
}
