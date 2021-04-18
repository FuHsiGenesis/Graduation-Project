#include "adc.h"
#include "delay.h"		 
#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ADC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
u16 ADC_Data[1][2]={0};

//ADC1
//PC5 --channel 15  VCOUT
//PB0 --channel 8   VIOUT
//初始化ADC			 DMA												   
void  Adc_dma_Init(void)
{    
  GPIO_InitTypeDef      GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	DMA_InitTypeDef       DMA_InitStructure; 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
	
	/************************************************************************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;    //通道选择
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&ADC1->DR; 	//DMA外设地址		 = & ADC1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_Data;		//DMA存储地址	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  //外设到存储器           
	DMA_InitStructure.DMA_BufferSize =1*2;   //数据传输量                      	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//16 bit data外设
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;        //存储器16 bit data  32??MCU?1?half-word?16 bits
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	
	
  /* GPIO初始化*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化  
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 


  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_2; //DMA
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描模式	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
  ADC_InitStructure.ADC_NbrOfConversion = 2;//转换3个通道
  ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	//设定指定的ADC通道组，设置转化顺序和采样时间
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_56Cycles );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15, 1, ADC_SampleTime_56Cycles );
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 2, ADC_SampleTime_56Cycles );
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
		/* Enable ADCx DMA */
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
   ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	DMA_Cmd(DMA2_Stream0, ENABLE);
}			  

//获得ADC值
//ch: @ref 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
u16 Get_Adc(u8 ADC_Channe1)   
{
	   u16 value;
	  
	   
		switch(ADC_Channe1)
		{
			case ADC_Channel_8: 
						value=ADC_Data[0][1];
						break;
			case ADC_Channel_15:  
						value=ADC_Data[0][0];
						break;
		}
		return value;
}

//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
	 


