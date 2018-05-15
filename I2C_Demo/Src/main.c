/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "SerialTransmit.h"
#include "Sensor.h"
#include "CommonGpio.h"
#include "SlaveDefine.h"
#include "RspHandle.h"
#include "ZigbeeXbee.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

osThreadId defaultTaskHandle;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char tmpStr[256];
flashData g_FlashData;
uint16_t SensorBoxAddress = DEFAULT_SLAVE_ADDRESS ;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C1_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint8_t g_pu8RxBeeBuff[128] = {0};
uint16_t g_u16RxBeeCount = 0;

osThreadId BeeTaskHandle;

QueueHandle_t xRxBeeeQueue;
uint8_t g_u8RxBeeBuff;
RTC_DateTypeDef g_Date;
RTC_TimeTypeDef g_Time;
void BeeTask(void const * argument);
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
 // MX_USART1_UART_Init();
 // MX_USART2_UART_Init();
 // MX_USART3_UART_Init();
  MX_RTC_Init();
//  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */
CommonGpioInit();
UartDebugInit();
ZigbeeInit();
I2cInit();
initFlashData();
//DebugPutString("Hello tuyen wala");
HAL_RTC_GetDate(&hrtc,&g_Date,RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc,&g_Time,RTC_FORMAT_BIN);
	DebugPutString("\r\nRTC Date: ");
	if(g_Date.WeekDay == RTC_WEEKDAY_MONDAY) {
		DebugPutString("Mon");
	} else if (g_Date.WeekDay == RTC_WEEKDAY_TUESDAY) {
		DebugPutString("Tue");
	} else if (g_Date.WeekDay == RTC_WEEKDAY_WEDNESDAY) {
		DebugPutString("Wed");
	} else if (g_Date.WeekDay == RTC_WEEKDAY_THURSDAY) {
		DebugPutString("Thus");
	} else if (g_Date.WeekDay == RTC_WEEKDAY_FRIDAY) {
		DebugPutString("Fri");
	} else if (g_Date.WeekDay == RTC_WEEKDAY_SATURDAY) {
		DebugPutString("Sat");
	} else if (g_Date.WeekDay == RTC_WEEKDAY_SUNDAY) {
		DebugPutString("Sun");
	} else DebugPutString("Invalid weekday");
	sprintf(tmpStr," %02u/%02u/%02u", g_Date.Date, g_Date.Month, g_Date.Year);
	DebugPutString(tmpStr);
	sprintf(tmpStr,"\r\nRTC Time: %02u:%02u:%02u", g_Time.Hours, g_Time.Minutes, g_Time.Seconds);
	DebugPutString(tmpStr);


	xRxBeeeQueue = xQueueCreate(32,sizeof(uint8_t));
	if(xRxBeeeQueue == 0){
		DebugPutString("\r\nInit xRxZigbeeQueue FAILED");
		while(1);
	}
	osThreadDef(beeTask,BeeTask,osPriorityNormal,0,256);
	BeeTaskHandle = osThreadCreate(osThread(beeTask),NULL);
	
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	HAL_UART_Receive_IT(&ZIGBEE,&g_u8RxBeeBuff,1);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	//DebugPutString("Hello tuyen wala");
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART3 init function */
static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void BeeTask(void const * argument){
	for(;;){
		//DebugPutString("\r\nBEETASK\r\n");
		while(xQueueReceive(xRxBeeeQueue, & g_pu8RxBeeBuff[g_u16RxBeeCount], (TickType_t)10) == pdPASS)
		{
			if(g_u16RxBeeCount++>100) break;
		}
		if(g_u16RxBeeCount>0)
			{
					DebugPutString("\r\nZigbee receive message ");
					sprintf(tmpStr,"%02u bytes", g_u16RxBeeCount);
					DebugPutString(tmpStr);
					for(int i=0; i<g_u16RxBeeCount; i++){
						DebugPutString("\t");
						DebugPutHex(g_pu8RxBeeBuff[i]);
					}
					if(ZigbeeXbeeHandleMessage(g_pu8RxBeeBuff,g_u16RxBeeCount)){
						DebugPutString("\r\nZigbee Handle Message OK");
					} 
					else {
						DebugPutString("\r\nZigbee Handle Message ERROR");
					}
					memset(g_pu8RxBeeBuff,0,128);
						g_u16RxBeeCount = 0;
			}
		osDelay(110);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	//BaseType_t xRxRs485Woken;
	BaseType_t xRxBeeWoken;
//	if(huart->Instance == RS485.Instance){
//		xRxRs485Woken = pdFALSE;
//		xQueueSendFromISR(xRxRs485Queue,&g_u8RxRs485Buff,&xRxRs485Woken);
//		HAL_UART_Receive_IT(&RS485,&g_u8RxRs485Buff,1);
//	}
	if(huart->Instance == ZIGBEE.Instance){
		xRxBeeWoken = pdFALSE;
		xQueueSendFromISR(xRxBeeeQueue,&g_u8RxBeeBuff,&xRxBeeWoken);
		HAL_UART_Receive_IT(&ZIGBEE,&g_u8RxBeeBuff,1);
	}
}
/* USER CODE END 4 */

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		DebugPutString("*");
		//SensorCommunication();
		// sensor am2315  port 1,2,3,4 channel 1 
		if(u8Port1_channel1 ==1)
		{
		DebugPutString("\r\nport1 = AM2315\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH1();
		AM2315UpdateValue();
		}
		if(u8Port2_channel1 ==1)
		{
		DebugPutString("\r\nport2 = AM2315\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH2();
		AM2315UpdateValue();
		}
		if(u8Port3_channel1 ==1)
		{
		DebugPutString("\r\nport3 = AM2315\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH3();
		AM2315UpdateValue();
		}
		if(u8Port4_channel1 ==1)
		{
		DebugPutString("\r\nport4 = AM2315\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH4();
		AM2315UpdateValue();
		}
		// sensor am2315  port 1,2,3,4 channel 2 chua lam 
		
		// sensor bh1750 port 1,2,3,4 channel 1 
		if(u8Port1_channel1 ==2)
		{
		DebugPutString("\r\nport1 = BH1750\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH1();
		BH1750UpdateValue();
		}
		if(u8Port2_channel1 ==2)
		{
		DebugPutString("\r\nport2 = BH1750\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH2();
		BH1750UpdateValue();
		}
		if(u8Port3_channel1 ==2)
		{
		DebugPutString("\r\nport3 = BH1750\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH3();
		BH1750UpdateValue();
		}
		if(u8Port4_channel1 ==2)
		{
		DebugPutString("\r\nport4 = BH1750\r\n");
		I2C_ENABLE();
		I2C_SELECT_CH4();
		BH1750UpdateValue();
		}
		// sensor bh1750 port 1,2,3,4 channel 2 chua lam 
    osDelay(1000);
  }
  /* USER CODE END 5 */ 
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
/* USER CODE BEGIN Callback 0 */

/* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
/* USER CODE BEGIN Callback 1 */

/* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
