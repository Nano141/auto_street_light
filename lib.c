#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "masks.h"
#include <math.h>

void wait (int time){
  for (int i=0;i<=time;i++){}
}

void PORT_INIT(void){
  uint32_t dummy;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
  dummy = SYSCTL_RCGCGPIO_R;
  GPIO_PORTB_DEN_R |= 0x07;
  GPIO_PORTB_DIR_R &= ~0x03;
  GPIO_PORTB_DIR_R |= 0x04;
  GPIO_PORTF_LOCK_R |= 0x4c4f434b;
  GPIO_PORTF_CR_R |= 0x01f;
  GPIO_PORTF_DEN_R |= 0x06;
  GPIO_PORTF_DIR_R |= 0x06;
}

void GPTM_D_ONESHOT(){
  SYSCTL_RCGCTIMER_R |=0x01;
  TIMER0_CTL_R=0x0;
  TIMER0_CFG_R=0x0;
  TIMER0_TAMR_R=0x1;
  TIMER0_TAILR_R=1600000-1;//1 SEC
  TIMER0_CTL_R|=0x1;
  while((TIMER0_RIS_R & 0x1)==0){}
  TIMER0_ICR_R=0x1;
}

void Check_Move(void){
  while(1){
    if ((GPIO_PORTB_DATA_R & LIGHT)){
    if ((GPIO_PORTB_DATA_R & MOTION)){
      GPIO_PORTB_DATA_R |= 0x04;
      GPIO_PORTF_DATA_R |= BLUE;
   //for(int i = 0 ; i<5 ; i++)
    GPTM_D_ONESHOT();
    GPIO_PORTB_DATA_R &=~ 0x04;
    GPIO_PORTF_DATA_R &=~ BLUE;
    
    }
    }
  }
  }