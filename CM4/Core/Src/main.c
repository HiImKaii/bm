/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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

COM_InitTypeDef BspCOMInit;
USART_HandleTypeDef husart2;

/* USER CODE BEGIN PV */
// Hàm hỗ trợ: SubWord
//static uint32_t SubWord(uint32_t word) {
//    return (sbox[(word >> 24) & 0xFF] << 24) |
//           (sbox[(word >> 16) & 0xFF] << 16) |
//           (sbox[(word >> 8) & 0xFF] << 8) |
//           (sbox[word & 0xFF]);
//}
//
//// Hàm hỗ trợ: RotWord
//static uint32_t RotWord(uint32_t word) {
//    return (word << 8) | (word >> 24);
//}
//
//// AES key expansion
//void AES_Init(AES_Context *ctx, const uint8_t *key) {
//    uint32_t *w = (uint32_t *)ctx->RoundKey;
//    uint32_t temp;
//    int i = 0;
//
//    // Sao chép khóa ban đầu
//    memcpy(w, key, AES_KEY_SIZE);
//
//    // Mở rộng khóa
//    for (i = 4; i < 44; i++) {
//        temp = w[i - 1];
//        if (i % 4 == 0) {
//            temp = SubWord(RotWord(temp)) ^ (Rcon[i / 4 - 1] << 24);
//        }
//        w[i] = w[i - 4] ^ temp;
//    }
//}
//
//// Hàm hỗ trợ: AddRoundKey
//static void AddRoundKey(uint8_t state[4][4], const uint8_t *roundKey) {
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            state[j][i] ^= roundKey[i * 4 + j];
//        }
//    }
//}
//
//// Hàm hỗ trợ: SubBytes
//static void SubBytes(uint8_t state[4][4]) {
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            state[i][j] = sbox[state[i][j]];
//        }
//    }
//}
//
//// Hàm hỗ trợ: ShiftRows
//static void ShiftRows(uint8_t state[4][4]) {
//    uint8_t temp;
//
//    // Row 1
//    temp = state[1][0];
//    state[1][0] = state[1][1];
//    state[1][1] = state[1][2];
//    state[1][2] = state[1][3];
//    state[1][3] = temp;
//
//    // Row 2
//    temp = state[2][0];
//    state[2][0] = state[2][2];
//    state[2][2] = temp;
//    temp = state[2][1];
//    state[2][1] = state[2][3];
//    state[2][3] = temp;
//
//    // Row 3
//    temp = state[3][3];
//    state[3][3] = state[3][2];
//    state[3][2] = state[3][1];
//    state[3][1] = state[3][0];
//    state[3][0] = temp;
//}
//
//// Hàm hỗ trợ: MixColumns
//static uint8_t xtime(uint8_t x) {
//    return (x & 0x80) ? ((x << 1) ^ 0x1B) : (x << 1);
//}
//
//static void MixColumns(uint8_t state[4][4]) {
//    uint8_t temp[4];
//    for (int i = 0; i < 4; i++) {
//        uint8_t s0 = state[0][i];
//        uint8_t s1 = state[1][i];
//        uint8_t s2 = state[2][i];
//        uint8_t s3 = state[3][i];
//
//        temp[0] = xtime(s0) ^ xtime(s1) ^ s1 ^ s2 ^ s3;
//        temp[1] = s0 ^ xtime(s1) ^ xtime(s2) ^ s2 ^ s3;
//        temp[2] = s0 ^ s1 ^ xtime(s2) ^ xtime(s3) ^ s3;
//        temp[3] = xtime(s0) ^ s1 ^ s2 ^ xtime(s3);
//
//        state[0][i] = temp[0];
//        state[1][i] = temp[1];
//        state[2][i] = temp[2];
//        state[3][i] = temp[3];
//    }
//}
//
//// AES Encryption
//// Hàm AES_Encrypt: Mã hóa
//void AES_Encrypt(AES_Context *ctx, uint8_t *input, uint8_t *output) {
//    uint8_t state[4][4];
//    int round;
//
//    // Sao chép input vào state
//    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
//        state[i % 4][i / 4] = input[i];
//    }
//
//    // AddRoundKey
//    AddRoundKey(state, ctx->RoundKey);
//
//    // 9 vòng chính
//    for (round = 1; round < 10; round++) {
//        SubBytes(state);
//        ShiftRows(state);
//        MixColumns(state);
//        AddRoundKey(state, ctx->RoundKey + round * AES_BLOCK_SIZE);
//    }
//
//    // Vòng cuối (không có MixColumns)
//    SubBytes(state);
//    ShiftRows(state);
//    AddRoundKey(state, ctx->RoundKey + 10 * AES_BLOCK_SIZE);
//
//    // Sao chép state ra output
//    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
//        output[i] = state[i % 4][i / 4];
//    }
//}
//
//// Hàm hỗ trợ: InverseMixColumns
//void InvMixColumns(uint8_t state[4][4]) {
//    uint8_t temp[4];
//    for (int i = 0; i < 4; i++) {
//        uint8_t s0 = state[0][i];
//        uint8_t s1 = state[1][i];
//        uint8_t s2 = state[2][i];
//        uint8_t s3 = state[3][i];
//
//        temp[0] = xtime(xtime(xtime(s0 ^ s2))) ^ xtime(xtime(s1 ^ s3)) ^ s0;
//        temp[1] = xtime(xtime(xtime(s1 ^ s3))) ^ xtime(xtime(s0 ^ s2)) ^ s1;
//        temp[2] = xtime(xtime(xtime(s0 ^ s2))) ^ xtime(xtime(s1 ^ s3)) ^ s2;
//        temp[3] = xtime(xtime(xtime(s1 ^ s3))) ^ xtime(xtime(s0 ^ s2)) ^ s3;
//
//        state[0][i] = temp[0];
//        state[1][i] = temp[1];
//        state[2][i] = temp[2];
//        state[3][i] = temp[3];
//    }
//}
//
//// Hàm hỗ trợ: InvSubBytes
//void InvSubBytes(uint8_t state[4][4]) {
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            state[i][j] = rsbox[state[i][j]];
//        }
//    }
//}
//
//// Hàm hỗ trợ: InvShiftRows
//void InvShiftRows(uint8_t state[4][4]) {
//    uint8_t temp;
//
//    // Row 1
//    temp = state[1][3];
//    state[1][3] = state[1][2];
//    state[1][2] = state[1][1];
//    state[1][1] = state[1][0];
//    state[1][0] = temp;
//
//    // Row 2
//    temp = state[2][0];
//    state[2][0] = state[2][2];
//    state[2][2] = temp;
//    temp = state[2][1];
//    state[2][1] = state[2][3];
//    state[2][3] = temp;
//
//    // Row 3
//    temp = state[3][0];
//    state[3][0] = state[3][1];
//    state[3][1] = state[3][2];
//    state[3][2] = state[3][3];
//    state[3][3] = temp;
//}
//
//// Hoàn thiện hàm AES_Decrypt
//void AES_Decrypt(AES_Context *ctx, uint8_t *input, uint8_t *output) {
//    uint8_t state[4][4];
//    int round;
//
//    // Sao chép input vào state
//    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
//        state[i % 4][i / 4] = input[i];
//    }
//
//    // AddRoundKey cho vòng cuối
//    AddRoundKey(state, ctx->RoundKey + 10 * AES_BLOCK_SIZE);
//
//    // 9 vòng chính
//    for (round = 9; round > 0; round--) {
//        InvShiftRows(state);
//        InvSubBytes(state);
//        AddRoundKey(state, ctx->RoundKey + round * AES_BLOCK_SIZE);
//        InvMixColumns(state);
//    }
//
//    // Vòng đầu tiên (không có InvMixColumns)
//    InvShiftRows(state);
//    InvSubBytes(state);
//    AddRoundKey(state, ctx->RoundKey);
//
//    // Sao chép state ra output
//    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
//        output[i] = state[i % 4][i / 4];
//    }
//}
//
//
//void getInputFromKeyboard(uint8_t *buffer, size_t size) {
//    char input[2 * AES_BLOCK_SIZE + 1];
//    fgets(input, sizeof(input), stdin);
//
//    for (size_t i = 0; i < size; i++) {
//        sscanf(&input[i * 2], "%2hhx", &buffer[i]);
//    }
//}

