#ifndef __GRAYSENSOR_H
#define __GRAYSENSOR_H

extern uint16_t GraySensor_Value[5];

void GraySensor_Init(void);
extern int16_t GraySensor_Bias[];					//��ǰʱ������һʱ�̵�ƫ��
void GraySensor_BiasRead(void);


//��������ģ����
#define R2_Value		GraySensor_Value[0]
#define R1_Value		GraySensor_Value[1]
#define M_Value		GraySensor_Value[2]
#define L1_Value		GraySensor_Value[3]
#define L2_Value		GraySensor_Value[4]


#define R2_Bias			GraySensor_Bias[0]
#define R1_Bias			GraySensor_Bias[1]
#define M_Bias			GraySensor_Bias[2]
#define L1_Bias			GraySensor_Bias[3]
#define L2_Bias			GraySensor_Bias[4]






#endif
