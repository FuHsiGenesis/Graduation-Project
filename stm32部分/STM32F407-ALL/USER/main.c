#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "oled.h"
#include "mlx90614.h"

int main(void)
{ 
 
	u8 t,n; // ´®¿Ú
	u8 len;	// ´®¿Ú
	u16 times=30; // ´®¿Ú
	int temp=30; // ÎÂ¶È²ÎÊı
	int X_error=1000,Y_error=1000,Temp=0;//X_error¡¢Y_errorÎª¶æ»úË«×ÔÓÉ¶ÈÆ«²îÖµ£»TempÎª²âÁ¿ÌåÎÂ
  char Identity[10]=""; // ×Ö·û´®¶¨Òå
  u8 UsartDisPlay[200];  // oledÉÏÃæÏÔÊ¾µÄ
	
	//°´¼ü³õÊ¼»¯´úÂë¿é
  u8 key;             //±£´æ¼üÖµ
	delay_init(168);    //³õÊ¼»¯ÑÓÊ±º¯Êı
	KEY_Init();         //³õÊ¼»¯Óë°´¼üÁ¬½ÓµÄÓ²¼ş½Ó¿Ú
	//LED0=0;				  	//ÏÈµãÁÁºìµ	
	//LED_Init();				//³õÊ¼»¯LED¶Ë¿Ú 
	//BEEP_Init();      //³õÊ¼»¯·äÃùÆ÷¶Ë¿Ú
	
	//MLX90614³õÊ¼»¯
	SMBus_Init();
	
	//´®¿Ú³õÊ¼»¯´úÂë¿é//Ö»ÓÃÀ´½ÓÊÕÉí·İĞÅÏ¢
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
  OLED_ShowString(0,8 ,"Temp:",16);  
	OLED_ShowString(0,40,"Identity:",16); 
//	OLED_ShowString(0,32,"X_error:",12); 
//	OLED_ShowString(0,48,"Y_error:",12); 
	OLED_Refresh_Gram();//¸üĞÂÏÔÊ¾µ½OLED	 
	while(1)
	{
		if(USART_RX_STA&0x8000) // Èç¹ûÊÕµ½Êı¾İ
		{					   
			len=USART_RX_STA&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			for(t=0;t<len;t++)
			{
				 if(USART_RX_BUF[t]==0xb3)     
					 if(USART_RX_BUF[t+1]==0xb3)
						  n=t+2;    
			}
		 OLED_Fill(64,0,123,63,0);   //²¿·ÖÇåÆÁ
     for(t=0;n<len;t++,n++)
				UsartDisPlay[t] = USART_RX_BUF[n];  
			OLED_ShowString(64,32,UsartDisPlay,12);
			USART_RX_STA=0;
		}
		OLED_Refresh_Gram();        //¸üĞÂÏÔÊ¾µ½OLED
		for(t=0;t<=100;t++)
			UsartDisPlay[t] ='\0';    //ÏÔÊ¾Êı×éÇå¿Õ
		temp=SMBus_ReadTemp(); 
		OLED_ShowNum(64,32,temp,3,24);
		
	}
}

