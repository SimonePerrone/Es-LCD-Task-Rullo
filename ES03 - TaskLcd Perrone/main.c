/** ****************************************************************************************
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*        _____   ____
*       |  ___| |  _ \
*       | |     | |_| |
*       |  _|   |  _ /
*       | |     | |_| |
*   www.|_|     |_____/-labs.blogspot.it, https://github.com/filippo-bilardo 
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* \mainpage STML476VG Framework
*
* @brief FRAMEWORK per l'utilizzo del microcontrollore ARM Cortex-M4 presente nelle
* schede STML476VG Discovery e supporto al kernel FreeRTOS
* 
* @author Filippo Bilardo
* @date 09/10/21 
* @version 1.0 09/10/21 Versione iniziale 
*
* @section LICENSE
* Open Source Licensing 
* This program is free software: you can redistribute it and/or modify it under the terms 
* of the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or (at your option) any later version.
* This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
* withouteven the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* You should have received a copy of the GNU General Public License along with this
* program. If not, see(http://www.gnu.org/licenses/).
*/
//------------------------------------------------------------------------------------------
//=== INCLUDES =============================================================================
//------------------------------------------------------------------------------------------
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
//#include "queue.h"                    // ARM.FreeRTOS::RTOS:Core
#include <stdio.h>
#include "Led.h"
#include "Pulsanti.h"
#include "clock.h"
#include "Arduino.h"
#include "event_groups.h" 
#include "Lcd.h"
//#include "SysClock.h"

#define EV_OBJECT_DETECTED 1 << 0 //bit
EventGroupHandle_t xEventGroup;
void vTaskPA0(void * pvParameters);  //test eventgroup ultrasuoni 
void vTaskLcd(void * pvParameters);  

#define EV_OBJECT_DETECTED 1 << 0 //bit
#define EV_OBJECT_BLACK 1 << 1 //bit
#define EV_OBJECT_WHITE 1 << 2 //bit
#define EV_OBJECT_DEX 1 << 3 //bit
#define EV_OBJECT_SIX 1 << 4 //bit

int main(void) {
		
	pllInit(0,10,0);
	//SwInit();
	SwCenterInit();
	SwDownInit ();
	SwLeftInit ();
	SwRightInit ();
	SwUpInit ();
	
	LedInit();
	LCD_Init();
	LCD_DisplayString((uint8_t *)"Ciao");
	


	xTaskCreate(vTaskPA0, /* Pointer to the function that implements the task.              */
		"Task 2 (PA0 check)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */

	xTaskCreate(vTaskLcd, /* Pointer to the function that implements the task.              */
		"Task 1 (Toggle LCD)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */
	
	xEventGroup=xEventGroupCreate();
	vTaskStartScheduler();	
}

void vTaskPA0(void * pvParameters){
	while(1){
		while(!digitalRead(PA0));
		while(digitalRead(PA0)){;}
			xEventGroupSetBits(xEventGroup,EV_OBJECT_DETECTED);
			
	}	
}
void vTaskLcd(void * pvParameters) {
	
	int PacchiNeri=0;
	int PacchiBianchi=0;
	char LcdMessage[8];
	EventBits_t colore;
	LCD_DisplayString((uint8_t *)"0");
	
	//const EventBits_t xBitsToWaitFor = EV_OBJECT_WHITE|EV_OBJECT_BLACK;
	
	while(1) {
		//colore=xEventGroupWaitBits(xEventGroup,xBitsToWaitFor,pdTRUE,pdFALSE,portMAX_DELAY);
		if(colore==EV_OBJECT_WHITE) {
			PacchiBianchi++;														//Incrementa il numero di pacchi Bianchi visualizzati di 1
			sprintf(LcdMessage,"B%d N%d", PacchiBianchi, PacchiNeri);
			LCD_Clear();
			LCD_DisplayString((uint8_t *)LcdMessage);			//Stampa a schermo i numeri di pacchi Bianchi visualizzati
		}
		if(colore==EV_OBJECT_BLACK){
			PacchiNeri++;																//Incrementa il numero di pacchi Neri visualizzati di 1
			sprintf(LcdMessage,"B%d N%d", PacchiBianchi, PacchiNeri);
			LCD_Clear();
			LCD_DisplayString((uint8_t *)LcdMessage);			//Stampa a schermo i numeri di pacchi Bianchi visualizzati
		}
	}
}
	
