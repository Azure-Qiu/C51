#include "smg.h"
/** 
 **  @brief    ����ܷ�װ
 **  		   1. ��ʱˢ��
 **  		   		(1) �ַ���̬��ʾ������һ�����롣�����ַ��������ڳ�ʼ������
 **  		   		(2) �ַ������ݶ�̬��ʾ
 **  		   		(3) ���������ݶ�̬��ʾ��������ʾС����
 **  		   		(4) �������ݶ�̬��ʾ��������ʾ������
 **  		   2. ��ʱ��ˢ��
 **  @author   QIU
 **  @date     2024.02.13
 **/


/*-------------------------------------------------------------------*/

//��������������������
u8 code smgduan[] = {0x3f,0x06,0x5b,0x4f,0x66, //0 1 2 3 4
					 0x6d,0x7d,0x07,0x7f,0x6f, //5 6 7 8 9
					 0x77,0x7c,0x58,0x5e,0x79, //A b c d E
					 0x71,0x76,0x30,0x0e,0x38, //F H I J L
					 0x54,0x3f,0x73,0x67,0x50, //n o p q r
					 0x6d,0x3e,0x3e,0x6e,0x40};//s U v y -  


/**
 **  @brief   ָ���ڼ�������ܵ�����38����������λѡ��������������
 **  @param   pos���������ң������λ�� 1~8
 **  @retval  ��
 **/
void select_38(u8 pos){
	u8 temp_pos = 8 - pos; // 0~7
	A1 = temp_pos % 2; //��λ
	temp_pos /= 2;
	A2 = temp_pos % 2; 
	temp_pos /= 2;
	A3 = temp_pos % 2; //��λ
}


/**
 **  @brief   �������ݲ�ȡ����Ӧ��������������
 **  @param   dat:��Ҫ��ʾ���ַ�
 **  @retval  ��Ӧ���������ֵ
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
		default:return 0x00; //����ʾ
	}
}



/**
 **  @brief   ���������ASCII�룬��ʾ��Ӧ�ַ���1�ֽڣ�
 **  @param   dat���ַ����ݣ�����ASCIIֵ
 **  @param   pos����ʾλ�� 1~8
 **  @retval  ��
 **/
void smg_showChar(u8 dat, u8 pos, bit flag){
	// ����������һ�������
	select_38(pos);
	// ��������
	SMG_PORT = parse_data(dat);
	// �ӱ��
	if(flag) SMG_PORT |= 0x80;
}





/*-------------------------------------------------------------------*/
/*-----------------------��ʱ��ˢ��----------------------------------*/
/*-------------------------------------------------------------------*/


/**
 **  @brief   ��ʱ��ˢ��
 **  @param   dat���ַ����飬����'\0'��β
 **  @param   pos����ʾλ��
 **  @param   dot��С����λ��
 **  @retval  ��
 **/
void smg_flush_Bydelay(u8 dat[], u8 pos, u8 dot){
	u8 i;
	// ��������ֱ�ӽض�
	for(i=0;(i<9-pos)&&(dat[i]!='\0');i++){
		// �����С���㣬��������ǰ��һλ
		if(dat[i] == '.'){
			pos -= 1;
			continue;
		}
		// ��ʾ
		smg_showChar(dat[i], pos+i, (dot == i+1)?true:false);
        // ��ʱ1ms
		delay_ms(1);
		// ��Ӱ
		SMG_PORT = 0x00; 
	}
}



/**
 **  @brief   ��ʾ�ַ�������̬��ʾ��
 **  @param   dat���ַ����飬����'\0'��β
 **  @param   pos����ʾλ��
 **  @retval  ��
 **/
void smg_showString(u8 dat[], u8 pos){
	u8 i = 0, dot = 0;
	// ���ж��Ƿ����С����
	while(dat[i]!='\0'){
		if(dat[i] == '.') break;
		i++;
	}
	// ��¼�±��λ��
	if(i < strlen(dat)) dot = i;
	// ��ʱ��ˢ��
	smg_flush_Bydelay(dat, pos, dot);
}



/**
 **  @brief   �������ʾ��������������
 **  @param   dat: ����
 **  @param   pos: ��ʾλ��
 **  @retval  ��
 **/
void smg_showInt(int dat, u8 pos){
	xdata u8 temp[9];
	sprintf(temp, "%d", dat); // ������
	smg_showString(temp, pos);
}



/**
 **  @brief   �������ʾ����������С���㣩
 **  @param   dat: ������
 **  @param   len: ָ������
 **  @param   pos: ��ʾλ��
 **  @retval  ��
 **/
void smg_showFloat(double dat, u8 len, u8 pos){
	xdata u8 temp[10];
	int dat_now;
	dat_now = dat * pow(10, len) + 0.5 * (dat>0?1:-1); // ��������(����)�����ڸ��������������δ��׼ȷ
	sprintf(temp, "%d", dat_now); // ������
	smg_flush_Bydelay(temp, pos, len?(strlen(temp) - len):0);
}



/*-------------------------------------------------------------------*/
/*--------------------------��ʱ����ˢ��-----------------------------*/
/*-------------------------------------------------------------------*/

/**
 **  @brief   �������ʾ�ַ�������ʱ����ˢ�£�
 **  @param   dat���ַ����飬����'\0'��β
 **  @param   pos����ʾλ��
 **  @retval  ����ֵ
 **/
void smg_showString_Bytimer(u8 dat[], u8 pos){
	// ����ܼ������� С����λ��
	static u8 smg_counter = 0, dot_counter = 0, dot_port[8];
	// �ݴ浱ǰλ��
	u8 temp;
	
	// ����Ӱ
	SMG_PORT = 0x00; 
	
	// �����С���㣬������
	if(dat[smg_counter] == '.'){
		// ��¼С����λ�ã���һ��ˢ��
		dot_port[smg_counter-1] = true;
		// ����������һλ
		smg_counter++;
		// С�������������
		dot_counter++;
		return;
	}
	// ���㵱ǰλ��
	temp = pos+smg_counter-dot_counter;
	// �ж��Ƿ��С���㣨��⵽С����ĺ��漸λ����ǰ�ƣ�
	smg_showChar(dat[smg_counter], temp, dot_port[smg_counter]);
	
	// ����ǽ�����������(�������ֽض�)
	if(temp == 8 | dat[smg_counter] == '\0'){
		// ����
		smg_counter = 0;
		// ���ݱ�־�����Ƿ����С����
		if(dot_counter){
			// ����
			dot_counter = 0;
		}else{
			// ���
			strcpy(dot_port, "");
		}
		return;
	}else{
		smg_counter++;
	}
}
