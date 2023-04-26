/*
**************************************************************************************************
* @file    		w5500_conf.c
* @author  		WIZnet Software Team 
* @version 		V1.0
* @date    		2015-02-14
* @brief  		����MCU����ֲW5500������Ҫ�޸ĵ��ļ�������W5500��MAC��IP��ַ
**************************************************************************************************
*/
#include <stdio.h> 
#include <string.h>

#include "w5500_conf.h"
#include "utility.h"
#include "w5500.h"
#include "dhcp.h"
#include "board.h"
/*IP���÷���ѡ��������ѡ��*/
const uint8	ip_from = IP_FROM_DEFINE;//IP_FROM_DEFINE;//IP_FROM_DEFINE;				///IP_FROM_DHCP


const static char sign[]="[w55Conf]";
extern SPI_HandleTypeDef hspi1;
CONFIG_MSG  		ConfigMsg;																	/*���ýṹ��*/
EEPROM_MSG_STR  EEPROM_MSG;															/*EEPROM�洢��Ϣ�ṹ��*/

/*����MAC��ַ,������W5500�����������ͬһ�ֳ���������ʹ�ò�ͬ��MAC��ַ*/
uint8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};
#if 1
/*����Ĭ��IP��Ϣ*/
//uint8 local_ip[4]  ={192,168,16,88};											/*����W5500Ĭ��IP��ַ*/
uint8 subnet[4]    ={255,255,255,0};										/*����W5500Ĭ����������*/
//uint8 gateway[4]   ={192,168,16,1};											/*����W5500Ĭ������*/
uint8 dns_server[4]={114,114,114,114};									/*����W5500Ĭ��DNS*/
uint16 local_port=5000;	                       					/*���屾�ض˿�*/

/*����Զ��IP��Ϣ*/
//uint8  remote_ip[4]={192,168,1,109};											/*Զ��IP��ַ*/
//uint16 remote_port=8080;																/*Զ�˶˿ں�*/
//uint8  remote_ip[4]={192,168,16,6};											/*Զ��IP��ַ*/

#else

//uint8 local_ip[4]  ={192,168,1,88};											/*����W5500Ĭ��IP��ַ*/
uint8 subnet[4]    ={255,255,255,0};										/*����W5500Ĭ����������*/
//uint8 gateway[4]   ={192,168,1,1};											/*����W5500Ĭ������*/
uint8 dns_server[4]={114,114,114,114};									/*����W5500Ĭ��DNS*/

uint16 local_port=5000;	                       					/*���屾�ض˿�*/

//uint16 remote_port=11001;																
//uint8  remote_ip[4]={192,168,1,102};											/*????ip*/
#endif



uint8   dhcp_ok   = 0;													   			/*dhcp�ɹ���ȡIP*/
uint32	ms        = 0;															  	/*�������*/
uint32	dhcp_time = 0;															  	/*DHCP���м���*/
volatile uint8_t	    ntptimer  = 0;															  	/*NPT�����*/

