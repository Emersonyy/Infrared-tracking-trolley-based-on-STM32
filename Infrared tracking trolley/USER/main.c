#include "stm32f10x.h"
#include "xunji.h"
#include "delay.h"


/*
			双轮驱动
*/
void Serial_Init(void)//蓝牙模块（没用到）
{
	GPIO_InitTypeDef GPIOInitStructure;
	USART_InitTypeDef  USARTInitStructure;
	NVIC_InitTypeDef N;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	

	GPIOInitStructure.GPIO_Mode =GPIO_Mode_AF_PP ;
	GPIOInitStructure.GPIO_Pin =GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	

	GPIOInitStructure.GPIO_Mode =GPIO_Mode_IPU ;
	GPIOInitStructure.GPIO_Pin =GPIO_Pin_3;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	
	
	
	

	USARTInitStructure.USART_BaudRate=9600;
	USARTInitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USARTInitStructure.USART_Mode =USART_Mode_Rx |USART_Mode_Tx;
	USARTInitStructure.USART_Parity =USART_Parity_No ;
	USARTInitStructure.USART_StopBits=USART_StopBits_1 ;
	USARTInitStructure.USART_WordLength=USART_WordLength_8b ;
	USART_Init(USART2,&USARTInitStructure);
	
	USART_ITConfig(USART2 ,USART_IT_RXNE ,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 );
	

	N.NVIC_IRQChannel =USART2_IRQn ;
	N.NVIC_IRQChannelCmd =ENABLE ;
	N.NVIC_IRQChannelPreemptionPriority =1;
	N.NVIC_IRQChannelSubPriority =1;
	NVIC_Init (&N);
	
	USART_Cmd(USART2 ,ENABLE );

}
u8 RX_Data;
u8 RX_Flag;
void USART2_IRQHandler(void)
{
	if(USART_GetFlagStatus (USART2,USART_IT_RXNE)==SET)
	{
		
		RX_Data =USART_ReceiveData (USART2 );
		
		RX_Flag =1;
		
		USART_ClearITPendingBit (USART2,USART_IT_RXNE);
		
		
	}
	
	
	
}

void 	LEFT()//快速左转
{
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare1(TIM4,70);
		
		IN1 = 0;
		IN2 = 0;
		
		IN3 = 0;
		IN4 = 1;
}

void RIGHT()//快速右转
{
		TIM_SetCompare1(TIM3,70);
		TIM_SetCompare1(TIM4,0);
								
		IN1 = 0;
		IN2 = 1;
									
		IN3 = 0;
		IN4 = 0;
	
}

void Self_Right()//自右转，左轮向前，右轮向后
{
	TIM_SetCompare1(TIM3,50);
	TIM_SetCompare1(TIM4,45);
	
	IN1 = 0;
	IN2 = 1;
									
	IN3 = 1;
	IN4 = 0;
}


void Self_Left()//自左转
{
	TIM_SetCompare1(TIM3,45);
	TIM_SetCompare1(TIM4,45);
	
	IN1 = 1;
	IN2 = 0;
									
	IN3 = 0;
	IN4 = 1;
}


//初始化小车状态
 void Init()
{
	TIM_SetCompare1(TIM3,25);
	TIM_SetCompare1(TIM4,25);
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}

int a=0;

int main(void)
 {	

		motor_gpio();   //引脚初始化
	  Serial_Init();
		xunji_gpio();
		pwm();           //PWM初始化
	 	bizhang_gpio();//避障初始化  
	 
		delay_init();
	  Init();	 //初始化小车状态
	 
	 while(1)
	 {
		 if(RX_Data ==0X47)//蓝牙
					{
						run();
					}
					if(RX_Data ==0X48)
					{
						left ();
					}
						if(RX_Data ==0X4A)
					{
						right ();
					}
					if(RX_Data ==0X4B)
					{
						back ();
					}
					if(RX_Data ==0X49)
					{
						stop();
					}
					if(RX_Data ==0X41)
					{
						Self_Left ();
					}
					if(RX_Data ==0X42)
					{
						Self_Right ();
					}
	 	if(LEFT_OUT==0&&RIGHT_OUT==0)//直路
			{
				a=0;
			}
			if(LEFT_OUT==0&&RIGHT_OUT==1)//右转大弯
			{
				a=1;
			}
			if(LEFT_OUT==1&&RIGHT_OUT==0)//左转大弯
			{
				a=2;
			}
			if(LEFT_IN==0&&LEFT_OUT==0&&RIGHT_OUT==0&&RIGHT_IN==0)//补充直路条件
			{
				a=3;
			}
			if((LEFT_IN==1||LEFT_OUT==1)&&RIGHT_OUT==0&&RIGHT_IN==0)//环路时快速左转
			{
				a=4;
			}
			if(LEFT_IN==0&&LEFT_OUT==0&&RIGHT_OUT==0&&RIGHT_IN==1)//环路时慢速右转
			{
				a=5;
			}
			if(LEFT_IN==1&&LEFT_OUT==0&&RIGHT_OUT==0&&RIGHT_IN==1)//刚入环路时的检测状态
			{
				a=6;
			}
			if(LEFT_IN==0&&LEFT_OUT==0&&RIGHT_OUT==1&&RIGHT_IN==1)//刚入直角弯时的检测状态
			{
				a=7;
			}
			if(LEFT_IN==1&&LEFT_OUT==1&&RIGHT_OUT==0&&RIGHT_IN==0)//补充条件4
			{
				a=8;
			}
			if(LEFT_IN==1&&LEFT_OUT==1&&RIGHT_OUT==1&&RIGHT_IN==1)//通过十字的条件
			{
				a=9;
			}

			
			switch(a)
			{
				case 0:run();   break;
				case 1:right(); break;
				case 2:left();  break;
				case 3:run();   break;
				case 4:LEFT();  break;
				case 5:right(); break;
				case 6:Self_Right();  delay_ms(30); back(); delay_ms(20); break;//环路弯1
				case 7:Self_Right();  delay_ms(30); back(); delay_ms(25); RIGHT(); break;//直角弯
				case 8:LEFT();  break;
				case 9:run(); delay_ms(15);  break;
			}
						if(RED_LEFT==0)//红外避障
						{
							right();
							delay_ms(45);
						}			
			
		}
			
	 
//RO、RI踩到黑色为1

			/*while(1)
			{
				 if(LEFT_OUT==0&&RIGHT_OUT==0)        //都没踩到黑线
					{
							 run();

					}
					
					else if(LEFT_OUT==0&&RIGHT_OUT==1)   //右边探头踩到黑线
					{
					
							right();
							
							if(RIGHT_IN==1&&LEFT_IN==1)
								{		

									do
									{
										Self_Right();
										delay_ms (30);
									}
									while(LEFT_OUT==0&&RIGHT_OUT==0);
								}
						
						
					}
					
					else if(LEFT_OUT==1&&RIGHT_OUT==0)  //左边探头踩到黑线
					{
					
							left();
						
					}
					
		      else if(LEFT_OUT==1&&RIGHT_OUT==1)   //都踩到黑线
					{				
							run();
					}
											//直角弯
					 
						
					else
					{
							run();
				
					}
				}*/
}

