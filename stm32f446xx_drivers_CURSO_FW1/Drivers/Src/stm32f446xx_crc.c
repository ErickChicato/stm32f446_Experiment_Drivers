/*
 * stm32f446xx_crc.h
 *
 *  Created on: Jun 11, 2024
 *  Author: Erick Chicatto
 *  Experiment Driver
 */
#include "stm32f446xx_crc.h"

/*
 *Configure the register like the read pin for writing and reading
 * */
void ConfigureDataRegister(CRC_RegDef_t *pConf,int config,int pin){

	if(config==READ){
		pConf->DR |= (1<<pin);
	}
	else if(config==WRITE){
		pConf->DR |= (0<<pin);
	}

}



/*
 *Configure the independt data register , control register
 * */
void ConfigureIndDataRegisterControlReg(CRC_RegDef_t *pConf,int config,int pin){

	//IDR config
	if(config == 0){
		pConf->IDR |= (1<<pin) & 0xFFFFFF ;
	}

	//CR config read
	else if(config == 1){
		pConf->CR |= (1<<0);
	}

	//CR config write
	else if(config ==2){
		pConf->CR |= (1<<1);
	}

}
