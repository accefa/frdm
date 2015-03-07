/*
 * Shell.c
 *
 *  Created on: Mar 7, 2015
 *      Author: Nino
 */

#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED1.h"
#include "LED2.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
		CLS1_ParseCommand,
#if LED1_PARSE_COMMAND_ENABLED
		LED1_ParseCommand,
#endif
		NULL
};

static void ShellTask(void *pvParameters)
{
	unsigned char buf[48];

	(void)pvParameters;
	buf[0] = '\0';
	(void)CLS1_ParseWithCommandTable((unsigned char*)CLS1_CMD_HELP, CLS1_GetStdio(), CmdParserTable);

	while (1) {
		(void)CLS1_ReadAndParseWithCommandTable(buf, sizeof(buf), CLS1_GetStdio(), CmdParserTable);
		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
		LED1_Neg();
	}
}

void SHELL_Init(void)
{
	CLS1_Init();
	if (FRTOS1_xTaskCreate(
			ShellTask,
			"Shell",
			configMINIMAL_STACK_SIZE+200,
			NULL,
			tskIDLE_PRIORITY,
			NULL ) != pdPASS) {
		while (1) {
			// out of heap?
		}
	}
}
