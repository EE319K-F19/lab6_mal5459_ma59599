// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 9/2/19 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"

void EnableInterrupts(void);
void DisableInterrupts(void);
void SysTick_Handler(void);
void SysTick_Init(void);

const uint8_t SINE[32]={8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};
const uint8_t GUITAR[32]={5,5,4,1,1,3,8,11,11,9,4,2,5,11,15,13,9,7,5,5,6,8,8,7,4,3,3,3,3,4,5,5};
uint8_t first_time = 1;
uint8_t wave_elem	= 0;
	
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0; 
  NVIC_ST_RELOAD_R = 0x00FFFFFF;   //Any value
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 0x00000007;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; //Priority 2
} 

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();
	SysTick_Init();
	
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period: Hz
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){
	if(period > 0){
		EnableInterrupts();
		uint32_t cycles = period*80000000/32/494;
		NVIC_ST_RELOAD_R = cycles;
		if(first_time ==1){
			first_time = 0;
			NVIC_ST_CURRENT_R = NVIC_ST_RELOAD_R;
		}
	}else{
		DisableInterrupts();
	}	
}

void SysTick_Handler(void){
	DAC_Out(SINE[wave_elem]);
	wave_elem = (wave_elem+1) & 0x1F;
}


