#include "smg.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
/** 
 **  @brief    数码管封装
 **  		   1. 字符静态显示：仅需一次输入。输入字符。可用于初始清屏。
 **  		   2. 字符串数据动态显示
 **  		   3. 浮点型数据动态显示：可以显示小数。
 **  		   4. 整型数据动态显示：可以显示负数。
 **  @author   QIU
 **  @date     2024.01.31
 **/


/*-------------------------------------------------------------------*/

//共阴极数码管字形码编码
u8 code smgduan[] = {0x3f,0x06,0x5b,0x4f,0x66, //0 1 2 3 4
					 0x6d,0x7d,0x07,0x7f,0x6f, //5 6 7 8 9
					 0x77,0x7c,0x58,0x5e,0x79, //A b c d E
					 0x71,0x76,0x30,0x0e,0x38, //F H I J L
					 0x54,0x3f,0x73,0x67,0x50, //n o p q r
					 0x6d,0x3e,0x3e,0x6e,0x40};//s U v y -  


/**
 **  @brief   指定第几个数码管点亮，38译码器控制位选（不对外声明）
 **  @param   pos：从左至右，数码管位置 1~8
 **  @retval  无
 **/
void select_38(u8 pos){
	u8 temp_pos = 8 - pos; // 0~7
	A1 = temp_pos % 2; //高位
	temp_pos /= 2;
	A2 = temp_pos % 2; 
	temp_pos /= 2;
	A3 = temp_pos % 2; //低位
}


/**
 **  @brief   解析数据并取得相应数码管字形码编码
 **  @param   dat:想要显示的字符
 **  @retval  对应字形码编码值
 **/
u8 parse_data(u8 dat){
	switch(dat){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':return smgduan[dat-'0'];
		case 'a':
		case 'A':return smgduan[10];
		case 'b':
		case 'B':return smgduan[11];
		case 'c':
		case 'C':return smgduan[12];
		case 'd':
		case 'D':return smgduan[13];
		case 'e':
		case 'E':return smgduan[14];
		case 'f':
		case 'F':return smgduan[15];
		case 'h':
		case 'H':return smgduan[16];
		case 'i':
		case 'I':return smgduan[17];
		case 'j':
		case 'J':return smgduan[18];
		case 'l':
		case 'L':return smgduan[19];
		case 'n':
		case 'N':return smgduan[20];
		case 'o':
		case 'O':return smgduan[21];
		case 'p':
		case 'P':return smgduan[22];
		case 'q':
		case 'Q':return smgduan[23];
		case 'r':
		case 'R':return smgduan[24];
		case 's':
		case 'S':return smgduan[25];
		case 'u':
		case 'U':return smgduan[26];
		case 'v':
		case 'V':return smgduan[27];
		case 'y':
		case 'Y':return smgduan[28];
		case '-':return smgduan[29];
		default:return 0x00; //不显示
	}
}



/**
 **  @brief   根据输入的ASCII码，显示对应字符（1字节）
 **  @param   dat：字符数据，或其ASCII值
 **  @param   pos：显示位置 1~8
 **  @retval  无
 **/
void smg_showChar(u8 dat, u8 pos, bit flag){
	// 解析点亮哪一个数码管
	select_38(pos);
	// 解析数据
	SMG_PORT = parse_data(dat);
	// 加标点
	if(flag) SMG_PORT |= 0x80;
}




/**
 **  @brief   延时法刷新
 **  @param   dat：字符数组，需以'\0'结尾
 **  @param   pos：显示位置
 **  @param   dot：小数点位置
 **  @retval  无
 **/
void smg_cycle(u8 dat[], u8 pos, u8 dot){
	u8 i;
	// 超出部分直接截断
	for(i=0;(i<9-pos)&&(dat[i]!='\0');i++){
		// 如果是小数点，跳过，往前移一位
		if(dat[i] == '.'){
			pos -= 1;
			continue;
		}
		if(dot == i+1){
			smg_showChar(dat[i], pos+i, true);
		}else{
			smg_showChar(dat[i], pos+i, false);
		}
		delay_ms(1); //延时1ms
		SMG_PORT = 0x00; //消影
	}
}



/**
 **  @brief   显示字符串（动态显示）
 **  @param   dat：字符数组，需以'\0'结尾
 **  @param   pos：显示位置
 **  @retval  无
 **/
void smg_showString(u8 dat[], u8 pos){
	u8 i = 0, dot = 0;
	// 先判断是否存在小数点
	while(dat[i]!='\0'){
		if(dat[i] == '.') break;
		i++;
	}
	// 记录下标点位置
	if(i < strlen(dat)) dot = i;
	
	smg_cycle(dat, pos, dot);
}


/**
 **  @brief   数码管显示整数（含正负）
 **  @param   dat: 整数
 **  @param   pos: 显示位置
 **  @retval  无
 **/
void smg_showInt(int dat, u8 pos){
	xdata u8 temp[9];
	sprintf(temp, "%d", dat); // 含正负
	smg_showString(temp, pos);
}



/**
 **  @brief   数码管显示浮点数（含小数点）
 **  @param   dat: 浮点数
 **  @param   len: 指定精度
 **  @param   pos: 显示位置
 **  @retval  无
 **/
void smg_showFloat(double dat, u8 len, u8 pos){
	xdata u8 temp[10];
	int dat_now;
	dat_now = dat * pow(10, len) + 0.5 * (dat>0?1:-1); // 四舍五入(正负)，由于浮点数存在误差，结果未必准确
	sprintf(temp, "%d", dat_now); // 含正负
	smg_cycle(temp, pos, len?(strlen(temp) - len):0);
}

