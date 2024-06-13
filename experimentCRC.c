#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_crc.h"


int main(void)
{
  //1. Enable the clk for crc
	CRC_EN_CLK();
  //2. Create the array that stores the number
	uint32_t numberTest[1]={0x424546 , 0x784613};
  //3.Take the input data into the register
	ConfigureDataRegister(WRITE, numberTest);
  //4. Configure the others registers
	ConfigureIndDataRegisterControlReg(0,numberTest);

    //
}

