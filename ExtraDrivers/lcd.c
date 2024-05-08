#include "LCD.h"
#include "Hzk16song.h"
#include "font.h"
#include "stm32f4xx_hal_rcc_ex.h"


//	LCD结构体，默认为横屏
lcd_dev lcddev;

/**********************************************************************************************************
函数名称：液晶us延时函数
输入参数：时间
输出参数：无
**********************************************************************************************************/
void LCD_delayus(unsigned int time)
{  
   unsigned short i=0; 
    
   while(time--)
   {
      i = 8;  
      while(i--) ;    
   }
}

/**********************************************************************************************************
函数名称：LCD延时函数（大约1ms）
输入参数：时间
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_delayms(unsigned int cnt)
{
	volatile unsigned int dl;
    
	while(cnt--)
	{
		for(dl = 0; dl < 20000; dl++);
	}
}


/**********************************************************************************************************
函数名称：写寄存器函数
输入参数：寄存器值
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_WR_REG(u16 regval)
{
    LCD->LCD_REG = regval; //写入要写的寄存器序号
}

/**********************************************************************************************************
函数名称：写数据函数
输入参数：数据
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_WR_DATA(u16 data)
{
    LCD->LCD_RAM = data;
}


/**********************************************************************************************************
函数名称：读数据函数
输入参数：无
输出参数：无
函数返回：读到的值
**********************************************************************************************************/
u16 LCD_RD_DATA(void)
{
    vu16 ram;															//	防止被优化
	
    ram = LCD->LCD_RAM;
    
	return ram;
}


/**********************************************************************************************************
函数名称：写寄存器数据函数
输入参数：寄存器值、数据
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{
    LCD->LCD_REG = LCD_Reg;												//	写入要写的寄存器序号
    LCD->LCD_RAM = LCD_RegValue;										//	写入数据
}

/**********************************************************************************************************
函数名称：读寄存器数据函数
输入参数：寄存器值
输出参数：无
函数返回：读到的数据
**********************************************************************************************************/
u16 LCD_ReadReg(u16 LCD_Reg)
{
    LCD_WR_REG(LCD_Reg);												//	写入要读的寄存器序号
    LCD_delayus(5);
	
    return LCD_RD_DATA();												//	返回读到的值
}

/**********************************************************************************************************
函数名称：写GRAM命令函数
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
    LCD->LCD_REG = lcddev.wramcmd;
}


/**********************************************************************************************************
函数名称：写RAM数据函数
输入参数：颜色值
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{
    LCD->LCD_RAM = RGB_Code;											//	写十六位GRAM
}


///**********************************************************************************************************
//函数名称：RGB转换函数
//输入参数：GBR格式的颜色值
//输出参数：无
//函数返回：RGB格式的颜色值
//函数说明：从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//**********************************************************************************************************/
//u16 LCD_BGR2RGB(u16 c)
//{
//    u16  r, g, b, rgb;
//	
//    b = (c >> 0) & 0x1f;
//    g = (c >> 5) & 0x3f;
//    r = (c >> 11) & 0x1f;
//    
//	rgb = (b << 11) + (g << 5) + (r << 0);
//    
//	return(rgb);
//}


///**********************************************************************************************************
//函数名称：延时函数
//输入参数：时间
//输出参数：无
//函数返回：无
//**********************************************************************************************************/
//void opt_delay(u8 i)
//{
//    while(i--);
//}


///**********************************************************************************************************
//函数名称：读取个某点的颜色值
//输入参数：x,y:坐标
//输出参数：无
//函数返回：此点的颜色
//**********************************************************************************************************/
//u16 LCD_ReadPoint(u16 x, u16 y)
//{
//    u16 r = 0;
//	
//    if(x >= lcddev.width || y >= lcddev.height)
//    {
//        return 0;														//	超过了范围,直接返回
//    }
//    
//    LCD_SetCursor(x, y);
//    
//    LCD_WR_REG(0X2E); 												    //	发送读GRAM指令
//    
//    r = LCD_RD_DATA();													//	dummy Read
//    
//    return r;
//}


