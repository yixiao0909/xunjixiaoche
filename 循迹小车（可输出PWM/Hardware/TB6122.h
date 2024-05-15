#ifndef __TB6122_H
#define __TB6122_H

void TB6122_Init(void);
void TB6122_R_Forward(uint16_t Speed);
void TB6122_R_Backward(uint16_t Speed);
void TB6122_L_Forward(uint16_t Speed);
void TB6122_L_Backward(uint16_t Speed);
void TB6122_Stop(void);

#endif
