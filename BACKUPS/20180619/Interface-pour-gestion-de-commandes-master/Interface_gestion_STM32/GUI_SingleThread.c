
#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_sdram.h"
#include "RTE_Components.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_Touch.h"                // ::Board Support:Touchscreen
#include "GUI.h"
#include "stdio.h"
#include "Driver_USART.h"               // ::CMSIS Driver:USART

#include <string.h>

//#include "GUI_SingleThread.h"

// fichier image
#include "icoBluetooth.c"
#include "icoList.c"
#include "icoNext.c"
#include "icoOpti.c"
#include "icoPrev.c"
#include "icoScan.c"
#include "icoSold.c"

extern ARM_DRIVER_USART Driver_USART6;

#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) {
  return os_time;
}
#endif

struct product { 
	char name[20];
	int  quantity;
	char barcode[20];
	char location[20];
	int  status;
};

/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
int ListItm0[4] = {  0,  0,192, 42};
int ListItm1[4] = {  0, 42,192, 84};
int ListItm2[4] = {  0, 84,192,126};
int ListItm3[4] = {  0,126,192,168};
int ListPrev[4] = { 12,200, 92,260};
int ListNext[4] = {100,200,180,260};

int ItemImag[4] = {199,  5,295,101};
int ItemSoOu[4] = {205,212,285,260};
int ItemScan[4] = {316,212,396,260};

int MenuOpti[4] = {420, 12,468, 60};
int MenuBlue[4] = {420,154,468,202};
int MenuFina[4] = {420,212,468,260};

struct product *productList;
int listSize = 6;

//Usage variables
char texte[50];
int writeState = 0;
int listPage = 0;
int oldPage = 0;
int BT = 0;
int itemScan = 0;
int itemSoldOut = 0;
int itemClick = -1;
int itemClicked = 0;
int finalizeList = 0;
int finalizeCheck = 0;
//GuiInit
void GUIThread (void const *argument);              // thread function
osThreadId tid_GUIThread;                           // thread id
osThreadDef (GUIThread, osPriorityIdle, 1, 2048);   // thread object

//Functionnal
void doScan(int,int,int);
int finalizeCommand(void);
void Init_UART(void);
void scanItem(int);
int setSoldOut(int);
void strcopy(char[],char[]);
void updateQuantity(int,int);
int UART_send(char*,int);
int UART_receive(char[]);
int UART_transmit(char*, char[]);
//Drawing
void cleanList(void);
void clearUI(void);
void drawElement(int,int,int,int);
void drawImages(void);
void drawItems(void);
void drawList(void);
void drawProduct(struct product*);
void drawString(char*);
void drawZone(void);
void makeUI(void);

int Init_GUIThread (void) {
  tid_GUIThread = osThreadCreate (osThread(GUIThread), NULL);
  if (!tid_GUIThread) return(-1);
  return(0);
}
/**
  * System Clock Configuration
  *   System Clock source            = PLL (HSE)
  *   SYSCLK(Hz)                     = 200000000
  *   HCLK(Hz)                       = 200000000
  *   AHB Prescaler                  = 1
  *   APB1 Prescaler                 = 4
  *   APB2 Prescaler                 = 2
  *   HSE Frequency(Hz)              = 25000000
  *   PLL_M                          = 25
  *   PLL_N                          = 400
  *   PLL_P                          = 2
  *   PLL_Q                          = 8
  *   VDD(V)                         = 3.3
  *   Main regulator output voltage  = Scale1 mode
  *   Flash Latency(WS)              = 6
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
  * Configure the MPU attributes
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
  * CPU L1-Cache enable
  */
