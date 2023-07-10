#ifndef INC_I2C_H_
#define INC_I2C_H_

#include <stdint.h>
#include <stm32l432xx.h>
#include <stdbool.h>

#define I2C_NACK -1


void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop (void);
int8_t I2C_Address (uint8_t Address);
void I2C_Write (uint8_t *data, uint8_t size);
void I2C_Read (uint8_t Address, uint8_t *buffer, uint8_t size);

#endif /* CSUG_LIBRARY_INC_I2C_H_ */
