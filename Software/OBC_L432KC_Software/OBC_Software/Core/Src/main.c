

/********************** INCLUDES *********************************/
#include <Port_Conf.h>
#include "stm32l4xx.h"

#include "main.h"

#include "../CSUG-library/Inc/I2C.hpp"
#include "Clocks.h"
#include "code_eleve.h"
#include "PWM.h"
#include "Timer.h"
#include "UART.h"

/********************** VARIABLES *********************************/


/********************** CODE *********************************/


/*
 * PA9 -> I2C_SCL
 * PA10 -> I2C_SDA
 *
 * PA12 -> CAN1_TD
 * PA11 -> CAN1_RD
 *
 * PB7 -> UART1_RX
 * PB6 -> UART1_TX
 */

int main(void)
{
	//Init clock and flash
	SystemInit();

	ClockConfiguration(); //must do a function setting the clock's source and setting the prescaler of HCLK, PCLK1 & PCLK2

	SetClocks();	//must do a function to set peripherals clocks

	InitPeripheral();		// Init peripheral I/O's
	InitTimer_1();			//init timer 1
	I2C_Init();			//init I2C mode
	while (1)
	{


	}

}


