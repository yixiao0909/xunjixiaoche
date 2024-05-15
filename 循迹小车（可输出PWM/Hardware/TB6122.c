#include "stm32f10x.h"  
#include "TB6122.h"            // Device header
#include "PWM.h"


#define TB6122_GPIO_CLK		RCC_APB2Periph_GPIOA
#define TB6122_GPIO			GPIOA
#define AIN2				GPIO_Pin_8			
#define AIN1				GPIO_Pin_9			
#define STBY				GPIO_Pin_10			
#define BIN1				GPIO_Pin_11		
#define BIN2				GPIO_Pin_12		
//AO1 AO2 ��������		BO1 BO2 �����ҵ��

void TB6122_Init(void)
{
	//��ʼ��GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = AIN1 | AIN2 | BIN1 |BIN2 | STBY;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//ʹ��TB6122
	GPIO_SetBits(TB6122_GPIO,STBY);
	
	GPIO_ResetBits(TB6122_GPIO,AIN1);
	GPIO_SetBits(TB6122_GPIO,AIN2);
	GPIO_ResetBits(TB6122_GPIO,BIN1);
	GPIO_SetBits(TB6122_GPIO,BIN2);

	
	//��ʼ��PWM
	PWM_Init();
	
	PWM_A_SetCompare(50);
	PWM_B_SetCompare(50);
}


/**
  * @brief	�ҵ����ת
  * @param  ת�٣�ռ�ձȣ�
  * @retval ��
  */

void TB6122_R_Forward(uint16_t Speed)
{
	//�����ٶ�
	PWM_B_SetCompare(Speed);
	
	//������ת
	GPIO_ResetBits(TB6122_GPIO, BIN1);
	GPIO_SetBits(TB6122_GPIO, BIN2);
}


/**
  * @brief	�ҵ����ת
  * @param  ת�٣�ռ�ձȣ�
  * @retval ��
  */

void TB6122_R_Backward(uint16_t Speed)
{
	//�����ٶ�
	PWM_B_SetCompare(Speed);
	
	//���÷�ת
	GPIO_SetBits(TB6122_GPIO, BIN1);
	GPIO_ResetBits(TB6122_GPIO, BIN2);
}



/**
  * @brief	������ת
  * @param  ת�٣�ռ�ձȣ�
  * @retval ��
  */

void TB6122_L_Forward(uint16_t Speed)
{
	//�����ٶ�
	PWM_A_SetCompare(Speed);
	
	//������ת
	GPIO_ResetBits(TB6122_GPIO, AIN1);
	GPIO_SetBits(TB6122_GPIO, AIN2);
}



/**
  * @brief	������ת
  * @param  ת�٣�ռ�ձȣ�
  * @retval ��
  */

void TB6122_L_Backward(uint16_t Speed)
{
	//�����ٶ�
	PWM_A_SetCompare(Speed);
	
	//���÷�ת
	GPIO_SetBits(TB6122_GPIO, AIN1);
	GPIO_ResetBits(TB6122_GPIO, AIN2);
}



/**
  * @brief	ֹͣ
  * @param  ��
  * @retval ��
  */

void TB6122_Stop(void)
{
	GPIO_ResetBits(TB6122_GPIO, AIN1);
	GPIO_ResetBits(TB6122_GPIO, AIN2);	
	GPIO_ResetBits(TB6122_GPIO, BIN1);
	GPIO_ResetBits(TB6122_GPIO, BIN2);	
}




