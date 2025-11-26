/*
 * CanFrame.cpp
 *
 *  Created on: 25.11.2019
 *      Author: ber
 */

#include "CanFrame.h"
#include "main.h"
#include "stm32f429i_discovery_lcd.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

extern CAN_HandleTypeDef canHandle;

CanFrame::CanFrame() : mDataSize(0), mId(0xFFFFFFFF) {

}

CanFrame::~CanFrame() {

}

bool CanFrame::setData(uint8_t *data, unsigned int len) {
	if (len > 8) {
		return false;
	}
	memcpy(mData, data, len);
	mDataSize = len;
	return true;
}

void CanFrame::setId(uint32_t id) {
	mId = id;
}

bool CanFrame::addData(uint8_t data) {
	if (mDataSize >= 8) {
		return false;
	}
	mData[mDataSize] = data;
	mDataSize++;
	return true;
}

bool CanFrame::txData(void) {
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef txHeader;

	if(!isValid()) {
		return false;
	}
	if (HAL_CAN_GetTxMailboxesFreeLevel(&canHandle) != 3 ) {
		// only send message if none is in queue
		return false;
	}

	// daten frame vorbereiten
	txHeader.StdId = mId;
	txHeader.ExtId = 0x00;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.IDE = CAN_ID_STD;
	txHeader.DLC = mDataSize;

	/* Start the Transmission process */
	if (HAL_CAN_AddTxMessage(&canHandle, &txHeader, mData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
		return false;
	}

	return true;
}

bool CanFrame::rxData(void) {
	CAN_RxHeaderTypeDef rxHeader;
	uint8_t rxData[8];

	if (HAL_CAN_GetRxFifoFillLevel(&canHandle, CAN_RX_FIFO0) == 0) {
		return false;
	}

	if (HAL_CAN_GetRxMessage(&canHandle, CAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK)
	{
		/* Reception Error */
		return false;
	}



	mId = rxHeader.StdId;
	memcpy(mData, rxData, rxHeader.DLC);
	mDataSize = rxHeader.DLC;
	return true;
}

void CanFrame::getData(uint8_t *data, unsigned int *len) {
	memcpy(data, mData, mDataSize);
	*len = mDataSize;
}

uint32_t CanFrame::getId(void) {
	return mId;
}

bool CanFrame::isValid(void) {
	if ((mId < (0x01 << 12)) && mDataSize > 0 && mDataSize < 9) {
		return true;
	}
	return false;
}

void CanFrame::printData(unsigned int ln, unsigned int col) {
	if (!isValid()) {
		return;
	}
	LCD_SetPrintPosition(ln, col);
	printf ("%03lx", mId);
	col += 5;
	for (int i = 0; i < mDataSize; i++) {
		LCD_SetPrintPosition(ln, col);
		printf ("%02x", mData[i]);
		col = col + 3;
	}
}
