#include "sim800c.h"



void InitSIM800_USART (void){
//Tx->PB10; Rx->PB11; Baud rate 9600; RXNEIE; USART Enable
/***********************************SIM800_USART clock init************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 	/* I/O port C clock enable */
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; /* USART3 clock enable */
	RCC->APB2ENR |=	RCC_APB2ENR_AFIOEN;		/* Alternate Function I/O clock enable */
	
/**********************************SIM800_USART TX pin init************************************/
	GPIOB->CRH &=	~GPIO_CRH_CNF10_0;				/* CNF10[1:0] 10 (Alternate function output Push-pull) */
	GPIOB->CRH |=	GPIO_CRH_CNF10_1;				/* CNF10[1:0] 10 (Alternate function output Push-pull) */
	GPIOB->CRH |= GPIO_CRH_MODE10;   			/* MODE10[1:0] 11 (Output mode, max speed 50 MHz) */  
	
/**********************************SIM800_USART RX pin init************************************/
	GPIOB->CRH |=	GPIO_CRH_CNF11_0;				/* CNF11[1:0] 01 (Floating input) */
	GPIOB->CRH &=	~GPIO_CRH_CNF11_1;			/* CNF11[1:0] 01 (Floating input) */
	GPIOB->CRH &= ~GPIO_CRH_MODE11;   		/* MODE11[1:0] 00 (Input mode) */  

/********************************SIM800_USART baud rate congig**********************************/	
	SIM800_USART->BRR=0xEA6; 									/* Baud rate 9600 (36MHz -> 3750 in HEX 0xEA6)*/
	
/*******************************SIM800_USART enable bits congig*********************************/	
	SIM800_USART->CR1 |= USART_CR1_TE;					/* Transmitter Enable */
	SIM800_USART->CR1 |= USART_CR1_RE;					/* Receiver Enable */
	SIM800_USART->CR1 |= USART_CR1_UE;					/* USART Enable */

/******************************SIM800_USART RXNE interrupt enable********************************/	
	SIM800_USART->CR1 |=USART_CR1_IDLEIE;				/* IDLE Interrupt Enable */
	SIM800_USART->CR1 |=USART_CR1_RXNEIE;				/* RXNE Interrupt Enable */
	NVIC_EnableIRQ(SIM800_IRQn);
}

void InitSIM800_GPIO (void){
//PB14 SIM800 power suply (SIM900_PWR_ON), 0 is ON
GPIOB->CRH &= ~GPIO_CRH_CNF14; 				/* CNF14[1:0] 00 (General purpose output push-pull) */
GPIOB->CRH &= ~GPIO_CRH_MODE14_0;			/* MODE14[1:0] 10 (Output mode, max speed 2 MHz) */
GPIOB->CRH |= GPIO_CRH_MODE14_1;   		/* MODE14[1:0] 10 (Output mode, max speed 2 MHz) */  

//PA8 SIM800 power suply (SIM900_PWR_ON), 0 is ON
GPIOA->CRH &= ~GPIO_CRH_CNF8; 				/* CNF8[1:0] 00 (General purpose output push-pull) */
GPIOA->CRH &= ~GPIO_CRH_MODE8_0;   		/* MODE8[1:0] 10 (Output mode, max speed 2 MHz) */
GPIOA->CRH |= GPIO_CRH_MODE8_1;   		/* MODE8[1:0] 10 (Output mode, max speed 2 MHz) */		
}
void PowerOnSIM800 (void){
	PKEY_SIM800_OFF();
  POWER_SIM800_ON();
	vTaskDelay(1000);
  PKEY_SIM800_ON();
	vTaskDelay(5000);	
}

void SendSIM800_USART(char chr){
	while (!(SIM800_USART->SR & USART_SR_TC)); 	/* Transmission is complete */
	SIM800_USART->DR = chr;											/* Transmit data */
}

void SendStringSIM800_USART(char* str){
	uint8_t i =0;
	while(str[i]){
			while (!(SIM800_USART->SR & USART_SR_TC)); 	/* Transmission is complete */
			SIM800_USART->DR = str[i++];								/* Transmit data */
	}
}
