/**
 *	|----------|
 *	| INCLUDES |
 *	|----------|
 */

//Including Components
#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

//---Including Libraries
//Including STM Libraries
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_sdram.h"
#include "RTE_Components.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_Touch.h"                // ::Board Support:Touchscreen
#include "Driver_USART.h"               // ::CMSIS Driver:USART
//Including functionnal Libraries
#include "GUI.h"
#include "stdio.h"
#include <string.h>

//---Including Images
//Buttons icons
#include "icoBluetooth.c"
#include "icoList.c"
#include "icoNext.c"
#include "icoOpti.c"
#include "icoPrev.c"
#include "icoScan.c"
#include "icoSold.c"
//Items images
#include "tomate.c"


/**
 *	|-------|
 *	| SETUP |
 *	|-------|
 */
 
//---Setting up drivers
//UART DRIVERS
extern ARM_DRIVER_USART Driver_USART6;
#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) {
  return os_time;
}
#endif

//GUI INIT
void GUIThread (void const *argument);              // thread function
osThreadId tid_GUIThread;                           // thread id
osThreadDef (GUIThread, osPriorityIdle, 1, 2048);   // thread object


/**
 *	|------------|
 *	| STRUCTURES |
 *	|------------|
 */
 
//---Declaring the structure
struct product { 
	char name[20];
	const GUI_BITMAP *image;
	int  quantity;
	char barcode[20];
	char location[20];
	int  status;
};


/**
 *	|-----------|
 *	| VARIABLES |
 *	|-----------|
 */

//---UI Elements
//List Elements
int ListItm0[4] = {  0,  0,192, 42};
int ListItm1[4] = {  0, 42,192, 84};
int ListItm2[4] = {  0, 84,192,126};
int ListItm3[4] = {  0,126,192,168};
int ListPrev[4] = { 12,200, 92,260};
int ListNext[4] = {100,200,180,260};
//Item Elements
int ItemImag[4] = {199,  5,295,101};
int ItemSoOu[4] = {205,212,285,260};
int ItemScan[4] = {316,212,396,260};
//Menu Elements
int MenuOpti[4] = {420, 12,468, 60};
int MenuBlue[4] = {420,154,468,202};
int MenuFina[4] = {420,212,468,260};

//---Pointer to array
//Pointer to productList
struct product *productList;

//---Variables
//Usage variables
int listSize = 0;
int listPage = 0;
int oldPage = 0;
int BT = 0;
int itemScan = 0;
int itemSoldOut = 0;
int olditemSoldOut = 0;
int itemClick = -1;
int itemClicked = 0;
int finalizeList = 0;


/**
 *	|-----------------------|
 *	| FUNCTIONS DEFINITIONS |
 *	|-----------------------|
 */

//---Functionnal
//
void doScan(int,int,int);
//Checks
int  finalizeCommand(void);
//Updates
void newList(int);
void scanItem(int);
int  setSoldOut(int);
void updateListElement(int,char*,const GUI_BITMAP *,int,char*,int);
void updateQuantity(int,int);
//Job
void strcopy(char[],char[]);
//UART
void UART_init(void);
int  UART_send(char*,int);
int  UART_receive(char[]);
int  UART_transfert(char*, int);
int  UART_transmit(char*, char[]);

//---Drawing
//All
void clearUI(void);
void drawElement(int,int,int,int);
void drawImages(struct product*);
void drawString(char*);
void drawZone(void);
void makeUI(void);
//List
void cleanList(void);
void drawList(void);
//Item
void drawProduct(struct product*);


/**
 *	|------------------------|
 *	| FUNCTIONS DECLARATIONS |
 *	|------------------------|
 */

//---Global Functions
/**
 *  Function   : Init_GUIThread
 *  Parameters : None
 *  Utility    : Initializes the GUI Thread.
 *	Status     : In-use (present at start of the project)
 */
