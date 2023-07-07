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
void I2C_Init(void){
	/*Initialization settings: Figure 355 reference manual, and master configuration

	 * 1.Clear PE bit in I2C_CR1
	 * 2.Configure ANFOFF and DNF[3:0] in I2C_CR1
	 * 3.Choose the clock source for I2C in RCC_CCIPR
	 * 4.Configure PRESC[3:0], SDADEL[3:0], SCLDEL[3:0], SCLH[7:0], SCLL[7:0] in I2C_TIMINGR
	 * ( see calculus in spreadsheet )
	 * 5.Configure NOSTRETCH in I2C_CR1
	 */

	//1.Clear PE bit in I2C_CR1
	I2C1->CR1 &= ~(1<<0);  // Clear PE bit

	//2.Configure ANFOFF and DNF[3:0] in I2C_CR1
	I2C1->CR1 |= (1<<12);   // ANFOFF disabled
	I2C1->CR1 &= ~(0xF<<8); //Digital filter disabled

	// 3.Choose the clock source for I2C in RCC_CCIPR
	RCC->CCIPR |= (1<<12); //SYSCLK as clock source for the I2C ( settled in Clocks.c )

	//4. Configure PRESC[3:0], SDADEL[3:0], SCLH[7:0], SCLL[7:0] in I2C_TIMINGR
	I2C1->TIMINGR |= (0x8<<28) | (0xC<<20) | (0x8<<16) | (0x23<<8) | (0x2C<<0);
	// PRESC = 8 (0x8), SCLDEL = 12 (0xC), SDADEL = 8 (0x8U), SCLH = 35 (0x23U), SCLL=44 (0x2C)

	//5. Configure NOSTRETCH in I2C_CR1
	I2C1->CR1 |= (1<<17); //Clock stretch disabled

	//6. Enable PE
	I2C->CR1 |= (1<<0); // PE bit setted

}

// ***********************************************************************************************************************//
// Function  name  : I2C_Start
// Description     : Set PE bit in I2C_CR1
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void I2C_Start(void){
	I2C->CR2 |= (1<<13); // PE bit setted
}

// ***********************************************************************************************************************//
// Function  name  : I2C_Stop
// Description     : Reset PE bit in I2C_CR1
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void I2C_Stop(void){
	//I2C1->CR1 &= ~(1<<0);  // Clear PE bit
}

// ***********************************************************************************************************************//
// Function  name  : I2C_Address
// Description     : Master locking the address of the slave
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void I2C_Address(uint8_t Address){
	/* Master communication initialization (address phase) 1149 page of user manual pdf

	 *1. In I2C CR_2 choose addressing mode (7 BIT)
	 *2. In I2C CR_2set SADD
	 *3. In I2C CR_2 set the transfer direction RD_WRN
	 *4. In I2C CR_2 set NBYTES to transfer.
	 * */


}













