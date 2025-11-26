#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif

void canInitHardware(void);
void canInit(void);
void canSendTask(void);
void canReceiveTask(void);

#ifdef __cplusplus
}
#endif

#endif // CAN_H
