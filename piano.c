// Piano.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 4 keys, but you could have more
// Runs on LM4F120 or TM4C123
// Program written by: Mario Ayerra and Mihael Lobsenz
// Date Created: 3/6/17 
// Last Modified: 10/17/19 
// Lab number: 6
// Hardware connections: 4 switches to PE3-0

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// **************Piano_Init*********************
// Initialize four piano key inputs, called once to initialize the digital ports
// Input: none 
// Output: none
void Piano_Init(void){ 
  //Initialize PortE 3-0
	SYSCTL_RCGCGPIO_R |= 0x10; // Turn on portE clock
	while((SYSCTL_RCGCGPIO_R & 0x10) == 0){}
	GPIO_PORTE_DEN_R |= 0x0F;  // Use pins 3-0
	GPIO_PORTE_DIR_R &= ~0x0F; // All inputs
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
//   bit n is set if key n is pressed
uint32_t Piano_In(void){
  uint32_t reading;
	reading = (GPIO_PORTE_DATA_R & 0x0F);
	return reading;
}
