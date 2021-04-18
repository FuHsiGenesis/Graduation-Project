// convert decimal to hex 
#include "dec2hex.h"
#include "stdio.h"
//---------------------------------------
//Name: dec2hex
//Function: Converter dec code to hex code
//Parameters: float e (New emissivity)
//Return:     unsigned int c
//            c is the head address of c[4]
//---------------------------------------
unsigned int *dec2hex(float e)
{
    long int a=(e*65535)+0.5;
    int j,m=0,i=0;
    unsigned int b[16];
    unsigned int c[4],t;
    b[15]=0x0f;
    b[14]=0x0e;
	b[13]=0x0d;
	b[12]=0x0c;
	b[11]=0x0b;
	b[10]=0x0a;
	b[9]=0x09;
	b[8]=0x08;
	b[7]=0x07;
	b[6]=0x06;
	b[5]=0x05;
	b[4]=0x04;
	b[3]=0x03;
	b[2]=0x02;
	b[1]=0x01;				   
	b[0]=0;
	
	while(a!=0)
	{
	   j=a%16;				   //Modulus operator
           c[i++]=b[j];
	   a=a/16;				   //Remainder operator
	   m++;
	 }
	for(i=0;i<m/2;i++)
	{					   //
	    t=c[i];				   //Reverse order of array c[4]
	    c[i]=c[m-i-1];		           //
	    c[m-i-1]=t;
	}
        
	return c;				   //Return the head address of c[4]
}

    