int Init_GUIThread (void) {
  tid_GUIThread = osThreadCreate (osThread(GUIThread), NULL);
  if (!tid_GUIThread) return(-1);
  return(0);
}
/**
 *  Function   : SystemClock_Config
 *  Parameters : None
 *  Utility    : Configure the Clock Frequency.
 *	Status     : In-use (present at start of the project)
 */
static void SystemClock_Config (void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the OverDrive to reach the 200 MHz Frequency */
  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
}
/**
 *  Function   : MPU_Config
 *  Parameters : None
 *  Utility    : Configure the Configure and Enable the MPU.
 *	Status     : In-use (present at start of the project)
 */
static void MPU_Config (void) {
  MPU_Region_InitTypeDef MPU_InitStruct;
  /* Disable the MPU */
  HAL_MPU_Disable();
  /* Configure the MPU attributes for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0xC0200000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_2MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
/**
 *  Function   : CPU_CACHE_Enable
 *  Parameters : None
 *  Utility    : Enables the Cache for the CPU.
 *	Status     : In-use (present at start of the project)
 */
static void CPU_CACHE_Enable (void) {
  /* Enable I-Cache */
  SCB_EnableICache();
  /* Enable D-Cache */
  SCB_EnableDCache();
}
/**
 *  Function   : GUIThread
 *  Parameters : -in : void const *argument (Already given by the Init_GUIThread)
 *  Utility    : Maintain the GUI, main execution.
 *	Status     : In-use (present at start of the project)
 */
void GUIThread (void const *argument) {
  int X = 0,Y = 0;
	int press = 1, oldPress = 0;
	int productDrawned=0, listDrawned=0;
	char name[50], rec[50];
	//---SETUP
	//Init
	MPU_Config ();
	CPU_CACHE_Enable();                       
  HAL_Init();                               
  BSP_SDRAM_Init();                         
  SystemClock_Config();   
	UART_init();                
  GUI_Init();
	Touch_Initialize();	
	//Clear the UI
	GUI_SetBkColor(GUI_WHITE);
  GUI_Clear();
	//Setup
	makeUI();	
  while (1) 
	{
		//---MAIN JOB
		//Draw the images
		drawImages((productList+1+(itemClicked + (4*oldPage))));	
		//Check if a product is printed
		if(productDrawned == 0) 
		{
			drawProduct(productList+1);						
			productDrawned=1;
		}
		//Get touch positions
		X = GUI_TOUCH_GetxPhys();
		Y = GUI_TOUCH_GetyPhys();
		//Get touch states
		GUI_PID_STATE *pState;									
		if(press != GUI_TOUCH_GetState(pState)) 
		{
			press = GUI_TOUCH_GetState(pState);			
			oldPress = 0;
		} 
		else 
		{
			oldPress = 1;
		}			
		if(press == 1 && oldPress == 0) 
		{
			doScan(X,Y, press);
		}		
		//Reload the GUI
		GUI_Exec();
  }
}
/**
 *  Function   : main
 *  Parameters : None
 *  Utility    : Starts the program
 *	Status     : In-use (present at start of the project)
 */
int main (void) {
	newList(4);
	updateListElement(0, "Pommes de terre", &bmtomate,15, "2°Allee, 5°Panier", 0);
	updateListElement(1, "Poireau        ", &bmtomate, 2, "2°Allee, 5°Panier", 0);
	updateListElement(2, "Courgette      ", &bmtomate, 3, "2°Allee, 5°Panier", 0);
	updateListElement(3, "Carotte        ", &bmtomate, 5, "2°Allee, 5°Panier", 0);	
	osKernelInitialize ();                  
  Init_GUIThread();
  osKernelStart ();                         
  osDelay(osWaitForever);
}
//---Functionnal
/**
 *  Function   : doScan
 *  Parameters : -in : int x, 
 *							 -in : int y, 
 *  						 -in : int isPressed
 *  Utility    : Main job ,Scan the possibilities of executions with the X and Y position.
 *							 Do nothing if isPredded = 0
 *	Status     : In-use 
 */
void doScan(int x, int y, int isPressed) {
	char scan[50];
	int finalizeCheck = 0;
	if(isPressed == 1) {
		//---SCAN PART
		//Scan if soldout button is NOT pressed
		if(((x<ItemSoOu[0])||(x>ItemSoOu[2]))||((y<ItemSoOu[1])||(y>ItemSoOu[3])))
		{
			olditemSoldOut = 0;
			sprintf (scan, "                      ");		
		}
		//Scan nav buttons
		if ((x>ListPrev[0])&&(x<ListPrev[2])&&(y>ListPrev[1])&&(y<ListPrev[3]))
		{
			sprintf (scan, "Previous Items !");
			if(listPage > 0) 
			{
				listPage = listPage - 1;
				drawList();
			} 
			else 
			{
				sprintf (scan, "Previous Items ! (MAX)");
			}				
		}
		else if ((x>ListNext[0])&&(x<ListNext[2])&&(y>ListNext[1])&&(y<ListNext[3]))
		{
			sprintf (scan, "Next Items !");
			if((listPage+1)*4 < listSize-1) 
			{
				listPage = listPage + 1;
				drawList();
			} 
			else 
			{
				sprintf (scan, "Next Items ! (MAX)");
			}
		}
		//Scan item sold out button
		else if ((x>ItemSoOu[0])&&(x<ItemSoOu[2])&&(y>ItemSoOu[1])&&(y<ItemSoOu[3]))
		{
			if(olditemSoldOut == 0) 
			{
				itemSoldOut = 1;
			} 
			else if (olditemSoldOut == 1) 
			{
				itemSoldOut = 2;
				olditemSoldOut = 0;
			}			
		}
		//Scan product scan button
		else if ((x>ItemScan[0])&&(x<ItemScan[2])&&(y>ItemScan[1])&&(y<ItemScan[3]))
		{
			sprintf (scan, "Scanning Item");
			itemScan = 1;
		}
		//Scan Options menu
		else if ((x>MenuOpti[0])&&(x<MenuOpti[2])&&(y>MenuOpti[1])&&(y<MenuOpti[3]))
		{
			sprintf (scan, "Options");
		}
		//Scan Bluetooth menu
		else if ((x>MenuBlue[0])&&(x<MenuBlue[2])&&(y>MenuBlue[1])&&(y<MenuBlue[3]))
		{
			sprintf (scan, "Bluetooth");
			BT = 1;
		}
		//Scan List Menu
		else if ((x>MenuFina[0])&&(x<MenuFina[2])&&(y>MenuFina[1])&&(y<MenuFina[3]))
		{
			sprintf (scan, "Finalizing Command");
			finalizeList = 1;
		}
		//Scan on Item that are on the list
		else if ((x>ListItm0[0])&&(x<ListItm0[2])&&(y>ListItm0[1])&&(y<ListItm0[3]))
		{
			sprintf (scan, "Item 1 in list");
			itemClick = 0;
		}
		else if ((x>ListItm1[0])&&(x<ListItm1[2])&&(y>ListItm1[1])&&(y<ListItm1[3]))
		{
			sprintf (scan, "Item 2 in list");
			itemClick = 1;
		}
		else if ((x>ListItm2[0])&&(x<ListItm2[2])&&(y>ListItm2[1])&&(y<ListItm2[3]))
		{
			sprintf (scan, "Item 3 in list");
			itemClick = 2;
		}
		else if ((x>ListItm3[0])&&(x<ListItm3[2])&&(y>ListItm3[1])&&(y<ListItm3[3]))
		{
			sprintf (scan, "Item 4 in list");
			itemClick = 3;
		} 
		
		//---EXECUTION PART
		//Executing item clicking
		if(itemClick != -1) 
		{
			oldPage = listPage;
			if(itemClick + (4*oldPage) < listSize-1)
			{
				drawProduct((productList+1+(itemClick + (4*oldPage))));
			}
			itemClicked = itemClick;
			itemClick = -1;
		}
		//Executing item scan
		if(itemScan == 1) 
		{			
			if((productList+1+(itemClicked + (4*oldPage)))->quantity > 0) 
			{
				scanItem(itemClicked + (4*oldPage));
				drawList();
				drawProduct((productList+1+(itemClicked + (4*oldPage))));
			} 
			else 
			{
				sprintf (scan, "Item quantity = 0");
			}
			itemScan = 0;
		}
		//Executing item soldout 
		if(itemSoldOut == 1 || itemSoldOut == 2) 
		{
			if(itemSoldOut == 1) 
			{
				sprintf (scan, "Are you sure ?");	
				olditemSoldOut = 1;
			}
			else if(itemSoldOut == 2) 
			{
				int state = 0;
				state = setSoldOut(itemClicked + (4*oldPage));
				drawList();
				drawProduct((productList+1+(itemClicked + (4*oldPage))));
				if(state == 0) 
				{
					sprintf (scan, "Item set as Sold Out");
				} 
				else 
				{
					sprintf (scan, "Can't set as Sold Out");					
				}
			}			
			itemSoldOut = 0;
		}
		//Executing list finalizing 
		if(finalizeList == 1) 
		{
			finalizeCheck = finalizeCommand();
			if(finalizeCheck == 0) 
			{
				sprintf (scan, "List is not finished");				
			} 
			else if (finalizeCheck == -1)
			{
				sprintf (scan, "List finished with sold out");					
			} 
			else 
			{
				sprintf (scan, "List finished !");	
			}
			if(finalizeCheck != 0) 
			{
				clearUI();
				GUI_SetFont(&GUI_Font20_1);
				drawString(scan);
				osDelay(1000);
				sprintf (scan, "Getting new list");				
				clearUI();
				GUI_SetFont(&GUI_Font20_1);
				drawString(scan);
				newList(7);
				updateListElement(0, "Farine   ", &bmtomate, 1, "1°Allee, 3°Panier  ", 0);
				updateListElement(1, "Chocolat ", &bmtomate, 3, "8°Allee, 3°Panier  ", 0);
				updateListElement(2, "Lait     ", &bmtomate, 6, "2°Allee, 3°Panier  ", 0);
				updateListElement(3, "Levure   ", &bmtomate, 1, "10°Allee, 12°Panier", 0);
				updateListElement(4, "Yaourt   ", &bmtomate, 2, "6°Allee, Frigidaire", 0);
				updateListElement(5, "Camembert", &bmtomate, 1, "6°Allee, Frigidaire", 0);
				updateListElement(6, "Courgette", &bmtomate, 3, "3°Allee, 1°Panier  ", 0);
				osDelay(1000);
				sprintf (scan, "List obtained !");
				clearUI();
				GUI_SetFont(&GUI_Font20_1);
				drawString(scan);
				itemClicked = 0;
				listPage = 0;
				oldPage = 0;		
				drawList();		
				drawProduct((productList+1+(itemClicked + (4*oldPage))));
			}
			finalizeList = 0;
		}
		//Executing Bluetooth pairing
		if(BT == 1) 
		{
			int err = 0, state = 0;	
			char rec[50];
			while(state != 1) 
			{
				err = UART_send("AT+PAIR=00,1C,97,14,35,02,5000", 25);		
				err = UART_receive(rec);
				if(strcmp(rec, "OK") || strcmp(rec, "FAIL"))
				{
					state = 1;
				}
				osDelay(100);	
			}
			if(strcmp(rec, "OK")) 
			{
				sprintf (scan, "Connected !");
			}
			if(strcmp(rec, "FAIL")) 
			{
				sprintf (scan, "Failed to connect");
			}
			BT = 0;
		}		
		clearUI();
		GUI_SetFont(&GUI_Font20_1);
		drawString(scan);
	}
}
/**
 *  Function   : finalizeCommand
 *  Parameters : -out: int
 *  Utility    : Returns the state of the Command
 * 							 Returns  0 if Command is not finished
 *							 Returns  1 if Command is done without error
 *							 Returns -1 if Command is done with error
 *	Status     : In-use 
 */
int finalizeCommand() {
	int code = 0;
	for(int i=0; i<listSize-1; i++) 
	{
		if((productList+1+i)->status==0) 
		{
			return 0;
		} 
		else if ((productList+1+i)->status==-1) 
		{
			code = -1;
		}		
	}
	if(code == 0)
	{
		code = 1;
	}
	
	return code;
}
/**
 *  Function   : newList
 *  Parameters : -in : int s
 *  Utility    : Clear the last List and allocate memory for a new one.
 *	Status     : In-use 
 */
void newList(int s) {
	free(productList);
	listSize = s+1;
	productList = (struct product*) malloc(listSize * sizeof(struct product));	
}
/**
 *  Function   : scanItem
 *  Parameters : -in : int no
 *  Utility    : Scans the item
 *	Status     : In-use (Not-Finished)

 *  Usage      : Should listen to bluetooth entries and launch the update after.
 */
void scanItem(int no) {
	int scan = 1;
	
	if(scan == 1) 
	{
		updateQuantity(no, 1);
	}	
}
/**
 *  Function   : setSoldOut
 *  Parameters : -in : int no,
 *               -out: int
 *  Utility    : Set an item as SoldOut
 *               Returns 1 if item status different of 0
								 Returns 0 if function succeed
 *	Status     : In-use
 */
int setSoldOut(int no) {
	if((productList+1+no)->status != 0) 
	{
		return 1;		
	}
	(productList+1+no)->quantity = -1;
	(productList+1+no)->status = -1;	
	return 0;
}
/**
 *  Function   : strcopy
 *  Parameters : -in : char name[],
 *               -in : char prod[]
 *  Utility    : Copy the string from name to prod
 *	Status     : In-use
 */
void strcopy(char name[],char prod[]) {
	int c=0;
	while (name[c] != '\0') 
	{
    prod[c] = name[c];
    c++;
	}
	prod[c] = 0;
}
/**
 *  Function   : UART_init
 *  Parameters : none
 *  Utility    : Initialize the UART communication
 *	Status     : In-use
 */
void UART_init() {
	Driver_USART6.Initialize(NULL);
	Driver_USART6.PowerControl(ARM_POWER_FULL);
	Driver_USART6.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_NONE		|
							ARM_USART_FLOW_CONTROL_NONE,
							38400);	
	Driver_USART6.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART6.Control(ARM_USART_CONTROL_RX,1);
}
/**
 *  Function   : UART_send
 *  Parameters : -in :char *string, 
 *               -in : int size
 *               -out: int
 *  Utility    : Send the string via UART (Size needed)
 *               Returns  0 if succeed
 *               Returns -1 if error
 *	Status     : In-use
 */
