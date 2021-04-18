//Show temperature on digital LEDs
#include <STC12C5410AD.H>
#include "digitalLED.h"	    

//---------------------------------------
//Define I/O port to control digital LEDs

sbit a0 = P1^7;		           //Assign P17 as a0 line
sbit a1 = P1^5;			   //Assign P15 as a1 line
sbit a2 = P1^6;			   //Assign P16 as a2 line
//---------------------------------------
//---------------------------------------
//Name: show
//Function: show the temperature on digital LEDs
//Parameters: unsigned int mahh[],int number
//Comments: show the numbers which stored in mahh[5]
//---------------------------------------
void show(unsigned int mahh[],int number)
{
unsigned char yanshicon;  
unsigned char weicon;
unsigned char code LED_tab[10]={ 

						        0xFC,       	        //0
                                                        0x60,       	        //1
                                                        0xDA,		        //2
						        0xF2,			//3
						        0x66,			//4
						        0xB6,			//5
						        0xBE,			//6
						        0xE0,			//7
						        0xFE,			//8
						        0xF6,			//9						       	     						        
};
 
  	P2=0;		                                //Turn-off display
	a0=1;
	a1=1;
	a2=1;
                         //a2,a1,a0 control the display position, when it is changed from 0-7
			 //the corresponding digital LEDs is from 1-8
	
	while(1)
	{	  	   	
		if(++yanshicon>200)		   //Execute once every 200 scan cycle
		{
		 	yanshicon=0;
		    if(++weicon>7) weicon=0;       //Rotate the display position within the range from 0-7	 	
			P2=0;                      //Turn-off display			
			switch(weicon)
			{
				case 0:		      //The content of first display position
				   P2=0;              //Turn-off display
				   a0=0;
				   a1=0;
				   a2=0;
				break;
				case 1:		      //The content of second display position
				   P2=0;              //Turn-off display
				   a0=1;
				   a1=0;
				   a2=0;
				break;
				case 2:		      //The content of third display position
				   P2=0;              //Turn-off display
				   a0=0;
				   a1=1;
				   a2=0;
				break;
				case 3:			    //The content of fourth display position
				   P2=LED_tab[mahh[4]];     //Display mahh[4]
				   a0=1;
				   a1=1;
				   a2=0;
				break;
			    case 4:			    //The content of fifth display position
				   P2=LED_tab[mahh[3]];     //Display mahh[3]
				   a0=0;
				   a1=0;
				   a2=1;
				break;
				case 5:			    //The content of sixth display position
				   P2=LED_tab[mahh[2]];     //Display mahh[2]
				   a0=1;
				   a1=0;
				   a2=1;
				break;
				case 6:			    //The content of seventh display position
				   P2=LED_tab[mahh[1]];     //Display mahh[1]
				   a0=0;
				   a1=1;
				   a2=1;
				break;
				case 7:			    //The content of eighth display position
				   P2=LED_tab[mahh[0]];     //Display mahh[0]
				   a0=1;
				   a1=1;
				   a2=1;
				break;
				default:

				break;
			}					
		}  	
	}
                    
}