#ifndef STP_H
#define STP_H

#define STP_POS_MIN	-100
#define STP_POS_MAX	100

#define STP_PARSE_COMMAND_ENABLED 1	/* set to 1 if method ParseCommand()
					is present, 0 otherwise */

byte STP_ParseCommand(const unsigned char *cmd,
		       bool *handled,
		       const CLS1_StdIOType *io);

void spi_write(uint8_t* data);
void spi_read(uint8_t *data);

#endif /* STP_H */
