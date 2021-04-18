#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "myiic.h"
//ALIENTEK 探索者STM32F407开发板 实验1
//跑马灯实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{ 
 int i;
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	  //OLED_GPIO_Init();
	IIC_Init();
    OLED_Init();
  /**下面是通过直接操作库函数的方式实现IO控制**/	
	
	while(1)
	{
	

				OLED_P8x16Str(0,0,"HelTec");//第一行 -- 8x16的显示单元显示ASCII码
				OLED_P8x16Str(0,2,"OLED Display");
				OLED_P8x16Str(0,4,"www.heltec.cn");
				OLED_P6x8Str(0,6,"cn.heltec@gmail.com");
				OLED_P6x8Str(0,7,"heltec.taobao.com");
				delay_ms(1000);
             
				OLED_CLS();
         
		
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0对应引脚GPIOF.9拉低，亮  等同LED0=0;
	GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1对应引脚GPIOF.10拉高，灭 等同LED1=1;
	delay_ms(500);  		   //延时300ms
	GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0对应引脚GPIOF.0拉高，灭  等同LED0=1;
	GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1对应引脚GPIOF.10拉低，亮 等同LED1=0;
	delay_ms(500);                     //延时300ms
	}
}






