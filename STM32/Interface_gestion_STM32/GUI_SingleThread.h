typedef struct{
	char name[50];
	int barcode;
	int quantity;
	char location[50];
} product;

extern product list;

//Definition des positions
extern int ListItm0[4] = {  0,  0,192, 42};
extern int ListItm1[4] = {  0, 42,192, 84};
extern int ListItm2[4] = {  0, 84,192,126};
extern int ListItm3[4] = {  0,126,192,168};
extern int ListPrev[4] = { 12,200, 92,260};
extern int ListNext[4] = {100,200,180,260};

extern int ItemImag[4] = {199,  5,295,101};
extern int ItemSoOu[4] = {205,212,285,260};
extern int ItemScan[4] = {316,212,396,260};

extern int MenuOpti[4] = {420, 12,468, 60};
extern int MenuBlue[4] = {420,154,468,202};
extern int MenuFina[4] = {420,212,468,260};