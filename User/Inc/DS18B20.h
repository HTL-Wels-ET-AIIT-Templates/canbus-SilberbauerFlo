#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f4xx.h"

/* Defines
**********************************************************************/

/* Prototypes
**********************************************************************/
uint8_t ds1820_reset(GPIO_TypeDef * port, uint16_t used_pin);                    //reset device
float   ds1820_read_temp(GPIO_TypeDef * port, uint16_t used_pin);                //read temperature from device
void    ds1820_init(GPIO_TypeDef * port, uint16_t used_pin);                     //initialize device

#endif // __DS18B20_H
