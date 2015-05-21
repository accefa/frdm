/*
 * shell.h
 *
 *  Created on: Mar 7, 2015
 *      Author: Nino
 */

#ifndef SHELL_H_
#define SHELL_H_

#define PL_HAS_SHELL (1)

/*! \brief Serial driver initialization */
void SHELL_Init(void);

void shellSendDone(void);

#endif /* SHELL_H_ */
