#include "stm32f10x.h"                  // Device header

uint16_t GraySensor_Value[5];
uint16_t GraySeneor_PastValue[5];	//��һʱ�̵Ĵ�������ֵ
int16_t GraySensor_Bias[5];			

void GraySensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//��ӦAPB272MHZ6��Ƶ
	
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
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ��ADC1��ADC2����ת�����Ե�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ѡ�ô���Դ������ʹ���ڲ����������
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ѡ������ת��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ѡ��ɨ��ģʽ
	ADC_InitStructure.ADC_NbrOfChannel = 5;//ѡ��ͨ����Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//����վ����ʼ��ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݿ��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//��ַ�Ƿ�������������ΪADC��ַһ��
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)GraySensor_Value;//�洢������ַ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݿ��
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢����ַ�Ƿ�����
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//ָ������վ����Դ�˻���Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = 5;//���伸��
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//�Ƿ��Զ���װ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�Ƿ����������
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//ָ��ͨ�����ȼ�
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);//����ָ����ADC��У׼�Ĵ���
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1); //��ʼָ��ADC��У׼״̬ 
	while (ADC_GetCalibrationStatus(ADC1) == SET);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//�������ADCת��
	
	//��ʼ����һʱ�̴�����ֵ
	uint8_t i=0;
	for(i=0;i<5;i++)
	{
		GraySeneor_PastValue[i] = GraySensor_Value[i];
	}
	
}


/**
  * @brief	��ǰʱ������һʱ�̵�ƫ���ȡ
  * @param  ��
  * @retval Bias����
  */

void GraySensor_BiasRead(void)
{
	uint8_t i;
	

	//���㵱ǰƫ��
	for(i = 0; i < 5 ; i++)
	{
		GraySensor_Bias[i] = GraySensor_Value[i] - GraySeneor_PastValue[i];
	}
	for(i = 0 ; i < 5 ; i++)
	{
		GraySeneor_PastValue[i] = GraySensor_Value[i];
	}
}
