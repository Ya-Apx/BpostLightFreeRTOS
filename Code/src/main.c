#include "main.h"

uint8_t linesCounter=0;

int main (void){
	InitRCC_HSI_PLL();
	InitGPIO();
	InitUSART2();
	InputKeyInit();
	OutputKeyInit();

	xTaskCreate(vTaskReadKey, "readKey", 128, NULL, 1, NULL);
	xTaskCreate(vTaskClickKey, "clickKey", 128, NULL, 1, NULL);
	xTaskCreate(vTaskBlink, "justBlink", 128, NULL, 1, NULL);
	
	xQueueSendKey = xQueueCreate(3, sizeof(uint8_t));
	
	vTaskStartScheduler();
	
	while(1){
	}
}
/*********************************************IRQ**********************************************/
void USART1_IRQHandler (void){
	if (USART1->SR & USART_SR_RXNE){ 					/* Read Data Register Not Empty */
	}
	if (USART1->SR & USART_SR_IDLE){ 					/* IDLE line detected */
		ClearFlagIDLE(USART1);									/* RXNE flag cleared */
	}
}
void USART2_IRQHandler (void){
	if (USART2->SR & USART_SR_RXNE){ 					/* Read Data Register Not Empty */
	}
	if (USART2->SR & USART_SR_IDLE){ 					/* IDLE line detected */
		ClearFlagIDLE(USART2);									/* RXNE flag cleared */
	}
}
/*****************************************tasks************************************************/

void vTaskReadKey (void *argumen){
	for(;;){
		ChangeLines();
		vTaskDelay(5);
	}
}

void vTaskClickKey (void *argumen){
	uint8_t key=0;
	for(;;){
		if(uxQueueMessagesWaiting(xQueueSendKey)){ //number of messages stored in a queue !=0
			xQueueReceive(xQueueSendKey, &key, 0);
			switch(key){
				/****line 0****/
/*
				case 0x31:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY0_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY0_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY0_SET();
						while(!(OUTPUTKEY0_READ())){
							__nop();
						}
					}
					break;
				}
*/
				case 0x32:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY0_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY1_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY1_SET();
						while(!(OUTPUTKEY0_READ())){
							__nop();
						}
					}
					break;
				}
				case 0x33:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY0_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY2_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY2_SET();
						while(!(OUTPUTKEY0_READ())){
							__nop();
						}
					}
					break;
				}
				case 0x41:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY0_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY3_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY3_SET();
						while(!(OUTPUTKEY0_READ())){
							__nop();
						}
					}					break;
				}
				/****line 1****/
/*
				case 0x34:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY1_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY0_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY0_SET();
						while(!(OUTPUTKEY1_READ())){
							__nop();
						}
					}
					break;
				}
*/
				case 0x35:{
					for (uint8_t i=0; i<=8; i++){
						while(OUTPUTKEY1_READ()){

						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY1_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY1_SET();
						while(!(OUTPUTKEY1_READ())){
						}
					}
					break;
				}
				case 0x36:{
					for (uint8_t i=0; i<=7; i++){
						while(OUTPUTKEY1_READ()){
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY2_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY2_SET();
						while(!(OUTPUTKEY1_READ())){
						}
					}
					break;
				}
				case 0x42:{
					for (uint8_t i=0; i<=6; i++){
						while(OUTPUTKEY1_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY3_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY3_SET();
						while(!(OUTPUTKEY1_READ())){
							__nop();
						}
					}
					break;
				}
				/****line 2****/
/*
				case 0x37:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY2_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY0_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY0_SET();
						while(!(OUTPUTKEY2_READ())){
							__nop();
						}
					}
					break;
				}
*/
				case 0x38:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY2_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY1_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY1_SET();
						while(!(OUTPUTKEY2_READ())){
							__nop();
						}
					}
					break;
				}
				case 0x39:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY2_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY2_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY2_SET();
						while(!(OUTPUTKEY2_READ())){
							__nop();
						}
					}
					break;
				}
				case 0x43:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY2_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY3_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY3_SET();
						while(!(OUTPUTKEY2_READ())){
							__nop();
						}
					}
					break;
				}
				/****line 3****/
