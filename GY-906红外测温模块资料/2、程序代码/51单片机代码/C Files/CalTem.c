//Calculate Temperature based on hex data
#include "CalTem.h"
//---------------------------------------
//Name: CALTEMP
//Function: Calculate Temperature
//Parameters: unsigned long int TEMP(Data read from MLX90614)
//Return:     unsigned int mah 
//            mah is the head address of mah[5]
//Comments: The equation for conversion Hex code to Temperature data is T=(Data)*0.02-273.15
//---------------------------------------
unsigned int *CALTEMP(unsigned long int TEMP)
{
      unsigned long int T;
	  unsigned int a,b;
      unsigned int A4,A5,A6,A7,A8;
	  unsigned int mah[5];
      T=TEMP*2;
    
      if(T>=27315)
            {
               T=T-27315;
               a=T/100;
               b=T-a*100;

               if(a>=100)
                   {
                      A4=a/100;
                      a=a%100;
                      A5=a/10;
                      a=a%10;
                      A6=a;
                    }
               else if(a>=10)
                    {
                      A4=0;
                      A5=a/10;
                      a=a%10;
                      A6=a;
                    }

               else 

                    {
                      A4=0;
                      A5=0;
                      A6=a;
                    }
               if(b>=10)
                    {
                      A7=b/10;
                      b=b%10;
                      A8=b;
                    }
                else
                    {
                      A7=0;
                      A8=b;
                    }
             }

         else
               {
                  T=27315-T;
                  a=T/100;
                  b=T-a*100;
                  A4=9;

                  if(a>=10)
                      {
                         A5=a/10;
                         a=a%10;
                         A6=a;
                      }
                  else 
                      {
                         A5=0;
                         A6=a;
                      }
                  if(b>=10)
                      {
                         A7=b/10;
                         b=b%10;
                         A8=b;
                      }
                  else
                      {
                         A7=0;
                         A8=b;
                      }
                }
		
                mah[4]=A4;
		mah[3]=A5;
		mah[2]=A6;
		mah[1]=A7;
		mah[0]=A8;
 
  return mah;

}