
#include "stm32f446xx_interrp.h"

void SystemConfigurationController(int option){

	Syscfg_RegDef_t *configReg;
	/*ENABLE THE CLK!*/
	SYSCFG_EN_CLK();
	/*1. Select the option*/
	switch(option){
	/*2. Set the bytes for the mem_mode*/
	case 1 :
		configReg->MEMRMP |= MainFlashMemoryMapped;
		break;
	case 2 :
		configReg->MEMRMP |= SystemFlashMemoryMapped;
		break;
	case 3:
		configReg->MEMRMP |= FMC_Bank1;
		break;
	case 4:
		configReg->MEMRMP |= EmbeddedSRAM;
		break;
	case 5:
		configReg->MEMRMP |= FMC_SDRAM;
	/*3. Set the bytes for the SWP_FMC*/
	case 6:
		configReg->MEMRMP |= NoFMCMemoryMappingSwap;
	case 7:
		configReg->MEMRMP |= SDRAM_Banks;



	default:
		break;
	}


}



