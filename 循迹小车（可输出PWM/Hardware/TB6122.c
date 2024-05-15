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
//AO1 AO2 控制左电机		BO1 BO2 控制右电机

void TB6122_Init(void)
{
	//初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = AIN1 | AIN2 | BIN1 |BIN2 | STBY;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//使能TB6122
	GPIO_SetBits(TB6122_GPIO,STBY);
	
	GPIO_ResetBits(TB6122_GPIO,AIN1);
	GPIO_SetBits(TB6122_GPIO,AIN2);
	GPIO_ResetBits(TB6122_GPIO,BIN1);
	GPIO_SetBits(TB6122_GPIO,BIN2);

	
	//初始化PWM
	PWM_Init();
	
	PWM_A_SetCompare(50);
	PWM_B_SetCompare(50);
}


/**
  * @brief	右电机正转
  * @param  转速（占空比）
  * @retval 无
  */

void TB6122_R_Forward(uint16_t Speed)
{
	//设置速度
	PWM_B_SetCompare(Speed);
	
	//设置正转
	GPIO_ResetBits(TB6122_GPIO, BIN1);
	GPIO_SetBits(TB6122_GPIO, BIN2);
}


/**
  * @brief	右电机反转
  * @param  转速（占空比）
  * @retval 无
  */

void TB6122_R_Backward(uint16_t Speed)
{
	//设置速度
	PWM_B_SetCompare(Speed);
	
	//设置反转
	GPIO_SetBits(TB6122_GPIO, BIN1);
	GPIO_ResetBits(TB6122_GPIO, BIN2);
}



/**
  * @brief	左电机正转
  * @param  转速（占空比）
  * @retval 无
  */

void TB6122_L_Forward(uint16_t Speed)
{
	//设置速度
	PWM_A_SetCompare(Speed);
	
	//设置正转
	GPIO_ResetBits(TB6122_GPIO, AIN1);
	GPIO_SetBits(TB6122_GPIO, AIN2);
}



/**
  * @brief	左电机反转
  * @param  转速（占空比）
  * @retval 无
  */

void TB6122_L_Backward(uint16_t Speed)
{
	//设置速度
	PWM_A_SetCompare(Speed);
	
	//设置反转
	GPIO_SetBits(TB6122_GPIO, AIN1);
	GPIO_ResetBits(TB6122_GPIO, AIN2);
}



/**
  * @brief	停止
  * @param  无
  * @retval 无
  */

void TB6122_Stop(void)
{
	GPIO_ResetBits(TB6122_GPIO, AIN1);
	GPIO_ResetBits(TB6122_GPIO, AIN2);	
	GPIO_ResetBits(TB6122_GPIO, BIN1);
	GPIO_ResetBits(TB6122_GPIO, BIN2);	
}




