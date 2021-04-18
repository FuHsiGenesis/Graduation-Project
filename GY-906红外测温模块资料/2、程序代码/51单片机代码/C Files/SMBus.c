// Read IR temperature from MLX90614
// version 0.1.  2010/02/04
// Author Linhong Song
// This document describe C programme based on STC12C5604AD.
// Including reading temperature from MLX90614, writing data into MLX90614 EEPROM.
// CalTem.h and digitalLEDs are optional, customer have other alternative which depends on their application
//---------------------------------------
//Include Head files
//---------------------------------------
#include <STC12C5410AD.H>	
#include "stdio.h" 
#include "intrins.h" 
#include "string.h"
#include "SMBus_CM.h"				      //Include SMBus_CM.h (Contain Start, Stop, Send, Receive etc.)
#include "SMBus_OP.h"				      //Include SMBus_OP.h (Contain Read data from MLX90614 and Write data into MLX90614)
#include "digitalLED.h"			              //Include digitalLED.h(For showing Temperature on digital LEDs)
#include "CalTem.h"				      //Include CalTem.h(For calculating Temperature based on Hex data)
#include "dec2hex.h"			              //Include dec2hex.h(For convertering dec to hex)
#include "Delay.h"                                    //Include Delay.h

//---------------------------------------
//Define I/O port and the direction for SMBus signals

#define _SDA_OUTPUT P1M0=0x10;P1M1=0x10;         //Set SDA as Open-drain Output 
#define _SDA_INPUT P1M0=0x10;P1M1=0x00;		 //Set SDA as Input
#define _SCL_IO P1M0=0x08;P1M1=0x08;		 //Set SCL as Open-drain I/O

 
sbit SDA = P1^4;   //Assign P14 as SDA line
sbit SCL = P1^3;   //Assign P13 as SCL line

//--------------------------------------- 

//---------------------------------------
//Function Read object Temperature
//---------------------------------------
void main()
{						
	unsigned char slaveaddress;	 			  
        unsigned long int DATA;
	unsigned int *mahm;
	 
        _SCL_IO;
        _SDA_OUTPUT;

       SCL=0;				        //
       Delay(1200);				//SMBus request£¬Switch PWM mode to SMBus mode(at least 2ms)
       SCL=1;				        //
       while(1)
       {
	    slaveaddress=MEM_READ(0x00,0x2E);                       //Get the slave address which stored in EEPROM "0Eh" 
	    DATA=MEM_READ(slaveaddress,0x07);			    //Read Object Temperature from MLX90614 RAM 07h
	    mahm=CALTEMP(DATA);				            //Calculate the Temperature based on Hex code
            show(mahm,5); 					    //Show the Temperature on Digital LEDs		 
	    
	 }
}

//---------------------------------------