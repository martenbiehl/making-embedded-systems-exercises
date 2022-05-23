// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include <stdio.h>
#include "string.h"
#include "consoleIo.h"
#include "usart.h"

#define RX_BUFFER_SIZE 12
uint8_t rxBuffer[RX_BUFFER_SIZE] = {0};
volatile uint16_t dataAvailable = 0;

eConsoleError ConsoleIoInit(void)
{
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1,	rxBuffer, RX_BUFFER_SIZE);
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{

	uint32_t i = 0;
	char ch;

	while ( ( EOF != ch ) && ( i < bufferLength ) && (i < dataAvailable) && (i < RX_BUFFER_SIZE) )
	{
		ch = (char) rxBuffer[i];
		buffer[i] = (uint8_t) ch;
		i++;
	}

	if (i == dataAvailable) // Data has been processed
	{
		dataAvailable = 0;
	}


	HAL_UART_Transmit(&huart1, buffer, RX_BUFFER_SIZE, 100);

	*readLength = i;


	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer, RX_BUFFER_SIZE);

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	HAL_UART_Transmit(&huart1, (uint8_t*) buffer, strlen(buffer), 100);
	return CONSOLE_SUCCESS;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size)
{
	if (huart->Instance == USART1)
	{
		dataAvailable = size;
	}
}
