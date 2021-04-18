#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


//ALIENTEK Ì½Ë÷ÕßSTM32F407¿ª·¢°å ÊµÑé3
//°´¼üÊäÈëÊµÑé-¿âº¯Êı°æ±¾ 
//¼¼ÊõÖ§³Ö£ºwww.openedv.com
//ÌÔ±¦µêÆÌ£ºhttp://eboard.taobao.com
//¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾    
//×÷Õß£ºÕıµãÔ­×Ó @ALIENTEK 


int main(void)
{ 
 
  u8 key;           //±£´æ¼üÖµ
	delay_init(168);  //³õÊ¼»¯ÑÓÊ±º¯Êı
	LED_Init();				//³õÊ¼»¯LED¶Ë¿Ú 
	BEEP_Init();      //³õÊ¼»¯·äÃùÆ÷¶Ë¿Ú
	KEY_Init();       //³õÊ¼»¯Óë°´¼üÁ¬½ÓµÄÓ²¼ş½Ó¿Ú
	LED0=0;				  	//ÏÈµãÁÁºìµ
	while(1)
	{
		key=KEY_Scan(0);		//µÃµ½¼üÖµ
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//¿ØÖÆ·äÃùÆ÷
					BEEP=!BEEP;
					break;
				case KEY0_PRES:	//¿ØÖÆLED0·­×ª
					LED0=!LED0;
					break;
				case KEY1_PRES:	//¿ØÖÆLED1·­×ª	 
					LED1=!LED1;
					break;
				case KEY2_PRES:	//Í¬Ê±¿ØÖÆLED0,LED1·­×ª 
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}else delay_ms(10); 
	}

}
