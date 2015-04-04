/*
 * Shell.c
 *
 *  Created on: Mar 7, 2015
 *      Author: Nino
 */

#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "LED_red.h"
#include "LED_green.h"
#include "LED_blue.h"
#include "Error.h"
#include "BLDC.h"
#include "WAIT1.h"
#include "STP.h"
#include "DC.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
		CLS1_ParseCommand,
#if LED1_PARSE_COMMAND_ENABLED
		LED1_ParseCommand,
#endif
#if LED2_PARSE_COMMAND_ENABLED
		LED2_ParseCommand,
#endif
#if BLDC_PARSE_COMMAND_ENABLED
		BLDC_ParseCommand,
#endif
#if STP_PARSE_COMMAND_ENABLED
		STP_ParseCommand,
#endif
#if DC_PARSE_COMMAND_ENABLED
		DC_ParseCommand,
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
		// FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	}
}

void SHELL_Init(void)
{
	set_status(STATUS_BUSY);
	WAIT1_Waitms(1000);
	CLS1_Init();
	if (FRTOS1_xTaskCreate(
			ShellTask,
			"Shell",
			configMINIMAL_STACK_SIZE+200,
			NULL,
			tskIDLE_PRIORITY,
			NULL ) != pdPASS) {
		while (1) {
			set_status(STATUS_ERROR);
		}
	}
	set_status(STATUS_OK);
}
