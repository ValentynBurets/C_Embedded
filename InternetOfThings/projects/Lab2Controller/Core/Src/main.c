/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#define lcdPort GPIOE
#define rsPin GPIO_PIN_7
#define rwPin GPIO_PIN_10
#define enPin GPIO_PIN_11
#define dh4Pin GPIO_PIN_12
#define dh5Pin GPIO_PIN_13
#define dh6Pin GPIO_PIN_14
#define dh7Pin GPIO_PIN_15

#define RS(X) HAL_GPIO_WritePin(lcdPort, rsPin, (X))
#define RW(X) HAL_GPIO_WritePin(lcdPort, rwPin, (X))
#define EN(X) HAL_GPIO_WritePin(lcdPort, enPin, (X))
#define DH4(X) HAL_GPIO_WritePin(lcdPort, dh4Pin, (X))
#define DH5(X) HAL_GPIO_WritePin(lcdPort, dh5Pin, (X))
#define DH6(X) HAL_GPIO_WritePin(lcdPort, dh6Pin, (X))
#define DH7(X) HAL_GPIO_WritePin(lcdPort, dh7Pin, (X))
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

void lcdSend(uint8_t isCommand, uint8_t data) {
 RS(isCommand!=0);
 HAL_Delay(1);
 DH7(((data >> 7) & 1)==1);
 DH6(((data >> 6) & 1)==1);
 DH5(((data >> 5) & 1)==1);
 DH4(((data >> 4) & 1)==1);
 EN(1);
 HAL_Delay (1);
 EN(0);
 DH7(((data >> 3) & 1)==1);
 DH6(((data >> 2) & 1)==1);
 DH5(((data >> 1) & 1)==1);
 DH4((data & 1)==1);
 EN(1);
 HAL_Delay (1);
 EN(0);
}

void lcdCommand(uint8_t cmd) {
 lcdSend(1, cmd);
}
void lcdChar(const char chr) {
 lcdSend(0, (uint8_t)chr);
}

void setCursor(uint8_t col, uint8_t row)
{
 lcdSend(1,0x80 | (col | row*0x40));
}
void parametrsToggle(uint8_t display,uint8_t cursor,uint8_t blink){
 uint8_t comm = 0x08;
 if(display)comm|=0x04;
 if(cursor)comm|=0x02;
 if(blink)comm|=0x01;
 lcdCommand(comm);
}
void shiftToggle(uint8_t rightShift,uint8_t scrollInc){
 uint8_t comm = 0x04;
 if(rightShift)comm|=0x02;
 if(scrollInc)comm|=0x01;
 lcdCommand(comm);
}
void scrollRight(void){
 lcdCommand(0x10|0x08|0x00);
}
void scrollLeft(void){
 lcdCommand(0x10|0x08|0x04);
}
void clear(void)
{
 lcdCommand(0x01);
 HAL_Delay(2);
}
void home(void)
{
 lcdCommand(0x02);
 HAL_Delay(2);
}


void initLCD(void){
 HAL_Delay(40);
 lcdCommand(0x02);
 HAL_Delay(1);
 lcdCommand(0x28);
 HAL_Delay(1);
 lcdCommand(0x28);
 HAL_Delay(1);
 parametrsToggle(1,0,0);
 HAL_Delay(1);
 clear();
 shiftToggle(1,0);
}

void lcdString(char* str){
 for(uint8_t i=0;str[i]!='\0';i++){
 lcdChar(str[i]);
 }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  initLCD();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  char PIP[] = "Burets Valentyn Vasylovych/0";
  char text[] = "illumination red and green LED";

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	lcdString(PIP);

	HAL_Delay(5000);

	lcdString(text);

	HAL_Delay(5000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
