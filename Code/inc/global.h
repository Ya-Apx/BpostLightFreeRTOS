/*******************************************Library********************************************/
#include "stm32f10x.h"

/*******************************************Defines********************************************/
/****************************** hardvare define EV-STM32-SIM800********************************/
 //PA1 red LED
 #define LED_RED_ON()       GPIOA->BSRR |= GPIO_BSRR_BR1
 #define LED_RED_OFF()      GPIOA->BSRR |= GPIO_BSRR_BS1

 //PC13 green LED
 #define LED_GREEN_ON()       GPIOC->BSRR |= GPIO_BSRR_BR13
 #define LED_GREEN_OFF()      GPIOC->BSRR |= GPIO_BSRR_BS13

 //PD2 reley 1
 #define RELAY_1_ON()       GPIOD->BSRR |= GPIO_BSRR_BS2
 #define RELAY_1_OFF()      GPIOD->BSRR |= GPIO_BSRR_BR2

 //PB8 reley 2
 #define RELAY_2_ON()       GPIOB->BSRR |= GPIO_BSRR_BS8
 #define RELAY_2_OFF()      GPIOB->BSRR |= GPIO_BSRR_BR8

 //PB9 reley 3
 #define RELAY_3_ON()       GPIOB->BSRR |= GPIO_BSRR_BS9
 #define RELAY_3_OFF()      GPIOB->BSRR |= GPIO_BSRR_BR9

 //PB14 SIM800 power suply (SIM900_PWR_ON), 0 is ON
 #define POWER_SIM800_ON()       GPIOB->BSRR |= GPIO_BSRR_BR14
 #define POWER_SIM800_OFF()      GPIOB->BSRR |= GPIO_BSRR_BS14

 //PA8 SIM800 power suply (SIM900_PWR_ON), 0 is ON
 #define PKEY_SIM800_ON()       GPIOA->BSRR |= GPIO_BSRR_BR8
 #define PKEY_SIM800_OFF()      GPIOA->BSRR |= GPIO_BSRR_BS8;

//UART SIM800
 #define SIM800_USART USART3
 #define SIM800_IRQn USART3_IRQn

 #define SIM800_RX_PIN (1<<11)
 #define SIM800_RX_PORT GPIOB

 #define SIM800_TX_PIN (1<<10)
 #define SIM800_TX_PORT GPIOB


//  EEPROM
 #define EE_PORT   GPIOA
 #define EE_CS     (1<<4) // CS   - ?????????? ???????
 #define EE_SCK    (1<<5) // SCK  - ?????????? ?????????
 #define EE_MOSI   (1<<7) // MOSI - ?????????? ?????????
 #define EE_MISO   (1<<6) // MISO - ?????????? ?????????

 #define EE_UNSELECT() GPIO_WriteBit(EE_PORT, EE_CS, Bit_SET)
 #define EE_SELECT()   GPIO_WriteBit(EE_PORT, EE_CS, Bit_RESET)

// ??????????????? ????? - ???????? 0

 #define OPTO_IN_MAX 4 // ?????????? ??????

 #define OPTO_IN_1_PIN   (1<<0) 
 #define OPTO_IN_1_PORT  GPIOA 
 #define OPTO_IN_1_ACTIVE  ( GPIO_ReadInputDataBit(OPTO_IN_1_PORT, OPTO_IN_1_PIN) == Bit_RESET) 

 #define OPTO_IN_2_PIN   (1<<8) 
 #define OPTO_IN_2_PORT  GPIOC 
 #define OPTO_IN_2_ACTIVE  ( GPIO_ReadInputDataBit(OPTO_IN_2_PORT, OPTO_IN_2_PIN) == Bit_RESET) 

 #define OPTO_IN_3_PIN   (1<<9) 
 #define OPTO_IN_3_PORT  GPIOC 
 #define OPTO_IN_3_ACTIVE  ( GPIO_ReadInputDataBit(OPTO_IN_3_PORT, OPTO_IN_3_PIN) == Bit_RESET)

 #define OPTO_IN_4_PIN   (1<<10) 
 #define OPTO_IN_4_PORT  GPIOC 
 #define OPTO_IN_4_ACTIVE  ( GPIO_ReadInputDataBit(OPTO_IN_4_PORT, OPTO_IN_4_PIN) == Bit_RESET)


 // ????????????? ??????, ?????????? 1, ???????? ????? 0

 #define TRANSISTOR_1_PIN (1<<13) 
 #define TRANSISTOR_1_PORT GPIOB
 #define TRANSISTOR_1_ON()       GPIO_WriteBit(TRANSISTOR_1_PORT, TRANSISTOR_1_PIN, Bit_SET)
 #define TRANSISTOR_1_OFF()      GPIO_WriteBit(TRANSISTOR_1_PORT, TRANSISTOR_1_PIN, Bit_RESET)

 #define TRANSISTOR_2_PIN (1<<15) 
 #define TRANSISTOR_2_PORT GPIOB
 #define TRANSISTOR_2_ON()       GPIO_WriteBit(TRANSISTOR_2_PORT, TRANSISTOR_2_PIN, Bit_SET)
 #define TRANSISTOR_2_OFF()      GPIO_WriteBit(TRANSISTOR_2_PORT, TRANSISTOR_2_PIN, Bit_RESET)

 #define TRANSISTOR_3_PIN (1<<6) 
 #define TRANSISTOR_3_PORT GPIOC
 #define TRANSISTOR_3_ON()       GPIO_WriteBit(TRANSISTOR_3_PORT, TRANSISTOR_3_PIN, Bit_SET)
 #define TRANSISTOR_3_OFF()      GPIO_WriteBit(TRANSISTOR_3_PORT, TRANSISTOR_3_PIN, Bit_RESET)

 #define TRANSISTOR_4_PIN (1<<7) 
 #define TRANSISTOR_4_PORT GPIOC
 #define TRANSISTOR_4_ON()       GPIO_WriteBit(TRANSISTOR_4_PORT, TRANSISTOR_4_PIN, Bit_SET)
 #define TRANSISTOR_4_OFF()      GPIO_WriteBit(TRANSISTOR_4_PORT, TRANSISTOR_4_PIN, Bit_RESET)