/**
*@brief		����W5500��IP��ַ
*@param		��
*@return	��
*/
void set_w5500_ip(void)
{	
	mac[5]=packFlash.netIpFlash.macaddr;
		
   /*���ƶ����������Ϣ�����ýṹ��*/
	memcpy(ConfigMsg.mac, mac, 6);
	memcpy(ConfigMsg.lip,packFlash.netIpFlash.localIp,4);
	memcpy(ConfigMsg.sub,subnet,4);
	memcpy(ConfigMsg.gw,packFlash.netIpFlash.gateway,4);
	memcpy(ConfigMsg.dns,dns_server,4);
	if(ip_from==IP_FROM_DEFINE)	
		printf("%sʹ�ö����IP��Ϣ����W5500\r\n",sign);
	
	

	/*ʹ��DHCP��ȡIP�����������DHCP�Ӻ���*/		
	if(ip_from==IP_FROM_DHCP)								
	{
		/*����DHCP��ȡ��������Ϣ�����ýṹ��*/
		if(dhcp_ok==1)
		{
			printf("%sIP from DHCP\r\n",sign);	 
			memcpy(ConfigMsg.lip,DHCP_GET.lip, 4);
			memcpy(ConfigMsg.sub,DHCP_GET.sub, 4);
			memcpy(ConfigMsg.gw,DHCP_GET.gw, 4);
			memcpy(ConfigMsg.dns,DHCP_GET.dns,4);
		}
		else
		{
			printf("%sDHCP�ӳ���δ����,���߲��ɹ�\r\n",sign);
			printf("%sʹ�ö����IP��Ϣ����W5500\r\n",sign);
		}
	}
		
	/*����������Ϣ��������Ҫѡ��*/	
	ConfigMsg.sw_ver[0]=FW_VER_HIGH;
	ConfigMsg.sw_ver[1]=FW_VER_LOW;	

	/*��IP������Ϣд��W5500��Ӧ�Ĵ���*/	
	setSUBR(ConfigMsg.sub);
	setGAR(ConfigMsg.gw);
	setSIPR(ConfigMsg.lip);
	
	getSIPR (packFlash.netIpFlash.localIp);			
	printf("%sW5500 IP��ַ   : %d.%d.%d.%d\r\n", sign,packFlash.netIpFlash.localIp[0],packFlash.netIpFlash.localIp[1],\
												packFlash.netIpFlash.localIp[2],packFlash.netIpFlash.localIp[3]);
	getSUBR(subnet);
	printf("%sW5500 �������� : %d.%d.%d.%d\r\n",sign, subnet[0],subnet[1],subnet[2],subnet[3]);
	getGAR(packFlash.netIpFlash.gateway);
	printf("%sW5500 ����     : %d.%d.%d.%d\r\n",sign, packFlash.netIpFlash.gateway[0],packFlash.netIpFlash.gateway[1],\
													packFlash.netIpFlash.gateway[2],packFlash.netIpFlash.gateway[3]);
	printf("%sW5500 �����ַ : %02X %02X %02X %02X %02X %02X\r\n",sign, mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

/**
*@brief		����W5500��MAC��ַ
*@param		��
*@return	��
*/
void set_w5500_mac(void)
{
	memcpy(ConfigMsg.mac, mac, 6);
	setSHAR(ConfigMsg.mac);	/**/
	memcpy(DHCP_GET.mac, mac, 6);
}

/**
*@brief		W5500Ƭѡ�ź����ú���
*@param		val: Ϊ��0����ʾƬѡ�˿�Ϊ�ͣ�Ϊ��1����ʾƬѡ�˿�Ϊ��
*@return	��
*/
void wiz_cs(uint8_t val)
{
	if (val == LOW) 
	{
	  //GPIO_ResetBits(WIZ_SPIx_SCS_PORT, WIZ_SPIx_SCS); 		
		HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_RESET);
	}
	else if (val == HIGH)
	{

		HAL_GPIO_WritePin(W5500_CS_GPIO_Port, W5500_CS_Pin, GPIO_PIN_SET);
	}
}

/**
*@brief		����W5500��Ƭѡ�˿�SCSnΪ��
*@param		��
*@return	��
*/
void iinchip_csoff(void)
{
	wiz_cs(LOW);
}

/**
*@brief		����W5500��Ƭѡ�˿�SCSnΪ��
*@param		��
*@return	��
*/
void iinchip_cson(void)
{	
   wiz_cs(HIGH);
}

/**
*@brief		W5500��λ���ú���
*@param		��
*@return	��
*/
void reset_w5500(void)
{
	HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
	rt_thread_mdelay(200);
  HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET);	
	rt_thread_mdelay(200);
	HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
	rt_thread_mdelay(1600);
}


uint8_t SPI_SendByte(uint8_t byte)
{
 uint8_t rxbyte=0;
 uint8_t SPITimeout =200;
 while(__HAL_SPI_GET_FLAG(&hspi1,SPI_FLAG_TXE)==RESET)
 {
  if((SPITimeout--)==0){
		HAL_SPI_ErrorCallback(&hspi1);
		return 0;
	}
 }
 HAL_SPI_TransmitReceive(&hspi1,&byte,&rxbyte,1,100);
 return rxbyte;
}

/**
*@brief		STM32 SPI1��д8λ����
*@param		dat��д���8λ����
*@return	��
*/
uint8  IINCHIP_SpiSendData(uint8 dat)
{
   return(SPI_SendByte(dat));
}



/**
*@brief		д��һ��8λ���ݵ�W5500
*@param		addrbsb: д�����ݵĵ�ַ
*@param   data��д���8λ����
*@return	��
*/
void IINCHIP_WRITE( uint32 addrbsb,  uint8 data)
{
   iinchip_csoff();                              		
   IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);	
   IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
   IINCHIP_SpiSendData( (addrbsb & 0x000000F8) + 4);  
   IINCHIP_SpiSendData(data);                   
   iinchip_cson();                            
}

/**
*@brief		��W5500����һ��8λ����
*@param		addrbsb: д�����ݵĵ�ַ
*@param   data����д��ĵ�ַ����ȡ����8λ����
*@return	��
*/
uint8 IINCHIP_READ(uint32 addrbsb)
{
   uint8 data = 0;
   iinchip_csoff();                            
   IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);
   IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
   IINCHIP_SpiSendData( (addrbsb & 0x000000F8))    ;
   data = IINCHIP_SpiSendData(0x00);            
   iinchip_cson();                               
   return data;    
}

