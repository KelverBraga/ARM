/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};
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
RTC_HandleTypeDef hrtc;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

/* USER CODE BEGIN PV */
//FTP
/*
ati1
at+cpin?
at+cops?
at^sics=1,"conType","GPRS0"
at^SICS=1,"inactTO","65535"
at^sics=1,alphabet,1
at^SICS=1,"user","tim"
at^SICS=1,"passwd","tim"
at^SICS=1,"apn","tim.br"

at^SISS=1,"srvType","ftp"
at^SISS=1,"conId","1"
at^SISS=1,alphabet,"1"
at^SISS=1,"address","ftpput://infrateste:testeinfra@ftp3.simepar.br:21/example.txt;type=a"
AT^SISO?
AT^SISO=1
AT^SICI?
AT^SISO?
at^sisw=1,100
at^sisw=1,0,1
at^sisc=1
AT+CFUN= 1,1
*/


char ATFun[]= "at+cfun=1,1\r\n";
//GPRS connection profile
char ATI[]="ati\r\n";
char ATc[]="at+cpin?\r\n";
char AT1[]="at+cops?\r\n";
uint8_t ATtype[]="at^sics=1,\"conType\",\"GPRS0\"\r\n";
uint8_t ATtimeout[]="at^SICS=1,\"inactTO\",\"65535\"\r\n";
uint8_t ATsicsAlp[]= "at^sics=1,\"alphabet\",\"1\"\r\n";
uint8_t ATsicsUser[] ="at^SICS=1,\"user\",\"tim\"\r\n";
char ATsics[]="at^SICS=1,\"passwd\",\"tim\"\r\n";
char ATsicsAPN[]="at^SICS=1,\"apn\",\"tim.br\"\r\n";

//Configure the service profile 1 for FTP:
char ATFTPtype[]="at^SISS=1,\"srvType\",\"ftp\"\r\n";
char ATFTPId[]= "at^SISS=1,\"conId\",\"1\"\r\n";

char ATFTP1[]="at^SISS=1";
char ATFTP2[]=",\"address\"";
char ATFTP3[]=",\"ftpput://infrateste:testeinfra@ftp3.simepar.br:21/sime.txt;type=a\"\r\n";

//at^SISS=1,"address","ftpput://infrateste:testeinfra@ftp3.simepar.br:21/example.txt;type=a"
//char ATFTP2[]=".txt;type=a\"\r\n";

//Make an FTP connection:
char ATFTOpenServ[]="at^siso=1\r\n";
char ATFTOsiso[]="at^siso?\r\n";
char ATFTPsici[]="AT^SICI?\r\n";
char ATFTOpenServw[]="at^SISW: 1,100\r\n";
char ATFTOpenServwb[]="at^sisw=1,100\r\n";
char ATFTsisw[]="at^sisw=1,0,1\r\n";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int volatile counter=0;
int timestamp;
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
  SystemClock_Config();
  MX_GPIO_Init();
  MX_RTC_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();

  /* USER CODE BEGIN 2 */
HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
char txData[]="Simepar\n\r";
char Dados[40];
char Tempo[40];

  /* USER CODE END 2 */
sTime.Hours = 10;
sTime.Minutes = 13;
sTime.Seconds = 45;
HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
sDate.Date = 22;
sDate.Month = 7;
sDate.Year = 19;

  /* Infinite loop */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
 
  HAL_Delay(2000);
  HAL_UART_Transmit(&huart1,(uint8_t*)ATI,strlen(ATI),20);
HAL_UART_Receive(&huart1,(uint8_t*)ATI,strlen(ATI),20);
  HAL_Delay(5000);  
 
HAL_UART_Transmit(&huart1,(uint8_t*)ATc,strlen(ATc),20);
HAL_UART_Receive(&huart1,(uint8_t*)ATc,strlen(ATc),20);
  HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)AT1,strlen(AT1),20);
  HAL_UART_Receive(&huart1,(uint8_t*)AT1,strlen(AT1),20);
HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATtype,strlen(ATtype),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATtype,strlen(ATtype),40);
HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATtimeout,strlen(ATtimeout),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATtimeout,strlen(ATtimeout),40);
HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATsicsAlp,strlen(ATsicsAlp),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATsicsAlp,strlen(ATsicsAlp),40);
HAL_Delay(5000);
 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATsicsUser,strlen(ATsicsUser),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATsicsUser,strlen(ATsicsUser),40);
