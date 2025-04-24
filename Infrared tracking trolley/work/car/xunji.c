#include "xunji.h"  
#include "stm32f10x.h"

void motor_gpio()//电机
{
		GPIO_InitTypeDef  GPIO_InitStructure; 
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
		GPIO_Init(GPIOB, &GPIO_InitStructure);			     
	

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	  //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
	


}

void xunji_gpio()//红外寻迹
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 ;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);		

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);		

	
}
void bizhang_gpio()//避障
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);		
		
	
	
}
void pwm()//pwm调速
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PWM左接D12-PA6-TIM3-CH1,右接D3-PA7-TIM3-CH2 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOA, &GPIO_InitStructure);//D5-PB1 D9-PB8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PWM左接D12-PA6-TIM3-CH1,右接D3-PA7-TIM3-CH2 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用输出 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOB, &GPIO_InitStructure);//D5-PB1 D9-PB8
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4, ENABLE);	  //使能定时器4\3时钟 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIOB时钟
	  

	
	TIM_TimeBaseStructure.TIM_Period =99;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =71;     //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数模式    
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //输出极性:TIM输出比较极性高
  TIM_OCInitStructure.TIM_Pulse=0;
	
	
	 
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);   //使能TIM4在CCR1上的预装载寄存器
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);   //使能TIM4在CCR3上的预装载寄存器

	
	TIM_Cmd(TIM3, ENABLE);   //使能TIM4
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

	
