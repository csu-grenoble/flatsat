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
	/*
	//
	RCC->CR |= (1<<16);
	while( (RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY );
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
	while( (RCC->CR & RCC_CR_PLLRDY ) != RCC_CR_PLLRDY );
	//
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while( (RCC->CFGR & (0b11<<2) ) != RCC_CFGR_SWS_PLL );

	*/
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  /** Configure the main internal regulator output voltage
	  */
	  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	  {
	    //Error_Handler();
	  }

	  /** Configure LSE Drive Capability
	  */
	  HAL_PWR_EnableBkUpAccess();
	  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
	  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	  RCC_OscInitStruct.MSICalibrationValue = 0;
	  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	  RCC_OscInitStruct.PLL.PLLM = 1;
	  RCC_OscInitStruct.PLL.PLLN = 40;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	   // Error_Handler();
	  }

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	  {
	   // Error_Handler();
	  }

	  /** Enable MSI Auto calibration
	  */
	  HAL_RCCEx_EnableMSIPLLMode();
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













