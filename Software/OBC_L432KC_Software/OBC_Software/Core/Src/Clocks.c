// DESCRIPTION ***************************************************************//
/* Functions in this file are used to:
 * - configure main clock (HCLK) and peripheral clocks (APB1, APB2...) of the system
 * - enable clock of specific peripherals
 */

// **********************HEADER FILES ************************************//
#include "stm32l4xx.h"
#include "Clocks.h"

// ******************* user macro ****************************************//
#define PLL_M 1
#define PLL_N 20
#define PLL_R 0 // PLL_R = 2

// FUNCTIONS *****************************************************************//


// ***********************************************************************************************************************//
// Function name   : ClockConfiguration
// Description     : Define the value of each clock of the device :
//					 SYSCLK : Define by a PLL
//
//
//	  			SYSCLK = 80MHz
//
//
//					 HCLK : Set at its maximum value : 80MHz (= SYSCLK / PRESCALER)
//					 PCLK1: Set at its maximum value : 80MHz (= SYSCLK / PRESCALER)
//					 PCLK2: Set at its maximum value : 80MHz (= SYSCLK / PRESCALER)
// Parameters      : None
// Retval          : None
// ***********************************************************************************************************************//
void ClockConfiguration(void)
{
	/**********STEPS**********
	 * Enable HSE and wait for it to become ready
	 * Set Power Enable Clock and set Voltage regulator
	 * Configure the Flash latency
	 * Configure pre-scalars HCLK, PCLK1, PCLK2
	 * Configure the main PLL
	 * Enable the PLL and wait for it becoming ready
	 * Select the clock source and wait to be set
	 * */
	//
	RCC->CR |= RCC_CR_HSEON;
	while( !(RCC->CR & RCC_CR_HSERDY) );
	//
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	PWR->CR1 |= (1<<10); //Selecting High-performance range
	//
	FLASH->ACR |= (1<<2); // Select 4WS
	//
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; //AHB div 1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1; //APB1 div 1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; //APB2 div 1
	//
	RCC->PLLCFGR = (PLL_M<<4) | (PLL_N << 8) | (PLL_R << 25); // Configuration of PLL PSCLR
	RCC->PLLCFGR = (0b11<<0); //choosing HSE clock
	//
	RCC->CR |= RCC_CR_PLLON;
	while( !(RCC->CR & RCC_CR_PLLRDY ) );
	//
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL );


}

// ***********************************************************************************************************************//
// Function  name  : SetClocks
// Description     : It will activate the peripheral clocks
// Parameters      : N/A
// Return          : N/A
// ***********************************************************************************************************************//
void SetClocks(){
	/**************steps*******************
	/Enable GPIOX clock
	/ Enable  clock
	*/

	//
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN); // peripheral clock GPIOA enabled

	//
	RCC->APB1ENR1 |= (1<<21) ; //I2C1 clock enabled
}













