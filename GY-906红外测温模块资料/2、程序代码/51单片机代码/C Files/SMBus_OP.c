//This document contains C programmes for reading data from MLX90614, writing data into MLX90614
//PEC calculation 

#include <STC12C5410AD.H>
#include "SMBus_CM.h"
#include "intrins.h"
#include "SMBus_OP.h" 
#include "Delay.h"
  
//---------------------------------------
sbit SDA = P1^4;   //Assign P14 as SDA line					  
sbit SCL = P1^3;   //Assign P13 as SCL line					  
//---------------------------------------
//      CALCULATE THE PEC PACKET
//Name: PEC_cal
//Function: Calculate the PEC of received bytes
//Parameters: unsigned char pec[], int n
//Return: pec[0] - This byte contains calculated crc value
//Comments:	Refer to "System Management BUS specification Version 2.0" and " AN "SMBus communication with MLX90614"
//---------------------------------------

unsigned char PEC_cal(unsigned char pec[],int n)

{
     unsigned char crc[6];
     unsigned char Bitposition=47;
     unsigned char shift;
     unsigned char i;
     unsigned char j;
     unsigned char temp;

 do{
          crc[5]=0;           			        //Load CRC value 0x000000000107
          crc[4]=0;
          crc[3]=0;
          crc[2]=0;
          crc[1]=0x01;
          crc[0]=0x07;
          Bitposition=47;     		                //Set maximum bit position at 47
          shift=0;

          //Find first 1 in the transmitted bytes

          i=5;                				//Set highest index (package byte index)
          j=0;                			        //Byte bit index, from lowest
          while((pec[i]&(0x80>>j))==0 && (i>0))
		  
		  {
             Bitposition--;
             if(j<7)
			     {
                    j++;
                 }
             else
			     {
                   j=0x00;
                   i--;
                 }
           }//End of while, and the position of highest "1" bit in Bitposition is calculated 
       
          shift=Bitposition-8;                          //Get shift value for CRC value

		                                        //Shift CRC value left with "shift" bits

          while(shift)
		  {
              for(i=5;i<0xFF;i--)
			     {  
                    if((crc[i-1]&0x80) && (i>0))        //Check if the MSB of the byte lower is "1"
			 {   		                //Yes - current byte + 1
                          temp=1;			//No - current byte + 0
                         }				//So that "1" can shift between bytes
                    else
			 {
                          temp=0;
                         }
                     crc[i]<<=1;
                     crc[i]+=temp;
                  } 

                  shift--;
             } 

           //Exclusive OR between pec and crc

           for(i=0;i<=5;i++)
		 {
                   pec[i]^=crc[i];
			 }  

		}while(Bitposition>8); 

	return pec[0];
}
 
//---------------------------------------

//--------------------------------------
//READ DATA FROM RAM/EEPROM
//Name: MEM_READ
//Function: Read the data from MLX90614 with given slave address and command
//Parameters: unsigned char slave_addR (slave address)
//            unsigned char cmdR	 (command)
//Return: unsigned long int Data
//--------------------------------------

unsigned long int MEM_READ(unsigned char slave_addR, unsigned char cmdR)
{
 	
	
	 unsigned char DataL;		                 //
	 unsigned char DataH;				 //Data packets from MLX90614
	 unsigned char PEC;				 //
	 unsigned long int Data;			 //Register value returned from MLX90614
	 unsigned char Pecreg;				 //Calculated PEC byte storage
         unsigned char arr[6];				 //Buffer for the sent bytes
	 unsigned char ack_nack;
	 unsigned char SLA;
												 
	 SLA=(slave_addR<<1);


   begin:		             

	 start_bit();                 			     //Send start bit
	 TX_byte(SLA);					     //Send slave address, write
	 if(slave_ack()==0)
	 {
	     stop_bit();
	     goto begin;
         }						     //Send command
         TX_byte(cmdR);
	 if(slave_ack()==0)
	 {
	     stop_bit();
	    goto begin;
     }
	 						     //Send Repeated start bit
	 start_bit(); 					     //Send slave address, read
	 TX_byte(SLA+1);
	 if(slave_ack()==0)
	 {
	     stop_bit();
	     goto begin;
	 }

	 DataL=RX_byte(0);					 //
								 //Read two bytes data
	 DataH=RX_byte(0);					 //

	 PEC=RX_byte(ack_nack);				         //Read PEC from MLX90614
	 if(ack_nack==1)					 //Master sends ack or nack
	                                              //This depends on the pec calculation, if the PEC is not correct, send nack and goto begin
	 {
	     stop_bit();
	     goto begin;
	 }							 //Send stop bit
	 stop_bit();
	 

	 arr[5]=(SLA);
         arr[4]=cmdR;
         arr[3]=(SLA+1);               
         arr[2]=DataL;
         arr[1]=DataH;
         arr[0]=0;                  
    											 
	 Pecreg=PEC_cal(arr,6);  				 //Calculate CRC 

	 if(PEC==Pecreg)
	    {
		  ack_nack=0;
		}

	 else
	    {
		 ack_nack=1;
	    }

	  Data=(DataH*256)+DataL;
      
	  return Data;

}

//--------------------------------------
 		
//--------------------------------------
//     WRITE DATA INTO EEPROM
//Name: EEPROM_WRITE
//Function: Write the data into MLX90614 with given slave address, command and corresponding data
//Parameters: unsigned char slave_addW (slave address)
//            unsigned char cmdW	 (command)
//            unsigned char DataL 
//            unsigned char DataH
//--------------------------------------

void EEPROM_WRITE(unsigned char slave_addW,unsigned char cmdW,unsigned char DataL,unsigned char DataH)
{

     unsigned char Pecreg;					//Calculated PEC byte storage
     unsigned char SLA;
     unsigned char arr[6];					//Buffer for the transmitted bytes

     SLA=(slave_addW<<1);
     
     arr[5]=0;
     arr[4]=SLA;
     arr[3]=cmdW;
     arr[2]=DataL;
     arr[1]=DataH;
     arr[0]=0;
     Pecreg=PEC_cal(arr,6);

   begin:
     start_bit();						//Send start bit
     TX_byte(SLA);						//Send slave address, write
     if(slave_ack()==0)								  
     {
         stop_bit();
	 goto begin;
     }
     TX_byte(cmdW);						//Send command
     if(slave_ack()==0)
     {
         stop_bit();
	 goto begin;
     }
     TX_byte(DataL);						//Send Low Data byte
     if(slave_ack()==0)
     {
         stop_bit();
	 goto begin;
     }
     TX_byte(DataH);						//Send High Data byte
     if(slave_ack()==0)
     {
         stop_bit();
	 goto begin;
     }
     TX_byte(Pecreg);						//Send PEC 
     if(slave_ack()==0)
     {
         stop_bit();
	 goto begin;
     }
     stop_bit();	            				//Send stop bit
     Delay(200);						//Wait 5ms
    
}
													
	 