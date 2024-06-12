
#include "stm32f446xx_gpio.h"

void GPIO_ClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t status)
{
	if(status == ENABLE){
		if(pGPIOx == GPIOA)
			GPIOA_EN_CLK();
		else if(pGPIOx == GPIOB)
			GPIOB_EN_CLK();
		else if(pGPIOx == GPIOC)
			GPIOC_EN_CLK();
		else if(pGPIOx == GPIOD)
			GPIOD_EN_CLK();
		else if(pGPIOx == GPIOE)
			GPIOE_EN_CLK();
		else if(pGPIOx == GPIOF)
			GPIOF_EN_CLK();
		else if(pGPIOx == GPIOG)
			GPIOG_EN_CLK();
		else if(pGPIOx == GPIOH)
			GPIOH_EN_CLK();
	}else if(status == DISABLE){
		if(pGPIOx == GPIOA)
			GPIOA_DIS_CLK();
		else if(pGPIOx == GPIOB)
			GPIOB_DIS_CLK();
		else if(pGPIOx == GPIOC)
			GPIOC_DIS_CLK();
		else if(pGPIOx == GPIOD)
			GPIOD_DIS_CLK();
		else if(pGPIOx == GPIOE)
			GPIOE_DIS_CLK();
		else if(pGPIOx == GPIOF)
			GPIOF_DIS_CLK();
		else if(pGPIOx == GPIOG)
			GPIOG_DIS_CLK();
		else if(pGPIOx == GPIOH)
			GPIOH_DIS_CLK();
	}
}

void GPIO_Init(GPIO_handle_t *pGPIOHandle){
	//Las interrupciones van con los GPIO!, estan relacionadas !
	//Aqui en este caso son registros dobles
	// 1. Habilitar el clk
	GPIO_ClkCtrl(pGPIOHandle->pGPIOx, ENABLE);
	//2. Configurar modo
	if(pGPIOHandle->GPIO_config.GPIO_Mode > GPIO_Mode_AN){
    // Modo con configuracion , configurar flancos de disparo
		if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_IT_FE){
			EXTI->FTSR |= (1<<pGPIOHandle->GPIO_config.GPIO_Pin);
			EXTI->RTST &= ~(1<<pGPIOHandle->GPIO_config.GPIO_Pin);
			}
		else if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_IT_RE){
			EXTI->RTST |= (1<<pGPIOHandle->GPIO_config.GPIO_Pin);
			EXTI->FTSR &= ~(1<<pGPIOHandle->GPIO_config.GPIO_Pin);
			}
		else if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_IT_RFE){
			EXTI->FTSR |= (1<<pGPIOHandle->GPIO_config.GPIO_Pin);
			EXTI->RTST |= (1<<pGPIOHandle->GPIO_config.GPIO_Pin);
		}


	//Habilitar el clk
	SYSCFG_EN_CLK();
	//Configurar SYSCFG
	uint8_t regidx;
	uint8_t blkidx;
	//
	regidx = pGPIOHandle->GPIO_config.GPIO_Pin/4; //get the number of register
	blkidx = pGPIOHandle->GPIO_config.GPIO_Pin%4; //selec the number of the pin of the register

	// To select the correct alternate function array
	SYSCFG->EXTICR[regidx] &= ~(0x0f << (blkidx*4) ); //elegimos el bloque
	SYSCFG->EXTICR[regidx] |= (PORT_NUMBER(pGPIOHandle->pGPIOx) << (blkidx*4));

	//Habilitar la interrupcion EXTI
	EXTI->IMR |= (1<<pGPIOHandle->GPIO_config.GPIO_Pin);

	}

	else{
	// Modo sin interrupcion
	// 2. Configurar modo (IN , OUT , AF O AN)
	pGPIOHandle->pGPIOx->MODER &= ~(0x03 << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));//Reset the pin
	pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->GPIO_config.GPIO_Mode << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));

	// 3. Configurar speed
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x03 << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));
	pGPIOHandle->pGPIOx->OSPEEDR |= (pGPIOHandle->GPIO_config.GPIO_Speed << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));

	// 4. Configurar pull-up/pull-down
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x03 << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));
	pGPIOHandle->pGPIOx->PUPDR |= (pGPIOHandle->GPIO_config.GPIO_PuPd << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));

		// 5. Configurar tipo de salida (Push-Pull/Open drain)
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x01 << pGPIOHandle->GPIO_config.GPIO_Pin);
	pGPIOHandle->pGPIOx->OTYPER |= (pGPIOHandle->GPIO_config.GPIO_OType << pGPIOHandle->GPIO_config.GPIO_Pin);

	// 6. Configurar la funcion alternativa
    if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_AF){
    	uint8_t regidx;
    	uint8_t blkidx;

    	regidx = pGPIOHandle->GPIO_config.GPIO_AltFun / 8;
    	blkidx = pGPIOHandle->GPIO_config.GPIO_AltFun % 8;

    	// To select the correct alternate function array
    	pGPIOHandle->pGPIOx->AFR[regidx] &= ~(0x0f << (blkidx*4) ); //elegimos el bloque
    	pGPIOHandle->pGPIOx->AFR[regidx] |= ( (pGPIOHandle->GPIO_config.GPIO_AltFun) << (pGPIOHandle->GPIO_config.GPIO_Pin) ); // una vez que elegimos el bloque la configuramos
    }
   }

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
		GPIOA_RESET();
	else if(pGPIOx == GPIOB)
		GPIOB_RESET();
	else if(pGPIOx == GPIOC)
		GPIOC_RESET();
	else if(pGPIOx == GPIOD)
		GPIOD_RESET();
	else if(pGPIOx == GPIOE)
		GPIOE_RESET();
	else if(pGPIOx == GPIOF)
		GPIOF_RESET();
	else if(pGPIOx == GPIOG)
		GPIOG_RESET();
	else if(pGPIOx == GPIOH)
		GPIOH_RESET();
}

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin)
{
	return (uint8_t)((pGPIOx->IDR >> pin) & 0x01); // ¿For what this? to shift to the right , see vs the reference manual
}

uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx)
{
	return (uint16_t)(pGPIOx->IDR & 0xFFFF);
}

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin, uint8_t value)
{
	if(value == SET){
		pGPIOx->ODR |= (1 << pin);
	}else if(value == RESET){
		pGPIOx->ODR &= ~(1 << pin);
	}
}

void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = (uint32_t)value;
}

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin)
{
	pGPIOx->ODR ^= (1 << pin);
}

// To configure the NVIC
void GPIO_NVIC_IRQ_Enable(uint8_t IRQ){

  if(IRQ < 32){
	  NVIC_ISER0 |= (1<<IRQ);
  }
  else if(IRQ < 64){
	  NVIC_ISER1 |= (1<<IRQ-32);
  }
  else if(IRQ < 96){
	  NVIC_ISER2 |= (1<<IRQ-64);
  }
}


void GPIO_NVIC_IRQ_Disable(uint8_t IRQ){

	if(IRQ < 32){
	   NVIC_ICER0 |= (1<<IRQ);
	  }
	else if(IRQ < 64){
	  NVIC_ICER1 |= (1<<IRQ-32);
	  }
    else if(IRQ < 96){
	  NVIC_ICER2 |= (1<<IRQ-64);
	}

}


void GPIO_NVIC_Priority(uint8_t IRQ,uint32_t priority){

	uint8_t regidx;
	uint8_t blkidx;

	regidx = IRQ/4;
	blkidx = IRQ%4;

	uint32_t *NVIC_IPR = (uint32_t*)(NVIC_IPR_BASEADDR +regidx*4);

	*NVIC_IPR &=~(0xFF << (blkidx*8));
	*NVIC_IPR |= (priority << (blkidx*8+4));

}


void GPIO_IRQHandler(uint8_t pin){

	//Clean the flag
	if(EXTI->PR & (1<<pin)){
		EXTI->PR |= (1<<pin);
	}

}


