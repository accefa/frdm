#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include <stdlib.h>

#define MENU_CMD_HELP		"help"
#define MENU_CMD_ROTATE		"rotate"
#define MENU_CMD_DISTANCE	"distance"
#define MENU_CMD_ROTATOR	"rotator"
#define MENU_CMD_SHOOTER	"shooter"
#define MENU_CMD_LOADER		"loader"
#define MENU_CMD_SETRPM		"setrpm"
#define MENU_CMD_FIRE		"fire"
#define MENU_CMD_RESET		"reset"

typedef enum {
	HELP,
	ROTATE,
	DISTANCE,
	ROTATOR,
	SHOOTER,
	LOADER,
	SETRPM,
	FIRE,
	RESET,
	number_of_commands
} cmd_t;

int check_command(unsigned char *input);
void get_command_name(unsigned char *output, unsigned char *input);

void run_command(int command, unsigned char *answer, ...);

#endif /* COMMAND_H */
