#include <stdint.h>


#define AHB1ENR 0x40023830UL

void Delay(uint32_t cnt){

	while(cnt){
		cnt--;
	}

}


int main(void){

	*(uint32_t*)AHB1ENR |= (1<<0);
	*(uint32_t*)0x40020000UL |= (1<<10);

	while(1){
		*(uint32_t*)0x40020014UL |= (1<<5);
		Delay(500000);
		*(uint32_t*)0x40020014UL &= ~(1<<5);
	}

}
