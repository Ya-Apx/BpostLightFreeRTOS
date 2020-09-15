#include "key.h"  


#ifdef debug_keyRead
#include "usart.h" 
#endif

uint8_t linesCounter=0;
extern uint8_t currButt;
extern xQueueHandle xQueueSendKey;

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
      ReadKey(linesCounter);
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
			if (!(COLUMN0_READ())){
				while(!(COLUMN0_READ())){
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
				while(!(COLUMN1_READ())){
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
				while(!(COLUMN2_READ())){
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
				while(!(COLUMN3_READ())){
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
				while(!(COLUMN0_READ())){
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
				while(!(COLUMN1_READ())){
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
				while(!(COLUMN2_READ())){
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
				while(!(COLUMN3_READ())){
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
				while(!(COLUMN0_READ())){
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
				while(!(COLUMN1_READ())){
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
				while(!(COLUMN2_READ())){
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
				while(!(COLUMN3_READ())){
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
		case 3:{
			//*
			if (!(COLUMN0_READ())){
				currButt=0x2a;
				while(!(COLUMN0_READ())){
					vTaskDelay(50);
				}
				#ifdef debug_keyRead
				/**************************key"*"***************************/
				SendUSART(USART2, 0x2a);
				/***********************************************************/
				#endif
			}	
			//0
			else if (!(COLUMN1_READ())){
				while(!(COLUMN1_READ())){
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
				while(!(COLUMN2_READ())){
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
				while(!(COLUMN3_READ())){
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
	GPIOB->CRL &= ~GPIO_CRL_CNF0_0; 		/* CNF0[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRL |= GPIO_CRL_CNF0_1;			/* CNF0[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRL &= ~GPIO_CRL_MODE0;			/* MODE0[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR0; 				/* ODR0 1 (General purpose Input pull-up) */
	
	GPIOB->CRL &= ~GPIO_CRL_CNF1_0; 		/* CNF1[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRL |= GPIO_CRL_CNF1_1;			/* CNF1[1:0] 10 (General purpose Input pull-up/pull-downn) */
	GPIOB->CRL &= ~GPIO_CRL_MODE1;			/* MODE1[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR1; 				/* ODR1 1 (General purpose Input pull-up) */
	
	GPIOB->CRL &= ~GPIO_CRL_CNF2_0; 		/* CNF2[1:0] 10 (General purpose pull-up/pull-down) */
	GPIOB->CRL |= GPIO_CRL_CNF2_1;			/* CNF2[1:0] 10 (General purpose pull-up/pull-down) */
	GPIOB->CRL &= ~GPIO_CRL_MODE2;			/* MODE2[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR2; 				/* ODR2 1 (General purpose Input pull-up) */
	
	GPIOB->CRL &= ~GPIO_CRL_CNF3_0; 		/* CNF3[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRL |= GPIO_CRL_CNF3_1;			/* CNF3[1:0] 10 (General purpose Input pull-up/pull-down) */
	GPIOB->CRL &= ~GPIO_CRL_MODE3;			/* MODE3[1:0] 00 */
	GPIOB->ODR |= GPIO_ODR_ODR3; 				/* ODR3 1 (General purpose Input pull-up) */
	
	/***************************************WRITE pins init****************************************/	
	GPIOB->CRL &= ~GPIO_CRL_CNF4; 			/* CNF4[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRL &= ~GPIO_CRL_MODE4_0;		/* MODE4[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRL |= GPIO_CRL_MODE4_1;   	/* MODE4[1:0] 10 (Output mode, max speed 2 MHz) */  

	GPIOB->CRL &= ~GPIO_CRL_CNF5; 			/* CNF5[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRL &= ~GPIO_CRL_MODE5_0;		/* MODE5[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRL |= GPIO_CRL_MODE5_1;   	/* MODE5[1:0] 10 (Output mode, max speed 2 MHz) */  

	GPIOB->CRL &= ~GPIO_CRL_CNF6; 			/* CNF6[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRL &= ~GPIO_CRL_MODE6_0;		/* MODE6[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRL |= GPIO_CRL_MODE6_1;   	/* MODE6[1:0] 10 (Output mode, max speed 2 MHz) */  

	GPIOB->CRL &= ~GPIO_CRL_CNF7; 			/* CNF7[1:0] 00 (General purpose output push-pull) */
	GPIOB->CRL &= ~GPIO_CRL_MODE7_0;		/* MODE7[1:0] 10 (Output mode, max speed 2 MHz) */
	GPIOB->CRL |= GPIO_CRL_MODE7_1;   	/* MODE7[1:0] 10 (Output mode, max speed 2 MHz) */ 
	
}


