/*
 * stm32f446xx_interrp.h
 *
 *  Created on: Apr 22, 2024
 *      Author: robo1
 */

#ifndef INC_STM32F446XX_INTERRP_H_
#define INC_STM32F446XX_INTERRP_H_

#include "stm32f446xx.h"

/*@Interrupt mask on line x , for EXTI mask registers*/
typedef enum {
	IsMasked,
	IsNotMasked
}EXTI_Mask_Register_t;


/*@System configuration controller*/
typedef enum{
	NoFMCMemoryMappingSwap,
	SDRAM_Banks,
	Reserved01,
	Reserved02
}SystemConfigurationController01_t;


/*@System configuration controller*/
typedef enum{
	MainFlashMemoryMapped,
	SystemFlashMemoryMapped,
	FMC_Bank1,
	EmbeddedSRAM,
	FMC_SDRAM,
}SystemConfigurationController02_t;

/*@System peripheral mode configuration Register*/
typedef enum{
	NoAffect,
	Affect
}PeripheralModeConfiguration_t;

/*@External Interrupt Configuration Register 01*/
typedef enum {
	PA_pin1,
	PB_pin1,
	PC_pin1,
	PD_pin1,
	PE_pin1,
	PF_pin1,
	PG_pin1,
	PH_pin1
}ExternalInterruptConf01_t;

/*@External Interrupt Configuration Register 02*/
typedef enum {
	PA_pin2,
	PB_pin2,
	PC_pin2,
	PD_pin2,
	PE_pin2,
	PF_pin2,
	PG_pin2,
	PH_pin2
}ExternalInterruptConf02_t;

/*@External Interrupt Configuration Register 03*/
typedef enum {
	PA_pin3,
	PB_pin3,
	PC_pin3,
	PD_pin3,
	PE_pin3,
	PF_pin3,
	PG_pin3,
	PH_pin3
}ExternalInterruptConf03_t;


/*@External Interrupt Configuration Register 04*/
typedef enum {
	PA_pin4,
	PB_pin4,
	PC_pin4,
	PD_pin4,
	PE_pin4,
	PF_pin4,
	PG_pin4,
	PH_pin4
}ExternalInterruptConf04_t;

/*@Compensation cell control register */
typedef enum{
  CompensationCellNotReady,
  CompensationCellReady
}CellControlRegister_t;


/*@Compensation cell power-down*/
typedef enum{
  CellPowerDownMode,
  CompensationCellEnabled
}CellPowerDown_t;

/*@ConfigurationRegister*/


/************Functions************/
void SystemConfigurationController(int option);




#endif /* INC_STM32F446XX_INTERRP_H_ */
