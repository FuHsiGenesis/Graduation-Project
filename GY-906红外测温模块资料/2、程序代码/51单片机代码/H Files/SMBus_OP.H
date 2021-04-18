#ifndef SMBUS_OP_H
#define SMBUS_OP_H

unsigned char PEC_cal(unsigned char pec[],int n);
unsigned long int MEM_READ(unsigned char slave_addR,unsigned char cmdR);
void EEPROM_WRITE(unsigned char slave_addW,unsigned char cmdW,unsigned char DataL,unsigned char DataH);



#endif
