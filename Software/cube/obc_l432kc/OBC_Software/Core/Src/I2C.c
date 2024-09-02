//*************************HEADERS************************
#include "I2C.h"
#include <stdint.h>

//**************************CODE**************************

// ***********************************************************************************************************************//
// Function  name  : I2C_Init
// Description     : Configures I2C communication
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void I2C_Init(void) {
	/*Initialization settings: Figure 355 reference manual, and master configuration

	 * 1.Clear PE bit in I2C_CR1
	 * 2.Configure ANFOFF and DNF[3:0] in I2C_CR1
	 * 3.Choose the clock source for I2C in RCC_CCIPR
	 * 4.Configure PRESC[3:0], SDADEL[3:0], SCLDEL[3:0], SCLH[7:0], SCLL[7:0] in I2C_TIMINGR
	 * ( see calculus in spreadsheet )
	 * 5.Configure NOSTRETCH in I2C_CR1
	 * 6.
	 */

	//1.Clear PE bit in I2C_CR1
	I2C1->CR1 &= ~(1 << 0);  // Clear PE bit

	//2.Configure ANFOFF and DNF[3:0] in I2C_CR1
	I2C1->CR1 |= (1 << 12);   // ANFOFF disabled
	I2C1->CR1 &= ~(0xF << 8); //Digital filter disabled

	// 3.Choose the clock source for I2C in RCC_CCIPR
	RCC->CCIPR &= ~(0b11 << 12);
	RCC->CCIPR |= (1 << 12); //SYSCLK as clock source for the I2C ( settled in Clocks.c )

	//4. Configure PRESC[3:0], SDADEL[3:0], SCLH[7:0], SCLL[7:0] in I2C_TIMINGR
	I2C1->TIMINGR &= ~(0xF << 28) | ~(0xF << 20) | ~(0xF << 16) | ~(0xFF << 8)
			| ~(0xFF << 0); //force 0
	I2C1->TIMINGR |= (0xD << 28) | (0x4 << 20) | (0x2 << 16) | (0xF << 8)
			| (0x13 << 0);
	// PRESC = 20 (0x14), SCLDEL = 5 (0x5), SDADEL = 3 (0x3), SCLH = 15 (0xFU), SCLL=19 (0x13)

	//5. Configure NOSTRETCH in I2C_CR1
	I2C1->CR1 |= (1 << 17); //Clock stretch disabled

	//6. Enable PE
	I2C1->CR1 |= (1 << 0); // PE bit setted

}

// ***********************************************************************************************************************//
// Function  name  : I2C_Start
// Description     : Set PE bit in I2C_CR1
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void I2C_Start(void) {
	I2C1->CR2 |= (1 << 13); // Set start bit in I2C CR_2
}

// ***********************************************************************************************************************//
// Function  name  : I2C_Stop
// Description     : Reset PE bit in I2C_CR1
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void I2C_Stop(void) {
	I2C1->CR2 |= (1 << 14);  // Set stop bit
}

// ***********************************************************************************************************************//
// Function  name  : I2C_Address
// Description     : Master locking the address of the slave
// Parameters      : Address of slave device to be read and size of bytes to write in slave
// Return          : NACK verification (0 for working address)
// ***********************************************************************************************************************//
int8_t I2C_Address(uint8_t Address) {
	/* Master communication initialization (address phase) 1149 page of user manual pdf
	 *0. Ensure STOP in I2C1_CR2 and AUTOEND = 0
	 *1. In I2C CR_2 choose addressing mode (7 BIT)
	 *2. In I2C CR_2set SADD
	 *3. In I2C CR_2 set the transfer direction RD_WRN
	 *4. In I2C CR_2 set NBYTES to transfer.
	 * */

	//0. Ensure STOP in I2C1_CR2 and AUTOEND=0
	I2C1->CR2 |= (1 << 14);
	I2C1->CR2 &= ~(1 << 25);

	//1. In I2C CR_2 choose addressing mode (7 BIT)
	I2C1->CR2 &= ~(1 << 11);

	//2. In I2C CR_2set SADD
	I2C1->CR2 &= ~(0x3FF);
	I2C1->CR2 |= (Address << 1);

	//3. In I2C CR_2 set the transfer direction RD_WRN (write for addressing phase)
	I2C1->CR2 &= ~(1 << 10);

	//4. In I2C CR_2 set NBYTES to transfer. (writing 1 bit)
	I2C1->CR2 &= ~(0xFF < 16);
	I2C1->CR2 |= (2 << 16);

//	if((I2C1->ISR & (1<<4))) //
//		return I2C_NACK;

	return 0;
}

