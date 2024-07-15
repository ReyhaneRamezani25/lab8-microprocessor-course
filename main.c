#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "LCD16x2Lib/LCD.h"
#include <stdio.h>
#include <string.h>
void SysTick_Handler(void);
void display_msg();
void display_clock();
void delay(int ms);

char msg[] = "Hello!This is LAB8.The end is near.";

void GPIO_init(){
    SystemCoreClockUpdate();


   RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

    
    GPIOC->MODER &= ~(0x3 << (26)); 
    GPIOC->MODER &= ~(0x3 << (16)); 

    
    SYSCFG->EXTICR[3] |= (0x2 << 4 );
    EXTI->FTSR |= (1 << 13);                   
    EXTI->IMR |= (1 << 13);                    
    NVIC_EnableIRQ(EXTI15_10_IRQn);            

    
    SYSCFG->EXTICR[2] |= (0x2 << 0); 
    EXTI->FTSR |= (1 << 8);                      
    EXTI->IMR |= (1 << 8);                       
    NVIC_EnableIRQ(EXTI9_5_IRQn);              

    HAL_Init();
}

void EXTI15_10_IRQHandler() { 
    SystemCoreClockUpdate();
		FLASH->ACR = 2;
	RCC->CR &= ~RCC_CR_PLLON;
    if(SystemCoreClock== 16000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (192<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
    else if(SystemCoreClock==24000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (256<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==32000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (320<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==40000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (384<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==48000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (336<<RCC_PLLCFGR_PLLN_Pos) | (2<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==56000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (384<<RCC_PLLCFGR_PLLN_Pos) | (2<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==64000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (432<<RCC_PLLCFGR_PLLN_Pos) | (2<<RCC_PLLCFGR_PLLP_Pos);

		RCC->CR |= RCC_CR_PLLON;
		while((RCC->CR & RCC_CR_PLLRDY) == 0);
		RCC->CFGR |= (RCC_CFGR_SW_PLL | (4<<RCC_CFGR_PPRE1_Pos));
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		SystemCoreClockUpdate();
	
    EXTI->PR |= (1 << 13); 
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn); 
} 

void EXTI9_5_IRQHandler() {
	  SystemCoreClockUpdate();
		FLASH->ACR = 2;
	RCC->CR &= ~RCC_CR_PLLON;
       if(SystemCoreClock==24000000)
          RCC->PLLCFGR =( 16<<RCC_PLLCFGR_PLLM_Pos) | (192<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==32000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (192<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==40000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (256<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==48000000)
        RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (320<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==56000000)
        RCC->PLLCFGR =(16<<RCC_PLLCFGR_PLLM_Pos) | (384<<RCC_PLLCFGR_PLLN_Pos) | (3<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==64000000)
        RCC->PLLCFGR =  (16<<RCC_PLLCFGR_PLLM_Pos) | (336<<RCC_PLLCFGR_PLLN_Pos) | (2<<RCC_PLLCFGR_PLLP_Pos);
		else if(SystemCoreClock==72000000)
         RCC->PLLCFGR = (16<<RCC_PLLCFGR_PLLM_Pos) | (384<<RCC_PLLCFGR_PLLN_Pos) | (2<<RCC_PLLCFGR_PLLP_Pos);
   
		


		RCC->CR |= RCC_CR_PLLON;
		while((RCC->CR & RCC_CR_PLLRDY) == 0);
		RCC->CFGR |= (RCC_CFGR_SW_PLL | (4<<RCC_CFGR_PPRE1_Pos));
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		SystemCoreClockUpdate();
	
    EXTI->PR |= (1 << 8); 
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn); 
} 


int main(void)
{
	//==============================
	
	
	 
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 
 
  	
	//==============================
	GPIO_init();
	LCD_Init();
	while(1){
	display_clock();
	display_msg();
	}

	return 0;
}
void display_msg(){

	char display_str[17];
	int base = 0;
	if(strlen(msg) <= 16){
			LCD_Puts(0,1, msg);
			delay(200);
	}
	else{
			for(int i=0; i<= strlen(msg)-16; i++){
					strncpy(display_str, msg+base, 16);
					display_str[16] = '\0';
					LCD_Puts(0,1,display_str);
					delay(200);
					base++;
			}	
		}
}


void display_clock(){
	SystemCoreClockUpdate();
	unsigned int myclock = SystemCoreClock;
	char str[20];
	sprintf(str, "%d", myclock); 
	LCD_Puts(0,0, str);
}

void delay(int ms){
	volatile int i = 0;
	for(i=0; i < ms*1000; i++);
}


void SysTick_Handler(void){
  HAL_IncTick();
}


