//---------------------------------------
//Function change PWMCTRL configuration
//Set as PWM output mode
//---------------------------------------
{						
	 
         unsigned char slaveaddress;
         unsigned char PWMCTRLO;
         unsigned char PWMCTRHI;
         PWMCTRLO=0x07;                                     //Load New PWMCTRL Low byte(0x07 means select single PWM mode,enable PWM,and SDA pin as Push-Pull)
         PWMCTRHI=0x02;                                     //Load New PWMCTRL High byte(0x02 means PWM period is 1.024ms*1 and no PWM repetition)
	
         _SCL_IO;
         _SDA_OUTPUT;

         SCL=0;		//
	 Delay(1200);	//SMBus request time for switching PWM mode to SMBus mode (At least 2ms)
	 SCL=1;		//

	 slaveaddress=MEM_READ(0x00,0x2E);                  //Get the slave address which stored in EEPROM "0Eh"
	 
         EEPROM_WRITE(slaveaddress,0x22,0x00,0x00);         //Write 0x0000 into EEPROM "02h"	
                                                          
	 EEPROM_WRITE(slaveaddress,0x22,PWMCTRLO,PWMCTRHI); //Write New PWMCTRL into EEPROM "02h"

}

//---------------------------------------
//Function change PWMCTRL configuration
//Set as SMBus output mode
//---------------------------------------
{		
         unsigned char slaveaddress;
	 unsigned char PWMCTRLO;
         unsigned char PWMCTRHI;
         PWMCTRLO=0x01;                                     //Load New PWMCTRL Low byte(0x01 means select single PWM mode,disable PWM,and SDA pin as Open-Drain)
         PWMCTRHI=0x02;                                     //Load New PWMCTRL High byte(0x02 means PWM period is 1.024ms*1 and no PWM repetition)
						
         _SCL_IO;
         _SDA_OUTPUT;

	 SCL=1;
	 Delay(10);

	 SCL=0;		//
	 Delay(1200);	//SMBus request time for switching PWM mode to SMBus mode (At least 2ms)
	 SCL=1;		//
		
	 //After switching SMBus mode, change PWMCTRL configuration (SMBus), then after power off/on, the device will work in SMBus mode
		
         slaveaddress=MEM_READ(0x00,0x2E); 
	 EEPROM_WRITE(slaveaddress,0x22,0x00,0x00);         //Write 0x0000 into EEPROM "02h"	
                                                          
	 EEPROM_WRITE(slaveaddress,0x22,PWMCTRLO,PWMCTRHI); //Write New PWMCTRL into EEPROM "02h"


}


