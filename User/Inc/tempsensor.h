#ifndef __TEMPSENSOR_H
#define __TEMPSENSOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void tempSensorInit(void);
float tempSensorGetTemperature(void);

#ifdef __cplusplus
}
#endif
#endif // __TEMPSENSOR_H
