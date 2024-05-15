#include "stm32f10x.h"                  // Device header

uint16_t GraySensor_Value[5];
uint16_t GraySeneor_PastValue[5];	//上一时刻的传感器数值
int16_t GraySensor_Bias[5];			

void GraySensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//对应APB272MHZ6分频
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 5, ADC_SampleTime_13Cycles5);	
	
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式，ADC1和ADC2各自转换各自的
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//选用触发源（这里使用内部软件触发）
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//选择连续转换模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//选用扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 5;//选择通道数目
	ADC_Init(ADC1, &ADC_InitStructure);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//外设站点起始地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据宽度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//地址是否自增，不用因为ADC地址一定
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)GraySensor_Value;//存储器基地址
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//存储器数据宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器地址是否自增
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//指定外设站点是源端还是目的地
	DMA_InitStructure.DMA_BufferSize = 5;//传输几次
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//是否自动重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//是否用软件触发
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//指定通道优先级
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);//重置指定的ADC的校准寄存器
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1); //开始指定ADC的校准状态 
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发ADC转换
	
	//初始化上一时刻传感器值
	uint8_t i=0;
	for(i=0;i<5;i++)
	{
		GraySeneor_PastValue[i] = GraySensor_Value[i];
	}
	
}


/**
  * @brief	当前时刻与上一时刻的偏差读取
  * @param  无
  * @retval Bias数组
  */

void GraySensor_BiasRead(void)
{
	uint8_t i;
	

	//计算当前偏差
	for(i = 0; i < 5 ; i++)
	{
		GraySensor_Bias[i] = GraySensor_Value[i] - GraySeneor_PastValue[i];
	}
	for(i = 0 ; i < 5 ; i++)
	{
		GraySeneor_PastValue[i] = GraySensor_Value[i];
	}
}
