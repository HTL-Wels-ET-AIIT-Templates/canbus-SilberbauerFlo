/**
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "can.h"
#include "stm32f429i_discovery_lcd.h"
#include "tempsensor.h"
#include "CanFrame.h"

// function declarations
// ...

/**
 * canInit function
 * @param none
 * @return none
 */
extern "C" void cancppInit(void) {
	canInitHardware();

	LCD_SetFont(&Font12);
	LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	LCD_SetPrintPosition(3,1);
	printf("CAN1: Send-Recv");

	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_SetPrintPosition(5,1);
	printf("Send-Cnt:");
	LCD_SetPrintPosition(5,15);
	printf("%5d", 0);
	LCD_SetPrintPosition(7,1);
	printf("Recv-Cnt:");
	LCD_SetPrintPosition(7,15);
	printf("%5d", 0);
	LCD_SetPrintPosition(9,1);
	printf("Send-Data:");
	LCD_SetPrintPosition(15,1);
	printf("Recv-Data:");

	LCD_SetPrintPosition(30,1);
	printf("Bit-Timing-Register: 0x%lx", CAN1->BTR);

	tempSensorInit();
} 

/**
 * Send message on CAN Bus and show content on the display
 */
extern "C" void cancppSendTask(void) {
	CanFrame tx;
	static uint8_t sendCnt = 0;

	float t = tempSensorGetTemperature();
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_SetPrintPosition(11,1);
	printf("T: %3.2f", t);
	uint16_t p = t * 10 ;

	tx.setId(0x0F5);
	tx.addData(0xAF);
	tx.addData(sendCnt);
	tx.addData(p);
	tx.addData(p << 8);

	if (tx.txData()) {
		sendCnt++;
	}
	tx.printData(9, 13);
	LCD_SetPrintPosition(5,15);
	printf("%5d", sendCnt);
}

/**
 * Receive message on CAN Bus and show content on the display
 */
extern "C" void cancppReceiveTask(void) {
	CanFrame rx;
	static uint8_t recvCnt = 0;

	if (rx.rxData()) {
		recvCnt++;
		LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
		LCD_SetPrintPosition(7,15);
		printf("%5d", recvCnt);

		rx.printData(15, 13);
	}
}

