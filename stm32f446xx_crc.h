/*
 * stm32f446xx_crc.h
 *
 *  Created on: Jun 11, 2024
 *  Author: Erick Chicatto
 *  Experiment Driver
 */

#ifndef INC_STM32F446XX_CRC_H_
#define INC_STM32F446XX_CRC_H_

#include <stm32f446xx.h>

#define READ	1
#define WRITE	0

//1. Define the direction of the CRC
#define CRC_BASEADDR   0x40023000

//2. Enable CLK
#define CRC_EN_CLK()	(RCC->AHB1ENR |=  (1<<12))
#define CRC_DIS_CLK()	(RCC->AHB1ENR &=~ (1<<12))

//3.Structure of register to configure the bits
typedef struct {
	volatile uint32_t DR;
	volatile uint32_t IDR;
	volatile uint32_t CR;
}CRC_RegDef_t;



//4.Functions
void ConfigureDataRegister(int config,uint32_t *values);
void ConfigureIndDataRegisterControlReg(int config,uint32_t *values);





#endif /* INC_STM32F446XX_CRC_H_ */
