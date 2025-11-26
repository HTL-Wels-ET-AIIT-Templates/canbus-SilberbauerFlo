/*
 * CanFrame.h
 *
 *  Created on: 25.11.2019
 *      Author: ber
 */

#ifndef CANFRAME_H_
#define CANFRAME_H_

#include <stdint.h>

class CanFrame {
public:
	CanFrame();
	virtual ~CanFrame();

	bool setData(uint8_t *data, unsigned int len);
	void setId(uint32_t id);
	bool addData(uint8_t data);

	bool txData(void);
	bool rxData(void);

	void getData(uint8_t *data, unsigned int *len);
	uint32_t getId(void);
	bool isValid(void);
	void printData(unsigned int x, unsigned int y);

private:
	uint8_t mData[8];
	int mDataSize;
	uint32_t mId;	// set lowest ID as default
};

#endif /* CANFRAME_H_ */