int UART_send(char *string, int size) {
	int32_t err;
	while(Driver_USART6.GetStatus().tx_busy == 1); // attente buffer TX vide
	err = Driver_USART6.Send(string,size);
	if(err != 0) 
  {
		return -1;
	}		
	else 
  {
		return 0;	
	}
}
/**
 *  Function   : UART_receive
 *  Parameters : -in : char receive_tab[]
 *               -out: int
 *  Utility    : Receive contents from UART (Non-Blocking)
 *               Returns  0 if succeed
 *               Returns -1 if error
 *	Status     : In-use (Not-Finished)

 *  Usage : Needs to be tested
 */
int UART_receive(char receive_tab[]) {
	int32_t err;
	int i;
	while(Driver_USART6.GetStatus().rx_busy==1); 
	err = Driver_USART6.Receive(receive_tab,6);	
	if(err != 0) 
  {
	  return -1;
	} 
	else 
  {
	  return 0;
	}
}
/**
 *  Function   : UART_transfert
 *  Parameters : -in : char *string, 
 *               -in : int size
 *               -out: int
 *  Utility    : Send a command to Bluetooth HC-05 and get returns
 *               Returns  0 if succeed
 *               Returns -1 if error
 *	Status     : In-use (Not-Finished)

 *  Usage : Needs to be tested
 */
