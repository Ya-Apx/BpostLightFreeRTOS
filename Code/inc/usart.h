/*******************************************Library********************************************/
#include "stm32f10x.h"

/****************************************Used function*****************************************/
void InitUSART1 (void); //Tx->PA9; Rx->PA10; Baud rate 9600; RXNEIE; IDLE; USART Enable
void InitUSART2 (void); //Tx->PA2; Rx->PA3; Baud rate 115200; RXNEIE; USART Enable

void SendUSART(USART_TypeDef *USARTx, char chr);
void SendStringUSART(USART_TypeDef *USARTx, char* str);

void ClearFlagIDLE(USART_TypeDef *USARTx);

void ClearBuffer(char* str, uint8_t buffLen);

