#include "xunji.h"  
#include "stm32f10x.h"

void motor_gpio()//���
{
		GPIO_InitTypeDef  GPIO_InitStructure; 
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
		GPIO_Init(GPIOB, &GPIO_InitStructure);			     
	

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
	


}

void xunji_gpio()//����Ѱ��
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);		

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);		

	
}
void bizhang_gpio()//����
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);		
		
	
	
}
void pwm()//pwm����
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PWM���D12-PA6-TIM3-CH1,�ҽ�D3-PA7-TIM3-CH2 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);//D5-PB1 D9-PB8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PWM���D12-PA6-TIM3-CH1,�ҽ�D3-PA7-TIM3-CH2 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOB, &GPIO_InitStructure);//D5-PB1 D9-PB8
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);	  //ʹ�ܶ�ʱ��4\3ʱ�� 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);   //ʹ��GPIOBʱ��
	  

	
	TIM_TimeBaseStructure.TIM_Period =99;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =71;     //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM���ϼ���ģʽ    
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //�������:TIM����Ƚϼ��Ը�
  TIM_OCInitStructure.TIM_Pulse=0;
	
	
	 
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);   //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);   //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���

	
	TIM_Cmd(TIM3, ENABLE);   //ʹ��TIM4
	TIM_Cmd(TIM4, ENABLE);
}
void run()
{

		TIM_SetCompare1(TIM3,40);  
   	TIM_SetCompare1(TIM4,40);
		IN1 = 0;
		IN2 = 1;
		
		IN3 = 0;
		IN4 = 1;
}
void back()
{
		TIM_SetCompare1(TIM3,43);
		TIM_SetCompare1(TIM4,43);
	
		IN1 = 1;
		IN2 = 0;
		
 
		IN3 = 1;
		IN4 = 0;
}
void right()
{
			TIM_SetCompare1(TIM3,45);
			TIM_SetCompare1(TIM4,0);
			IN1 = 0;
			IN2 = 1;
			
			IN3 = 0;
			IN4 = 0;

	
}
void left()
{
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare1(TIM4,45);
		
		IN1 = 0;
		IN2 = 0;
		
		IN3 = 0;
		IN4 = 1;
}

void stop()
{

		 IN1 = 0;
		 IN2 = 0;
		
		 IN3 = 0;
		 IN4 = 0;
}

	