int UART_transfert(char *string, int size) {
	int Y = 0;
	char rec[50];
	while(Y != 1)
	{
		UART_send(string, size);		
		UART_receive(rec);
		if(strncmp(rec, "OK\r\n", 4) == 0) 
		{
			Y = 1;
			drawString("OK");
		} 
    else 
    {
		  drawString(rec);
		}		
		osDelay(200);
		GUI_Exec();
	}
}
/**
 *  Function   : updateQuantity
 *  Parameters : -in : int no,
 *               -in : int nbr
 *  Utility    : Reduce the quantity needed for the selected item
 *               no used to select the item
 *               nbr used to reduce the quantity
 *	Status     : In-use 
 */
void updateQuantity(int no,int nbr) {
	(productList+1+no)->quantity = (productList+1+no)->quantity - nbr;
	if((productList+1+no)->quantity==0) 
  { 
	  (productList+1+no)->status = 1; 
	}
}
/**
 *  Function   : updateListElement
 *  Parameters : -in : int pos, 
 *               -in : char* name,
 *               -in : const GUI_BITMAP *bmp, 
 *               -in : int quantity, 
 *               -in : char* place, 
 *               -in : int status
 *  Utility    : Update the item at pos
 *	Status     : In-use 
 */
void updateListElement(int pos, char* name, const GUI_BITMAP *bmp, int quantity, char* place, int status) {
	strcopy(name,(productList+1+pos)->name);
	(productList+1+pos)->image = bmp;
	(productList+1+pos)->quantity = quantity;
	strcopy(place,(productList+1+pos)->location);		
	(productList+1+pos)->status = status;
}
//---Drawing
/**
 *  Function   : cleanList
 *  Parameters : none
 *  Utility    : Clean the list
 *	Status     : In-use 
 */