/**********************************************************************************************************
函数名称：设置光标位置
输入参数：Xpos:横坐标
		  Ypos:纵坐标
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    if(lcddev.id == 0X5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(Xpos & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(Ypos >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(Ypos & 0XFF);
    }
}

/**********************************************************************************************************
函数名称：设置LCD的自动扫描方向
输入参数：方向
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_Scan_Dir(u8 dir)
{
    u16 regval = 0;
    u16 dirreg = 0;

    if(lcddev.id == 0X5510)                                             // 5510,特殊处理
    {
        switch(dir)
        {
        case    L2R_U2D://从左到右,从上到下
                regval |= (0 << 7) | (0 << 6) | (0 << 5);
                break;
        
        case    L2R_D2U://从左到右,从下到上
                regval |= (1 << 7) | (0 << 6) | (0 << 5);
                break;
        
        case    R2L_U2D://从右到左,从上到下
                regval |= (0 << 7) | (1 << 6) | (0 << 5);
                break;
        
        case    R2L_D2U://从右到左,从下到上
                regval |= (1 << 7) | (1 << 6) | (0 << 5);
                break;
        
        case    U2D_L2R://从上到下,从左到右
                regval |= (0 << 7) | (0 << 6) | (1 << 5);
                break;
        
        case    U2D_R2L://从上到下,从右到左
                regval |= (0 << 7) | (1 << 6) | (1 << 5);
                break;
        
        case    D2U_L2R://从下到上,从左到右
                regval |= (1 << 7) | (0 << 6) | (1 << 5);
                break;
        
        case    D2U_R2L://从下到上,从右到左
                regval |= (1 << 7) | (1 << 6) | (1 << 5);
                break;
        }

        if(lcddev.id == 0X5510)
        {
            dirreg = 0X3600;
        }
        if(lcddev.id != 0X5510)
        {
            regval |= 0X08;                                             // 5510不需要BGR
        }

        LCD_WriteReg(dirreg, regval);

        if(lcddev.id == 0X5510)
        {
            LCD_WR_REG(lcddev.setxcmd);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setxcmd + 1);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setxcmd + 2);
            LCD_WR_DATA((lcddev.width - 1) >> 8);
            LCD_WR_REG(lcddev.setxcmd + 3);
            LCD_WR_DATA((lcddev.width - 1) & 0XFF);
            LCD_WR_REG(lcddev.setycmd);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setycmd + 1);
            LCD_WR_DATA(0);
            LCD_WR_REG(lcddev.setycmd + 2);
            LCD_WR_DATA((lcddev.height - 1) >> 8);
            LCD_WR_REG(lcddev.setycmd + 3);
            LCD_WR_DATA((lcddev.height - 1) & 0XFF);
        }
    }
}

/**********************************************************************************************************
函数名称：画点
输入参数：x,y	坐标
		  color 颜色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_DrawPoint(u16 x, u16 y, u16 color)
{
    LCD_SetCursor(x, y);												//	设置光标位置
    LCD_WriteRAM_Prepare();												//	开始写入GRAM
    LCD->LCD_RAM = color;
}

/**********************************************************************************************************
函数名称：快速画点
输入参数：x,y:	坐标
		  color 颜色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_Fast_DrawPoint(u16 x, u16 y, u16 color)
{    
    if(lcddev.id == 0X5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(x >> 8);
        LCD_WR_REG(lcddev.setxcmd + 1);
        LCD_WR_DATA(x & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(y >> 8);
        LCD_WR_REG(lcddev.setycmd + 1);
        LCD_WR_DATA(y & 0XFF);
    }
    
    LCD->LCD_REG = lcddev.wramcmd;
    LCD->LCD_RAM = color;
}

//设置LCD显示方向
//dir:0,竖屏；1,横屏
/**********************************************************************************************************
函数名称：设置LCD显示方向
输入参数：dir:0,竖屏；1,横屏
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_Display_Dir(u8 dir)
{
    if(dir == 0)														//	竖屏
    {
        lcddev.dir = 0;	                                                // 竖屏
        lcddev.width = 240;
        lcddev.height = 320;

        if(lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width = 480;
            lcddev.height = 800;
        }
    }
    else 																//	横屏
    {
        lcddev.dir = 1;	                                                // 横屏
        lcddev.width = 320;
        lcddev.height = 240;

        if(lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0X2C00;
            lcddev.setxcmd = 0X2A00;
            lcddev.setycmd = 0X2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        }
    }
    
    LCD_Scan_Dir(DFT_SCAN_DIR);											//	默认扫描方向
}

///**********************************************************************************************************
//函数名称：设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//输入参数：sx,sy:窗口起始坐标(左上角)width,height:窗口宽度和高度,必须大于0!!
//输出参数：无
//函数返回：无
//**********************************************************************************************************/
//void LCD_Set_Window(u16 sx, u16 sy, u16 width, u16 height)
//{
//    u16 twidth, theight;
//	
//    twidth = sx + width - 1;
//    theight = sy + height - 1;
//	
//    LCD_WR_REG(lcddev.setxcmd);
//    LCD_WR_DATA(sx >> 8);
//    LCD_WR_DATA(sx & 0XFF);
//    LCD_WR_DATA(twidth >> 8);
//    LCD_WR_DATA(twidth & 0XFF);
//    LCD_WR_REG(lcddev.setycmd);
//    LCD_WR_DATA(sy >> 8);
//    LCD_WR_DATA(sy & 0XFF);
//    LCD_WR_DATA(theight >> 8);
//    LCD_WR_DATA(theight & 0XFF);
//}

