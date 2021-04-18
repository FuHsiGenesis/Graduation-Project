#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"


//ALIENTEK 探索者STM32F407开发板 实验12
//OLED显示实验-库函数版本 
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
int X_error=1000,Y_error=1000,Temp=0;//X_error、Y_error为舵机双自由度偏差值；Temp为测量体温
char *Identity="ZDS";
int main(void)
{ 
	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);     //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED
 	OLED_Init();				//初始化OLED
  OLED_ShowString(0,0 ,"Temp:",12);  
	OLED_ShowString(0,16,"Identity:",12); 
	OLED_ShowString(0,32,"X_error:",12); 
	OLED_ShowString(0,48,"Y_error:",12); 
	OLED_Refresh_Gram();//更新显示到OLED	 
	t=' ';  
	while(1) 
	{		
		OLED_ShowNum(64,32,X_error,4,12);//显示ASCII字符	 第五个空的数值决定的输出数值最大多少位，比如说现在该数值是4，则输出范围是（0~9999），超过该范围则会出输出异常；
		OLED_ShowNum(64,48,Y_error,4,12);	//显示ASCII字符的码值    
		OLED_ShowString(64,16,Identity,12); 
		OLED_Refresh_Gram();        //更新显示到OLED
		delay_ms(50);
		LED0=!LED0;
	}
}
