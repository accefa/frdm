#include "Application.h"
#include "RxBuf.h"
#include "AS1.h"
#include "command.h"
#include <stdlib.h>

static UART_Desc deviceData;

static void SendChar(unsigned char ch, UART_Desc *desc) {
	desc -> isSent = FALSE;
	while (AS1_SendBlock(desc -> handle, (LDD_TData*)&ch, 1) != ERR_OK) {

	}
	while (!desc -> isSent) {

	}
}

static void SendString(const unsigned char *str, UART_Desc *desc) {
	while (*str != '\0') {
		SendChar(*str++, desc);
	}
}

static void Init(void) {
	deviceData.handle = AS1_Init(&deviceData);
	deviceData.isSent = FALSE;
	deviceData.rxChar = '\0';
	deviceData.rxPutFct = RxBuf_Put;

	RxBuf_Init();

	while (AS1_ReceiveBlock(deviceData.handle, (LDD_TData *)&deviceData.rxChar, sizeof(deviceData.rxChar)) != ERR_OK) {

	}
}

void APP_Run(void) {
	unsigned char ch;
	unsigned char input[64] = { '\0' };
	unsigned char output[64] = { '\0' };
	uint8 pos = 0;

	Init();

	SendString((unsigned char*)"Hello World\r\n", &deviceData);

	while (1) {
		if (RxBuf_NofElements() != 0) {
			// SendString((unsigned char*)"echo: ", &deviceData);
			WAIT1_Waitms(100);
			while (RxBuf_NofElements() != 0) {
				// unsigned char ch;
				(void)RxBuf_Get(&ch);
				// SendChar(ch, &deviceData);
				input[pos] = ch;
				pos++;
			}
			input[pos] = ch = '\0';
			pos = 0;
			SendChar('\n', &deviceData);
			get_command_name(output, input);
			SendString(output, &deviceData);
		}
	}
}