/**********************************************************************************************************
函数名称：初始化lcd
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_Init(void)
{
    vu32 i = 0;


    //FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  						// 	使能BANK1
    __HAL_RCC_FSMC_CLK_ENABLE();
    LCD_delayms(100); 												    // 	delay 50 ms
    
    LCD_WR_REG(0XDA00);
    lcddev.id = LCD_RD_DATA();		//读回0X00
    LCD_WR_REG(0XDB00);
    lcddev.id = LCD_RD_DATA();		//读回0X80
    lcddev.id <<= 8;
    LCD_WR_REG(0XDC00);
    lcddev.id |= LCD_RD_DATA();		//读回0X00
    if(lcddev.id == 0x8000)
    {
        lcddev.id = 0x5510; //NT35510读回的ID是8000H,为方便区分,我们强制设置为5510
    }
    
    if(lcddev.id == 0X5510) //如果是这几个IC,则设置WR时序为最快
    {
        //重新配置写时序控制寄存器的时序
        FSMC_Bank1E->BWTR[6] &= ~(0XF << 0); //地址建立时间(ADDSET)清零
        FSMC_Bank1E->BWTR[6] &= ~(0XF << 8); //数据保存时间清零
        FSMC_Bank1E->BWTR[6] |= 3 << 0;		//地址建立时间(ADDSET)为3个HCLK =18ns
        FSMC_Bank1E->BWTR[6] |= 2 << 8; 	//数据保存时间(DATAST)为6ns*3个HCLK=18ns
    }
    
    if(lcddev.id == 0x5510)
    {
        LCD_WriteReg(0xF000, 0x55);
        LCD_WriteReg(0xF001, 0xAA);
        LCD_WriteReg(0xF002, 0x52);
        LCD_WriteReg(0xF003, 0x08);
        LCD_WriteReg(0xF004, 0x01);
        //AVDD Set AVDD 5.2V
        LCD_WriteReg(0xB000, 0x0D);
        LCD_WriteReg(0xB001, 0x0D);
        LCD_WriteReg(0xB002, 0x0D);
        //AVDD ratio
        LCD_WriteReg(0xB600, 0x34);
        LCD_WriteReg(0xB601, 0x34);
        LCD_WriteReg(0xB602, 0x34);
        //AVEE -5.2V
        LCD_WriteReg(0xB100, 0x0D);
        LCD_WriteReg(0xB101, 0x0D);
        LCD_WriteReg(0xB102, 0x0D);
        //AVEE ratio
        LCD_WriteReg(0xB700, 0x34);
        LCD_WriteReg(0xB701, 0x34);
        LCD_WriteReg(0xB702, 0x34);
        //VCL -2.5V
        LCD_WriteReg(0xB200, 0x00);
        LCD_WriteReg(0xB201, 0x00);
        LCD_WriteReg(0xB202, 0x00);
        //VCL ratio
        LCD_WriteReg(0xB800, 0x24);
        LCD_WriteReg(0xB801, 0x24);
        LCD_WriteReg(0xB802, 0x24);
        //VGH 15V (Free pump)
        LCD_WriteReg(0xBF00, 0x01);
        LCD_WriteReg(0xB300, 0x0F);
        LCD_WriteReg(0xB301, 0x0F);
        LCD_WriteReg(0xB302, 0x0F);
        //VGH ratio
        LCD_WriteReg(0xB900, 0x34);
        LCD_WriteReg(0xB901, 0x34);
        LCD_WriteReg(0xB902, 0x34);
        //VGL_REG -10V
        LCD_WriteReg(0xB500, 0x08);
        LCD_WriteReg(0xB501, 0x08);
        LCD_WriteReg(0xB502, 0x08);
        LCD_WriteReg(0xC200, 0x03);
        //VGLX ratio
        LCD_WriteReg(0xBA00, 0x24);
        LCD_WriteReg(0xBA01, 0x24);
        LCD_WriteReg(0xBA02, 0x24);
        //VGMP/VGSP 4.5V/0V
        LCD_WriteReg(0xBC00, 0x00);
        LCD_WriteReg(0xBC01, 0x78);
        LCD_WriteReg(0xBC02, 0x00);
        //VGMN/VGSN -4.5V/0V
        LCD_WriteReg(0xBD00, 0x00);
        LCD_WriteReg(0xBD01, 0x78);
        LCD_WriteReg(0xBD02, 0x00);
        //VCOM
        LCD_WriteReg(0xBE00, 0x00);
        LCD_WriteReg(0xBE01, 0x64);
        //Gamma Setting
        LCD_WriteReg(0xD100, 0x00);
        LCD_WriteReg(0xD101, 0x33);
        LCD_WriteReg(0xD102, 0x00);
        LCD_WriteReg(0xD103, 0x34);
        LCD_WriteReg(0xD104, 0x00);
        LCD_WriteReg(0xD105, 0x3A);
        LCD_WriteReg(0xD106, 0x00);
        LCD_WriteReg(0xD107, 0x4A);
        LCD_WriteReg(0xD108, 0x00);
        LCD_WriteReg(0xD109, 0x5C);
        LCD_WriteReg(0xD10A, 0x00);
        LCD_WriteReg(0xD10B, 0x81);
        LCD_WriteReg(0xD10C, 0x00);
        LCD_WriteReg(0xD10D, 0xA6);
        LCD_WriteReg(0xD10E, 0x00);
        LCD_WriteReg(0xD10F, 0xE5);
        LCD_WriteReg(0xD110, 0x01);
        LCD_WriteReg(0xD111, 0x13);
        LCD_WriteReg(0xD112, 0x01);
        LCD_WriteReg(0xD113, 0x54);
        LCD_WriteReg(0xD114, 0x01);
        LCD_WriteReg(0xD115, 0x82);
        LCD_WriteReg(0xD116, 0x01);
        LCD_WriteReg(0xD117, 0xCA);
        LCD_WriteReg(0xD118, 0x02);
        LCD_WriteReg(0xD119, 0x00);
        LCD_WriteReg(0xD11A, 0x02);
        LCD_WriteReg(0xD11B, 0x01);
        LCD_WriteReg(0xD11C, 0x02);
        LCD_WriteReg(0xD11D, 0x34);
        LCD_WriteReg(0xD11E, 0x02);
        LCD_WriteReg(0xD11F, 0x67);
        LCD_WriteReg(0xD120, 0x02);
        LCD_WriteReg(0xD121, 0x84);
        LCD_WriteReg(0xD122, 0x02);
        LCD_WriteReg(0xD123, 0xA4);
        LCD_WriteReg(0xD124, 0x02);
        LCD_WriteReg(0xD125, 0xB7);
        LCD_WriteReg(0xD126, 0x02);
        LCD_WriteReg(0xD127, 0xCF);
        LCD_WriteReg(0xD128, 0x02);
        LCD_WriteReg(0xD129, 0xDE);
        LCD_WriteReg(0xD12A, 0x02);
        LCD_WriteReg(0xD12B, 0xF2);
        LCD_WriteReg(0xD12C, 0x02);
        LCD_WriteReg(0xD12D, 0xFE);
        LCD_WriteReg(0xD12E, 0x03);
        LCD_WriteReg(0xD12F, 0x10);
        LCD_WriteReg(0xD130, 0x03);
        LCD_WriteReg(0xD131, 0x33);
        LCD_WriteReg(0xD132, 0x03);
        LCD_WriteReg(0xD133, 0x6D);
        LCD_WriteReg(0xD200, 0x00);
        LCD_WriteReg(0xD201, 0x33);
        LCD_WriteReg(0xD202, 0x00);
        LCD_WriteReg(0xD203, 0x34);
        LCD_WriteReg(0xD204, 0x00);
        LCD_WriteReg(0xD205, 0x3A);
        LCD_WriteReg(0xD206, 0x00);
        LCD_WriteReg(0xD207, 0x4A);
        LCD_WriteReg(0xD208, 0x00);
        LCD_WriteReg(0xD209, 0x5C);
        LCD_WriteReg(0xD20A, 0x00);

        LCD_WriteReg(0xD20B, 0x81);
        LCD_WriteReg(0xD20C, 0x00);
        LCD_WriteReg(0xD20D, 0xA6);
        LCD_WriteReg(0xD20E, 0x00);
        LCD_WriteReg(0xD20F, 0xE5);
        LCD_WriteReg(0xD210, 0x01);
        LCD_WriteReg(0xD211, 0x13);
        LCD_WriteReg(0xD212, 0x01);
        LCD_WriteReg(0xD213, 0x54);
        LCD_WriteReg(0xD214, 0x01);
        LCD_WriteReg(0xD215, 0x82);
        LCD_WriteReg(0xD216, 0x01);
        LCD_WriteReg(0xD217, 0xCA);
        LCD_WriteReg(0xD218, 0x02);
        LCD_WriteReg(0xD219, 0x00);
        LCD_WriteReg(0xD21A, 0x02);
        LCD_WriteReg(0xD21B, 0x01);
        LCD_WriteReg(0xD21C, 0x02);
        LCD_WriteReg(0xD21D, 0x34);
        LCD_WriteReg(0xD21E, 0x02);
        LCD_WriteReg(0xD21F, 0x67);
        LCD_WriteReg(0xD220, 0x02);
        LCD_WriteReg(0xD221, 0x84);
        LCD_WriteReg(0xD222, 0x02);
        LCD_WriteReg(0xD223, 0xA4);
        LCD_WriteReg(0xD224, 0x02);
        LCD_WriteReg(0xD225, 0xB7);
        LCD_WriteReg(0xD226, 0x02);
        LCD_WriteReg(0xD227, 0xCF);
        LCD_WriteReg(0xD228, 0x02);
        LCD_WriteReg(0xD229, 0xDE);
        LCD_WriteReg(0xD22A, 0x02);
        LCD_WriteReg(0xD22B, 0xF2);
        LCD_WriteReg(0xD22C, 0x02);
        LCD_WriteReg(0xD22D, 0xFE);
        LCD_WriteReg(0xD22E, 0x03);
        LCD_WriteReg(0xD22F, 0x10);
        LCD_WriteReg(0xD230, 0x03);
        LCD_WriteReg(0xD231, 0x33);
        LCD_WriteReg(0xD232, 0x03);
        LCD_WriteReg(0xD233, 0x6D);
        LCD_WriteReg(0xD300, 0x00);
        LCD_WriteReg(0xD301, 0x33);
        LCD_WriteReg(0xD302, 0x00);
        LCD_WriteReg(0xD303, 0x34);
        LCD_WriteReg(0xD304, 0x00);
        LCD_WriteReg(0xD305, 0x3A);
        LCD_WriteReg(0xD306, 0x00);
        LCD_WriteReg(0xD307, 0x4A);
        LCD_WriteReg(0xD308, 0x00);
        LCD_WriteReg(0xD309, 0x5C);
        LCD_WriteReg(0xD30A, 0x00);

        LCD_WriteReg(0xD30B, 0x81);
        LCD_WriteReg(0xD30C, 0x00);
        LCD_WriteReg(0xD30D, 0xA6);
        LCD_WriteReg(0xD30E, 0x00);
        LCD_WriteReg(0xD30F, 0xE5);
        LCD_WriteReg(0xD310, 0x01);
        LCD_WriteReg(0xD311, 0x13);
        LCD_WriteReg(0xD312, 0x01);
        LCD_WriteReg(0xD313, 0x54);
        LCD_WriteReg(0xD314, 0x01);
        LCD_WriteReg(0xD315, 0x82);
        LCD_WriteReg(0xD316, 0x01);
        LCD_WriteReg(0xD317, 0xCA);
        LCD_WriteReg(0xD318, 0x02);
        LCD_WriteReg(0xD319, 0x00);
        LCD_WriteReg(0xD31A, 0x02);
        LCD_WriteReg(0xD31B, 0x01);
        LCD_WriteReg(0xD31C, 0x02);
        LCD_WriteReg(0xD31D, 0x34);
        LCD_WriteReg(0xD31E, 0x02);
        LCD_WriteReg(0xD31F, 0x67);
        LCD_WriteReg(0xD320, 0x02);
        LCD_WriteReg(0xD321, 0x84);
        LCD_WriteReg(0xD322, 0x02);
        LCD_WriteReg(0xD323, 0xA4);
        LCD_WriteReg(0xD324, 0x02);
        LCD_WriteReg(0xD325, 0xB7);
        LCD_WriteReg(0xD326, 0x02);
        LCD_WriteReg(0xD327, 0xCF);
        LCD_WriteReg(0xD328, 0x02);
        LCD_WriteReg(0xD329, 0xDE);
        LCD_WriteReg(0xD32A, 0x02);
        LCD_WriteReg(0xD32B, 0xF2);
        LCD_WriteReg(0xD32C, 0x02);
        LCD_WriteReg(0xD32D, 0xFE);
        LCD_WriteReg(0xD32E, 0x03);
        LCD_WriteReg(0xD32F, 0x10);
        LCD_WriteReg(0xD330, 0x03);
        LCD_WriteReg(0xD331, 0x33);
        LCD_WriteReg(0xD332, 0x03);
        LCD_WriteReg(0xD333, 0x6D);
        LCD_WriteReg(0xD400, 0x00);
        LCD_WriteReg(0xD401, 0x33);
        LCD_WriteReg(0xD402, 0x00);
        LCD_WriteReg(0xD403, 0x34);
        LCD_WriteReg(0xD404, 0x00);
        LCD_WriteReg(0xD405, 0x3A);
        LCD_WriteReg(0xD406, 0x00);
        LCD_WriteReg(0xD407, 0x4A);
        LCD_WriteReg(0xD408, 0x00);
        LCD_WriteReg(0xD409, 0x5C);
        LCD_WriteReg(0xD40A, 0x00);
        LCD_WriteReg(0xD40B, 0x81);

        LCD_WriteReg(0xD40C, 0x00);
        LCD_WriteReg(0xD40D, 0xA6);
        LCD_WriteReg(0xD40E, 0x00);
        LCD_WriteReg(0xD40F, 0xE5);
        LCD_WriteReg(0xD410, 0x01);
        LCD_WriteReg(0xD411, 0x13);
        LCD_WriteReg(0xD412, 0x01);
        LCD_WriteReg(0xD413, 0x54);
        LCD_WriteReg(0xD414, 0x01);
        LCD_WriteReg(0xD415, 0x82);
        LCD_WriteReg(0xD416, 0x01);
        LCD_WriteReg(0xD417, 0xCA);
        LCD_WriteReg(0xD418, 0x02);
        LCD_WriteReg(0xD419, 0x00);
        LCD_WriteReg(0xD41A, 0x02);
        LCD_WriteReg(0xD41B, 0x01);
        LCD_WriteReg(0xD41C, 0x02);
        LCD_WriteReg(0xD41D, 0x34);
        LCD_WriteReg(0xD41E, 0x02);
        LCD_WriteReg(0xD41F, 0x67);
        LCD_WriteReg(0xD420, 0x02);
        LCD_WriteReg(0xD421, 0x84);
        LCD_WriteReg(0xD422, 0x02);
        LCD_WriteReg(0xD423, 0xA4);
        LCD_WriteReg(0xD424, 0x02);
        LCD_WriteReg(0xD425, 0xB7);
        LCD_WriteReg(0xD426, 0x02);
        LCD_WriteReg(0xD427, 0xCF);
        LCD_WriteReg(0xD428, 0x02);
        LCD_WriteReg(0xD429, 0xDE);
        LCD_WriteReg(0xD42A, 0x02);
        LCD_WriteReg(0xD42B, 0xF2);
        LCD_WriteReg(0xD42C, 0x02);
        LCD_WriteReg(0xD42D, 0xFE);
        LCD_WriteReg(0xD42E, 0x03);
        LCD_WriteReg(0xD42F, 0x10);
        LCD_WriteReg(0xD430, 0x03);
        LCD_WriteReg(0xD431, 0x33);
        LCD_WriteReg(0xD432, 0x03);
        LCD_WriteReg(0xD433, 0x6D);
        LCD_WriteReg(0xD500, 0x00);
        LCD_WriteReg(0xD501, 0x33);
        LCD_WriteReg(0xD502, 0x00);
        LCD_WriteReg(0xD503, 0x34);
        LCD_WriteReg(0xD504, 0x00);
        LCD_WriteReg(0xD505, 0x3A);
        LCD_WriteReg(0xD506, 0x00);
        LCD_WriteReg(0xD507, 0x4A);
        LCD_WriteReg(0xD508, 0x00);
        LCD_WriteReg(0xD509, 0x5C);
        LCD_WriteReg(0xD50A, 0x00);
        LCD_WriteReg(0xD50B, 0x81);

        LCD_WriteReg(0xD50C, 0x00);
        LCD_WriteReg(0xD50D, 0xA6);
        LCD_WriteReg(0xD50E, 0x00);
        LCD_WriteReg(0xD50F, 0xE5);
        LCD_WriteReg(0xD510, 0x01);
        LCD_WriteReg(0xD511, 0x13);
        LCD_WriteReg(0xD512, 0x01);
        LCD_WriteReg(0xD513, 0x54);
        LCD_WriteReg(0xD514, 0x01);
        LCD_WriteReg(0xD515, 0x82);
        LCD_WriteReg(0xD516, 0x01);
        LCD_WriteReg(0xD517, 0xCA);
        LCD_WriteReg(0xD518, 0x02);
        LCD_WriteReg(0xD519, 0x00);
        LCD_WriteReg(0xD51A, 0x02);
        LCD_WriteReg(0xD51B, 0x01);
        LCD_WriteReg(0xD51C, 0x02);
        LCD_WriteReg(0xD51D, 0x34);
        LCD_WriteReg(0xD51E, 0x02);
        LCD_WriteReg(0xD51F, 0x67);
        LCD_WriteReg(0xD520, 0x02);
        LCD_WriteReg(0xD521, 0x84);
        LCD_WriteReg(0xD522, 0x02);
        LCD_WriteReg(0xD523, 0xA4);
        LCD_WriteReg(0xD524, 0x02);
        LCD_WriteReg(0xD525, 0xB7);
        LCD_WriteReg(0xD526, 0x02);
        LCD_WriteReg(0xD527, 0xCF);
        LCD_WriteReg(0xD528, 0x02);
        LCD_WriteReg(0xD529, 0xDE);
        LCD_WriteReg(0xD52A, 0x02);
        LCD_WriteReg(0xD52B, 0xF2);
        LCD_WriteReg(0xD52C, 0x02);
        LCD_WriteReg(0xD52D, 0xFE);
        LCD_WriteReg(0xD52E, 0x03);
        LCD_WriteReg(0xD52F, 0x10);
        LCD_WriteReg(0xD530, 0x03);
        LCD_WriteReg(0xD531, 0x33);
        LCD_WriteReg(0xD532, 0x03);
        LCD_WriteReg(0xD533, 0x6D);
        LCD_WriteReg(0xD600, 0x00);
        LCD_WriteReg(0xD601, 0x33);
        LCD_WriteReg(0xD602, 0x00);
        LCD_WriteReg(0xD603, 0x34);
        LCD_WriteReg(0xD604, 0x00);
        LCD_WriteReg(0xD605, 0x3A);
        LCD_WriteReg(0xD606, 0x00);
        LCD_WriteReg(0xD607, 0x4A);
        LCD_WriteReg(0xD608, 0x00);
        LCD_WriteReg(0xD609, 0x5C);
        LCD_WriteReg(0xD60A, 0x00);
        LCD_WriteReg(0xD60B, 0x81);

        LCD_WriteReg(0xD60C, 0x00);
        LCD_WriteReg(0xD60D, 0xA6);
        LCD_WriteReg(0xD60E, 0x00);
        LCD_WriteReg(0xD60F, 0xE5);
        LCD_WriteReg(0xD610, 0x01);
        LCD_WriteReg(0xD611, 0x13);
        LCD_WriteReg(0xD612, 0x01);
        LCD_WriteReg(0xD613, 0x54);
        LCD_WriteReg(0xD614, 0x01);
        LCD_WriteReg(0xD615, 0x82);
        LCD_WriteReg(0xD616, 0x01);
        LCD_WriteReg(0xD617, 0xCA);
        LCD_WriteReg(0xD618, 0x02);
        LCD_WriteReg(0xD619, 0x00);
        LCD_WriteReg(0xD61A, 0x02);
        LCD_WriteReg(0xD61B, 0x01);
        LCD_WriteReg(0xD61C, 0x02);
        LCD_WriteReg(0xD61D, 0x34);
        LCD_WriteReg(0xD61E, 0x02);
        LCD_WriteReg(0xD61F, 0x67);
        LCD_WriteReg(0xD620, 0x02);
        LCD_WriteReg(0xD621, 0x84);
        LCD_WriteReg(0xD622, 0x02);
        LCD_WriteReg(0xD623, 0xA4);
        LCD_WriteReg(0xD624, 0x02);
        LCD_WriteReg(0xD625, 0xB7);
        LCD_WriteReg(0xD626, 0x02);
        LCD_WriteReg(0xD627, 0xCF);
        LCD_WriteReg(0xD628, 0x02);
        LCD_WriteReg(0xD629, 0xDE);
        LCD_WriteReg(0xD62A, 0x02);
        LCD_WriteReg(0xD62B, 0xF2);
        LCD_WriteReg(0xD62C, 0x02);
        LCD_WriteReg(0xD62D, 0xFE);
        LCD_WriteReg(0xD62E, 0x03);
        LCD_WriteReg(0xD62F, 0x10);
        LCD_WriteReg(0xD630, 0x03);
        LCD_WriteReg(0xD631, 0x33);
        LCD_WriteReg(0xD632, 0x03);
        LCD_WriteReg(0xD633, 0x6D);
        //LV2 Page 0 enable
        LCD_WriteReg(0xF000, 0x55);
        LCD_WriteReg(0xF001, 0xAA);
        LCD_WriteReg(0xF002, 0x52);
        LCD_WriteReg(0xF003, 0x08);
        LCD_WriteReg(0xF004, 0x00);
        //Display control
        LCD_WriteReg(0xB100, 0xCC);
        LCD_WriteReg(0xB101, 0x00);
        //Source hold time
        LCD_WriteReg(0xB600, 0x05);
        //Gate EQ control
        LCD_WriteReg(0xB700, 0x70);
        LCD_WriteReg(0xB701, 0x70);
        //Source EQ control (Mode 2)
        LCD_WriteReg(0xB800, 0x01);
        LCD_WriteReg(0xB801, 0x03);
        LCD_WriteReg(0xB802, 0x03);
        LCD_WriteReg(0xB803, 0x03);
        //Inversion mode (2-dot)
        LCD_WriteReg(0xBC00, 0x02);
        LCD_WriteReg(0xBC01, 0x00);
        LCD_WriteReg(0xBC02, 0x00);
        //Timing control 4H w/ 4-delay
        LCD_WriteReg(0xC900, 0xD0);
        LCD_WriteReg(0xC901, 0x02);
        LCD_WriteReg(0xC902, 0x50);
        LCD_WriteReg(0xC903, 0x50);
        LCD_WriteReg(0xC904, 0x50);
        LCD_WriteReg(0x3500, 0x00);
        LCD_WriteReg(0x3A00, 0x55); //16-bit/pixel
        LCD_WR_REG(0x1100);
        LCD_delayus(120);
        LCD_WR_REG(0x2900);
    }
    
    LCD_Display_Dir(0);		//默认为竖屏
    
    LCD_BL_ON;              // 打开背光

    LCD_Clear(WHITE);

//    LCD_WR_REG(0x29);	                                                //  开启显示
//    
//    LCD_Display_Dir(1);												    //	默认为横屏

//    LCD_Clear(WHITE);
}


/**********************************************************************************************************
函数名称：清屏函数
输入参数：color:要清屏的填充色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_Clear(u16 color)
{
    u32 index = 0;
	
    u32 totalpoint = lcddev.width;
    totalpoint *= lcddev.height; 										//	得到总点数
	
    LCD_SetCursor(0x00, 0x0000);									    //	设置光标位置
    
    LCD_WriteRAM_Prepare();     									    //	开始写入GRAM
    
    for(index = 0; index < totalpoint; index++)
    {
        LCD->LCD_RAM = color;
    }
}


///**********************************************************************************************************
//函数名称：在指定区域内填充单个颜色
//输入参数：(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//		  color:要填充的颜色
//输出参数：无
//函数返回：无
//**********************************************************************************************************/
//void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
//{
//    u16 i, j;
//    u16 xlen = 0;
//	
//    xlen = ex - sx + 1;
//    
//    for(i = sy; i <= ey; i++)
//    {
//        LCD_SetCursor(sx, i);      									    //	设置光标位置
//        
//        LCD_WriteRAM_Prepare();     								    //	开始写入GRAM
//        
//        for(j = 0; j < xlen; j++)
//        {
//            LCD->LCD_RAM = color;									    //	显示颜色
//        }
//    }
//}


