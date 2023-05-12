/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include "7inchRegist.h"
const static char sign[]="[LCD]";
extern struct  rt_messagequeue LCDmque;

uint8_t  sendLCDBuf[LCD_BUF_LEN];
uint8_t  recLCDBuf[LCD_BUF_LEN];



//��LCD��Ļ�������� ���õײ㴮�ڷ��ͺ���
static void LCDDataSend(uint8_t *buf,int lenth)
{
	 //rt_kprintf("%s LCD send:",sign);
	 for(int i=0;i<lenth;i++){
		 HAL_UART_Transmit(&huart5,buf+i,1,1000); 
		 //rt_kprintf("%02x ",buf[i]);
	 }
	 rt_thread_mdelay(5);//�����������ݰ� �ְ�
	 //rt_kprintf("\n");
	
}
//��� return 0-��Ӧ����  1-�ظ���ȷ
//5A A5 03 82 4F 4B 
static int LCDWriteResp(uint8_t *recBuf,int lenth)
{
		if(lenth<4)
				return 0;
		if((recBuf[0]==(uint8_t)(LCD_HEAD>>8))&&\
		 (recBuf[1]==(uint8_t)(LCD_HEAD))&&\
		 (recBuf[3]==LCD_WRITE)&&\
		 (recBuf[4]==(uint8_t)(LCD_RUN>>8))&&\
		 (recBuf[5]==(uint8_t)(LCD_RUN))){
			  // rt_kprintf("%sresponse\n",sign);
				 return 1;
		}
		return 0;
}



//5a a5 15 82 54 10 47 59 4e 4a 4c 58 53 44 30 30 30 30 30 30 31 36 38 ff 
//5a a5 15 82 14 20 47 59 4e 4a 4c 58 53 44 30 30 30 30 30 30 31 36 38 ff 


// 5a a5 15 82 14 20 47 59 4e 4a 4c 58 53 44 30 30 30 30 30 30 35 36 32 ff 
// 5a a5 15 82 54 10 47 59 4e 4a 4c 58 53 44 30 30 30 30 30 30 31 36 38 ff 
//��� return 0 ����Ӧ  1 ������Ӧ 
int LCDWtite(uint16_t addr,uint8_t *data,uint8_t dataLen)
{
		extern rt_mutex_t   lcdSend_mutex;
		rt_mutex_take(lcdSend_mutex,RT_WAITING_FOREVER);
	  int len=0;
		rt_memset(sendLCDBuf,0,LCD_BUF_LEN);
//		rt_memset(recLCDBuf,0,LCD_BUF_LEN);
		sendLCDBuf[len++]=(uint8_t)(LCD_HEAD>>8);
	  sendLCDBuf[len++]=(uint8_t)LCD_HEAD;		
	  sendLCDBuf[len++]=dataLen+2+1;						//������ʱ���0  2-headlen 1-writelen
	  sendLCDBuf[len++]=LCD_WRITE;  						
		sendLCDBuf[len++]=(uint8_t)(addr>>8);	
		sendLCDBuf[len++]=(uint8_t)addr;		
	  for (int i=0;i<dataLen;i++){
				sendLCDBuf[len++]=data[i];
		}
//    int repTimes=2;
//		while(repTimes--){
			//data send
//		rt_kprintf("%s fa:",sign);
//		for(int i=0;i<len;i++){//ACUID_LEN
//			 	rt_kprintf("%0x ",sendLCDBuf[i]);
//		}
//   rt_kprintf("%\n ");
		LCDDataSend(sendLCDBuf,len);
		rt_mutex_release(lcdSend_mutex);
//		rt_kprintf("%\n ");
			//data rec
//				int revLen=0;
//				if(rt_mq_recv(&LCDmque, recLCDBuf+revLen, 1, 25) == RT_EOK){
//					revLen++;
//				}
//				while(rt_mq_recv(&LCDmque, recLCDBuf+revLen, 1, 2) == RT_EOK){
//					revLen++;
//				}
//				if(revLen){
//					return LCDWriteResp(recLCDBuf,revLen);
//				}
//		}
		return 0;
}



