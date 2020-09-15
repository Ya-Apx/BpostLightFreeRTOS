/*******************************************Library********************************************/
#include "stm32f10x.h"
/****************************************Used function*****************************************/

void InitRCC(void); //HSE/1 = 8MHz; PLLx9=72MHz; SYSCLK/1 = 72MHz; APB1 = HCLK/2 = 36MHz; APB2 = HCLK/1 = 72MHz;
void InitRCC_HSI_PLL(void); //HSI/2 = 4MHz; PLLx12=48MHz; SYSCLK/1 = 48MHz; APB1 = HCLK/2 = 24MHz; APB2 = HCLK/1 = 48MHz;

void InitGPIO(void); //PA1->output push-pull, 2MHz; PC13->output push-pull, 2MHz;

void InputKeyInit(void);
void OutputKeyInit(void);
