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
void ConfigureDataRegister(int config,uint32_t *values){

	CRC_RegDef_t *pConf;

	if(config==READ){
		pConf->DR |= *values; // is that feasible?
	}
	else if(config==WRITE){
		pConf->DR |= *values;
	}

}



/*
 *Configure the independt data register , control register
 * */
void ConfigureIndDataRegisterControlReg(int config,uint32_t *values){

	CRC_RegDef_t *pConf;

	//IDR config
	if(config == 0){
		pConf->IDR |= *values & 0xFFFFFF ;
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