/*
				case 0x2a:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY3_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY0_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY0_SET();
						while(!(OUTPUTKEY3_READ())){
							__nop();
						}
					}
					break;
				}
*/
				case 0x30:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY3_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY1_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY1_SET();
						while(!(OUTPUTKEY3_READ())){
							__nop();
						}
					}					break;
				}
				case 0x23:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY3_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY2_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY2_SET();
						while(!(OUTPUTKEY3_READ())){
							__nop();
						}
					}					
					break;
				}
				case 0x44:{
					for (uint8_t i=0; i<=5; i++){
						while(OUTPUTKEY3_READ()){
							__nop();
						}
						TickType_t xLastWakeTime=xTaskGetTickCount();
						OUTPUTKEY3_RESET(); 
						vTaskDelayUntil(&xLastWakeTime,PRESSDELAY);
						OUTPUTKEY3_SET();
						while(!(OUTPUTKEY3_READ())){
							__nop();
						}
					}					
					break;
				}
				default:{
					break;
				}
			}
			SendUSART(USART2,key);
		}
	}
}

void vTaskBlink (void *argumen){
	for(;;){
		GPIOA->BSRR |= GPIO_BSRR_BS11;		/* PC13 LED1 (GREEN) set=OFF */
		vTaskDelay(500);
		GPIOA->BSRR |= GPIO_BSRR_BR11;		/* PC13 LED1 (GREEN) reset=ON */
		vTaskDelay(500);
		//vTaskDelay(200);
	}
}
/******************************************FUNCTIONS*******************************************/
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
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x31;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"1"***************************/
				SendUSART(USART2, 0x31);
				/***********************************************************/
				#endif
			}	
			//2
			else if (!(COLUMN1_READ())){
				while(!(COLUMN1_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x32;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"2"***************************/
				SendUSART(USART2, 0x32);
				/***********************************************************/
				#endif
			}
			//3
			else if (!(COLUMN2_READ())){
				while(!(COLUMN2_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x33;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"3"***************************/
				SendUSART(USART2, 0x33);
				/***********************************************************/
				#endif				
			}
			//A
			else if (!(COLUMN3_READ())){
				while(!(COLUMN3_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x41;
				xQueueSend(xQueueSendKey, &key,0);
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
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x34;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"4"***************************/
				SendUSART(USART2, 0x34);
				/***********************************************************/
				#endif
			}	
			//5
			else if (!(COLUMN1_READ())){
				while(!(COLUMN1_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x35;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"5"***************************/
				SendUSART(USART2, 0x35);
				/***********************************************************/
				#endif
			}
			//6
			else if (!(COLUMN2_READ())){
				while(!(COLUMN2_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x36;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"6"***************************/
				SendUSART(USART2, 0x36);
				/***********************************************************/
				#endif
			}
			//B
			else if (!(COLUMN3_READ())){
				while(!(COLUMN3_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x42;
				xQueueSend(xQueueSendKey, &key,0);
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
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x37;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"7"***************************/
				SendUSART(USART2, 0x37);
				/***********************************************************/
				#endif
			}	
			//8
			else if (!(COLUMN1_READ())){
				while(!(COLUMN1_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x38;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"8"***************************/
				SendUSART(USART2, 0x38);
				/***********************************************************/
				#endif
			}
			//9
			else if (!(COLUMN2_READ())){
				while(!(COLUMN2_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x39;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"9"***************************/
				SendUSART(USART2, 0x39);
				/***********************************************************/
				#endif
			}
			//C
			else if (!(COLUMN3_READ())){
				while(!(COLUMN3_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x43;
				xQueueSend(xQueueSendKey, &key,0);
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
				while(!(COLUMN0_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x2a;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"*"***************************/
				SendUSART(USART2, 0x2a);
				/***********************************************************/
				#endif
			}	
			//0
			else if (!(COLUMN1_READ())){
				while(!(COLUMN1_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x30;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"0"***************************/
				SendUSART(USART2, 0x30);
				/***********************************************************/
				#endif
			}
			//#
			else if (!(COLUMN2_READ())){
				while(!(COLUMN2_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x23;
				xQueueSend(xQueueSendKey, &key,0);
				#ifdef debug_keyRead
				/**************************key"#"***************************/
				SendUSART(USART2, 0x23);
				/***********************************************************/
				#endif
			}
			//D
			else if (!(COLUMN3_READ())){
				while(!(COLUMN3_READ())){
					vTaskDelay(DEBOUNCEDELAY);
				}
				const uint8_t key=0x44;
				xQueueSend(xQueueSendKey, &key,0);
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
/**********************************************************************************************/

