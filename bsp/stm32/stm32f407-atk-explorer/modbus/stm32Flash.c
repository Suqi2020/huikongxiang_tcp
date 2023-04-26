#include "board.h"


//#include "stmflash.h"

const static char sign[]="[flash]";
////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//STM32�ڲ�FLASH��д ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
packIpUartStru packFlash   __attribute__ ((aligned (4)));
deviceFlashStru sheet    __attribute__ ((aligned (4)))={0};

extern void uartSingConf(int num,int bps);

static void flash(int argc, char *argv[])
{
		if(argc==1){
				goto ERR;
		}
		if(argc==2){
			if(0==rt_strcmp((char *)"save", argv[1])){
				rt_kprintf("%sflash save OK\n",sign);
				stm32_flash_erase(FLASH_IP_SAVE_ADDR, sizeof(packFlash));//ÿ�β���128k�ֽ����� �洢ʱ����Ҫһ��洢
				stm32_flash_write(FLASH_IP_SAVE_ADDR,(uint8_t*)&packFlash,sizeof(packFlash));
				stm32_flash_write(FLASH_MODBUS_SAVE_ADDR,(uint8_t*)&sheet,sizeof(sheet));
		  }
			else
				goto ERR;
		}
		return;
		ERR:
		//rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[flash save]\n",sign);
}
MSH_CMD_EXPORT(flash,flash save);//FINSH_FUNCTION_EXPORT_CMD



//modbus+�豸����(������)+ID+model+�˿�(port1-port4)+�豸��ַ(0/255-�ر��豸)+�ɼ����(��)
		
		


//static const uint8_t portStr[UART_NUM][6]={"port1","port2","port3","port4"};

//static void uart(int argc, char *argv[])
//{
//	  
//		if(argc!=3){
//				goto ERR;
//		}
//		rt_strcpy((char *)packFlash.acuId,argv[1]);
//		ERR:
//		rt_kprintf("%s[uart �˿�(1-4) ������]\n",sign);
//		rt_kprintf("%sfor example\n",sign);
//		rt_kprintf("%s[uart port1 9600]\n",sign);

//}
//MSH_CMD_EXPORT(uart,uart config);//FINSH_FUNCTION_EXPORT_CMD
static const uint8_t portStr[UART_NUM][6]={"port1","port2","port3","port4"};
////////////////////��������/////////////////////////////
static void uart(int argc, char *argv[])
{
	  
		if(argc!=3){
				goto ERR;
		}

		for(int i=0;i<UART_NUM;i++){
				if(0==rt_strcmp((char *)portStr[i], argv[1])){
						packFlash.uartBps[i]    =atoi32(argv[2],10);
						uartSingConf(i,packFlash.uartBps[i]);
						rt_kprintf("%sport%d config OK\n",sign,i+1);
				}
		}
		return;
		ERR:
		rt_kprintf("%s[uart �˿�(1-4) ������]\n",sign);
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[uart port1 9600]\n",sign);

}
MSH_CMD_EXPORT(uart,uart config);//FINSH_FUNCTION_EXPORT_CMD

////////////////////////ACUID����///////////////////////////////////
static void acuid(int argc, char *argv[])
{
		if(argc!=2){
				goto ERR;
		}
		rt_strcpy(packFlash.acuId,argv[1]);
		rt_kprintf("%sacuid OK\n",sign);
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[acuid  100000000000001]\n",sign);

}
MSH_CMD_EXPORT(acuid,acuid config);//FINSH_FUNCTION_EXPORT_CMD


void printAcuid()
{
		rt_kprintf("%sAcuid:%s\n",sign,packFlash.acuId);
	//  rt_kprintf("%Acuid:s%s\n",sign,packFlash.acuId);
}

