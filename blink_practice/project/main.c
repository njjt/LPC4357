#include "lpc43xx.h"

uint32_t Time;

void System_Init(void) {
	
	uint32_t TimeOut;
	
	//We select the internal oscillator @12MHz
	
	LPC_CGU->BASE_M4_CLK = (1<<11) | (1<<24);
	
	//We select and enable the external oscillator @12MHz.
	
	LPC_CGU->XTAL_OSC_CTRL = (1<<0) | (0<<2);
	
	//Configuration a 90<=100Mhz<=110Mhz
	
	LPC_CGU->PLL1_CTRL = (0<<1)  |
                       (0<<1)	 |
	                     (0<<6)  |
	                     (0<<7)  |
                       (0<<8)  |
                       (0<<11) |
                       (2<<12) |
                       (24<<16) |
                       (6<<24);	
	while(!(LPC_CGU->PLL1_STAT & (1<<0)));
	
	for(TimeOut=4000;TimeOut>0;TimeOut--);
	LPC_CGU->BASE_M4_CLK = (1<<11) | (9<<24);
	
	//Configuration a 180Mhz
	LPC_CGU->PLL1_CTRL = (0<<1)  |
                       (0<<1)	 |
	                     (0<<6)  |
	                     (0<<7)  |
                       (0<<8)  |
                       (0<<11) |
                       (0<<12) |
                       (14<<16) |
                       (6<<24);	
}
int main(void) {
	
	LPC_SCU->SFSP7_7 = (0<<0);
	LPC_SCU->SFSPC_11 = (4<<0);
	LPC_SCU->SFSP9_3 = (0<<0);
	LPC_SCU->SFSP9_4 = (4<<0);
	
	LPC_GPIO_PORT->DIR[3] |= (1<<15);
	LPC_GPIO_PORT->DIR[6] |= (1<<10);
	LPC_GPIO_PORT->DIR[4] |= (1<<15);
	LPC_GPIO_PORT->DIR[5] |= (1<<17);
	
	while(1){
		//We set the bits to 1.
		LPC_GPIO_PORT->SET[3] |= (1<<15);
		LPC_GPIO_PORT->SET[6] |= (1<<10);
		LPC_GPIO_PORT->SET[4] |= (1<<15);
		LPC_GPIO_PORT->SET[5] |= (1<<17);
		
    for(Time=10000000;Time>0;Time++);	
		
		//We set the bits to 0
		
		LPC_GPIO_PORT->SET[3] |= (1<<15);
		LPC_GPIO_PORT->SET[6] |= (1<<10);
		LPC_GPIO_PORT->SET[4] |= (1<<15);
		LPC_GPIO_PORT->SET[5] |= (1<<17);
	}
}
