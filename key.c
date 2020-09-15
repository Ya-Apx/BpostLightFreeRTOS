#include "key.h"  
#include "usart.h" 

#define debug_keyRead

uint8_t linesCounter=0;
extern uint8_t currButt;

void ChangeLines (void){
	linesCounter=(linesCounter+1)%4;
	switch (linesCounter){
    case 0:{ 
			LINE0_RESET();
      LINE1_SET();
			LINE2_SET();
			LINE3_SET(); 
      ReadKey(linesCounter);
			break;
		}
    case 1:{ 
			LINE0_SET();
      LINE1_RESET();
			LINE2_SET();
			LINE3_SET(); 
      ReadKey(linesCounter);
			break;
    }     
    case 2:{ 
			LINE0_SET();
      LINE1_SET();
			LINE2_RESET();
			LINE3_SET(); 
      //ReadKey(linesCounter);
			break;
    }
    case 3:{ 
			LINE0_SET();
      LINE1_SET();
			LINE2_SET();
			LINE3_RESET(); 
      ReadKey(linesCounter);
			break;
    }
    default:{
      break;
    }
  }
}

void ReadKey (uint8_t line){
	switch (line){
		case 0:{
			//1
			if (!COLUMN0_READ()){
				while(!(COLUMN0_READ())) {
					vTaskDelay(50);
				}
				currButt=0x31;
				#ifdef debug_keyRead
				/**************************key"1"***************************/
				SendUSART(USART2, 0x31);
				/***********************************************************/
				#endif
			}	
			//2
			else if (!(COLUMN1_READ())){
					while(!(COLUMN1_READ())) {
					vTaskDelay(50);
				}
				currButt=0x32;
				#ifdef debug_keyRead
				/**************************key"2"***************************/
				SendUSART(USART2, 0x32);
				/***********************************************************/
				#endif
			}
			//3
			else if (!(COLUMN2_READ())){
					while(!(COLUMN2_READ())) {
					vTaskDelay(50);
				}
				currButt=0x33;
				#ifdef debug_keyRead
				/**************************key"3"***************************/
				SendUSART(USART2, 0x33);
				/***********************************************************/
				#endif				
			}
			//A
			else if (!(COLUMN3_READ())){
					while(!(COLUMN3_READ())) {
					vTaskDelay(50);
				}
				currButt=0x41;
				#ifdef debug_keyRead
				/**************************key"A"***************************/
				SendUSART(USART2, 0x41);
				/***********************************************************/
				#endif
			}
			break;
		}	

		case 1:{
			//4
			if (!(COLUMN0_READ())){	
					while(!(COLUMN0_READ())) {
						vTaskDelay(50);
					}
				currButt=0x34;
				#ifdef debug_keyRead
				/**************************key"4"***************************/
				SendUSART(USART2, 0x34);
				/***********************************************************/
				#endif
			}	
			//5
			else if (!(COLUMN1_READ())){
					while(!(COLUMN1_READ())) {
						vTaskDelay(50);
					}
				currButt=0x35;
				#ifdef debug_keyRead
				/**************************key"5"***************************/
				SendUSART(USART2, 0x35);
				/***********************************************************/
				#endif
			}
			//6
			else if (!(COLUMN2_READ())){
					while(!(COLUMN2_READ())) {
						vTaskDelay(50);
					}
				currButt=0x36;
				#ifdef debug_keyRead
				/**************************key"6"***************************/
				SendUSART(USART2, 0x36);
				/***********************************************************/
				#endif
			}
			//B
			else if (!(COLUMN3_READ())){
					while(!(COLUMN3_READ())) {
						vTaskDelay(50);
					}
				currButt=0x42;
				#ifdef debug_keyRead
				/**************************key"B"***************************/
				SendUSART(USART2, 0x42);
				/***********************************************************/
				#endif
			}
			break;
		}	
		case 2:{
			//7
			if (!(COLUMN0_READ())){
					while(!(COLUMN0_READ())) {
						vTaskDelay(50);
					}
				currButt=0x37;
				#ifdef debug_keyRead
				/**************************key"7"***************************/
				SendUSART(USART2, 0x37);
				/***********************************************************/
				#endif
			}	
			//8
			else if (!(COLUMN1_READ())){
					while(!(COLUMN1_READ())) {
						vTaskDelay(50);
					}
				currButt=0x38;
				#ifdef debug_keyRead
				/**************************key"8"***************************/
				SendUSART(USART2, 0x38);
				/***********************************************************/
				#endif
			}
			//9
			else if (!(COLUMN2_READ())){
					while(!(COLUMN2_READ())) {
						vTaskDelay(50);
					}
				currButt=0x39;
				#ifdef debug_keyRead
				/**************************key"9"***************************/
				SendUSART(USART2, 0x39);
				/***********************************************************/
				#endif
			}
			//C
			else if (!(COLUMN3_READ())){
					while(!(COLUMN3_READ())) {
						vTaskDelay(50);
					}
				currButt=0x43;
				#ifdef debug_keyRead
				/**************************key"C"***************************/
				SendUSART(USART2, 0x43);
				/***********************************************************/
				#endif
			}
			break;
		}
		case 3:
		{
			//*
			if (!(COLUMN0_READ())){
					while(!(COLUMN0_READ())) {
						vTaskDelay(50);
					}				
				currButt=0x2a;
				#ifdef debug_keyRead
				/**************************key"*"***************************/
				SendUSART(USART2, 0x2a);
				/***********************************************************/
				#endif
			}	
			//0
			else if (!(COLUMN1_READ())){
					while(!(COLUMN1_READ())) {
						vTaskDelay(50);
					}
				currButt=0x30;
				#ifdef debug_keyRead
				/**************************key"0"***************************/
				SendUSART(USART2, 0x30);
				/***********************************************************/
				#endif
			}
			//#
			else if (!(COLUMN2_READ())){
					while(!(COLUMN2_READ())) {
						vTaskDelay(50);
					}
				currButt=0x23;
				#ifdef debug_keyRead
				/**************************key"#"***************************/
				SendUSART(USART2, 0x23);
				/***********************************************************/
				#endif
			}
			//D
			else if (!(COLUMN3_READ())){
					while(!(COLUMN3_READ())) {
						vTaskDelay(50);
					}
				currButt=0x44;
				#ifdef debug_keyRead
				/**************************key"D"***************************/
				SendUSART(USART2, 0x44);
				/***********************************************************/
				#endif
			}
			break;
		}		
		default:{
			break;
    }		
	}
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
	GPIOB->ODR &= ~GPIO_ODR_ODR14; 			/* ODR14 1 (General purpose Input pull-up) */
	
	GPIOB->CRH &= ~GPIO_CRH_CNF15_0; 		/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH |= GPIO_CRH_CNF15_1;			/* CNF8[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRH &= ~GPIO_CRH_MODE15;			/* MODE1[1:0] 00 */
	GPIOB->ODR &= ~GPIO_ODR_ODR15; 			/* ODR15 1 (General purpose Input pull-up) */
	
}

void OutputKeyInit(void){
}

