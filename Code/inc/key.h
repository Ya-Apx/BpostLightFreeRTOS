/*******************************************Library********************************************/
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/*******************************************Defines********************************************/
#define PRESSDELAY 10
/********************************************Macros********************************************/
/******************************************Input Key*******************************************/
#define LINE0_SET()         GPIOB->BSRR |= GPIO_BSRR_BS8
#define LINE0_RESET()       GPIOB->BSRR |= GPIO_BSRR_BR8
#define LINE1_SET()         GPIOB->BSRR |= GPIO_BSRR_BS9
#define LINE1_RESET()       GPIOB->BSRR |= GPIO_BSRR_BR9
#define LINE2_SET()         GPIOB->BSRR |= GPIO_BSRR_BS10
#define LINE2_RESET()       GPIOB->BSRR |= GPIO_BSRR_BR10
#define LINE3_SET()         GPIOB->BSRR |= GPIO_BSRR_BS11
#define LINE3_RESET()       GPIOB->BSRR |= GPIO_BSRR_BR11

#define COLUMN0_READ() 			GPIOB->IDR & GPIO_IDR_IDR12
#define COLUMN1_READ()			GPIOB->IDR & GPIO_IDR_IDR13
#define COLUMN2_READ()			GPIOB->IDR & GPIO_IDR_IDR14
#define COLUMN3_READ() 			GPIOB->IDR & GPIO_IDR_IDR15

/******************************************Output Key******************************************/
#define OUTPUTKEY0_SET()        GPIOB->BSRR |= GPIO_BSRR_BS4
#define OUTPUTKEY0_RESET()      GPIOB->BSRR |= GPIO_BSRR_BR4
#define OUTPUTKEY1_SET()        GPIOB->BSRR |= GPIO_BSRR_BS5
#define OUTPUTKEY1_RESET()      GPIOB->BSRR |= GPIO_BSRR_BR5
#define OUTPUTKEY2_SET()        GPIOB->BSRR |= GPIO_BSRR_BS6
#define OUTPUTKEY2_RESET()      GPIOB->BSRR |= GPIO_BSRR_BR6
#define OUTPUTKEY3_SET()        GPIOB->BSRR |= GPIO_BSRR_BS7
#define OUTPUTKEY3_RESET()      GPIOB->BSRR |= GPIO_BSRR_BR7

#define OUTPUTKEY0_READ() 			GPIOB->IDR & GPIO_IDR_IDR0
#define OUTPUTKEY1_READ()				GPIOB->IDR & GPIO_IDR_IDR1
#define OUTPUTKEY2_READ()				GPIOB->IDR & GPIO_IDR_IDR2
#define OUTPUTKEY3_READ() 			GPIOB->IDR & GPIO_IDR_IDR3

/***************************************Used Variables*****************************************/
// currButt {nop=0x00, one=0x31, two, three, four, five, six, seven, eight};



/****************************************Used function*****************************************/
void InputKeyInit(void);
void OutputKeyInit(void);
	
void ChangeLines (void);
void ReadKey (uint8_t column);
