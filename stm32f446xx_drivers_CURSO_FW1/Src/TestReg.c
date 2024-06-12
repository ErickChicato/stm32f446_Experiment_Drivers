#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_interrp.h"



int main(void)
{

	/*Test if you test at least one register */
	SystemConfigurationController(1);
	SystemConfigurationController(2);
	SystemConfigurationController(3);
	SystemConfigurationController(4);
	SystemConfigurationController(5);
	SystemConfigurationController(6);
	SystemConfigurationController(7);

}

void UART4_IRQHandler(void)
{

}
