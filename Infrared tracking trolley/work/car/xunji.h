
#ifndef __xunji_H
#define __xunji_H 	

#include "sys.h"  

#define      IN1         PBout(7)//D8-PB7改
#define      IN2         PBout(8)//D9-PB8改

#define      IN3         PAout(4)//D11-PA4改
#define      IN4         PBout(9)//D10-PB9改


#define      LEFT_OUT     PBin(0)//D4-PB0  
#define      RIGHT_OUT     PAin(7)//D3-PA7 
 
#define      LEFT_IN				PBin(1)//D5-PB1改 
#define      RIGHT_IN				PAin(8)//D6-PA8改
//PWM左接D12-PA6-TIM3-CH1,右接D3-PA7-TIM3-CH2
#define      RED_LEFT				  PAin(0) 

void run(void);
void left(void);
void right(void);
void back(void);;
void stop(void);
void motor_gpio(void);
void xunji_gpio(void);
void pwm(void);
void bizhang_gpio();
#endif


