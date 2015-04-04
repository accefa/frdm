/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PWM1.h"
#include "PwmLdd2.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "WAIT1.h"
/* Include inherited beans */
#include "LEDpin2.h"
#include "CLS1.h"
#include "UTIL1.h"

#include "BLDC.h"
#include "LED_red.h"
#include "LED_green.h"
#include "LED_blue.h"
#include "Error.h"
#include <string.h>
#include <stdio.h>

#include "STP.h"

static int STP_enable = 0;


static uint8_t PrintStatus(const CLS1_StdIOType *io)
{
	CLS1_SendStatusStr((unsigned char*)"STP",
			   (unsigned char*)"\r\n", io->stdOut);

	if (STP_get_enable() != 0) {
		CLS1_SendStatusStr((unsigned char*)"  on",
				   (unsigned char*)"yes\r\n",
				   io->stdOut);
	} else {
		CLS1_SendStatusStr((unsigned char*)"  off",
				   (unsigned char*)"no\r\n",
				   io->stdOut);
	}

	return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io)
{
	CLS1_SendHelpStr((unsigned char*)"STP",
			 (unsigned char*)"group of STP commands\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  help|status",
			 (unsigned char*)"print help or status information\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  on|off",
			 (unsigned char*)"turns it on or off\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  move n",
			 (unsigned char*)"moves to position n\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  reset",
			 (unsigned char*)"reset to initial setup\r\n",
			 io->stdOut);

	return ERR_OK;
}

byte STP_ParseCommand(const unsigned char *cmd,
		       bool *handled,
		       const CLS1_StdIOType *io)
{
	uint8_t res = ERR_OK;
	unsigned char message[64] = { '\0'};
	int32_t val;
	const unsigned char *p;

	if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
	    || UTIL1_strcmp((char*)cmd, "STP help") == 0) {
		*handled = TRUE;
		return PrintHelp(io);
	} else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS) == 0)
		   || (UTIL1_strcmp((char*)cmd, "STP status") == 0)) {
		*handled = TRUE;
		return PrintStatus(io);
	} else if (UTIL1_strcmp((char*)cmd, "STP on") == 0) {
		*handled = TRUE;
		// todo
		return ERR_OK;
	} else if (UTIL1_strcmp((char*)cmd, "STP off") == 0) {
		*handled = TRUE;
		// todo
		return ERR_OK;
	} else if (UTIL1_strcmp((char*)cmd, "STP reset") == 0) {
		*handled = TRUE;
		// todo
	} else if (UTIL1_strncmp((char*)cmd, "STP move ",
				 sizeof("STP move")-1) == 0) {
		if (!STP_enable) {
			CLS1_SendStr((unsigned char*)"STP is off, cannot move\r\n",
				     io->stdErr);
			res = ERR_FAILED;
		} else {
			p = cmd+sizeof("STP move");
			if (UTIL1_xatoi(&p, &val) == ERR_OK
			    && val >= BLDC_RPM_MIN && val <= BLDC_RPM_MAX) {
				// todo
				*handled = TRUE;
			} else {
				sprintf(message,
					"Wrong argument, must be in range %i to %i",
					STP_POS_MIN, STP_POS_MAX);
				CLS1_SendStr((unsigned char*)message,
					     io->stdErr);
			}
		}
	} else if (UTIL1_strcmp((char*)cmd, "STP init") == 0) {
		*handled = TRUE;
		// todo
	}
	return ERR_OK;
}

int STP_get_enable(void)
{
	return STP_enable;
}

void spi_write(uint8_t* data)
{
	return;
}

void spi_read(uint8_t* data)
{
	return;
}
