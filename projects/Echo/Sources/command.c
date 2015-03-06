#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "RxBuf.h"
#include "AS1.h"
#include "command.h"

static int distance = 150;
static int fire = 0;
static int loader = 0;
static int reset = 0;
static int rotate = 175;
static int rotator = 0;
static int rpm = 5999;
static int shooter = 0;

int check_command(unsigned char *input)
{
	int command = 0;

	if (strcmp(input, MENU_CMD_DISTANCE) == 0) {
		command = DISTANCE;
	} else if (strcmp(input, MENU_CMD_FIRE) == 0) {
		command = FIRE;
	} else if (strcmp(input, MENU_CMD_HELP) == 0) {
		command = HELP;
	} else if (strcmp(input, MENU_CMD_LOADER) == 0) {
		command = LOADER;
	} else if (strcmp(input, MENU_CMD_RESET) == 0) {
		command = RESET;
	} else if (strcmp(input, MENU_CMD_ROTATE) == 0) {
		command = ROTATE;
	} else if (strcmp(input, MENU_CMD_ROTATOR) == 0) {
		command = ROTATOR;
	} else if (strcmp(input, MENU_CMD_SETRPM) == 0) {
		command = SETRPM;
	} else if (strcmp(input, MENU_CMD_SHOOTER) == 0) {
		command = SHOOTER;
	} else {
		command = HELP;
	}

	return command;
}

void get_command_name(unsigned char *output, unsigned char *input)
{
	int command;
	command = check_command(input);

	switch (command) {
	case DISTANCE:
		strcpy(output, MENU_CMD_DISTANCE);
		break;
	case FIRE:
		strcpy(output, MENU_CMD_FIRE);
		break;
	case HELP:
		strcpy(output, MENU_CMD_HELP);
		break;
	case LOADER:
		strcpy(output, MENU_CMD_LOADER);
		break;
	case RESET:
		strcpy(output, MENU_CMD_RESET);
		break;
	case ROTATE:
		strcpy(output, MENU_CMD_ROTATE);
		break;
	case ROTATOR:
		strcpy(output, MENU_CMD_ROTATOR);
		break;
	case SETRPM:
		strcpy(output, MENU_CMD_SETRPM);
		break;
	case SHOOTER:
		strcpy(output, MENU_CMD_SHOOTER);
		break;
	default:
		strcpy(output, MENU_CMD_HELP);
		break;
	}
}

void run_command(int command, unsigned char *answer, ...)
{
	switch (command) {
	case DISTANCE:
		sprintf(answer, "distance = %i", distance);
		break;
	case FIRE:
		if (fire) {
			sprintf(answer, "fire = enabled");
		} else {
			sprintf(answer, "fire = disabled");
		}
		break;
	case HELP:
		sprintf(answer, "see manpage");
		break;
	case LOADER:
		if (loader) {
			sprintf(answer, "loader = enabled");
		} else {
			sprintf(answer, "loader = disabled");
		}
		break;
	case RESET:
		if (reset) {
			sprintf(answer, "fire = enabled");
		} else {
			sprintf(answer, "fire = disabled");
		}
		break;
	case ROTATE:
		sprintf(answer, "angle = %i", rotate);
		break;
	case ROTATOR:
		if (rotator) {
			sprintf(answer, "rotator = enabled");
		} else {
			sprintf(answer, "rotator = disabled");
		}
		break;
	case SETRPM:
		sprintf(answer, "RPM = %i", rpm);
		break;
	case SHOOTER:
		if (shooter) {
			sprintf(answer, "shooter = enabled");
		} else {
			sprintf(answer, "shooter = disabled");
		}
		break;
	default:
		break;
	}
}
