# LPC4357
This is the repo for practice code for LPC4357. I hope I could finally do a small simple OS on the board.


2023/10/7
The draft code for a blinky. Setting to first blink with a empty instruction:
void delay_ms(uint32_t milliseconds) {
    volatile uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 10000; j++) { // Adjust for your microcontroller's clock speed
            __NOP(); // No-operation instruction
        }
    }
}

2023/10/17
Find a nice tutorial site for this CPU http://lpc4300.com/lpc4357
