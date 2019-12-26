#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "masks.h"
#include <math.h>

void wait (int time){
  for (int i=0;i<=time;i++){}
}

void PORT_INIT(void){
  uint32_t dummy;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
  dummy = SYSCTL_RCGCGPIO_R;
  GPIO_PORTB_DEN_R |= 0xff;
  GPIO_PORTB_DIR_R = 0xff;
  GPIO_PORTF_LOCK_R |= 0x4c4f434b;
  GPIO_PORTF_CR_R |= 0x01f;
  GPIO_PORTF_DEN_R |= 0x06;
  GPIO_PORTF_DIR_R |= 0x06;
  GPIO_PORTF_DEN_R |= 0x11;
  GPIO_PORTF_DIR_R &= ~0x11;
  GPIO_PORTF_PUR_R |= 0x11;
  GPIO_PORTE_DEN_R |= 0x30;
  GPIO_PORTE_DIR_R &=~ 0x30;
  GPIO_PORTA_DEN_R |= 0x1c;
  GPIO_PORTA_DIR_R |= 0x1c;
}

void GPTM_D_ONESHOT(){
  SYSCTL_RCGCTIMER_R |=0x01;
  TIMER0_CTL_R=0x0;
  TIMER0_CFG_R=0x0;
  TIMER0_TAMR_R=0x1;
  TIMER0_TAILR_R=16000000-1;//1 SEC
  TIMER0_CTL_R|=0x1;
  while((TIMER0_RIS_R & 0x1)==0){}
  TIMER0_ICR_R=0x1;
}

void Check_Move(int Delay){
  while(1){
    if ((GPIO_PORTE_DATA_R & LIGHT)){
    if ((GPIO_PORTE_DATA_R & MOTION)){
      //GPIO_PORTE_DATA_R |= 0x04;
      GPIO_PORTF_DATA_R |= BLUE;
      for(int i=0 ; i<Delay ; i++){
        GPTM_D_ONESHOT();}
    //GPIO_PORTE_DATA_R &=~ 0x04;
    GPIO_PORTF_DATA_R &=~ BLUE;
    
    }
    }
  }
}

void LCD_command(unsigned char command){
    LCD_CTRL_DATA = 0;     	/* RS = 0, R/W = 0 */
    LCD_DATA_DATA = command;
    LCD_CTRL_DATA = EN;    	/* pulse E */
    timer(0.000001);
    LCD_CTRL_DATA = 0;
    if (command < 4){
    timer(0.002);
    }
    else{
    timer(0.00004);
    }
}

void LCD_START(void){
    timer(0.02);
    LCD_command(0x30);		// command 0x30 = Wake up
    timer(0.005);
    LCD_command(0x30);		// command 0x30 = Wake up #2
    timer(0.0001);
    LCD_command(0x30);		// command 0x30 = Wake up #3
    timer(0.0001);
  // Prepare LCD Operation and Function  
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}

void LCD_data(unsigned char data){
    LCD_CTRL_DATA = RS;    /* RS = 1, R/W = 0 */
    LCD_DATA_DATA = data;
    LCD_CTRL_DATA = EN | RS;   /* pulse E */
    timer(0.000001);
    LCD_CTRL_DATA = 0;
    timer(0.00004);
}

 int Set_Delay(int value){
   
   
    while (1){
    if (!(GPIO_PORTF_DATA_R & SW1)){
      if ( value <= 8 ){
        value ++;
        LCD_command(0x01);
        LCD_data(value+48);
        timer(2);
      }
      else { value = 0;
      LCD_command(0x01);
      LCD_data(value+48);
      }
    }
    if (!(GPIO_PORTF_DATA_R & SW2)){
      return value;
      break;
    }
  }
  }

void timer(float time){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0; 
    NVIC_ST_RELOAD_R = (int)(16000000*time)-1;
    NVIC_ST_CTRL_R = 5;
    while((NVIC_ST_CTRL_R & 0x10000) == 0){}  
}