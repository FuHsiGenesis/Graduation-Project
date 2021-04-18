#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "oled.h"


int main(void)
{ 
 
	u8 t; // ´®¿Ú
	u8 len;	// ´®¿Ú
	u16 times=0; // ´®¿Ú
	int X_error=1000,Y_error=1000,Temp=0;//X_error¡¢Y_errorÎª¶æ»úË«×ÔÓÉ¶ÈÆ«²îÖµ£»TempÎª²âÁ¿ÌåÎÂ
  char Identity[10]=""; // ×Ö·û´®¶¨Òå

	//°´¼ü³õÊ¼»¯´úÂë¿é
  u8 key;             //±£´æ¼üÖµ
	delay_init(168);    //³õÊ¼»¯ÑÓÊ±º¯Êı
	KEY_Init();         //³õÊ¼»¯Óë°´¼üÁ¬½ÓµÄÓ²¼ş½Ó¿Ú
	//LED0=0;				  	//ÏÈµãÁÁºìµ	
	//LED_Init();				//³õÊ¼»¯LED¶Ë¿Ú 
	//BEEP_Init();      //³õÊ¼»¯·äÃùÆ÷¶Ë¿Ú
	
	//´®¿Ú³õÊ¼»¯´úÂë¿é
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(168);		//ÑÓÊ±³õÊ¼»¯ 
	uart_init(115200);	//´®¿Ú³õÊ¼»¯²¨ÌØÂÊÎª115200
	LED_Init();		  		//³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼ş½Ó¿Ú  
	
	//OLED³õÊ¼»¯
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÏµÍ³ÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init(168);     //³õÊ¼»¯ÑÓÊ±º¯Êı
	uart_init(115200);	//³õÊ¼»¯´®¿Ú²¨ÌØÂÊÎª115200
	LED_Init();					//³õÊ¼»¯LED
 	OLED_Init();				//³õÊ¼»¯OLED
  OLED_ShowString(0,0 ,"Temp:",12);  
	OLED_ShowString(0,16,"Identity:",12); 
	OLED_ShowString(0,32,"X_error:",12); 
	OLED_ShowString(0,48,"Y_error:",12); 
	OLED_Refresh_Gram();//¸üĞÂÏÔÊ¾µ½OLED	 
	while(1)
	{
		LED1=!LED1;
		delay_ms(200);
		if(USART_RX_STA&0x8000) // Èç¹ûÊÕµ½Êı¾İ
		{					   
			len=USART_RX_STA&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			for(t=0;t<len;t++)
			{
				LED0=!LED0;
				delay_ms(200);
				USART_SendData(USART1, USART_RX_BUF[t]);              //Ïò´®¿Ú1·¢ËÍÊı¾İ£¬USART_RX_BUF[]Îª´®¿Ú½ÓÊÕÊı¾İµÄ»º´æÇø£¬½ÓÊÕ»º³å,×î´ó200¸ö×Ö½Ú(¿âÀïÃæÓĞ¶¨Òå).
				OLED_ShowString(64,32,USART_RX_BUF,12);					      //µÚÈı¸öĞÎ²ÎµÄÊı¾İÀàĞÍÊÇ×Ö·û´®µÄµØÖ·£¬Ò²ÊÇ×Ö·û´®µÄÃû×Ö£¨²»´ø·½¿òºÅµÄ²¿·Ö£©   USART_RX_BUF
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//µÈ´ı·¢ËÍ½áÊø
			}
			USART_RX_STA=0;
		}
		OLED_Refresh_Gram();        //¸üĞÂÏÔÊ¾µ½OLED
		delay_ms(500);               //·şÎñÓÚLED,Ê¹µÃLEDµÄÁÁÃğ±ä»¯¿É¼ûLED0=!LED0;
	}
}

