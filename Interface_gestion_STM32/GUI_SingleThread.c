
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

// fichier image
#include "IT2R2.c"
#include "temperature.c"
#include "vitesse.c"
#include "train2.c"

#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) { 
  return os_time; 
}
#endif




/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
int ListPrev[4] = { 12,200, 92,260};
int ListNext[4] = {100,200,180,260};
int ItemImag[4] = {199,  5,295,101};
int ItemSoOu[4] = {205,212,285,260};
int ItemScan[4] = {316,212,396,260};
int MenuOpti[4] = {420, 12,468, 60};
int MenuBlue[4] = {420,154,468,202};
int MenuFina[4] = {420,212,468,260};

char texte[50];
int isWritten = 0;
int writeState = 0;

void GUIThread (void const *argument);              // thread function
osThreadId tid_GUIThread;                           // thread id
osThreadDef (GUIThread, osPriorityIdle, 1, 2048);   // thread object

void drawZone();
void drawItems();
void drawElements(int,int,int,int);
void doScan(int,int);
void clearUI();
void makeUI();

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

  int X,Y;
	
	MPU_Config ();
	CPU_CACHE_Enable();                       /* Enable the CPU Cache           */
  HAL_Init();                               /* Initialize the HAL Library     */
  BSP_SDRAM_Init();                         /* Initialize BSP SDRAM           */
  SystemClock_Config();                     /* Configure the System Clock     */

  GUI_Init();
	Touch_Initialize();
	
	GUI_SetBkColor(GUI_WHITE);
  GUI_Clear();
	makeUI();

	// definition police : forme, taille + couleur
  //GUI_SetFont(&GUI_Font32B_1);
	//GUI_SetColor(GUI_BLACK);
	//GUI_SetTextMode(GUI_TM_NORMAL);
	// Affichage texte
	//GUI_DispStringAt("Interface" , 5, 5);
	// Affichage nombre
	//GUI_SetFont(&GUI_Font20_1);
	
  /* Add GUI setup code here */

  while (1) {
    
    /* All GUI related activities might only be called from here */
		// Les images à afficher doivent être placées dans la boucle infinie
		/*GUI_DrawBitmap(&bmIT2R2, 290, 10);
		
		GUI_SetFont(&GUI_Font10_1);
		GUI_SetColor(GUI_BLACK);
		GUI_DrawBitmap(&bmtemperature, 70, 75);		// taille 63*94
		GUI_DispStringAt("Temperature" , 65, 160);
		GUI_DrawBitmap(&bmvitesse, 70+75+63, 85);		// 
		GUI_DispStringAt("Poste CAN" , 210, 160);
		GUI_DrawBitmap(&bmtrain, 70+2*75+2*63, 80);		//
		GUI_DispStringAt("Maquette train" , 342, 160);*/
		
		//GUI_CURSOR_Show();

		X = GUI_TOUCH_GetxPhys();
		Y = GUI_TOUCH_GetyPhys();
		
		GUI_SetFont(&GUI_Font10_1);
		sprintf (texte, "X=%04d", X);
		GUI_DispStringAt(texte , 420, 127);
		sprintf (texte, "Y=%04d", Y);
		GUI_DispStringAt(texte , 420, 142);
		
		doScan(X,Y);
		
		// mises à jour affichage
		GUI_Exec();
  }
}

/*********************************************************************
*
*       Main
*/
int main (void) {
	osKernelInitialize ();                    // initialize CMSIS-RTOS

  // initialize peripherals here

  // create 'thread' functions that start executing,
  Init_GUIThread();

  osKernelStart ();                         // start thread execution 
	
  osDelay(osWaitForever);
}

/*************************** End of file ****************************/

void drawZone() {
	// Délimitation des zones
	GUI_SetPenSize(2);		// épaisseur
	GUI_SetColor(GUI_BLACK);
	GUI_DrawLine(192, 0, 192, 272);		// X1, Y1, X2, Y2
	GUI_DrawLine(408, 0, 408, 272);		// X1, Y1, X2, Y2
}
void drawItems() {
	drawElements(ListPrev[0],ListPrev[1],ListPrev[2],ListPrev[3]);
	drawElements(ListNext[0],ListNext[1],ListNext[2],ListNext[3]);
	drawElements(ItemImag[0],ItemImag[1],ItemImag[2],ItemImag[3]);
	drawElements(ItemSoOu[0],ItemSoOu[1],ItemSoOu[2],ItemSoOu[3]);
	drawElements(ItemScan[0],ItemScan[1],ItemScan[2],ItemScan[3]);
	drawElements(MenuOpti[0],MenuOpti[1],MenuOpti[2],MenuOpti[3]);
	drawElements(MenuBlue[0],MenuBlue[1],MenuBlue[2],MenuBlue[3]);
	drawElements(MenuFina[0],MenuFina[1],MenuFina[2],MenuFina[3]);
}
void drawElements(int x1, int y1, int x2, int y2) {
	// Délimitation des éléments
	GUI_SetPenSize(1);		// épaisseur
	GUI_SetColor(GUI_BLUE);
	GUI_DrawRect(x1,y1,x2,y2);
}
void doScan(int x, int y) {
	if ((x>ListPrev[0])&&(x<ListPrev[2])&&(y>ListPrev[1])&&(y<ListPrev[3]))
	{
		if(writeState != 1) {
			clearUI();
			writeState = 1;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Previous Items on the list !");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "Cacahuetes");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if ((x>ListNext[0])&&(x<ListNext[2])&&(y>ListNext[1])&&(y<ListNext[3]))
	{
		if(writeState != 2) {
			clearUI();
			writeState = 2;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Next Items on the list !");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if ((x>ItemSoOu[0])&&(x<ItemSoOu[2])&&(y>ItemSoOu[1])&&(y<ItemSoOu[3]))
	{
		if(writeState != 3) {
			clearUI();
			writeState = 3;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Item set as \"Sold out !\"");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if ((x>ItemScan[0])&&(x<ItemScan[2])&&(y>ItemScan[1])&&(y<ItemScan[3]))
	{
		if(writeState != 4) {
			clearUI();
			writeState = 4;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Scanning Item");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if ((x>MenuOpti[0])&&(x<MenuOpti[2])&&(y>MenuOpti[1])&&(y<MenuOpti[3]))
	{
		if(writeState != 5) {
			clearUI();
			writeState = 5;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Options");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if ((x>MenuBlue[0])&&(x<MenuBlue[2])&&(y>MenuBlue[1])&&(y<MenuBlue[3]))
	{
		if(writeState != 6) {
			clearUI();
			writeState = 6;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Bluetooth");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if ((x>MenuFina[0])&&(x<MenuFina[2])&&(y>MenuFina[1])&&(y<MenuFina[3])) 
	{
		if(writeState != 7) {
			clearUI();
			writeState = 7;
			isWritten = 1;
			GUI_SetFont(&GUI_Font20_1);
			sprintf (texte, "Finalizing Command");
			GUI_DispStringAt(texte , 5, 210);
			sprintf (texte, "");
			GUI_DispStringAt(texte , 5, 230);
		}
	}
	else if (isWritten==1) {
		if(writeState != 0) {
			clearUI();
			writeState = 0;
		}
	}
}
void clearUI() {
		isWritten = 0;
		GUI_SetFont(&GUI_Font20_1);
		sprintf (texte, "                                          ");
		GUI_DispStringAt(texte , 5, 210);
		sprintf (texte, "                                          ");
		GUI_DispStringAt(texte , 5, 230);
		makeUI();
}
void makeUI() {	
	drawZone();
	drawItems();
}