#ifndef __MOTOR_H
#define __MOTOR_H


#define Speed_Start		20


extern int Speed_R;	//右轮理论速度
extern int Speed_L;	//左轮理论速度
	

void Motor_Tracking(void);
void Motor_TurnLeft(void);
void Motor_TurnRight(void);
//void Motor_Task(void);


#endif