void cleanList() {
	char list[50];
	for(int i=0;i<=3;i++) 
	{
		GUI_SetFont(&GUI_Font16_1);
		sprintf(list,"                          ");
		GUI_DispStringAt(list, 5, i*42 +13); 
		GUI_SetFont(&GUI_Font10_1);
		sprintf(list,"       ");
		GUI_DispStringAt(list, 167, i*42 +16); 
	}
}
/**
 *  Function   : clearUI
 *  Parameters : none
 *  Utility    : Clear completly the UI
 *	Status     : In-use 
 */
void clearUI() {
	char texte[50];
	sprintf (texte, "                                                 ");
	drawString(texte);
	makeUI();
}
/**
 *  Function   : drawElement
 *  Parameters : -in : int x1,
 *               -in : int y1,
 *               -in : int x2, 
 *               -in : int y2
 *  Utility    : Draw a rectangle between the points
 *	Status     : In-use 
 */
void drawElement(int x1, int y1, int x2, int y2) {
	GUI_SetPenSize(1);
	GUI_DrawRect(x1,y1,x2,y2);
}
/**
 *  Function   : drawImages
 *  Parameters : -in : struct product *prod
 *  Utility    : Draws the images on the UI
 *	Status     : In-use 
 */
void drawImages(struct product *prod) {
	GUI_DrawBitmap(prod->image, ItemImag[0], ItemImag[1]); 	
	GUI_DrawBitmap(&bmicoPrev, ListPrev[0], ListPrev[1]);
	GUI_DrawBitmap(&bmicoNext, ListNext[0], ListNext[1]); 
	GUI_DrawBitmap(&bmicoSold, ItemSoOu[0], ItemSoOu[1]); 
	GUI_DrawBitmap(&bmicoScan, ItemScan[0], ItemScan[1]); 
	GUI_DrawBitmap(&bmicoOpti, MenuOpti[0], MenuOpti[1]); 
	GUI_DrawBitmap(&bmicoBluetooth, MenuBlue[0], MenuBlue[1]); 
	GUI_DrawBitmap(&bmicoList, MenuFina[0], MenuFina[1]); 
}
/**
 *  Function   : drawList
 *  Parameters : none
 *  Utility    : Draws the list
 *	Status     : In-use 
 */
