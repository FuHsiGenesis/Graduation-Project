//---------------------------------------
//Function£ºChange SMBus address
//--------------------------------------
//--------------------------------------

{						
	 
         unsigned char slaveaddress;
         unsigned int DataLO;
         unsigned int DataHI;
         DataLO=0x5A;                                      //Load New slave address Low byte
         DataHI=0x00;                                      //Load New slave address High byte
	
         _SCL_IO;
         _SDA_OUTPUT;

         SCL=0;				        //
         Delay(1200);				//SMBus request£¬Switch PWM mode to SMBus mode(at least 2ms)
         SCL=1;				        //

	 slaveaddress=MEM_READ(0x00,0x2E);                 //Get the slave address which stored in EEPROM "0Eh"
	 
         EEPROM_WRITE(slaveaddress,0x2E,0x00,0x00);	   //Write 0x0000 into EEPROM "0Eh"
                                                           
	 EEPROM_WRITE(slaveaddress,0x2E,DataLO,DataHI);    //Write New slave address into EEPROM "0Eh"
                                                           //Need repower to active it
}
//---------------------------------------



