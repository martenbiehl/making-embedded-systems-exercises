/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define SM300D2_DATA_LENGTH 17
#define RX_BUFFER_SIZE 17
uint8_t rxBuffer[RX_BUFFER_SIZE] = {0};
uint8_t data[SM300D2_DATA_LENGTH] = {0};
volatile bool processData = false;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
//  HAL_UARTEx_ReceiveToIdle_DMA(&huart2,	rxBuffer, RX_BUFFER_SIZE);
  HAL_UART_Receive_DMA(&huart2, rxBuffer, RX_BUFFER_SIZE);
  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA8     ------> USART1_CK
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    PA11     ------> USART1_CTS
    PA12     ------> USART1_RTS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|STLINK_RX_Pin|STLINK_TX_Pin|GPIO_PIN_11
                          |GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA4     ------> USART2_CK
    PD3     ------> USART2_CTS
    PD4     ------> USART2_RTS
    PD5     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA8     ------> USART1_CK
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    PA11     ------> USART1_CTS
    PA12     ------> USART1_RTS
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|STLINK_RX_Pin|STLINK_TX_Pin|GPIO_PIN_11
                          |GPIO_PIN_12);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA4     ------> USART2_CK
    PD3     ------> USART2_CTS
    PD4     ------> USART2_RTS
    PD5     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size)
//{
//	if (huart->Instance == USART1)
//	{
//		;
//	} else if (huart->Instance == USART2) {
//		HAL_UART_Transmit(&huart1, rxBuffer, RX_BUFFER_SIZE, 100);
//
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxBuffer, RX_BUFFER_SIZE);
//	}
//}

//void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
//{
//  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_0);  // toggle PA0
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  processData = true;
}

uint8_t calculate_checksum(uint8_t *data) {
  uint8_t sum = 0;
  for (int i = 0; i < (SM300D2_DATA_LENGTH - 1); i++) {
    sum += *data++;
  }
  return sum;
}

void ProcessData() {
	if (processData) {
		int index = 0;
		while (rxBuffer[index] != 0x3c && index < RX_BUFFER_SIZE) {
			index++;
		}

		if (rxBuffer[index] == 0x3c) {
			// data found
//			if (index < RX_BUFFER_SIZE-17) {
				memcpy(data,&rxBuffer[index], SM300D2_DATA_LENGTH*sizeof(uint8_t));
				HAL_UART_Transmit(&huart1, data, SM300D2_DATA_LENGTH, 100);
				printf("\r\nMessage 0x%02x\r\n", 0x3c);

				if(data[0] == 0x3c && data[1] == 0x02) {
					uint8_t checksum = calculate_checksum(data);

				    printf("Received: 0x%02x, Calculated: 0x%02x, Possible: 0x%02x, 0x%02x",data[SM300D2_DATA_LENGTH - 1], checksum,  checksum - 0x80, checksum + 0x80);

				    if ((checksum != data[SM300D2_DATA_LENGTH - 1])) {// &&
//				      (checksum - 0x80 != data[SM300D2_DATA_LENGTH - 1]) &&
//				      (checksum + 0x80 != data[SM300D2_DATA_LENGTH - 1])) {
				      printf("\r\nError: Checksum does not match.");
				      return;
				    } else {
				      printf("\r\nChecksum correct");

				      const uint16_t co2 = (data[2] * 256) + data[3];
					  const uint16_t formaldehyde = (data[4] * 256) + data[5];
					  const uint16_t tvoc = (data[6] * 256) + data[7];
					  const uint16_t pm_2_5 = (data[8] * 256) + data[9];
					  const uint16_t pm_10_0 = (data[10] * 256) + data[11];
					  // A negative value is indicated by adding 0x80 (128) to the temperature value
					  const float temperature = ((data[12] + (data[13] * 0.1f)) > 128)
													? (((data[12] + (data[13] * 0.1f)) - 128) * -1)
													: data[12] + (data[13] * 0.1f);
					  const float humidity = data[14] + (data[15] * 0.1f);


					  printf("\r\n");
					  printf("CO₂: %u ppm\r\n", co2);
					  printf("Formaldehyde: %u µg/m³\r\n", formaldehyde);
					  printf("TVOC: %u µg/m³\r\n", tvoc);
					  printf("PM2.5: %u µg/m³\r\n", pm_2_5);
					  printf("PM10: %u µg/m³\r\n", pm_10_0);
					  printf("Temperature: %.2f °C\r\n", temperature);
					  printf("Humidity: %.2f percent\r\n", humidity);
					  printf("\r\n");
				    }
				} else {
					printf("\nWrong format");
				}
//			}
		} else {
			// no data found
		}

		processData = false;
//		HAL_UART_Receive_DMA(&huart2, rxBuffer, RX_BUFFER_SIZE);
	}
}

/* USER CODE END 1 */