///**********************************************************************************************************
//函数名称：在指定区域内填充指定颜色块
//输入参数：(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//		  color:要填充的颜色
//输出参数：无
//函数返回：无
//**********************************************************************************************************/
//void LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 *color)
//{
//    u16 height, width;
//    u16 i, j;
//	
//    width = ex - sx + 1; 												//	得到填充的宽度
//    height = ey - sy + 1;												//	高度
//	
//    for(i = 0; i < height; i++)
//    {
//        LCD_SetCursor(sx, sy + i);   									//	设置光标位置
//        LCD_WriteRAM_Prepare();     									//	开始写入GRAM
//		
//        for(j = 0; j < width; j++)
//        {
//            LCD->LCD_RAM = color[i * width + j]; 						//	写入数据
//        }
//    }
//}


/**********************************************************************************************************
函数名称：画线
输入参数：x1,y1:起点坐标
		  x2,y2:终点坐标
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    
    delta_x = x2 - x1; 													//	计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    
    if(delta_x > 0)
    {
        incx = 1; 														//	设置单步方向
    }
    else if(delta_x == 0)
    {
        incx = 0; 														//	垂直线
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    
    if(delta_y > 0)
    {
        incy = 1;
    }
    else if(delta_y == 0)
    {
        incy = 0; 														//	水平线
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    
    if( delta_x > delta_y)
    {
        distance = delta_x; 											//	选取基本增量坐标轴
    }
    else 
    {
        distance = delta_y;
    }
    
    for(t = 0; t <= distance + 1; t++ ) 								//	画线输出
    {
        LCD_DrawPoint(uRow, uCol, color); 								//	画点
        xerr += delta_x ;
        yerr += delta_y ;
        
        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}


/**********************************************************************************************************
函数名称：画矩形
输入参数：(x1,y1),(x2,y2):矩形的对角坐标
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
}


///**********************************************************************************************************
//函数名称：在指定位置画一个指定大小的圆
//输入参数：(x,y):中心点
//		  r    :半径
//输出参数：无
//函数返回：无
//**********************************************************************************************************/
//void LCD_Draw_Circle(u16 x0, u16 y0, u8 r, u16 color)
//{
//    int a, b;
//    int di;
//    
//	a = 0;
//	b = r;
//    
//	di = 3 - (r << 1);       											//	判断下个点位置的标志
//    
//	while(a <= b)
//    {
//        LCD_DrawPoint(x0 + a, y0 - b, color);        					//	5
//        LCD_DrawPoint(x0 + b, y0 - a, color);        					//	0
//        LCD_DrawPoint(x0 + b, y0 + a, color);        					//	4
//        LCD_DrawPoint(x0 + a, y0 + b, color);        					//	6
//        LCD_DrawPoint(x0 - a, y0 + b, color);        					//	1
//        LCD_DrawPoint(x0 - b, y0 + a, color);
//        LCD_DrawPoint(x0 - a, y0 - b, color);        					//	2
//        LCD_DrawPoint(x0 - b, y0 - a, color);        					//	7
//        
//		a++;
//        
//		//	使用Bresenham算法画圆
//        if(di < 0)
//        {
//            di += 4 * a + 6;
//        }
//        else
//        {
//            di += 10 + 4 * (a - b);
//            b--;
//        }
//    }
//}


