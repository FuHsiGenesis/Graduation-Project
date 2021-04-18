
///////////////////////////////////////////////////////////////////////////
//此程序为stm32F4的IIC驱动0.96OLED （4线）
//说明：
//     --------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PC9
//              SDA   接PA8   
//     ---------------------------------------------------------
//ACTION
///////////////////////////////////////////////////////////////////
#include "sys.h"
#include "delay.h"
#include "oled.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "myiic.h"
int main(void)
{ 
/*********************初始化*************************/

	 delay_init(168);  //初始化延时函数  168
	 IIC_Init();       //IIC初始化
   OLED_Init();		   //初始化OLED
	
	while(1)
	{
		OLED_ShowCHinese(0,0,0);//中
		OLED_ShowCHinese(18,0,1);//景
		OLED_ShowCHinese(36,0,2);//园
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
	} 	    
}


