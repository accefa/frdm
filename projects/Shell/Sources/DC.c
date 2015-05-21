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
#include "DC_DIR.h"
#include "DC_EN.h"

#include "DC.h"

static bool dc_top = DC_TOP_REACHED;
static bool dc_bot = DC_BOT_REACHED;

static uint8_t PrintStatus(const CLS1_StdIOType *io)
{
	CLS1_SendStatusStr((unsigned char*)"DC",
			   (unsigned char*)"\r\n", io->stdOut);

	if (DC_get_en() == DC_EN_ON) {
		CLS1_SendStatusStr((unsigned char*)"  on",
				(unsigned char*)"yes\r\n",
				io->stdOut);
	} else {
		CLS1_SendStatusStr((unsigned char*)"  on",
				(unsigned char*)"no\r\n",
				io->stdOut);
	}

	if (DC_get_dir() == DC_DIR_UP) {
		CLS1_SendStatusStr((unsigned char*)"  direction",
				(unsigned char*)"up\r\n",
				io->stdOut);
	} else {
		CLS1_SendStatusStr((unsigned char*)"  direction",
				(unsigned char*)"down\r\n",
				io->stdOut);
	}

	if (DC_get_top() == DC_TOP_REACHED) {
		CLS1_SendStatusStr((unsigned char*)"  top-limit",
				(unsigned char*)"reached\r\n",
				io->stdOut);
	} else {
		CLS1_SendStatusStr((unsigned char*)"  top-limit",
				(unsigned char*)"free\r\n",
				io->stdOut);
	}

	if (DC_get_bot() == DC_TOP_REACHED) {
		CLS1_SendStatusStr((unsigned char*)"  bot-limit",
				(unsigned char*)"reached\r\n",
				io->stdOut);
	} else {
		CLS1_SendStatusStr((unsigned char*)"  bot-limit",
				(unsigned char*)"free\r\n",
				io->stdOut);
	}

	return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io)
{
	CLS1_SendHelpStr((unsigned char*)"DC",
			 (unsigned char*)"group of DC commands\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  help|status",
			 (unsigned char*)"print help or status information\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  on|off",
			 (unsigned char*)"turns it on or off\r\n",
			 io->stdOut);

	CLS1_SendHelpStr((unsigned char*)"  up|down",
			 (unsigned char*)"sets the direction to up or down\r\n",
			 io->stdOut);
#ifndef DC_PWM_SOURCE_INTERNAL
	CLS1_SendHelpStr((unsigned char*)"  setpwm n",
			 (unsigned char*)"sets the PWM value to n\r\n",
			 io->stdOut);
#endif

	CLS1_SendHelpStr((unsigned char*)"  reset",
			 (unsigned char*)"reset to initial setup\r\n",
			 io->stdOut);

	return ERR_OK;
}

byte DC_ParseCommand(const unsigned char *cmd,
		       bool *handled,
		       const CLS1_StdIOType *io)
{
	uint8_t res = ERR_OK;
	unsigned char message[64] = { '\0'};
	int32_t val;
	const unsigned char *p;

	if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
	    || UTIL1_strcmp((char*)cmd, "DC help") == 0) {
		*handled = TRUE;
		return PrintHelp(io);
	} else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS) == 0)
		   || (UTIL1_strcmp((char*)cmd, "DC status") == 0)) {
		*handled = TRUE;
		return PrintStatus(io);
	} else if (UTIL1_strcmp((char*)cmd, "DC on") == 0) {
		*handled = TRUE;
		DC_set_en(DC_EN_ON);
		return ERR_OK;
	} else if (UTIL1_strcmp((char*)cmd, "DC off") == 0) {
		*handled = TRUE;
		DC_set_en(DC_EN_OFF);
		return ERR_OK;
	} else if (UTIL1_strcmp((char*)cmd, "DC up") == 0) {
		*handled = TRUE;
		DC_set_dir(DC_DIR_UP);
		return ERR_OK;
	} else if (UTIL1_strcmp((char*)cmd, "DC down") == 0) {
		*handled = TRUE;
		DC_set_dir(DC_DIR_DOWN);
		return ERR_OK;
	} else if (UTIL1_strncmp((char*)cmd, "DC setpwm ",
			sizeof("DC setpwm")-1) == 0) {
#ifdef DC_PWM_SOURCE_INTERNAL
		CLS1_SendStr((unsigned char*)"PWM is set by hardware\r\n",
						     io->stdErr);
		*handled = TRUE;
#else
		if (!DC_get_en()) {
			CLS1_SendStr((unsigned char*)"DC is off, cannot setpwm\r\n",
				     io->stdErr);
			res = ERR_FAILED;
		} else {
			p = cmd+sizeof("DC setpwm");
			if (UTIL1_xatoi(&p, &val) == ERR_OK
			    && val >= BLDC_RPM_MIN && val <= BLDC_RPM_MAX) {
				// todo
				*handled = TRUE;
			} else {
				sprintf(message,
					"Wrong argument, must be in range %i to %i",
					DC_PWM_MIN, DC_PWM_MAX);
				CLS1_SendStr((unsigned char*)message,
					     io->stdErr);
			}
		}
#endif
	} else if (UTIL1_strcmp((char*)cmd, "DC reset") == 0) {
		*handled = TRUE;
		// todo
	} else if (UTIL1_strcmp((char*)cmd, "DC init") == 0) {
		*handled = TRUE;
		// todo
	}
	return ERR_OK;
}

int DC_get_dir(void)
{
	return DC_DIR_GetVal();
}

int DC_set_dir(bool dir)
{
	if (dir == DC_DIR_UP) {
		DC_DIR_PutVal(DC_DIR_UP);
	} else {
		DC_DIR_PutVal(DC_DIR_DOWN);
	}
	return 0;
}

int DC_get_en(void)
{
	return DC_EN_GetVal();
}

int DC_set_en(bool en)
{
	if (en == DC_EN_ON) {
		DC_set_bot(DC_BOT_FREE);
		DC_set_top(DC_BOT_FREE);
		DC_EN_PutVal(DC_EN_ON);
	} else {
		DC_EN_PutVal(DC_EN_OFF);
	}
	return 0;
}


#ifndef DC_PWM_SOURCE_INTERNAL
int DC_get_PWM(void)
{
	// will not be implemented!
	return 0;
}

int DC_set_PWM(void)
{
	// will not be implemented!
	return 0;
}
#endif

bool DC_get_top(void)
{
	return dc_top;
}

bool DC_set_top(bool status)
{
	if (status) {
		set_status(STATUS_ERROR);
	} else {
		set_status(STATUS_OK);
	}
	return dc_top = status;
}

bool DC_get_bot(void)
{
	return dc_bot;
}

bool DC_set_bot(bool status)
{
	if (status) {
		set_status(STATUS_ERROR);
	} else {
		set_status(STATUS_OK);
	}
	return dc_bot = status;
}
