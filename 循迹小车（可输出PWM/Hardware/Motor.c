#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "TB6122.h"
#include "GraySensor.h"
#include "Delay.h"


uint16_t state;		
// 0��ʾֱ��  1��ʾƫ�����ҽ���  2��ʾƫ���������  3��ʾ��ת��  4��ʾ��ת��  5��ʾͣ��

float sensor_bias;
int Speed_R = Speed_Start;
int Speed_L = Speed_Start;
int Speed_Low = 35;
int Speed_High = 20;
//float kp = 0.01;




/**
  * @brief	С����ת��
  * @param  ��
  * @retval ��
  */

void Motor_TurnLeft(void)
{
	Speed_L = Speed_Low;
	Speed_R = Speed_High;
	TB6122_R_Forward(Speed_R);
	TB6122_L_Forward(Speed_L);
	//Delay_ms(100);				//��С�����ܳ�ȥһ�ξ���
	while(L1_Value > 900);
	while(M_Value > 900);		//ת��
}



/**
  * @brief	С����ת��
  * @param  ��
  * @retval ��
  */

void Motor_TurnRight(void)
{
	Speed_L = Speed_High;
	Speed_R = Speed_Low;
	TB6122_R_Forward(Speed_R);
	TB6122_L_Forward(Speed_L);
//	Delay_ms(100);				//��С�����ܳ�ȥһ�ξ���
	while(R1_Value > 900);
	while(M_Value > 900);		//ת��
}



/**
  * @brief	С��ѭ��
  * @param  ��
  * @retval ��
  */


void Motor_Tracking(void)
{
	
	if(L1_Value < 1000 & M_Value < 1000 & R1_Value <1000)	//��⵽Բ��ͣ��
	{
		state = 5;
	}
	else if(R2_Value < 1000)	//��ת��
	{
		state = 4;
	}
	else if(L2_Value < 1000) //��ת��
	{
		state = 3;
	}
	else if(L1_Value < 1200)  //ƫ���������
	{
		state = 2;
		sensor_bias = 1200 - L1_Value;	
		
	}
	else if(R1_Value < 1200)  //ƫ�����ҽ���
	{
		state = 1;
		sensor_bias = 1200 - R1_Value;
	}
	else		//ֱ��
	{
		state = 0;
		sensor_bias = 0;
	}
	
	
	

	//״̬�ж�
	
	if(state == 0)
	{
		Speed_L = Speed_Start;
		Speed_R = Speed_Start;	

		TB6122_R_Forward(Speed_R);
		TB6122_L_Forward(Speed_L);
	}
	else if(state == 1)
	{
		Speed_L = Speed_Start + sensor_bias;
		Speed_R = Speed_Start - sensor_bias;
		
		TB6122_R_Forward(Speed_R);
		TB6122_L_Forward(Speed_L);
	}
	else if(state == 2)
	{
		Speed_L = Speed_Start - sensor_bias;
		Speed_R = Speed_Start + sensor_bias;
		TB6122_R_Forward(Speed_R);
		TB6122_L_Forward(Speed_L);
	}
	else if(state == 3)
	{
		Motor_TurnLeft();
	}
	else if(state == 4)
	{
		Motor_TurnRight();
	}
	else if(state == 5)
	{
		Delay_ms(250);	
		TB6122_Stop();
	}
	
}