/**********************************************************************************************************
函数名称：显示中文字符
输入参数：x0，y0    起始坐标
		  pcStr     指向
		  PenColor  字体颜色
		  BackColor 字体背景
输出参数：无
函数返回：无
函数说明：显示汉字字符串，这个函数不能单独调用	
**********************************************************************************************************/
void LCD_ShowHzString(u16 x, u16 y, u8 *c, u16 PenColor, u16 BackColor)
{
	int i, j;
	u8 buffer[32];
	u16 tmp_char=0;
	unsigned int c1, c2;
    unsigned int c3 = 0;
    unsigned char *c4;
    
    c4 = c4;
    c1 = *c;	                                                        //  区号
    c2 = *(c + 1);	                                                    //  位号	修改正确
    c3 = ((c1 - 0xa1)*0x5e + (c2 - 0xa1))*0x20;                         //  汉字在字库中的地址
    c4 = (unsigned char*)&Hzk16[c3];                                    //  换算成指针
		  
	for(i=0;i<32;i++)
    {
        buffer[i] = Hzk16[c3+i];
    }

	for (i = 0; i < 16; i++)		 
	{
		tmp_char = buffer[i*2];
		tmp_char = (tmp_char << 8);
		tmp_char |= buffer[2*i + 1];                                    //  现在tmp_char存储着一行的点阵数据

		for (j = 0; j < 16; j++)
		{
			if((tmp_char >> 15 - j) & 0x01 == 0x01)//tmp_char >> (15 - j) & 0x01 == 0x01 aka tmp_char>>(15-j)&1 逆天
			{
				LCD_DrawPoint(x + j, y + i, PenColor);                  //  字符颜色
			}
			else
			{
				LCD_DrawPoint(x + j, y + i, BackColor);                 //  背景颜色
			}
		}
	}

}


