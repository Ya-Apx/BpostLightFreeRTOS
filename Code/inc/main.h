/*******************************************Library********************************************/
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "sysinit.h"
#include "usart.h"

/*******************************************Defines********************************************/
#define debug_keyRead

#define PRESSDELAY 1
#define KEYREADDELAY 1
#define DEBOUNCEDELAY 50


/********************************************Macros********************************************/
#define TOGGLE_LED() GPIOC->ODR ^= GPIO_ODR_ODR13

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

/****************************************Used function*****************************************/
void ChangeLines (void);
void ReadKey (uint8_t column);

/*************************************Used queue FreeRTOS**************************************/
xQueueHandle xQueueSendKey;
/*************************************Used tasks FreeRTOS**************************************/
void vTaskReadKey (void *argument);
void vTaskClickKey (void *argumen);

void vTaskBlink (void *argument);
