//----------------------------------------------------------------------------------------------------------------------------------------//
//Head files
//----------------------------------------------------------------------------------------------------------------------------------------//
#include <STC12C5410AD.H>
#include "stdio.h"
#include "math.h"
#include "intrins.h"
#include "string.h"
#include "PWM_display.h"                  //Including PWM_display.h (showing temperature on digital LEDs)
//----------------------------------------------------------------------------------------------------------------------------------------//
//Macro definition of I/O ports
//----------------------------------------------------------------------------------------------------------------------------------------//
  sbit P3_3=P3^3;    
//utilize MCU external interrupt source 1£¨INT1£©to measure PWM pulse on SDA pin of MLX90614
//----------------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------//
//Function: Calculate Temperature according PWM pulse width and period£¨Duty cycle£©
//----------------------------------------------------------------------------------------------------------------------------------------//
int Calculate(unsigned int t1pwm, unsigned int T1pwm)
{
  
   int DC;
   long int T;
   int T1;
   int K;
   int T1max=120;                                      //The maximum object temperature, saved in EEPROM 00h
   int T1min=-20;                                      //The minimum object temperature, saved in EEPROM 01h
   K=2*(T1max-T1min);

   DC=t1pwm*100000/T1pwm;                
   //Calculate Duty cycle, times 100,000 shifts the fixed point 5 position to the right
  
   T=(DC-0.125*100000)*K+T1min*100000;
  //calculate object temperature, DC is duty cycle
   T1=T/1000;                                          
  //To truncate the resolution to 0.01¡æ, a division by 1000 is done on the results
   return T1;

}
//----------------------------------------------------------------------------------------------------------------------------------------//
//Name£ºmain 
//Function£ºUse STC MCU external interrupt source port 1¡¢Timer 0 and 1 to measure PWM pulse width and period
//----------------------------------------------------------------------------------------------------------------------------------------//
void main(void)
{
   unsigned int A;
   unsigned int B;
   unsigned int C;
   unsigned int D;
   unsigned int Data1;
   unsigned int Data2;
   int Data;

   TMOD=0x19;                                 //Set timer 0£¨GATE=1£©and Timer 1£¨ GATE=0£©work in mode 1
   TH0=0x00;                                  //Clear TH0, TL0 
   TL0=0x00;
   ET0=1;                                     //Open Timer 0 interrupt enable
   ET1=1;                                     //Open Timer 1 interrupt enable
   EA=1;                                      //Open overall interrupt enable
   TL1=0x00;                                  //Clear TH1, TL1 
   TH1=0x00;
   EX1=0;                                     //Turn-off INT1 interrupt

while(P3_3==1)		                      //Wait INT1 low pulse
{;}
while(P3_3==0)		                      //Wait INT1 high pulse
{;}
TR0=1;                                        //Open timer 0
TR1=1;			                      //Open timer 1
while(P3_3==1)		                      //Wait INT1 low pulse
{;}
TR0=0;                                        //Clear timer 0
C=TL0;                                        //T0 Low byte sends to C
D=TH0;                                        //T0 High byte sends to D
while(P3_3==0)		                      //Wait INT1 high pulse
{;}           
TR1=0;                                        //Clear timer 1
A=TL1;                                        //T1 Low byte sends to A
B=TH1;                                        //T1 High byte sends to B
Data2=(D<<8)+C;
Data1=(B<<8)+A;

Data=Calculate(Data2,Data1);                  //Calculate temperature based on counter value
display(Data);                                //Show temperature 
}








  