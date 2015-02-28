#ifndef APPLICATION_H
#define APPLICATION_H

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
	LDD_TDeviceData *handle;
	volatile uint8_t isSent;
	uint8_t rxChar;
	uint8_t (*rxPutFct)(uint8_t);
} UART_Desc;

void APP_Run(void);

#endif /* APPLICATION_H */
