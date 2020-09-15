/*******************************************Library********************************************/
#include "usart.h"

/****************************************Used function*****************************************/
void InitUSART1 (void){
/**************************************USART1 clock init***************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 	/* I/O port A clock enable */
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; /* USART1 clock enable */
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;		/* Alternate Function I/O clock enable */
	
/*************************************USART1 TX pin init***************************************/
	GPIOA->CRH &=	~GPIO_CRH_CNF9_0;				/* CNF9[1:0] 10 (Alternate function output Push-pull) */
	GPIOA->CRH |=	GPIO_CRH_CNF9_1;				/* CNF9[1:0] 10 (Alternate function output Push-pull) */
	GPIOA->CRH |= GPIO_CRH_MODE9;   			/* MODE9[1:0] 11 (Output mode, max speed 50 MHz) */  
	
/*************************************USART1 RX pin init***************************************/
	GPIOA->CRH |=	GPIO_CRH_CNF10_0;				/* CNF10[1:0] 01 (Floating input) */
	GPIOA->CRH &=	~GPIO_CRH_CNF10_1;			/* CNF10[1:0] 01 (Floating input) */
	GPIOA->CRH &= ~GPIO_CRH_MODE10;   		/* MODE10[1:0] 00 (Input mode) */  

/***********************************USART1 baud rate congig*************************************/
/*|  MHz  | 9600 | 19200 | 38400 | 115200 |*****************************************************/	
/*|---------------------------------------|*****************************************************/
/*|  24   | 2500 | 1250  |  625  |   208  |****(48 000 000 + 115 200/2)/115 200 = 417***********/
/*|  36   | 3750 | 1875  |  938  |   313  |*****************************************************/
/*|  48   | 5000 | 2500  |  1250 |   417  |*****************************************************/
/*|  72   | 7500 | 3750  |  1875 |   625  |*****************************************************/	
	USART1->BRR=0xD0; 									/* Baud rate 115200 (24MHz -> 208 in HEX 0xD0)*/ 
	
/**********************************USART1 enable bits congig************************************/	
	USART1->CR1 |= USART_CR1_TE;					/* Transmitter Enable */
	USART1->CR1 |= USART_CR1_RE;					/* Receiver Enable */
	USART1->CR1 |= USART_CR1_UE;					/* USART Enable */

/*********************************USART1 RXNE interrupt enable***********************************/	
	USART1->CR1 |=USART_CR1_IDLEIE;   		/*IDLE Interrupt Enable */
	USART1->CR1 |=USART_CR1_RXNEIE;				/*RXNE Interrupt Enable */
	NVIC_EnableIRQ(USART1_IRQn);          /*Enable Interrupt in NVIC Interrupt Controller*/
}

void InitUSART2 (void){
/**************************************USART2 clock init***************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 	/* I/O port A clock enable */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; /* USART2 clock enable */
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;		/* Alternate Function I/O clock enable */
	
/*************************************USART2 TX pin init***************************************/
	GPIOA->CRL &=	~GPIO_CRL_CNF2_0;				/* CNF2[1:0] 10 (Alternate function output Push-pull) */
	GPIOA->CRL |=	GPIO_CRL_CNF2_1;				/* CNF2[1:0] 10 (Alternate function output Push-pull) */
	GPIOA->CRL |= GPIO_CRL_MODE2;   			/* MODE2[1:0] 11 (Output mode, max speed 50 MHz) */  
	
/*************************************USART2 RX pin init***************************************/
	GPIOA->CRL |=	GPIO_CRL_CNF3_0;				/* CNF3[1:0] 01 (Floating input) */
	GPIOA->CRL &=	~GPIO_CRL_CNF3_1;				/* CNF3[1:0] 01 (Floating input) */
	GPIOA->CRL &= ~GPIO_CRL_MODE3;   			/* MODE3[1:0] 00 (Input mode) */  

/***********************************USART2 baud rate congig*************************************/		
/*|  MHz  | 9600 | 19200 | 38400 | 115200 |*****************************************************/	
/*|---------------------------------------|*****************************************************/
/*|  24   | 2500 | 1250  |  625  |   208  |****(24 000 000 + 115 200/2)/115 200 = 208,83********/
/*|  36   | 3750 | 1875  |  938  |   313  |*****************************************************/
/*|  48   | 5000 | 2500  |  1250 |   417  |*****************************************************/
/*|  72   | 7500 | 3750  |  1875 |   625  |*****************************************************/	
	USART2->BRR=0xD0; 										/* Baud rate 115200 (24MHz -> 208 in HEX 0xD0 )*/ 
	
/**********************************USART2 enable bits congig************************************/	
	USART2->CR1 |= USART_CR1_TE;					/* Transmitter Enable */
	USART2->CR1 |= USART_CR1_RE;					/* Receiver Enable */
	USART2->CR1 |= USART_CR1_UE;					/* USART Enable */

/*********************************USART2 RXNE interrupt enable***********************************/	
	USART2->CR1 |=USART_CR1_IDLEIE;   		/*IDLE Interrupt Enable */
	USART2->CR1 |=USART_CR1_RXNEIE;				/*RXNE Interrupt Enable */
	NVIC_EnableIRQ(USART2_IRQn);          /*Enable Interrupt in NVIC Interrupt Controller*/
}


void SendUSART(USART_TypeDef *USARTx, char chr){
	while (!(USARTx->SR & USART_SR_TC)); 	/* Transmission is complete */
	USARTx->DR = chr;											/* Transmit data */
}

void SendStringUSART(USART_TypeDef *USARTx, char* str){
	uint8_t i =0;
	while(str[i]){
			while (!(USARTx->SR & USART_SR_TC)); 	/* Transmission is complete */
			USARTx->DR = str[i++];								/* Transmit data */
	}
}

void ClearFlagIDLE(USART_TypeDef *USARTx){
  __IO uint32_t tmpreg;
  tmpreg = USARTx->SR;
  (void) tmpreg;
  tmpreg = USARTx->DR;
  (void) tmpreg;
}

void ClearBuffer(char* buff, uint8_t buffLen){	
	for (uint8_t a=0;a<=buffLen-1;a++)
	{
		buff[a]=0;
	}
}

