/**********************************************************************************
 * ������  :GPRS
 * ����    :lza1205
 * ����    :https://blog.csdn.net/aa120515692
**********************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"


#include "gsm_code.h"
#include "gsm_base.h"
#include "tcp_base.h"

#include "all.h"

extern int client_main(void);
char buf[2000];
u32 ret;
/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : ����2������MG323ģ��ͨ�ţ�����1���ڴ��ڵ��ԣ����Ա��������س���ʱ����
					 �����͵�ģ��
*******************************************************************************/
int main(void)
{
	SysTick_Init_Config();

	USART1_Init_Config(115200);
	USART2_Init_Config(115200);
	Timer2_Init_Config();
	
	Delay_nMs(2000);
	UART1_SendString("���ÿͻ���ģʽ\r\n");
	Second_AT_Command("AT+CWMODE=1","OK",1);
	Set_ATE0();
	UART1_SendString("ɨ��wifi\r\n");

	ret = Second_AT_Command_Recv("AT+CWLAP","OK", buf, 2);
	UART1_SendData((u8 *)buf, ret);
/*
	if(strstr(buf,"HUAWEI")!=NULL)
	{
		UART1_SendString("����wifi\r\n");
		//lianjie
		Second_AT_Command("AT+CWJAP_DEF=\"HUAWEI\",\"076812345678\"", "OK", 10);
	}
	*/
	Second_AT_Command("AT+CWJAP_DEF=\"HUAWEI\",\"076812345678\"", "OK", 10);
	//Second_AT_Command("AT+CWJAP_DEF=\"Tenda_29F368\",\"wx133889\"", "OK", 10);

	//������
	Second_AT_Command("AT+CIPMUX=0","OK",1);
	
	//tcp ���ӵ�������
	Second_AT_Command("AT+CIPSTART=\"TCP\",\"106.13.62.194\",8080","OK",10);
	//Second_AT_Command("AT+CIPSTART=\"UDP\",\"106.13.62.194\",8000","OK",10);
	
	//Connect_Server(NULL);
	UART1_SendString("���� wifi �ɹ�\r\n");
	//����͸��ģʽ
	Second_AT_Command("AT+CIPMODE=1","OK",1);
	Second_AT_Command("AT+CIPSEND","OK",1);
	while(1)
	{
		client_main();
	}
}

