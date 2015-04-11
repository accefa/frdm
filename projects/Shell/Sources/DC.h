/*
 * DC.h
 *
 *  Created on: Apr 4, 2015
 *      Author: Nino
 */

#ifndef DC_H_
#define DC_H_

#define DC_PWM_SOURCE_INTERNAL 1

#ifndef DC_PWM_SOURCE_INTERNAL
#define DC_PWM_MIN	0
#define DC_PWM_MAX	100
#endif

#define DC_DIR_UP		1
#define DC_DIR_DOWN		0
#define DC_DIR_DEFAULT		DC_DIR_DOWN

#define DC_SRC_INTERNAL		1
#define DC_SRC_EXTERNAL		0
#define DC_SRC_DEFAULT		DC_SRC_INTERNAL

#define DC_EN_ON 		1
#define DC_EN_OFF 		0
#define DC_EN_DEFAULT		DC_EN_OFF

#define DC_HWRST_ON 		1
#define DC_HWRST_OFF 		0
#define DC_HWRST_DEFAULT	DC_HWRST_ON

#define DC_TOP_REACHED		1
#define DC_TOP_FREE		0

#define DC_BOT_REACHED		1
#define DC_BOT_FREE		0

#define DC_PARSE_COMMAND_ENABLED 1	/* set to 1 if method ParseCommand() */

byte DC_ParseCommand(const unsigned char *cmd,
		       bool *handled,
		       const CLS1_StdIOType *io);

// direction
int DC_get_dir(void);
int DC_set_dir(bool dir);

// clock source
int DC_get_src(void);
int DC_set_src(bool src);

// enable (PWM if external source)
int DC_get_en(void);
int DC_set_en(bool en);

// driver chip reset
int DC_get_hwrst(void);
int DC_set_hwrst(bool hwrst);

// driver chip fault flags
int DC_get_ff1(void);
int DC_get_ff2(void);

// PWM setting
int DC_get_PWM(void);
int DC_set_PWM(int PWM);

// top-end-positions
bool DC_get_top(void);
bool DC_set_top(bool status);

// bottom-end-positions
bool DC_get_bot(void);
bool DC_set_bot(bool status);


#endif /* DC_H_ */