void drawList() {	
	int i;
	char item[50];
	GUI_SetColor(GUI_BLACK);	
	drawElement(ListItm0[0],ListItm0[1],ListItm0[2],ListItm0[3]);
	drawElement(ListItm1[0],ListItm1[1],ListItm1[2],ListItm1[3]);
	drawElement(ListItm2[0],ListItm2[1],ListItm2[2],ListItm2[3]);
	drawElement(ListItm3[0],ListItm3[1],ListItm3[2],ListItm3[3]);
	cleanList();
	for(i=0;i<=3;i++) 
	{
		GUI_SetFont(&GUI_Font16_1);
		if((i + (4*listPage)) < listSize-1) 
		{ 
			GUI_SetFont(&GUI_Font16_1);
			sprintf(item,"%s", (productList+1+(i + (4*listPage)))->name);
			GUI_DispStringAt(item, 5, i*42 +13); 
			GUI_SetFont(&GUI_Font10_1);
			if((productList+1+(i + (4*listPage)))->quantity > 0) 
			{ 
			  sprintf(item,"x%02d", (productList+1+(i + (4*listPage)))->quantity);
			} 
			else if((productList+1+(i + (4*listPage)))->quantity == -1) 
			{ 
				GUI_SetColor(GUI_RED);
				sprintf(item,"Out ");
			}	
      else 
      { 
			  sprintf(item,"Ok !");
			}
			GUI_DispStringAt(item, 167, i*42 +16); 
			GUI_SetColor(GUI_BLACK);} 
	}
}
/**
 *  Function   : drawProduct
 *  Parameters : none
 *  Utility    : Draws the product on the Item part of the UI
 *	Status     : In-use 
 */