HAL_Delay(5000);
 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATsics,strlen(ATsics),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATsics,strlen(ATsics),40);
  HAL_Delay(5000);
 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATsicsAPN,strlen(ATsicsAPN),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATsicsAPN,strlen(ATsicsAPN),40);
HAL_Delay(5000);
 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTPtype,strlen(ATFTPtype),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTPtype,strlen(ATFTPtype),40);
HAL_Delay(5000);
 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTPId,strlen(ATFTPId),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTPId,strlen(ATFTPId),40);
HAL_Delay(5000);
 
  //HAL_UART_Transmit(&huart1,(uint8_t*)ATFTP1,strlen(ATFTP1),40);
//HAL_UART_Transmit(&huart1,(uint8_t*)ATFTP2,strlen(ATFTP2),40);
  //HAL_UART_Transmit(&huart1,(uint8_t*)ATFTP3,strlen(ATFTP3),40);
HAL_UART_Transmit(&huart1,(uint8_t*)"at^SISS=1,\"address\",\"ftpput://infrateste:testeinfra@ftp3.simepar.br:21/example.txt;type=a\"\r\n",94,40);
HAL_Delay(10000);

//HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  //sprintf(Tempo,"at^SISS=1,\"address\",\"ftpput://infrateste:testeinfra@ftp3.simepar.br:21/sime.txt;type=a\"\r\n");
//HAL_UART_Transmit(&huart1,(uint8_t*)Tempo,strlen(Tempo),40);
 
  //HAL_UART_Transmit(&huart1,(uint8_t*)ATFTP2,strlen(ATFTP2),40);
  //HAL_UART_Receive(&huart1,(uint8_t*)ATFTP2,strlen(ATFTP2),40);

 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTOpenServ,strlen(ATFTOpenServ),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTOpenServ,strlen(ATFTOpenServ),40);
HAL_Delay(5000);
 
  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTOsiso,strlen(ATFTOsiso),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTOsiso,strlen(ATFTOsiso),40);
HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTPsici,strlen(ATFTPsici),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTPsici,strlen(ATFTPsici),40);
HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTOsiso,strlen(ATFTOsiso),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTOsiso,strlen(ATFTOsiso),40);
  HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTOpenServw,strlen(ATFTOpenServw),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTOpenServw,strlen(ATFTOpenServw),40);
HAL_Delay(5000);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTOpenServwb,strlen(ATFTOpenServwb),40);
HAL_UART_Receive(&huart1,(uint8_t*)ATFTOpenServwb,strlen(ATFTOpenServwb),40);
  sprintf(Dados,"Timer:%d:%d:%d, Date:%d/%d/%d,Counter:%d \n",sTime.Hours, sTime.Minutes, sTime.Seconds, sDate.Date, sDate.Month, sDate.Year, counter);
  HAL_UART_Transmit(&huart1,(uint8_t*)Dados,strlen(Dados),40);
HAL_UART_Receive(&huart1,(uint8_t*)Tempo,strlen(Tempo),40);
HAL_Delay(50000);

HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  HAL_Delay(100);

  HAL_UART_Transmit(&huart1,(uint8_t*)ATFTsisw,strlen(ATFTsisw),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTsisw,strlen(ATFTsisw),40);
HAL_Delay(30000);

HAL_UART_Transmit(&huart1,(uint8_t*)ATFun,strlen(ATFun),40);
  HAL_UART_Receive(&huart1,(uint8_t*)ATFTsisw,strlen(ATFTsisw),40);
HAL_Delay(30000);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
   
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */

  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 15;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
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
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma1_channel1
  */
static void MX_DMA_Init(void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma1_channel1 on DMA1_Channel1 */
  hdma_memtomem_dma1_channel1.Instance = DMA1_Channel1;
  hdma_memtomem_dma1_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_LOW;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_channel1) != HAL_OK)
  {
    Error_Handler( );
  }

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
if(htim->Instance==TIM2){
timestamp=__HAL_TIM_GET_COUNTER(htim);
counter++;

}
}

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

