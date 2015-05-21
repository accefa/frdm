#ifndef STP_H
#define STP_H

#define STP_POS_MIN	-100
#define STP_POS_MAX	100

#define STP_EN_ON	1
#define STP_EN_OFF	0

#define STP_PARSE_COMMAND_ENABLED 1	/* set to 1 if method ParseCommand()
					is present, 0 otherwise */

byte STP_ParseCommand(const unsigned char *cmd,
		       bool *handled,
		       const CLS1_StdIOType *io);

void spi_write(uint8_t* data);
void spi_read(uint8_t *data);

void STP_move(int steps);
void STP_reset(void);

#endif /* STP_H */
