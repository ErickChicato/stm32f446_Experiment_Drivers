#include <stdio.h>
#include <string.h>

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_nvic.h"
#include "stm32f446xx_rcc.h"
#include "stm32f446xx_systick.h"
#include "stm32f446xx_wwdg.h"

GPIO_handle_t LED;
GPIO_handle_t Button;
uint32_t systick_delay;

WWDG_Config_t WWDG_Config;

void SYSCLK_PLL_setup(void);
void min11max25(uint8_t val);
void generate_fault(void);

void delay_ms(uint32_t ms)
{
	systick_delay = ms;
	while(systick_delay);
}

void SysTick_Handler(void)
{
	if(systick_delay > 0)
		systick_delay--;
}

void GPIO_setup(void)
{
	LED.pGPIOx = GPIOA;
	LED.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_config.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_config.GPIO_Pin = GPIO_PIN_5;
	LED.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	LED.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&LED);

	Button.pGPIOx = GPIOC;
	Button.GPIO_config.GPIO_Mode = GPIO_Mode_IN;
	Button.GPIO_config.GPIO_Pin = GPIO_PIN_13;
	Button.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	Button.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&Button);
}

void SYSTICK_setup(void)
{
	SYSTICK_Config_t SYSTICK_Config = {0};

	SYSTICK_Config.SYSTICK_Clock_Source = SYSTICK_Clk_Source_External;
	SYSTICK_Config.SYSTICK_Period = (SYSTICK_GetCalib() & 0x00FFFFFF) - 1;

	SYSTICK_Init(&SYSTICK_Config);
}

void WWDG_setup(void)
{
	WWDG_Config.WWDG_Prescaler = WWDG_Prescaler_4096x4;
	WWDG_Config.WWDG_Window = 97;		// Tmin: 10.48ms (1/37.5MHz)x4096x4x(valor_contaje - valor_ventana)
	WWDG_Config.WWDG_Counter = 121;		//Tmax: 25.34ms (1/37.5MHz)x4096x4x(valor_contaje - 0x40 + 1)

	WWDG_Init(&WWDG_Config);
}

int main(void)
{
	SYSCLK_PLL_setup();
	GPIO_setup();
	SYSTICK_setup();
	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);

	delay_ms(300);
	GPIO_WritePin(LED.pGPIOx, LED.GPIO_config.GPIO_Pin, SET);

	*((volatile uint32_t *)0xE0042008UL) |= (1 << 11);

	WWDG_setup();
	//WWDG_Refresh(&WWDG_Config); // Cargar antes de habilitar (como ya lo hacemos en WWDG_setup() no hace falta volver a hacerlo)
	WWDG_cmd(ENABLE);

	while(1){
		if(!GPIO_ReadPin(Button.pGPIOx, Button.GPIO_config.GPIO_Pin))
			generate_fault();

		min11max25(24);
		WWDG_Refresh(&WWDG_Config);
	}
}

void min11max25(uint8_t val)
{
	delay_ms(val);
}

void generate_fault(void)
{
	uint32_t *sram_address = (uint32_t *)0x20014000;
	*sram_address = 0xFFFFFFFF;
	void (*function_pointer)(void);

	function_pointer = (void *)sram_address;
	function_pointer();
}

void HardFault_Handler(void)
{
	while(1);
}

void SYSCLK_PLL_setup(void)
{
	uint32_t PLLM, PLLN, PLLP, PLLQ, PLLR;
	// 150MHz
	PLLM = 4;
	PLLN = 150;
	PLLP = 2;
	PLLR = 2;
	PLLQ = 8;

	// Configurar prescaler APB1 y APB2
	RCC_APB1CLKConfig(RCC_APB_Prescaler_4); // 37.5MHz
	RCC_APB2CLKConfig(RCC_APB_Prescaler_2); // 75MHz

	// Habilitar HSE
	RCC_HSEConfig(RCC_HSE_ON);

	// Esperar a que HSE este OK
	RCC_WaitForCLKRDY(RCC_Clock_HSE);

	// Configurar el PLL
	RCC_PLLConfig(RCC_PLL_Source_HSE, PLLM, PLLN, PLLP, PLLQ, PLLR);

	// Habilitar PLL
	RCC_PLLCmd(ENABLE);

	// Esperar a que PLL este OK
	RCC_WaitForCLKRDY(RCC_Clock_PLL);

	// Flash latency
	*((volatile uint32_t *)0x40023C00) = 0x04;

	// Seleccionar PLL_P como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_PLL_P);

}

void assert_failed(uint8_t *file, uint32_t line){
	while(1);
}

