#include "Application.h"
#include "RxBuf.h"
#include "AS1.h"

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
	Init();
	SendString((unsigned char*)"Hello World\r\n", &deviceData);
	while (1) {
		if (RxBuf_NofElements() != 0) {
			SendString((unsigned char*)"echo: ", &deviceData);
			while (RxBuf_NofElements() != 0) {
				unsigned char ch;
				(void)RxBuf_Get(&ch);
				SendChar(ch, &deviceData);
			}
		}
	}
}
