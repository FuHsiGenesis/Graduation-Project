//This document contains start_bit, stop_bit, tranmit and receive byte 
#include <STC12C5410AD.H>
#include "SMBus_CM.h"
#include "intrins.h"
#include "Delay.h" 
//---------------------------------------
//Define I/O port and the direction for SMBus signals

#define _SDA_OUTPUT P1M0=0x10;P1M1=0x10;        //Set SDA as Open-drain Output 
#define _SDA_INPUT P1M0=0x10;P1M1=0x00;		//Set SDA as Input
#define _SCL_IO P1M0=0x08;P1M1=0x08;		//Set SCL as Open-drain I/O

 
sbit SDA = P1^4;   //Assign P14 as SDA line
sbit SCL = P1^3;   //Assign P13 as SCL line


//---------------------------------------
//Name: start_bit
//Function: Generates start condition on SMBus
//Comments: Refer to "System Management BUS specification Version 2.0
void start_bit()
{
   
   _SDA_OUTPUT;				      //Set SDA as output 
   SDA=1;				      //Set SDA line
   _nop_();_nop_();				  
   SCL=1;				      //Set SCL line
   Delay(5);				      //Generate bus free time between stop and start condition (Tbuf=4.7us min)
   SDA=0;				      //Clear SDA line
   Delay(5);				      //Hold time after (Repeated) start condition, after this time, generate the first clock
   					      //Thd:sta=4us min
   SCL=0;				      //Clear SCL line
   _nop_();_nop_();

}

//---------------------------------------

//---------------------------------------
//Name: stop_bit
//Function: Generates stop condition on SMBus
//Comments: Refer to "System Management BUS specification Version 2.0
void stop_bit()
{
  
  _SDA_OUTPUT;					   //Set SDA as output
  SCL=0;			     		   //Clear SCL line
  Delay(5);
  SDA=0;					   //Clear SDA line
  Delay(5);
  SCL=1;					   //Set SCL line
  Delay(5);					   //Stop condition setup time(Tsu:sto=4.0us min)
  SDA=1;					   //Set SDA line
  
}

//---------------------------------------

//---------------------------------------
//Name: send_bit

void send_bit(unsigned char bit_out)
{
    
  _SDA_OUTPUT;					  //Set SDA as output to transmit data on SMBus

  if(bit_out==0)				  //Check bit
            					  //Set SDA if bit_out=1
	     SDA=0;
  else							  
             SDA=1;				  //Clear SDA if bit_out=0
  

  _nop_();						  //
  _nop_();						  //Tsu:dat=250ns minimum
  _nop_();						  //
  SCL=1;						  //Set SCL line
  Delay(4);						  //High Level of Clock Pulse (10.6us)
  SCL=0;						  //Clear SCL line
  Delay(4);
   
}

//---------------------------------------

//---------------------------------------
//Name: receive_bit

unsigned char receive_bit()
{
  unsigned char bit_in;
 
  _SDA_INPUT;				       //Set SDA as input
  SCL=1;				       //Set SCL line
  Delay(2);

  if(SDA==1)				       //Read bit, save it in bit_in
       bit_in=1;
  else
       bit_in=0;

  Delay(2);
  SCL=0;				       //Clear SCL line
  Delay(4);
  return bit_in;

}

//---------------------------------------


//--------------------------------------
//Name: slave_ack
//Function: Get acknowledgment bit from slave device
//Return:  unsigned char ack
//         1 - ACK
//         0 - NACK
//---------------------------------------

unsigned char slave_ack()
{
   unsigned char ack;
   ack=0;
   _SDA_INPUT;				        //Set SDA as input
   SCL=1;					//Set SCL line
   Delay(2);
      
   if(SDA==1)					//Read bit, save it in ack
         ack=0;
   else
         ack=1;
   
   Delay(2);   
   SCL=0;					//Clear SCL line
   Delay(4);   
   return ack;
}

//---------------------------------------


//--------------------------------------
//     TRANSMIT Byte
//Name: TX_byte
//Function: Sends a byte on SMBus
//Parameters: unsigned char TX_buffer(the byte which will be send on the SMBus)
//Comments: Sends MSbit first
//---------------------------------------

void TX_byte(unsigned char TX_buffer)
{
   unsigned char Bit_counter;
   unsigned char bit_out;
   
    
   for(Bit_counter=8;Bit_counter;Bit_counter--)
   {
       if(TX_buffer&0x80)
            
		     bit_out=1;		          //If the current bit of TX_buffer is 1, set bit_out
		else
		     bit_out=0;	         	  //Otherwise clear bit_out
       
       send_bit(bit_out);			  //Send the current bit on SMBus
	   
	   TX_buffer<<=1;			  //Get next bit to check
			  
	}
			            	                      
}

//---------------------------------------


//--------------------------------------
//RECEIVE Byte
//Name: RX_byte
//Function: Receives a byte on SMBus
//Parameters: unsigned char ack_nack (acknowledgment bit)
//         0 - Master device sends ACK
//         1 - Master device sends NACK
//Return:  unsigned char RX_buffer (Received byte on the SMBus)
//Comments: MSbit received first
//---------------------------------------

unsigned char RX_byte(unsigned char ack_nack)
{
  
    unsigned char RX_buffer;
    unsigned char Bit_counter;


    for(Bit_counter=8;Bit_counter;Bit_counter--)
    {
                	
				if(receive_bit()==1)	   //Read a bit from the SDA line
                
				{
				  RX_buffer<<=1;	   //If the bit is HIGH save 1 in RX_buffer 
			          RX_buffer|=0x01;
				}
				else			   //If the bit is LOW save 0 in RX_buffer
				{
				  RX_buffer<<=1;
				  RX_buffer&=0xfe;
				}
			
	 } 

	 send_bit(ack_nack);				   //Sends acknowledgment bit
				
	 return RX_buffer;

}

//---------------------------------------



