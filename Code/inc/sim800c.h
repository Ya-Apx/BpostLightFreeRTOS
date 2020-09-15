/*******************************************Library********************************************/
#include "stm32f10x.h"

/*******************************************Defines********************************************/
//PB14 SIM800 power suply (SIM900_PWR_ON), 0 is ON
#define POWER_SIM800_ON()       GPIOB->BSRR |= GPIO_BSRR_BR14
#define POWER_SIM800_OFF()      GPIOB->BSRR |= GPIO_BSRR_BS14

//PA8 SIM800 power suply (SIM900_PWR_ON), 0 is ON
#define PKEY_SIM800_ON()       GPIOA->BSRR |= GPIO_BSRR_BR8
#define PKEY_SIM800_OFF()      GPIOA->BSRR |= GPIO_BSRR_BS8;

//UART SIM800
#define SIM800_USART USART3
#define SIM800_IRQn USART3_IRQn
#define SIM800_IRQHandler USART3_IRQHandler

/****************************************Used function*****************************************/
void PowerOnSIM800(void);
void InitSIM800_GPIO (void);
void InitSIM800_USART (void);	//Tx->PB10; Rx->PB11; Baud rate 9600; RXNEIE; IDLE; USART Enable
void SendStringSIM800_USART(char* str);
void SendSIM800_USART(char chr);


