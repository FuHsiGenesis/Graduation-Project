#include "mlx90614.h"
#include "TM1637.h"
#include "systick.h"//延迟函数
#include "math.h"//ceil取整函数要用到
/****************************************************************************
* Function Name  : main
* Description    : Main program.

STM32F103C8T6 连接mlx90614红外测温模块，读取温度显示在TM1637数码管上

PB6 SCL; 
PB7 SDA;
PA3：数码管CLK;
PB10：数码管DIO
****************************************************************************/
int main()
{ 
	unsigned char chi1,chi2,ch3,ch4;//数码管第1234位
	int i,a,b;//定义整数
	double temp;//温度变量浮点数
	SMBus_Init();//初始化
	TM1637_Init();//数码管初始化
	TM1637_NixieTubeDisplay();//数码管显示，需要先运行一次。
	
	while(1)
	{
		temp=SMBus_ReadTemp();  //读取温度
		a = (int)(temp*10)%10;//小数点后一位
		b = (int)(temp*100)%10;//小数点后二位
		i=(int)temp;//取整 
		chi1=i/10%10;//十位
	  chi2=i/1%10;//个位
		ch3=a;
		ch4=b;
	  TM1637_mhDisplay(chi1,chi2,ch3,ch4);//用冒号区分整数小数
	  delay_ms (1000);
		/*
    i=ceil(temp); //向上取整，只显示整数值
		chi1=i/1000%10;/
		chi2=i/100%10;//
		ch3=i/10%10;//
		ch4=i/1%10;//
		TM1637_Display(chi1,chi2,ch3,ch4);
		
		*/		
	}			
}