// ***********************************************************************************************************************//
// Function  name  : I2C_Write
// Description     : Master writing function in I2C slave device
// Parameters      : data to be written in slave device ( or register address ), nmbr of bytes to be written
// Return          : NACK verification (0 for working address)
// ***********************************************************************************************************************//
void I2C_Write(uint8_t *data, uint8_t size) {
	/* Flowchart in the page 1152 (Figure 369)
	 *
	 *1. Wait for TXIS in ISR register to be set ( = 1)
	 *2. Wait for start bit to reset
	 *3. Write the number of bytes to be written
	 *3. Loop for writing multiple size data in I2C1_TXDR
	 *4. Wait for I2C1_ISR.TC to be set
	 * */
	while ((I2C1->ISR & I2C_ISR_TXE) == 0)
		;
	while ((I2C1->CR2 & I2C_CR2_START) == I2C_CR2_START)
		;

	I2C1->CR2 |= (size << 16);

	while (size) {
		I2C1->TXDR = *data++;
		size--;
		while ((I2C1->ISR & I2C_ISR_TXIS) == 0)
			;
		while ((I2C1->ISR & I2C_ISR_TC) == 0)
			;
	}
}

// ***********************************************************************************************************************//
// Function  name  : I2C_Write
// Description     : Master writing function in I2C slave device
// Parameters      : data to be written in slave device ( or register address )
// Return          : NACK verification (0 for working address)
// ***********************************************************************************************************************//
void I2C_Read(uint8_t Address, uint8_t *buffer, uint8_t size) {
	/*Figure 372 Flowchart
	 *1. Write the slave address
	 *2. Wait for start bit to reset
	 *3. Write the number of bytes to be read
	 *4. In I2C CR_2 set the transfer direction RD_WRN
	 *5. Wait for I2C_ISR.RXNE = 1
	 *6. Loop to read I2C_RXDR
	 *7. Wait for I2C1_ISR.TC to be set
	 * */

	//1. Write the slave address
	I2C1->CR2 |= (Address << 1);

	//2. Wait for star bit to reset
	while ((I2C1->CR2 & I2C_CR2_START) == I2C_CR2_START)
		;

	//3. Write the number of bytes to be read
	I2C1->CR2 |= (size << 16);

	//4. In I2C CR_2 set the transfer direction RD_WRN for read
	I2C1->CR2 |= (1 << 10);

	//5. Wait for I2C_ISR.RXNE = 1

	//6. Loop to read I2C_RXDR
	while (size) {
		while ((I2C1->ISR & I2C_ISR_RXNE) == 0)
			;
		*(buffer++) = (uint8_t) ( I2C1->RXDR & 0xFF);
		size--;
	}
	while ((I2C1->ISR & I2C_ISR_TC) == 0)
		;

}

void I2C_Write_Adress(uint8_t address, uint8_t *data, uint8_t size) {
	/* Master communication initialization (address phase) 1149 page of user manual pdf
	 *0. Ensure STOP in I2C1_CR2 and AUTOEND = 0
	 *1. In I2C CR_2 choose addressing mode (7 BIT)
	 *2. In I2C CR_2set SADD
	 *3. In I2C CR_2 set the transfer direction RD_WRN
	 *4. In I2C CR_2 set NBYTES to transfer.
	 * */

	//0. Ensure STOP in I2C1_CR2 and AUTOEND=0
	I2C1->CR2 &= ~(1 << 14);
	I2C1->CR2 &= ~(1 << 25);

	//1. In I2C CR_2 choose addressing mode (7 BIT)
	I2C1->CR2 &= ~(1 << 11);

	//2. In I2C CR_2set SADD
	I2C1->CR2 &= ~(0x3FF);
	I2C1->CR2 |= (address << 1);

	//3. In I2C CR_2 set the transfer direction RD_WRN (write for addressing phase)
	I2C1->CR2 &= ~(1 << 10);

	//4. In I2C CR_2 set NBYTES to transfer. (writing 1 bit)
	I2C1->CR2 &= ~(0xFF < 16);
	I2C1->CR2 |= ((uint32_t)(size) << 16);

	//start
	I2C_Start();



	/* Flowchart in the page 1152 (Figure 369)
	 *
	 *1. Wait for TXIS in ISR register to be set ( = 1)
	 *2. Wait for start bit to reset
	 *3. Write the number of bytes to be written
	 *3. Loop for writing multiple size data in I2C1_TXDR
	 *4. Wait for I2C1_ISR.TC to be set
	 * */
	while (size) {
		while ((I2C1->ISR & I2C_ISR_TXIS) == 0)
					;
		I2C1->TXDR = *(data++);
		size--;
	}

	while ((I2C1->ISR & I2C_ISR_TC) == 0)
		;
	I2C_Stop();

}

