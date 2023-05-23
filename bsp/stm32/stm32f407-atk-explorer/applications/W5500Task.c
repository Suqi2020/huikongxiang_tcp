#include "W5500Task.h"
#include "board.h"

//w5500����״̬��ά�� 
const static char task[]="[w55task]";

rt_sem_t  w5500Iqr_semp = RT_NULL;//w5500������ʱ���ж�����

/***************----- ��������������� -----***************/
//unsigned char Gateway_IP[4];//����IP��ַ 
//unsigned char Sub_Mask[4];	//�������� 
//unsigned char Phy_Addr[6];	//�����ַ(MAC) 
//unsigned char IP_Addr[4];	//����IP��ַ 

//unsigned char S0_Port[2];	//�˿�0�Ķ˿ں�(5000) 
//unsigned char S0_DIP[4];	//�˿�0Ŀ��IP��ַ 
//unsigned char S0_DPort[2];	//�˿�0Ŀ�Ķ˿ں�(6000) 



/***************----- �˿ڵ�����ģʽ -----***************/
unsigned char S0_Mode =3;	//�˿�0������ģʽ,0:TCP������ģʽ,1:TCP�ͻ���ģʽ,2:UDP(�㲥)ģʽ
#define TCP_SERVER	0x00	//TCP������ģʽ
#define TCP_CLIENT	0x01	//TCP�ͻ���ģʽ 

rt_bool_t  gbNetState =RT_FALSE;   //����״̬  false ����  true����




/*******************************************************************************
* ������  : Load_Net_Parameters
* ����    : װ���������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ���ء����롢�����ַ������IP��ַ���˿ںš�Ŀ��IP��ַ��Ŀ�Ķ˿ںš��˿ڹ���ģʽ
*******************************************************************************/
//void Load_Net_Parameters(void)
//{
//	Gateway_IP[0] = 192;//�������ز���
//	Gateway_IP[1] = 168;
//	Gateway_IP[2] = 1;
//	Gateway_IP[3] = 1;

//	Sub_Mask[0]=255;//������������
//	Sub_Mask[1]=255;
//	Sub_Mask[2]=255;
//	Sub_Mask[3]=0;

//	Phy_Addr[0]=0x0c;//���������ַ
//	Phy_Addr[1]=0x29;
//	Phy_Addr[2]=0xab;
//	Phy_Addr[3]=0x7c;
//	Phy_Addr[4]=0x00;
//	Phy_Addr[5]=0x01;

//	IP_Addr[0]=192;//���ر���IP��ַ
//	IP_Addr[1]=168;
//	IP_Addr[2]=1;
//	IP_Addr[3]=199;

//	S0_Port[0] = 0x13;//���ض˿�0�Ķ˿ں�5000 
//	S0_Port[1] = 0x88;

//	S0_DIP[0]=192;//���ض˿�0��Ŀ��IP��ַ
//	S0_DIP[1]=168;
//	S0_DIP[2]=1;
//	S0_DIP[3]=190;
//	
//	S0_DPort[0] = 0x17;//���ض˿�0��Ŀ�Ķ˿ں�6000
//	S0_DPort[1] = 0x70;

//	S0_Mode=TCP_CLIENT;//���ض˿�0�Ĺ���ģʽ,TCP�ͻ���ģʽ
//}

void  w5500Task(void *parameter)
{
	static rt_err_t ret=0;
	W5500_enum W5500State=W5500InitEnum;
  static uint8_t dhcpTick=0;
	static uint8_t rstW5500Ct=0;
//  stm32_flash_read(FLASH_IP_SAVE_ADDR,(uint8_t*)&netIpFlash,sizeof(netIpFlash));
  while(1) 														/*ѭ��ִ�еĺ���*/ 
  {
#ifdef  USE_WDT
		rt_event_send(&WDTEvent,EVENT_WDT_W5500);
#endif
		switch(W5500State)
		{
			case W5500InitEnum:
						w5500Init();
			      W5500State=W5500DHCPEnum;
			      rt_kprintf("%s init����\r\n",task);
				break;
			case W5500DHCPEnum:
				    if(ip_from==IP_FROM_DHCP){//IP_FROM_DHCP)
							if(RT_TRUE == do_dhcp()){                        /*DHCP���Գ���*/
									W5500State=W5500NetOKEnum;
									break;
							}
						}
						else{
							  set_w5500_ip();
								rt_kprintf("%sW5500 ������IP:%d.%d.%d.%d\r\n",task,packFlash.netIpFlash.remoteIp[0],\
							      packFlash.netIpFlash.remoteIp[1],packFlash.netIpFlash.remoteIp[2],packFlash.netIpFlash.remoteIp[3]);
								rt_kprintf("%sW5500 �����˿�:%d \r\n",task,packFlash.netIpFlash.remotePort);
								W5500State=W5500NetOKEnum;

								break;
						}
						if(dhcpTick++>=5){//1���׼  200*5
								dhcpTick=0;
								dhcp_time++;//dhcp��ʱ ģ�ⶨʱ��
							  rstW5500Ct++;
						}  
						if(rstW5500Ct>=30){//û�����Ļ� ÿ��30��ȥ���³�ʼ��w5500
							 rstW5500Ct=0;
							 W5500State=W5500InitEnum;
						}
						rt_thread_mdelay(200);//��Ҫ�޸� 
				break;
			case W5500NetOKEnum:{
			      //ret=rt_sem_take(w5500Iqr_semp,1000);//����1�� ��ѯ�ж�״̬ ���ж���//RT_WAITING_FOREVER
			      static int count=0;      
						void loopback_tcp(uint16 port);
						loopback_tcp( packFlash.netIpFlash.remotePort);
						rt_thread_delay(100);
					  if(gbNetState ==RT_FALSE){//û����  ���³�ʼ��
								if(count++>5){ //5����������ж�5�� ��û���� ����
										W5500State=W5500InitEnum;
									  count=0;
								}
								
						}
				break;}
//			case W5500NetOKEnum:
//			      ret=rt_sem_take(w5500Iqr_semp,1000);//����1�� ��ѯ�ж�״̬ ���ж���//RT_WAITING_FOREVER
//			      static int count=0;      
//						if(ret==RT_EOK){
//								W5500ISR();//w5500
//								loopback_tcpc(SOCK_TCPC, packFlash.netIpFlash.remotePort);//W5500�ڲ��Զ�ά���������� �˴�ֻ���Ĵ���
//						}

//					  if(gbNetState ==RT_FALSE){//û����  ���³�ʼ��
//								if(count++>5){ //5����������ж�5�� ��û���� ����
//										W5500State=W5500InitEnum;
//									  count=0;
//								}
//								
//						}
//				break;
		}
	}

}	
//��װ�ⲿ���÷��� �����ӿ�
void netSend(uint8_t *data,int len)
{
		if(send(SOCK_TCPC,	data,len)==0){//��������ʱ����ʵ���ط�  2s���ղ����ظ�
				gbNetState=RT_FALSE;//������� ��������
				
			  if(offLine.times<(sizeof(offLine.relayTimer)/sizeof(offLine.relayTimer[0]))){
					  offLine.times++;
						offLine.relayTimer[offLine.times]=rt_tick_get()/1000;
				}
				rt_kprintf("%snet send fail %d %d\n",task,offLine.times,sizeof(offLine.relayTimer)/sizeof(offLine.relayTimer[0]));
				extern void  LCDDispNetOffline();
				extern void  LCDDispNetErrState();
				LCDDispNetOffline();
			  LCDDispNetErrState();
		}
		else{
				rt_kprintf("%snet send succ\n",task);
		}	
}


	
