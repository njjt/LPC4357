#include "lpc43xx.h"
#include "Board_LED.h"                


int main(void) {
    LED_Initialize(); // Initialize LEDs

    while (1) {
        LED_On(0); // Turn on the LED

        // Add a delay to control the blinking speed
        // You can adjust the delay duration based on your requirements
        for (volatile int i = 0; i < 1000000; i++);  // Adjust the loop count for your desired delay

        LED_Off(0); // Turn off the LED

        // Add a delay to control the blinking speed
        // You can adjust the delay duration based on your requirements
        for (volatile int i = 0; i < 1000000; i++);  // Adjust the loop count for your desired delay
    }
}