void drawProduct(struct product* prod) {
	char item[50]="";	
	GUI_SetFont(&GUI_Font24_1);
	GUI_DispStringAt("                               ", 204, 115); 
	GUI_SetFont(&GUI_Font16_1);
	GUI_DispStringAt("                               " , 204, 140); 
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringAt("                 ", 300, 85); 
	GUI_SetFont(&GUI_Font24_1);
	GUI_DispStringAt(prod->name , 204, 115); 
	GUI_SetFont(&GUI_Font16_1);
	GUI_DispStringAt(prod->location , 204, 140); 
	GUI_SetFont(&GUI_Font20_1);
	if(prod->quantity > 0) 
  { 
	  sprintf(item," x%02d",prod->quantity);
	}	
  else if(prod->quantity == -1) 
  { 
	  sprintf(item,"Sold Out !");
	} 
  else 
  { 
	  sprintf(item,"complete");
	}
	GUI_DispStringAt(item, 300, 85); 
}
/**
 *  Function   : drawString
 *  Parameters : in : char *txt
 *  Utility    : Prints a message on the UI 
 *	Status     : In-use 
 */
void drawString(char *txt) {	
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringAt(txt, 5, 175);
}
/**
 *  Function   : drawZone
 *  Parameters : none
 *  Utility    : Separates hte parts of the UI (List - Item - Menu)
 *	Status     : In-use 
 */
void drawZone() {
	GUI_SetPenSize(2);		
	GUI_SetColor(GUI_BLACK);
	GUI_DrawLine(192, 0, 192, 272);		
	GUI_DrawLine(408, 0, 408, 272);		
}
/**
 *  Function   : makeUI
 *  Parameters : none
 *  Utility    : Draws the UI
 *	Status     : In-use 
 */
void makeUI() {
	drawZone(); 
	drawImages((productList+1+(itemClicked + (4*oldPage))));
	drawList();
}