/**
*@brief		��W5500д��len�ֽ�����
*@param		addrbsb: д�����ݵĵ�ַ
*@param   buf��д���ַ���
*@param   len���ַ�������
*@return	len�������ַ�������
*/
uint16 wiz_write_buf(uint32 addrbsb,uint8* buf,uint16 len)
{
   uint16 idx = 0;
   if(len == 0) printf("%sUnexpected2 length 0\r\n",sign);
   iinchip_csoff();                               
   IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);
   IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
   IINCHIP_SpiSendData( (addrbsb & 0x000000F8) + 4); 
   for(idx = 0; idx < len; idx++)
   {
     IINCHIP_SpiSendData(buf[idx]);
   }
   iinchip_cson();                           
   return len;  
}

/**
*@brief		��W5500����len�ֽ�����
*@param		addrbsb: ��ȡ���ݵĵ�ַ
*@param 	buf����Ŷ�ȡ����
*@param		len���ַ�������
*@return	len�������ַ�������
*/
uint16 wiz_read_buf(uint32 addrbsb, uint8* buf,uint16 len)
{
  uint16 idx = 0;
  if(len == 0)
  {
    printf("%sUnexpected2 length 0\r\n",sign);
  }
  iinchip_csoff();                                
  IINCHIP_SpiSendData( (addrbsb & 0x00FF0000)>>16);
  IINCHIP_SpiSendData( (addrbsb & 0x0000FF00)>> 8);
  IINCHIP_SpiSendData( (addrbsb & 0x000000F8));    
  for(idx = 0; idx < len; idx++)                   
  {
    buf[idx] = IINCHIP_SpiSendData(0x00);
  }
  iinchip_cson();                                  
  return len;
}



//netIpFlashStru netIpFlash  __attribute__ ((aligned (4)));;

static void net(int argc, char *argv[])
{
	  if(ip_from != IP_FROM_DEFINE){
				printf("%sERR:use IP_FROM_DHCP\r\n",sign);
				return;
		}
		if(argc==1){
				goto ERR;
		}
//		int i;
		if(0==rt_strcmp((char *)"macaddr", argv[1])){
				if(argc!=3){
					goto ERR;
				}
				mac[5]=atoi16(argv[2],10);
				packFlash.netIpFlash.macaddr=mac[5];
				rt_kprintf("%smacaddr OK\n",sign);

		}
		else 	if(0==rt_strcmp((char *)"localIp", argv[1])){
				if(argc!=6){
					goto ERR;
				}
				packFlash.netIpFlash.localIp[0] =atoi16(argv[2],10);
				packFlash.netIpFlash.localIp[1] =atoi16(argv[3],10);
				packFlash.netIpFlash.localIp[2] =atoi16(argv[4],10);
				packFlash.netIpFlash.localIp[3] =atoi16(argv[5],10);

				rt_kprintf("%slocalIp OK\n",sign);
		}
		else 	if(0==rt_strcmp((char *)"gateway", argv[1])){
				if(argc!=6){
					goto ERR;
				}
			  packFlash.netIpFlash.gateway[0] =atoi16(argv[2],10);
				packFlash.netIpFlash.gateway[1] =atoi16(argv[3],10);
				packFlash.netIpFlash.gateway[2] =atoi16(argv[4],10);
				packFlash.netIpFlash.gateway[3] =atoi16(argv[5],10); 
	
				rt_kprintf("%sgateway OK\n",sign);

		}
		else 	if(0==rt_strcmp((char *)"remoteIp", argv[1])){
				if(argc!=6){
					goto ERR;
				}
			  packFlash.netIpFlash.remoteIp[0] =atoi16(argv[2],10);
				packFlash.netIpFlash.remoteIp[1] =atoi16(argv[3],10);
				packFlash.netIpFlash.remoteIp[2] =atoi16(argv[4],10);
				packFlash.netIpFlash.remoteIp[3] =atoi16(argv[5],10);
		
				rt_kprintf("%sremoteIp OK\n",sign);

				//STMFLASH_Write(FLASH_IP_SAVE_ADDR,(uint32_t*)&netIpFlash,sizeof(netIpFlash));
		}
		else 	if(0==rt_strcmp((char *)"remotePort", argv[1])){
				if(argc!=3){
					goto ERR;
				}
				packFlash.netIpFlash.remotePort=atoi32(argv[2],10);

		
				rt_kprintf("%sremotePort OK\n",sign);
		}
		
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[net macaddr 100]\n",sign);
		rt_kprintf("%s[net localIp 192 168 1 122]\n",sign);
		rt_kprintf("%s[net gateway 192 168 1 1]\n",sign);
		rt_kprintf("%s[net remoteIp 192 168 1 100]\n",sign);
		rt_kprintf("%s[net remotePort 8080]\n",sign);

}
MSH_CMD_EXPORT(net,ip port config);//FINSH_FUNCTION_EXPORT_CMD