// Hàm hỗ trợ in hex
//void printHex(const uint8_t *data, size_t size) {
//    for (size_t i = 0; i < size; i++) {
//        printf("%02X ", data[i]);
//    }
//    printf("\n");
//}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_USART2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_SW1, BUTTON_MODE_EXTI);
  BSP_PB_Init(BUTTON_SW2, BUTTON_MODE_EXTI);
  BSP_PB_Init(BUTTON_SW3, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* Boot CPU2 */
  HAL_PWREx_ReleaseCore(PWR_CORE_CPU2);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  printf("Hello World\r\n");
//	  HAL_UART_Transmit(&husart2, "hello\n\r",10, 100);
	  HAL_Delay(100);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  husart2.Instance = USART2;
  husart2.Init.BaudRate = 115200;
  husart2.Init.WordLength = USART_WORDLENGTH_8B;
  husart2.Init.StopBits = USART_STOPBITS_1;
  husart2.Init.Parity = USART_PARITY_NONE;
  husart2.Init.Mode = USART_MODE_TX_RX;
  husart2.Init.CLKPolarity = USART_POLARITY_LOW;
  husart2.Init.CLKPhase = USART_PHASE_1EDGE;
  husart2.Init.CLKLastBit = USART_LASTBIT_DISABLE;
  husart2.Init.ClockPrescaler = USART_PRESCALER_DIV1;
  husart2.SlaveMode = USART_SLAVEMODE_DISABLE;
  if (HAL_USART_Init(&husart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_USARTEx_SetTxFifoThreshold(&husart2, USART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_USARTEx_SetRxFifoThreshold(&husart2, USART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_USARTEx_DisableFifoMode(&husart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
