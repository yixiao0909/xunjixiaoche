#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"
#include "OLED.h"
#include "GraySensor.h"
#include "TB6122.h"
#include "Motor.h"

uint8_t i;//����һ��16λ��ȫ�ֱ���Num

int main(void)
{
	
	OLED_Init();
	OLED_ShowString(1,1,"R2");
    OLED_ShowString(2,1,"R1");
	OLED_ShowString(3,1,"L1");
	OLED_ShowString(4,1,"L2");

////	PWM_Init();
//	TB6122_Init();
    GraySensor_Init();
//	Motor_Tracking();
//	Motor_TurnLeft();
//    Motor_TurnRight();
////	PWM_A_SetCompare(50);
////  PWM_B_SetCompare(50);
	while(1)
	{

		OLED_ShowNum(1, 5, R2_Value, 6);
		OLED_ShowNum(2, 5, R1_Value, 6);
		OLED_ShowNum(3, 5, L1_Value, 6);
		OLED_ShowNum(4, 5, L2_Value, 6);
		Delay_ms(800);

//		for (i = 0;i <= 100; i++)
//		{
//			PWM_A_SetCompare(i);//����CCR�Ĵ�����ֵ��������ֱ��ռ�ձȣ�ռ�ձ���CCR��ARR+1������
//			Delay_ms(10);
//		}
//		for (i = 0;i <= 100; i++)
//		{
//			Delay_ms(10);
//		}
//		
//		
//			for (i = 0;i <= 100; i++)
//		{
//			PWM_B_SetCompare(i);//����CCR�Ĵ�����ֵ��������ֱ��ռ�ձȣ�ռ�ձ���CCR��ARR+1������
//			Delay_ms(10);
//		}
//		for (i = 0;i <= 100; i++)
//		{
//			Delay_ms(10);
//		}
//	
		
	}
	
}
