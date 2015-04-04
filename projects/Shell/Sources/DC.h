/*
 * DC.h
 *
 *  Created on: Apr 4, 2015
 *      Author: Nino
 */

#ifndef DC_H_
#define DC_H_

#define DC_PWM_MIN	0
#define DC_PWM_MAX	100

#define DC_PARSE_COMMAND_ENABLED 1	/* set to 1 if method ParseCommand() */

byte DC_ParseCommand(const unsigned char *cmd,
		       bool *handled,
		       const CLS1_StdIOType *io);

#endif /* DC_H_ */
