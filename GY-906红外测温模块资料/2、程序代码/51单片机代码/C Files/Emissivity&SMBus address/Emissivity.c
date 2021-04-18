//---------------------------------------
//Function£º Change the emissivity
//---------------------------------------
{
							
	 unsigned char slaveaddress;

	 unsigned int *Emv;                               //Define a pointer to point integral variable
	 unsigned int EmvLO;
	 unsigned int EmvHI;
	 float Emissivity=0.5;                            //Given a new Emissivity 
	 Emv=dec2hex(Emissivity);                         //Call subroutine (Converter dec code to hex code) return array head address

         EmvLO=(*(Emv+2)<<4)+*(Emv+3);                    //Load New emissivity Low byte 
         EmvHI=(*(Emv+0)<<4)+*(Emv+1);			  //Load New emissivity High byte                       

         _SCL_IO;
         _SDA_OUTPUT;
	
         SCL=0;				        //
         Delay(1200);				//SMBus request£¬Switch PWM mode to SMBus mode(at least 2ms)
         SCL=1;				        //																															
         
         slaveaddress=MEM_READ(0x00,0x2E);		    //Get the slave address which stored in EEPROM "0Eh"
  	 EEPROM_WRITE(slaveaddress,0x24,0x00,0x00);	    //Write 0x0000 into EEPROM "04h"
	                                                  
	 EEPROM_WRITE(slaveaddress,0x24,EmvLO,EmvHI);	    //Write New emissivity into EEPROM "04h"
						            //Need repower to active it

}
//--------------------------------------