//����������ʾ
void LCDDispIP()
{
	  uint8_t buf[10]={0};
		//��ʾIP
		buf[0]=0;
		buf[1]=packFlash.netIpFlash.localIp[0];
		LCDWtite(LOCAL_IP1_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.localIp[1];
		LCDWtite(LOCAL_IP2_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.localIp[2];
		LCDWtite(LOCAL_IP3_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.localIp[3];
		LCDWtite(LOCAL_IP4_ADDR,buf,1*2);
	  //��ʾ�˿�
		buf[1]=packFlash.netIpFlash.macaddr;
		LCDWtite(PHY_PORT_ADDR,buf,1*2);
		//Զ��IP
		buf[1]=packFlash.netIpFlash.remoteIp[0];
		LCDWtite(REMOTE_IP1_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.remoteIp[1];
		LCDWtite(REMOTE_IP2_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.remoteIp[2];
		LCDWtite(REMOTE_IP3_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.remoteIp[3];
		LCDWtite(REMOTE_IP4_ADDR,buf,1*2);
		//����IP
		buf[1]=packFlash.netIpFlash.gateway[0];
		LCDWtite(GATEWAY_IP1_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.gateway[1];
		LCDWtite(GATEWAY_IP2_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.gateway[2];
		LCDWtite(GATEWAY_IP3_ADDR,buf,1*2);
		buf[1]=packFlash.netIpFlash.gateway[3];
		LCDWtite(GATEWAY_IP4_ADDR,buf,1*2);
		//Զ��port
		buf[0]=0;
		buf[1]=0;
		buf[2]=(uint8_t)(packFlash.netIpFlash.remotePort>>8);
		buf[3]=(uint8_t)(packFlash.netIpFlash.remotePort);
		LCDWtite(REMOTE_PORT_ADDR,buf,2*2);
}
//����������ʾ
void LCDDispUart()
{
	  uint8_t buf[10]={0};
		//��ʾ�˿�1������
		buf[0]=(uint8_t)(packFlash.uartBps[0]>>24);
		buf[1]=(uint8_t)(packFlash.uartBps[0]>>16);
		buf[2]=(uint8_t)(packFlash.uartBps[0]>>8);
		buf[3]=(uint8_t)(packFlash.uartBps[0]>>0);
		LCDWtite(PORT1_ADDR,buf,2*2);
		
		//��ʾ�˿�2������
		buf[0]=(uint8_t)(packFlash.uartBps[1]>>24);
		buf[1]=(uint8_t)(packFlash.uartBps[1]>>16);
		buf[2]=(uint8_t)(packFlash.uartBps[1]>>8);
		buf[3]=(uint8_t)(packFlash.uartBps[1]>>0);
		LCDWtite(PORT2_ADDR,buf,2*2);
		//��ʾ�˿�3������
		buf[0]=(uint8_t)(packFlash.uartBps[2]>>24);
		buf[1]=(uint8_t)(packFlash.uartBps[2]>>16);
		buf[2]=(uint8_t)(packFlash.uartBps[2]>>8);
		buf[3]=(uint8_t)(packFlash.uartBps[2]>>0);
		LCDWtite(PORT3_ADDR,buf,2*2);
		//��ʾ�˿�4������
		buf[0]=(uint8_t)(packFlash.uartBps[3]>>24);
		buf[1]=(uint8_t)(packFlash.uartBps[3]>>16);
		buf[2]=(uint8_t)(packFlash.uartBps[3]>>8);
		buf[3]=(uint8_t)(packFlash.uartBps[3]>>0);
		LCDWtite(PORT4_ADDR,buf,2*2);
}


//lcd��Ļ���ô��ڲ�����
//void LCDConfUart()111
//{
//	  uint8_t buf[10]={0};
//		//��ʾ�˿�1������
//		buf[0]=(uint8_t)(packFlash.uartBps[0]>>24);
//		buf[1]=(uint8_t)(packFlash.uartBps[0]>>16);
//		buf[2]=(uint8_t)(packFlash.uartBps[0]>>8);
//		buf[3]=(uint8_t)(packFlash.uartBps[0]>>0);
//		LCDWtite(PORT1_ADDR,buf,2*2);
//		
//		//��ʾ�˿�2������
//		buf[0]=(uint8_t)(packFlash.uartBps[1]>>24);
//		buf[1]=(uint8_t)(packFlash.uartBps[1]>>16);
//		buf[2]=(uint8_t)(packFlash.uartBps[1]>>8);
//		buf[3]=(uint8_t)(packFlash.uartBps[1]>>0);
//		LCDWtite(PORT2_ADDR,buf,2*2);
//		//��ʾ�˿�3������
//		buf[0]=(uint8_t)(packFlash.uartBps[2]>>24);
//		buf[1]=(uint8_t)(packFlash.uartBps[2]>>16);
//		buf[2]=(uint8_t)(packFlash.uartBps[2]>>8);
//		buf[3]=(uint8_t)(packFlash.uartBps[2]>>0);
//		LCDWtite(PORT3_ADDR,buf,2*2);
//		//��ʾ�˿�4������
//		buf[0]=(uint8_t)(packFlash.uartBps[3]>>24);
//		buf[1]=(uint8_t)(packFlash.uartBps[3]>>16);
//		buf[2]=(uint8_t)(packFlash.uartBps[3]>>8);
//		buf[3]=(uint8_t)(packFlash.uartBps[3]>>0);
//		LCDWtite(PORT4_ADDR,buf,2*2);
//}
//LCD��ʾMCUID

void LCDDispMCUID()
{
	  //int k=0;
	  uint8_t buf[ACUID_LEN]={0};
//		k=sizeof(packFlash.acuId);
		for(int i=0;i<sizeof(packFlash.acuId);i++){//ACUID_LEN
			  if((uint8_t)packFlash.acuId[i]==0xff){
					 packFlash.acuId[i]=0;
				}
			 	buf[i]=packFlash.acuId[i];
		}
		int j=0;
		//k=strlen(packFlash.acuId);
		while((strlen(packFlash.acuId)+j)<ACUID_LEN){
				buf[strlen(packFlash.acuId)+j]=0xff;
				j++;
		}
		LCDWtite(MCUID_ADDR,buf,ACUID_LEN);
}


//5A A5 05 82 1A0C 0001 ֹͣ
//5A A5 05 82 1A0C 0000  ��ʼ
//����lcd����״̬ �����߻��ߴ�������ʱ�����
void LCDDispNetErrState()
{
	  extern rt_bool_t gbNetState;
//	  static rt_bool_t state =RT_FALSE;//��Ļ�ϵ��Ĭ����ʾҲ�ǵ��ߵ�
//	  if(state!=gbNetState){//״̬���ʱ����ȥ����
				uint8_t buf[10]={0};
				buf[0]=0;
				buf[1]=gbNetState;
				LCDWtite(NET_ERR_DISPLAY_ADDR,buf,1*2);

}
//������ʾ���ߴ���
int offLineIndex=1;
void  LCDDispNetOffline()
{
	  uint8_t buf[10]={0};
		extern rt_bool_t gbNetState;
		//��ʾ�ܹ����ߴ���
		buf[0]=(uint8_t)(offLine.times>>24);
		buf[1]=(uint8_t)(offLine.times>>16);
		buf[2]=(uint8_t)(offLine.times>>8);
		buf[3]=(uint8_t)(offLine.times>>0);
		LCDWtite(NET_OFFLINE_TOTALTIMES_ADDR,buf,2*2);
		if(offLine.times==0){
				//��ʾ�ڼ��ε���
				buf[0]=0;
				buf[1]=0;
				buf[2]=0;
				buf[3]=0;
				LCDWtite(NET_OFFLINE_TIMES_ADDR,buf,2*2);
						//��ʾ�ܹ����ߵ�ʱ��
				if(gbNetState==RT_FALSE){
					  int tick = rt_tick_get()/1000;
						buf[0]=(uint8_t)(tick>>24);
						buf[1]=(uint8_t)(tick>>16);
						buf[2]=(uint8_t)(tick>>8);
						buf[3]=(uint8_t)(tick>>0);
				}
				LCDWtite(NET_OFFLINE_RELAYTIME_ADDR,buf,2*2);
		}
		else{ 
				buf[0]=(uint8_t)(offLineIndex>>24);
				buf[1]=(uint8_t)(offLineIndex>>16);
				buf[2]=(uint8_t)(offLineIndex>>8);
				buf[3]=(uint8_t)(offLineIndex>>0);
				LCDWtite(NET_OFFLINE_TIMES_ADDR,buf,2*2);
			  int offTime;
				if(gbNetState==RT_FALSE){
						//rt_kprintf("[offLine]a the %d Time,relayTimer %d %d��\r\n",offLineIndex,rt_tick_get()/1000,offLine.relayTimer[offLineIndex]);
						if(offLineIndex==offLine.times)
								offTime=(rt_tick_get()/1000-offLine.relayTimer[offLineIndex]);//�����˴˴μ���һֱ++
						else
								offTime=offLine.relayTimer[offLineIndex];
				}
				else{
						//rt_kprintf("[offLine]b the %d Times,relayTimer %d ��\r\n",offLineIndex,offLine.relayTimer[offLineIndex]);
						offTime=offLine.relayTimer[offLineIndex];
				}
				buf[0]=(uint8_t)(offTime>>24);
				buf[1]=(uint8_t)(offTime>>16);
				buf[2]=(uint8_t)(offTime>>8);
				buf[3]=(uint8_t)(offTime>>0);
				LCDWtite(NET_OFFLINE_RELAYTIME_ADDR,buf,2*2);
		}
		
}





