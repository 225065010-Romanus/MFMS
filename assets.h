#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS     100
#define ASSET_ID_LEN   16
#define ASSET_NAME_LEN 50
#define ASSET_TYPE_LEN 30
#define ASSET_DEPT_LEN 30
#define ASSET_COND_LEN 15

typedef struct {
    char   id[ASSET_ID_LEN];
    char   name[ASSET_NAME_LEN];
    char   type[ASSET_TYPE_LEN];
    double purchaseValue;
    char   department[ASSET_DEPT_LEN];
    char   condition[ASSET_COND_LEN];
} Asset;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);

void displayAssetReport(void);
int  getAssetCount(void);
double getTotalAssetValue(void);
const Asset *getAssetByIndex(int index);

#endif
