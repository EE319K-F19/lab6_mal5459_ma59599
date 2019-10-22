// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 9/2/19 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

const uint32_t TONE[5]={0, 294, 392, 440, 494}; //D(294), G(392), A(440), B(494)

uint32_t reading;

int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
  
  while(1){
		reading = Piano_In();
		//Transform reading from {0x00, 0x01, 0x02, 0x04, 0x08, (other)} to {0, 1, 2, 3, 4, (0)}
		if(reading ==  0x04){
			reading = 3;
		}else if(reading == 0x08){
			reading = 4;
		}else if (reading != 0 && reading !=1 && reading != 2){
			reading = 0;
		}
		Sound_Play(TONE[reading]);
		
  }    
}