static void CPU_CACHE_Enable (void) {
  /* Enable I-Cache */
  SCB_EnableICache();
  /* Enable D-Cache */
  SCB_EnableDCache();
}
void GUIThread (void const *argument) {
  int X = 0,Y = 0,*s;
	int press = 1, passed = 0;
	int productDrawned=0, listDrawned=0;
	char name[50], rec[50];

	//Init
	MPU_Config ();
	CPU_CACHE_Enable();                       /* Enable the CPU Cache           */
  HAL_Init();                               /* Initialize the HAL Library     */
  BSP_SDRAM_Init();                         /* Initialize BSP SDRAM           */
  SystemClock_Config();                     /* Configure the System Clock     */
  GUI_Init();
	Touch_Initialize();
	
	//Clear the UI
	GUI_SetBkColor(GUI_WHITE);
  GUI_Clear();
		
	makeUI();
	Init_UART();
	while(Y != 1) {
		X = UART_send("AT", 2);		
		X = UART_receive(rec);
		if(strcmp(rec, "OK"))
			Y = 1;
		osDelay(100);	
	}//*/
	Y = 0;
	while(Y != 1) {
		X = UART_send("AT+ROLE=1", 9);		
		X = UART_receive(rec);
		if(strcmp(rec, "OK"))
			Y = 1;
		osDelay(100);	
	}//*/
	while(Y != 1) {
		X = UART_send("AT+INIT", 7);		
		X = UART_receive(rec);
		if(strcmp(rec, "OK"))
			Y = 1;
		osDelay(100);	
	}//*/
	
  while (1) {
		drawImages();															//Draws the images on the UI
		if(productDrawned == 0) {
			drawProduct(productList);								//Print product informations on the UI once
			productDrawned=1;
		}
		
		//GUI_CURSOR_Show();											//Get the coordinates
		X = GUI_TOUCH_GetxPhys();
		Y = GUI_TOUCH_GetyPhys();
		
		//Getting state of screen
		GUI_PID_STATE *pState;										//Getting state
		if(press != GUI_TOUCH_GetState(pState)) {	//0 if [0->1] pressed
			press = GUI_TOUCH_GetState(pState);			//1 else
			passed = 0;
		} else {
			passed = 1;
		}			
		
		if(press == 1 && passed == 0) {
			//Do Stuff
			doScan(X,Y, press);
		}		
		//Debug
		/*GUI_SetFont(&GUI_Font10_1);
		sprintf (texte, "X=%04d", X);
		GUI_DispStringAt(texte , 420, 127);
		sprintf (texte, "Y=%04d", Y);
		GUI_DispStringAt(texte , 420, 142);
		sprintf (texte, "P=%04d", listPage);
		GUI_DispStringAt(texte , 420, 112);//*/
		//Update UI
		GUI_Exec();
  }
}
/*********************************************************************
*
*       Main
*/
int main (void) {
	int i, *s;
	char name[50],barc[50],loca[50];
	
	productList = (struct product*) malloc(listSize * sizeof(struct product));	
	for(i=0;i<listSize;i++) {
		sprintf(name,"Product %d",i+1);
		strcopy(name,(productList+i)->name);    //Init Product Name
		(productList+i)->quantity = i+1;			  //Init Product Quantity
		sprintf(barc,"0112233445");
		strcopy(barc,(productList+i)->barcode); //Init Product Barcode
		sprintf(loca,"%d°Allee",i+1);
		strcopy(loca,(productList+i)->location);//Init Product Location		
		(productList+i)->status = 0;            //Init Product Status
	}
	
	osKernelInitialize ();                    // initialize CMSIS-RTOS
  Init_GUIThread();
  osKernelStart ();                         // start thread execution
  osDelay(osWaitForever);
}
//---FUNCTIONNAL---//
void doScan(int x, int y, int isPressed) {
	char scan[50];
	//Scan list navigation	
	if(isPressed == 1) {
		
		if((x<ItemSoOu[0])&&(x>ItemSoOu[2])&&(y<ItemSoOu[1])&&(y>ItemSoOu[3])){
			itemSoldOut = 0;	
			sprintf (scan, "                      ");		
		}
		
		if ((x>ListPrev[0])&&(x<ListPrev[2])&&(y>ListPrev[1])&&(y<ListPrev[3]))
		{
			sprintf (scan, "Previous Items !");
			if(listPage > 0) {
				listPage = listPage - 1;
				drawList();
			} else 
				sprintf (scan, "Previous Items ! (MAX)");			
		}
		else if ((x>ListNext[0])&&(x<ListNext[2])&&(y>ListNext[1])&&(y<ListNext[3]))
		{
			sprintf (scan, "Next Items !");
			if((listPage+1)*4 < listSize) {
				listPage = listPage + 1;
				drawList();
			} else 
				sprintf (scan, "Next Items ! (MAX)");
		}
		//Scan item sold out button
		else if ((x>ItemSoOu[0])&&(x<ItemSoOu[2])&&(y>ItemSoOu[1])&&(y<ItemSoOu[3]))
		{
			//sprintf (scan, "Item set as \"Sold out !\"");
			if(itemSoldOut == 0) {
				itemSoldOut = 1;
			} else if (itemSoldOut == 1) {
				itemSoldOut = 2;
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
		
		//Functionnal
		if(itemClick != -1) {
			oldPage = listPage;
			if(itemClick + (4*oldPage) < listSize)
				drawProduct((productList+(itemClick + (4*oldPage))));
			itemClicked = itemClick;
			itemClick = -1;
		}
		if(itemScan == 1) {			
			if((productList+(itemClicked + (4*oldPage)))->quantity > 0) {
				scanItem(itemClicked + (4*oldPage));
			} else {
				sprintf (scan, "Item quantity = 0");
			}
			itemScan = 0;
		}
		if(itemSoldOut == 1 || itemSoldOut == 2) {
			if(itemSoldOut == 1) {
				sprintf (scan, "Are you sure ?");	
			} else if(itemSoldOut == 2) {
				int state = 0;
				state = setSoldOut(itemClicked + (4*oldPage));
				if(state == 0) {
					sprintf (scan, "Item set as Sold Out");
				} else {
					sprintf (scan, "Can't set as Sold Out");					
				}
				itemSoldOut = 0;
			}
		}
		if(finalizeList == 1) {
			finalizeCheck = finalizeCommand();
			if(finalizeCheck == 0) {
				sprintf (scan, "List is not finished");				
			} else if (finalizeCheck == -1){
				sprintf (scan, "List finished with sold out");					
			} else {
				sprintf (scan, "List finished !");							
			}
			finalizeList = 0;
		}
		if(BT == 1) {
			int err = 0, state = 0;	
			char rec[50];
			while(state != 1) {
				err = UART_send("AT+PAIR=00,1C,97,14,35,02,5000", 25);		
				err = UART_receive(rec);
				if(strcmp(rec, "OK") || strcmp(rec, "FAIL"))
					state = 1;
				osDelay(100);	
			}//*/
			if(strcmp(rec, "OK")) 
				sprintf (scan, "Connected !");
			if(strcmp(rec, "FAIL")) 
				sprintf (scan, "Failed to connect");
				
			BT = 0;
		}		
		clearUI();
		GUI_SetFont(&GUI_Font20_1);
		drawString(scan);
	}
}
int finalizeCommand() {
	int code = 0;
	for(int i=0; i<listSize; i++) {
		if((productList+i)->status==0) {
			return 0;
		} else if ((productList+i)->status==-1) {
			code = -1;
		}		
	}
	if(code == 0)
		code = 1;
	
	return code;
}
void Init_UART() {
	char name[50];
	int i;
	Driver_USART6.Initialize(NULL);
	Driver_USART6.PowerControl(ARM_POWER_FULL);
	
	Driver_USART6.Control(	ARM_USART_MODE_ASYNCHRONOUS |
							ARM_USART_DATA_BITS_8		|
							ARM_USART_STOP_BITS_1		|
							ARM_USART_PARITY_NONE		|
							ARM_USART_FLOW_CONTROL_NONE,
							9600);	
	Driver_USART6.Control(ARM_USART_CONTROL_TX,1);
	Driver_USART6.Control(ARM_USART_CONTROL_RX,1);
}
void scanItem(int no) {
	int scan = 1;
	
	if(scan == 1) {
		updateQuantity(no, 1);
	}	
}
int setSoldOut(int no) {
	if((productList+no)->status != 0) {
		return 1;		
	}
	(productList+no)->quantity = -1;
	(productList+no)->status = -1;	
	drawList();
	drawProduct((productList+no));
	return 0;
}
void strcopy(char name[],char prod[]) {
	int c=0;
	while (name[c] != '\0') {
   prod[c] = name[c];
   c++;
	}
}
int UART_send(char* string, int size) {
	int32_t err;
	while(Driver_USART6.GetStatus().tx_busy == 1); // attente buffer TX vide
	err = Driver_USART6.Send(string,size);
	if(err != 0) {
		return -1;
	} else {
		return 0;
	}
}
int UART_receive(char receive_tab[]) {
	int32_t err;
	int i=0;
	while(Driver_USART6.GetStatus().rx_busy==1) {;
		err = Driver_USART6.Receive(receive_tab+i,1);
		i++;
	}
	if(err != 0) {
		return -1;
	} else {
		return 0;
	}
}
int UART_transmit(char* out, char in[]) {
	int32_t err;
	err = UART_send(out, strlen(out));
	if(err != 0) {
		return -1;
	} else {
		return 0;
	}
	err = UART_receive(in);
	if(err != 0) {
		return -2;
	} else {
		return 0;
	}
}
void updateQuantity(int no,int nbr) {
	(productList+no)->quantity = (productList+no)->quantity - nbr;
	if((productList+no)->quantity==0) {
		(productList+no)->status = 1;
	}
	drawList();
	drawProduct((productList+no));
}
//---DRAWING---//
void cleanList() {
	char list[50];
	for(int i=0;i<=3;i++) {
		GUI_SetFont(&GUI_Font16_1);
		sprintf(list,"                ");
		GUI_DispStringAt(list, 5, i*42 +13); // Display Name	
		GUI_SetFont(&GUI_Font10_1);
		sprintf(list,"       ");
		GUI_DispStringAt(list, 167, i*42 +16); // Display quantity
	}
}
void clearUI() {
		sprintf (texte, "                                      ");
		drawString(texte);
		makeUI();
}
void drawElement(int x1, int y1, int x2, int y2) {
	// Délimitation des éléments
	GUI_SetPenSize(1);		// épaisseur
	GUI_DrawRect(x1,y1,x2,y2);
}
void drawImages() {
	//Draw Bitmaps on the screen
	GUI_DrawBitmap(&bmicoPrev, ListPrev[0], ListPrev[1]); //Previous
	GUI_DrawBitmap(&bmicoNext, ListNext[0], ListNext[1]); //Next
	
	GUI_DrawBitmap(&bmicoSold, ItemSoOu[0], ItemSoOu[1]); //Sold Out
	GUI_DrawBitmap(&bmicoScan, ItemScan[0], ItemScan[1]); //Scan
	
	GUI_DrawBitmap(&bmicoOpti, MenuOpti[0], MenuOpti[1]); //Options 
	GUI_DrawBitmap(&bmicoBluetooth, MenuBlue[0], MenuBlue[1]); //Bluetooth
	GUI_DrawBitmap(&bmicoList, MenuFina[0], MenuFina[1]); //Command
}
void drawItems() {
	GUI_SetColor(GUI_BLUE);
	drawElement(ItemImag[0],ItemImag[1],ItemImag[2],ItemImag[3]);
}
void drawList() {	
	char item[50];
	//Draw the area
	GUI_SetColor(GUI_BLACK);
	
	drawElement(ListItm0[0],ListItm0[1],ListItm0[2],ListItm0[3]);
	drawElement(ListItm1[0],ListItm1[1],ListItm1[2],ListItm1[3]);
	drawElement(ListItm2[0],ListItm2[1],ListItm2[2],ListItm2[3]);
	drawElement(ListItm3[0],ListItm3[1],ListItm3[2],ListItm3[3]);
	
	//DEBUG --- Print the size of the array
	/*GUI_SetFont(&GUI_Font10_1);
	sprintf (item, "S=%04d", listSize);
	GUI_DispStringAt(item , 420, 97);//*/
	
	//Clean the area
	cleanList();
	for(int i=0;i<=3;i++) {
		GUI_SetFont(&GUI_Font16_1);
		//Write on the area
		if(i + (4*listPage) < listSize) {
			GUI_SetFont(&GUI_Font16_1);
			sprintf(item,"%s", (productList+(i + (4*listPage)))->name);
			GUI_DispStringAt(item, 5, i*42 +13); // Display Name	
			GUI_SetFont(&GUI_Font10_1);
			if((productList+(i + (4*listPage)))->quantity > 0) {
				sprintf(item,"x%02d", (productList+(i + (4*listPage)))->quantity);
			} else if((productList+(i + (4*listPage)))->quantity == -1) {
				GUI_SetColor(GUI_RED);
				sprintf(item,"Out ");				
			}	else {
				sprintf(item,"Ok !");
			}
			GUI_DispStringAt(item, 167, i*42 +16); // Display quantity	
			GUI_SetColor(GUI_BLACK);
		}
	}
}
void drawProduct(struct product* prod) {
	GUI_SetFont(&GUI_Font24_1);
	GUI_DispStringAt("                 ", 204, 115); // Display name
	GUI_SetFont(&GUI_Font16_1);
	GUI_DispStringAt("                 " , 204, 140); // Display location
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringAt("                  ", 300, 85); // Display quantity	
	char item[50]="";
	GUI_SetFont(&GUI_Font24_1);
	GUI_DispStringAt(prod->name , 204, 115); // Display name
	GUI_SetFont(&GUI_Font16_1);
	GUI_DispStringAt(prod->location , 204, 140); // Display location
	GUI_SetFont(&GUI_Font20_1);
	if(prod->quantity > 0) {
		sprintf(item," x%02d",prod->quantity);
	} else if(prod->quantity == -1) {
		sprintf(item,"Sold Out !");	
	} else {
		sprintf(item,"complete");		
	}
	GUI_DispStringAt(item, 300, 85); // Display quantity	
}
void drawString(char*txt) {
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringAt(txt , 5, 175);
}
void drawZone() {
	// Délimitation des zones
	GUI_SetPenSize(2);		// épaisseur
	GUI_SetColor(GUI_BLACK);
	GUI_DrawLine(192, 0, 192, 272);		// X1, Y1, X2, Y2
	GUI_DrawLine(408, 0, 408, 272);		// X1, Y1, X2, Y2
}
void makeUI() {
	drawZone();  // Délimitation des zones
	drawImages();//Draw Bitmaps on the screen
	drawItems(); //Draw Images Places
	drawList();
}
