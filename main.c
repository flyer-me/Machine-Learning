//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   : 
//  功能描述   : LCD SPI接口演示例程
//              说明:  
//              ----------------------------------------------------------------
//              GND     电源地
//              VCC     3.3v电源
//              SCLK      P1.5（SCL）
//              M0OSI      P1.6（SDA）
//              RES     P1.3
//              DC      P1.2
//              CS      不接  
//		BLK     不接 控制背光
//		MISO    P1.7
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "lcd.h"
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char


/******************************************************************************
      函数说明：端口初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void Initial_IO(void)
{
    P0DIR |= 0xff;     //P0定义为输出
    P1DIR |= 0xff;     //P1定义为输出
    
    //Master Mode 
    PERCFG |=0x02 ;          
    P1SEL|=0xE0;      //设置P1_5、P1_6、P1_7为外设I/O端口
    P1SEL &= ~0x10;   //P1_4设置为SSN
    P1DIR |= 0x10;    //SSN设置为输出
 
    //配置波特率
    U1GCR |= 0x11; //设置 BAUD_E为10
    U1BAUD |= 216; //设置BAUD_M为59 波特率设为38400
     
    //设为SPI Master模式
    U1CSR &= ~0xA0; // SPI MAster Mode
 
    //配置时钟极性、时钟相位、bit顺序
    U1GCR |= 0xC0;// CPOL = 1、CPHA = 1 设置时钟极性、相位
    U1GCR |= 0x20;//高位先传送
}


//******************************************************
int main(void)
 {	
	 u8 i,m;
	 float t=0;
        
         Initial_IO();  

	 Lcd_Init();			//初始化OLED  
	 LCD_Clear(WHITE);
	 BACK_COLOR=WHITE;

	 while(1)
	 {
		LCD_ShowChinese32x32(10,0,0,32,GBLUE);   //中
		LCD_ShowChinese32x32(45,0,1,32,GBLUE);   //景
		LCD_ShowChinese32x32(80,0,2,32,GBLUE);   //园
		LCD_ShowChinese32x32(115,0,3,32,GBLUE);  //电
		LCD_ShowChinese32x32(150,0,4,32,GBLUE);  //子
		LCD_ShowChinese32x32(10,75,0,16,RED);   //中
		LCD_ShowChinese32x32(45,75,1,16,RED);   //景
		LCD_ShowChinese32x32(80,75,2,16,RED);   //园
		LCD_ShowChinese32x32(115,75,3,16,RED);  //电
		LCD_ShowChinese32x32(150,75,4,16,RED);  //子
       		LCD_ShowString(10,35,"2.8 TFT SPI 240*320",RED);         
		
		LCD_ShowString(10,55,"LCD_W:",RED);	LCD_ShowNum(70,55,LCD_W,3,RED);
		LCD_ShowString(110,55,"LCD_H:",RED);LCD_ShowNum(160,55,LCD_H,3,RED);
		  
                for(i=0;i<2;i++)
		{
			for(m=0;m<6;m++)
			{
		           LCD_ShowPicture(0+m*40,120+i*40,39+m*40,159+i*40);
			}
		}
		
                while(1)
		{
                          LCD_ShowNum1(80,200,t,5,RED);
		          t+=0.01;
                }
          }
}
