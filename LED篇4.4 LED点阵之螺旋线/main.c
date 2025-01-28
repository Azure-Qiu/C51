#include <REGX52.H>
#include <INTRINS.H>
/** 
 **  @brief    绘制螺旋线
 **  @author   QIU
 **  @date     2023.08.23
 **/
/*-------------------------------------------------------------------*/
#define LED_PORT P0
#define SPEED 30

typedef unsigned char u8;
typedef unsigned int u16;

sbit SER = P3^4; // 串行数据输入引脚
sbit ST_CP = P3^5; // 存储寄存器时钟引脚
sbit SH_CP = P3^6; // 移位寄存器时钟引脚

// 全局变量
u8 x, y, num_step, count, dir, posY[8] = {0};

// 延时函数
void delay(u16 t){
	while(t--);
}

// 生成对应位置的二进制代码
u8 produce_B_Code(u8 pos){	
	return 0x01<<pos;
}

//串行数据生成对应并行数据
void Ser2Para(u8 dat){
	u8 i;
	for(i=0;i<8;i++){
		SER = dat>>7;
		dat <<= 1;
		SH_CP = 0;
		_nop_(); // 延迟一个机器周期
		SH_CP = 1; //获得一个上升沿
		_nop_(); 
	}
	ST_CP = 0;
	_nop_();
	ST_CP = 1;
	_nop_();
}

void clear_LED(){
	LED_PORT = 0xff; // 清屏
	Ser2Para(0x00); 
}


// 显示每帧画面
void display(u8 XDATA,u8 YDATA){
	LED_PORT = ~produce_B_Code(XDATA); // 按列由右往左扫描
	Ser2Para(YDATA);
	delay(100);
	clear_LED(); // 消影
}

// 更新方向与数组
void update_posY(u8 dir){
	// 判断方向
	switch(dir%4){
		case 0: // 向下
			y = y - 1; // 更新当前点坐标
			posY[x] += produce_B_Code(y); // 更新需要点亮的Y坐标码
			break;
		case 1: // 向右
			x = x - 1;
			posY[x] += produce_B_Code(y); // 更新需要点亮的Y坐标码
			break;
		case 2: // 向上
			y = y + 1; // 更新当前点坐标
			posY[x] += produce_B_Code(y); // 更新需要点亮的Y坐标码
			break;
		case 3: // 向左(往高位走)
			x = x + 1; // 更新当前点坐标
			posY[x] += produce_B_Code(y); // 更新需要点亮的Y坐标码
			break;
	}
}

// 重启
void reset(){
	u8 k;
	x = 4, y = 4, num_step = 1, count = 0, dir = 0;
	for(k=0;k<8;k++){
		if(k == x){
			posY[x] = produce_B_Code(y); // 记录初始化的值
		}else{
			posY[k] = 0;
		}
	}
}


/**
 **  @brief   螺旋线
 **  @param   count: 记录每个动作(上下，左右)需要执行几次
 **  @param   x, y:记录当前点的坐标
 **  @param   posY[]:记录当前需要点亮的灯的十六进制码
 **  @retval  返回值
 **/
int main(void){
	u8 i, j=0;
	reset(); // 初始化
	while(1){
		for(i=0;i<8;i++){
			// 逆时针
			display(i,posY[i]); // 把数组传过去
		}
		count++;
		// 下一帧
		if(count > SPEED){
			count = 0;
			// 更新一下posY数组，显示下一个点
			update_posY(dir);
			// 记录每更改一次方向需要几帧
			j++;
			// 每两组换向多走一步
			num_step = dir/2 + 1;
			// 更新方向
			if(j>=num_step){
				dir++;
				j=0; // 复位
			}
		}
		// 结束条件
		if(x==0 && y==8){
			delay(10000); // 保持画面
			clear_LED(); // 清屏
			delay(50000);
			reset(); // 重新开始
		}
	}
}