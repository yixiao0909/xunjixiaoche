#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "TB6122.h"
#include "GraySensor.h"
#include "Delay.h"


uint16_t state;		
// 0表示直行  1表示偏左向右矫正  2表示偏右向左矫正  3表示左转弯  4表示右转弯  5表示停车

float sensor_bias;
int Speed_R = Speed_Start;
int Speed_L = Speed_Start;
int Speed_Low = 35;
int Speed_High = 20;
//float kp = 0.01;




/**
  * @brief	小车左转弯
  * @param  无
  * @retval 无
  */

void Motor_TurnLeft(void)
{
	Speed_L = Speed_Low;
	Speed_R = Speed_High;
	TB6122_R_Forward(Speed_R);
	TB6122_L_Forward(Speed_L);
	//Delay_ms(100);				//让小车先跑出去一段距离
	while(L1_Value > 900);
	while(M_Value > 900);		//转弯
}



/**
  * @brief	小车右转弯
  * @param  无
  * @retval 无
  */

void Motor_TurnRight(void)
{
	Speed_L = Speed_High;
	Speed_R = Speed_Low;
	TB6122_R_Forward(Speed_R);
	TB6122_L_Forward(Speed_L);
//	Delay_ms(100);				//让小车先跑出去一段距离
	while(R1_Value > 900);
	while(M_Value > 900);		//转弯
}



/**
  * @brief	小车循迹
  * @param  无
  * @retval 无
  */


void Motor_Tracking(void)
{
	
	if(L1_Value < 1000 & M_Value < 1000 & R1_Value <1000)	//检测到圆点停车
	{
		state = 5;
	}
	else if(R2_Value < 1000)	//右转弯
	{
		state = 4;
	}
	else if(L2_Value < 1000) //左转弯
	{
		state = 3;
	}
	else if(L1_Value < 1200)  //偏右向左矫正
	{
		state = 2;
		sensor_bias = 1200 - L1_Value;	
		
	}
	else if(R1_Value < 1200)  //偏左向右矫正
	{
		state = 1;
		sensor_bias = 1200 - R1_Value;
	}
	else		//直行
	{
		state = 0;
		sensor_bias = 0;
	}
	
	
	

	//状态判断
	
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

