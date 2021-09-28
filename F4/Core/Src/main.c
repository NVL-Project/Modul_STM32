/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "lcd_character.h"
#include "stdio.h"

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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
uint32_t adc[3];
float ref, set;
char buff[10];
float data[3];
int cout,Set = 0;
int i = 0;
uint8_t SS[6]={
	0x00,
	0x01,
	0x02,
	0x04,
	0x08,
	0x0F,

};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
/*void display_data (float data)
{
	sprintf (x_char, "%0.2f", data);
    //SSD1306_Puts (x_char, &Font_7x10, 1);
    SSD1306_Puts (x_char, &Font_16x26, 1);

	SSD1306_UpdateScreen ();  // update display
}*/
void tampilLCD(float data)
{
	sprintf(buff, "%0.2f", data);
	lcd_puts(buff);
}
void RunningLed(void)
{

	/*HAL_GPIO_WritePin(GPIOC, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(GPIOC, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(GPIOC, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(GPIOC, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(GPIOC, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);

	HAL_GPIO_WritePin(GPIOC, LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	HAL_Delay(10);*/
	for (i=0; i<=6; i++)
	{
		GPIOC->ODR = ~(1<<i);
		HAL_Delay(10);
	}
	for (i=6; i>=0; i--)
	{
		GPIOC->ODR = ~(1<<i);
		HAL_Delay(10);
	}
}

void Btn(void)
{
	if(HAL_GPIO_ReadPin(GPIOA, BT1_Pin)==0)
		  {
		  if (cout < 3)
			  cout++;
		  //else
			  //cout=0
		  lcd_clear();
	  }
	  if (HAL_GPIO_ReadPin(GPIOA, BT2_Pin)==0)
	  {
		  if (cout > 0)
			  cout--;
		  //else
			  //cout=2;
		  lcd_clear();
	  }
	  if (HAL_GPIO_ReadPin(GPIOA, BT3_Pin) == 0)
	  {
		  if (Set < 1)
			  Set++;
		  else
			  Set=0;
		  lcd_clear();
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  lcd_init();
  /* USER CODE BEGIN 2 */

  //HAL_ADC_Start_DMA(&hadc1, adc, 3);
  //SSD1306_GotoXY(10, 10);
  //SSD1306_Putc ('T', &Font_11x18, 1);
  //HAL_Delay(1000);
  //SSD1306_Clear();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 100);
	  adc[0] = HAL_ADC_GetValue(&hadc1);
	  lcd_gotoxy(2, 0);
	  lcd_puts("LDR :");
	  lcd_gotoxy(8, 0);
	  //tampilLCD(adc[0]);
	  lcd_float6(adc[0]);

	  HAL_ADC_PollForConversion(&hadc1, 100);
	  adc[1] = HAL_ADC_GetValue(&hadc1);
	  lcd_gotoxy(2, 1);
	  lcd_puts("POT :");
	  lcd_gotoxy(8, 1);
	  //tampilLCD(adc[1]);
	  lcd_float6(adc[1]);

	  HAL_ADC_PollForConversion(&hadc1, 100);
	  adc[2] = HAL_ADC_GetValue(&hadc1);
	  lcd_gotoxy(2, 2);
	  lcd_puts("LM35 :");
	  lcd_gotoxy(8, 2);
	  tampilLCD((adc[2]*(5000.0/4096.0))/10);
	  lcd_gotoxy(14, 2);
	  lcd_puts("C");

	  //tampilLCD(adc[2]/set);
	  //8.192
	  HAL_ADC_Stop(&hadc1);

	  /*lcd_gotoxy(0, 3);
	  	  tampilLCD(adc[2]);
	  	  lcd_gotoxy(10, 3);
	  	  tampilLCD(ref);*/

	  lcd_gotoxy(2, 3);
	  lcd_puts("Motor :");

	  if (cout == 0)
	  {
		  lcd_gotoxy(0, 0);
		  lcd_puts(">");
	  }
	  if (cout == 1)
	  {
		  lcd_gotoxy(0, 1);
		  lcd_puts(">");
	  }
	  if (cout == 2)
	  {
		  lcd_gotoxy(0, 2);
		  lcd_puts(">");
	  }
	  if (cout == 3)
	  {
		  lcd_gotoxy(0, 3);
		  lcd_puts(">");
	  }

	  if(Set == 0 && cout == 3)
	  {
		  HAL_GPIO_WritePin(GPIOB, MOTOR_Pin, GPIO_PIN_RESET);
		  lcd_gotoxy(9, 3);
		  lcd_puts("Berhenti");
	  }
	  if(Set == 1 && cout == 3)
	  {
		  HAL_GPIO_WritePin(GPIOB, MOTOR_Pin, GPIO_PIN_SET);
		  lcd_gotoxy(9, 3);
		  lcd_puts("Jalan");
	  }

	  Btn();
	  RunningLed();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin 
                          |LED5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, RS_Pin|RW_Pin|EN_Pin|D4_Pin 
                          |D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin 
                           LED5_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin 
                          |LED5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BT1_Pin BT2_Pin BT3_Pin */
  GPIO_InitStruct.Pin = BT1_Pin|BT2_Pin|BT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : MOTOR_Pin */
  GPIO_InitStruct.Pin = MOTOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MOTOR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RS_Pin RW_Pin EN_Pin D4_Pin 
                           D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|EN_Pin|D4_Pin 
                          |D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
