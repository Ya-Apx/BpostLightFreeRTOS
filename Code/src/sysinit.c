/*******************************************Library********************************************/
#include "sysinit.h"

/****************************************Used function*****************************************/
void InitRCC(void){
	RCC->CR |= RCC_CR_HSEON; 						/* External high-speed clock enable */
	while (!(RCC->CR & RCC_CR_HSERDY));		/* Chek external High Speed clock ready flag */
	
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; /* Prefetch Buffer Enable | LATENCY[2:0] bits (Latency) */ // Clock Flash memory
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; 		/* AHB = SYSCLK/1 = 72MHz */
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; 	/* APB1 = HCLK/2 = 36MHz */
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; 	/* APB2 = HCLK/1 = 72MHz*/
	
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;			/* Clear PLLSRC bits */
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;		/* Clear PLLXTPRE bits */
	RCC->CFGR &= ~RCC_CFGR_PLLMULL;			/* Clear PLLMULL bits */
	
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; 	/* HSE clock selected as PLL entry clock source */
	RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; /* HSE clock not divided for PLL entry (HSE/1=8MHz) */
	RCC->CFGR |= RCC_CFGR_PLLMULL9;     /* PLL input clock*9 (8MHz*9=72MHz=SYSCLK)*/
	
	RCC->CR |= RCC_CR_PLLON;						/* enable PLL */
	while ((RCC->CR & RCC_CR_PLLRDY)==0);		/* Chek PLL clock ready flag */
	
	RCC->CFGR &= ~RCC_CFGR_SW; 					/* Clear System clock Switch bits */
	
	RCC->CFGR |= RCC_CFGR_SW_PLL; 			/* PLL selected as system clock*/
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1); /* wait till PLL is used */
}

void InitRCC_HSI_PLL(void){
	RCC->CR |= RCC_CR_HSION; 						/* Internal high-speed clock enable */
	while (!(RCC->CR & RCC_CR_HSIRDY));		/* Chek external High Speed clock ready flag */
	
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; /* Prefetch Buffer Enable | LATENCY[2:0] bits (Latency) */ // Clock Flash memory
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; 		/* AHB = SYSCLK/1 = 48MHz */
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; 	/* APB1 = HCLK/2 = 24MHz */
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; 	/* APB2 = HCLK/1 = 48MHz*/
	
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;			/* Clear PLLSRC bits */
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;		/* Clear PLLXTPRE bits */
	RCC->CFGR &= ~RCC_CFGR_PLLMULL;			/* Clear PLLMULL bits */
	
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_Div2; 	/* HSI clock selected as PLL entry clock source */
	RCC->CFGR |= RCC_CFGR_PLLMULL12;    /* PLL input clock*12 (4MHz*12=48MHz=SYSCLK)*/
	
	
	RCC->CR |= RCC_CR_PLLON;						/* enable PLL */
	while ((RCC->CR & RCC_CR_PLLRDY)==0);		/* Chek PLL clock ready flag */
	
	RCC->CFGR &= ~RCC_CFGR_SW; 					/* Clear System clock Switch bits */
	
	RCC->CFGR |= RCC_CFGR_SW_PLL; 			/* PLL selected as system clock*/
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1); /* wait till PLL is used */
}


void InitGPIO(void){		
/*********************************Serial wier clock  init*************************************/
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;		/* Alternate Function I/O clock enable */
	AFIO->MAPR &= ~ AFIO_MAPR_SWJ_CFG;		/* Clear Serial Wire JTAG configuration bits */
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;		/* JTAG-DP Disabled and SW-DP Enabled */ //remsp pb3,4
	
				
/**************************************GPIO clock init****************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		/* I/O port A clock enable */
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 	/* I/O port B clock enable */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 	/* I/O port C clock enable */
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; 	/* I/O port D clock enable */
	
/*************************************GPIO LED pin init***************************************/	
	GPIOA->CRH &= ~GPIO_CRH_CNF11; 			/* CNF8[1:0] 00 (General purpose output push-pull) */
	GPIOA->CRH &= ~GPIO_CRH_MODE11_0;		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOA->CRH |= GPIO_CRH_MODE11_1;   		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */  
	
}

