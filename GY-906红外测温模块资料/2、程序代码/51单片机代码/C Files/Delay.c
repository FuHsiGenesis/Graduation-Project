#include <STC12C5410AD.H>
#include "intrins.h"
#include "Delay.h"
	    
//---------------------------------------
//Name: Delay
//Function: Delay for a certain time 
//Parameters: N, means delay time is about N times of MCU machine cycle, 
//Comments: Machine cycle is equal to 12 times of clock cycle(1/Fosc), For STC12C5604AD, Fosc=11.0592MHz

void Delay(unsigned int N)
{ 
    unsigned int i;
    for(i=0;i<N;i++)
    _nop_();
    
}

//---------------------------------------