/**********************************************************************************************************
函数名称：显示ASCII码函数
输入参数：x，y      起始坐标（x:0~234 y:0~308）
		  num       字符ASCII码值
		  size      字符大小，使用默认8*16
		  PenColor  字体颜色
		  BackColor 字体背景颜色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u16 PenColor, u16 BackColor)
{       
    u8 temp, t1, t;
	u16 y0 = y;
    
	u8 csize = (size/8 + ((size%8)? 1 : 0))*(size/2);		            //  得到字体一个字符对应点阵集所占的字节数	
    
    //  得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
 	num = num - ' ';                                                    
	
    for(t = 0; t < csize; t++)
	{   
		if (size == 12)
        {
            temp = asc2_1206[num][t]; 	 	                            //  调用1206字体
        }
        
		else if(size == 16) 
        {
            temp = asc2_1608[num][t];	                                //  调用1608字体
        }
        
		else if(size == 24)
        {
            temp = asc2_2412[num][t];	                                //  调用2412字体
        }
		else 
        {
            return;								                        //  没有的字库
        }
        
		for(t1 = 0; t1 < 8; t1++)
		{			    
			if(temp&0x80)
            {
                LCD_Fast_DrawPoint(x, y, PenColor);
            }
            
			else
            {
                LCD_Fast_DrawPoint(x, y, BackColor);
            }
            
			temp <<= 1;
            
			y++;
			
            if (y >= lcddev.height)
            {
                return;		//超区域了
            }
            
			if((y - y0) == size)
			{
				y = y0;
				
                x++;
				
                if(x >= lcddev.width)
                {
                    return;	//超区域了
                }
				break;
			}
		}  	 
	}  	    	
}


/**********************************************************************************************************
函数名称：显示1个字符串函数
输入参数：x，y      起始坐标
	      p         指向字符串起始地址
		  PenColor  字符颜色
		  BackColor 背景颜色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_ShowCharString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t PenColor, uint16_t BackColor)
{   
	uint8_t size = 16;                                                  //  字符大小默认16*8
	 
    if(x > lcddev.width)                                                //  超出X轴字体最小单位，换行
    {
        x = 0;
        y += size;
    }			         
    
    if(y > lcddev.height)                                               //  超出Y轴字体最小单位，回到原点，并且清屏
    {
        y = x = 0;
        LCD_Clear(WHITE);
    }	 
    
    LCD_ShowChar(x, y, *p, size, PenColor, BackColor);			   		//	0表示非叠加方式
}


/**********************************************************************************************************
函数名称：显示字符串
输入参数：x,y			起点坐标
		  u8 *pcStr		字符
		  PenColor  	字符颜色
		  BackColor 	背景颜色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor)
{
    while(*pcStr)
	{
		if(*pcStr > 0xa1)                                               //  显示汉字
		{
			LCD_ShowHzString(x0, y0, pcStr, PenColor, BackColor);
			pcStr += 2;
			x0 += 16;
		}
		else                                                            //  显示字符
		{
			LCD_ShowCharString(x0, y0, pcStr, PenColor, BackColor);	
			pcStr +=1;
			x0+= 8;
		}
	}	
}

/**********************************************************************************************************
函数名称：LCD_DrawPoint
输入参数：x.y:画点的坐标
		  color：颜色
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_DrawOnrPoint(uint16_t xsta, uint16_t ysta, uint16_t color)
{
	LCD_SetCursor(xsta, ysta);  		                                //  设置光标位置
	LCD_WriteRAM_Prepare();          	                                //  开始写入GRAM
	LCD_WriteRAM(color); 

}


/**********************************************************************************************************
函数名称：显示图片
输入参数：StartX     行起始座标
          StartY     列起始座标
          EndX       行结束座标
          EndY       列结束座标
          pic        图片头指针
输出参数：无
函数返回：无
**********************************************************************************************************/
void LCD_DrawPicture(u16 StartX, u16 StartY, u16 Xend, u16 Yend, u8 *pic)
{
    static	u16 i = 0, j = 0;
    
    u16 *bitmap = (u16 *)pic;
    
    for(j = 0; j < Yend - StartY; j++)
    {
        for(i = 0; i < Xend - StartX; i++)
        {
            LCD_DrawOnrPoint(StartX + i, StartY + j, *bitmap++);
        }
    }
}