void InputKeyInit(void){
	/**************************************GPIO clock init****************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 	/* I/O port B clock enable */

	/***************************************LINE pins init****************************************/	
	GPIOB->CRH &= ~GPIO_CRH_CNF8; 			/* CNF8[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRH &= ~GPIO_CRH_MODE8_0;		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRH |= GPIO_CRH_MODE8_1;   		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */  

	GPIOB->CRH &= ~GPIO_CRH_CNF9; 			/* CNF9[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRH &= ~GPIO_CRH_MODE9_0;		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRH |= GPIO_CRH_MODE9_1;   		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */  

	GPIOB->CRH &= ~GPIO_CRH_CNF10; 			/* CNF10[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRH &= ~GPIO_CRH_MODE10_0;		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRH |= GPIO_CRH_MODE10_1;   		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */  

	GPIOB->CRH &= ~GPIO_CRH_CNF11; 			/* CNF11[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRH &= ~GPIO_CRH_MODE11_0;		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRH |= GPIO_CRH_MODE11_1;   		/* MODE1[1:0] 10 (Output mode, max speed 2 MHz) */ 

	/*************************************COLUMN pins init****************************************/	
	GPIOB->CRH &= ~GPIO_CRH_CNF12_0; 		/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH |= GPIO_CRH_CNF12_1;			/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH &= ~GPIO_CRH_MODE12;			/* MODE1[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR12; 			/* ODR12 1 (General purpose Input pull-up) */
	
	GPIOB->CRH &= ~GPIO_CRH_CNF13_0; 		/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH |= GPIO_CRH_CNF13_1;			/* CNF8[1:0] 10 (General purpose Input pull-up/pull-downn) */
	GPIOB->CRH &= ~GPIO_CRH_MODE13;			/* MODE1[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR13; 			/* ODR13 1 (General purpose Input pull-up) */
	
	GPIOB->CRH &= ~GPIO_CRH_CNF14_0; 		/* CNF8[1:0] 10 (General purpose pull-up/pull-down) */
	GPIOB->CRH |= GPIO_CRH_CNF14_1;			/* CNF8[1:0] 10 (General purpose pull-up/pull-down) */
	GPIOB->CRH &= ~GPIO_CRH_MODE14;			/* MODE1[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR14; 			/* ODR14 1 (General purpose Input pull-up) */
	
	GPIOB->CRH &= ~GPIO_CRH_CNF15_0; 		/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH |= GPIO_CRH_CNF15_1;			/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH &= ~GPIO_CRH_MODE15;			/* MODE1[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR15; 			/* ODR15 1 (General purpose Input pull-up) */
	
}

void OutputKeyInit(void){
	/**************************************GPIO clock init****************************************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 	/* I/O port B clock enable */
	
	/*************************************READ pins init****************************************/
	GPIOB->CRL &= ~(GPIO_CRL_MODE0|GPIO_CRL_CNF0);			/* MODE4[1:0] 00; CNF4[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_CNF0_1;			/* CNF0[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->ODR |= GPIO_ODR_ODR0; 				/* ODR0 1 (General purpose Input pull-up) */
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE1|GPIO_CRL_CNF1);			/* MODE5[1:0] 00; CNF5[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_CNF1_1;			/* CNF1[1:0] 10 (General purpose Input pull-up/pull-downn) */
	GPIOB->ODR |= GPIO_ODR_ODR1; 				/* ODR1 1 (General purpose Input pull-up) */
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE2|GPIO_CRL_CNF2);			/* MODE6[1:0] 00; CNF6[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_CNF2_1;			/* CNF2[1:0] 10 (General purpose pull-up/pull-down) */
	GPIOB->ODR |= GPIO_ODR_ODR2; 				/* ODR2 1 (General purpose Input pull-up) */
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE3|GPIO_CRL_CNF3);			/* MODE7[1:0] 00; CNF7[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_CNF3_1;			/* CNF3[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->ODR |= GPIO_ODR_ODR3; 				/* ODR3 1 (General purpose Input pull-up) */
	
	/***************************************WRITE pins init****************************************/	
	GPIOB->CRL &= ~(GPIO_CRL_MODE4|GPIO_CRL_CNF4);			/* MODE0[1:0] 00; CNF0[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_MODE4_1;   	/* MODE5[1:0] 10 (Output mode, max speed 2 MHz) */  
	GPIOB->BSRR &= ~GPIO_BSRR_BS4;

	GPIOB->CRL &= ~(GPIO_CRL_MODE5|GPIO_CRL_CNF5);			/* MODE0[1:0] 00; CNF0[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_MODE5_1;   	/* MODE5[1:0] 10 (Output mode, max speed 2 MHz) */  
	GPIOB->BSRR |= GPIO_BSRR_BS5;
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE6|GPIO_CRL_CNF6);			/* MODE0[1:0] 00; CNF0[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_MODE6_1;   	/* MODE6[1:0] 10 (Output mode, max speed 2 MHz) */  
	GPIOB->BSRR |= GPIO_BSRR_BS6;
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE7|GPIO_CRL_CNF7);			/* MODE0[1:0] 00; CNF0[1:0] 10 */
	GPIOB->CRL |= GPIO_CRL_MODE7_1;   	/* MODE7[1:0] 10 (Output mode, max speed 2 MHz) */ 
	GPIOB->BSRR |= GPIO_BSRR_BS7;
}
