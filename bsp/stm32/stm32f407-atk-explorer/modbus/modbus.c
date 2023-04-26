#include "board.h"
//#include    "modbus.h"

const static char sign[]="[modbus]";
/*
1��ʲôʱ���ȡ���� 
1.1 ��ʱ��ȡ  ���з��� 485 ��ʱ500ms �ȴ����н��� ������������  ����1�� ���Ᵽ��
1.2 ��������ȡ ���� ���з��� 485 ��ʱ500ms �ȴ����н��� ������������  ���뻥�Ᵽ��
    ÿ��485 1�����ն��� ����ֱ�ӵ��ô��ڷ��ͽӿ�
Ҫ����ʵ��Ѹ���л�����485�ӿ���ʹ�� ������ֻ��Ҫ�޸Ĵ��ڷ��ͽӿ� ���жϽ��սӿڼ���
      rs485Circula.c-cirCurrUartSend(uint8_t *buf,int len) ��drv_uart.c-USART2_IRQHandler��
����2346 modbus ����1 debug ����5 ������
//modbus�ӿ�ͨ��read  03 06 10 
*/
//��һ�������Ĵ���
//MQTTLenString test;
//// out --�������
uint8_t modbusReadReg(uint16_t slavAddr,uint16_t regAddr,uint8_t cmd,uint16_t len,uint8_t * out)
{
		int i=0;
	  out[i]=slavAddr;					 			i++;
	  out[i]=cmd;      					 		i++;
	  out[i]=(uint8_t)(regAddr>>8);   i++;
	  out[i]=(uint8_t) regAddr;       i++;
		out[i]=(uint8_t)(len>>8);       i++;
	  out[i]=(uint8_t) len;       		i++;
	  uint16_t crcRet=RTU_CRC(out ,i);
	  out[i]=(uint8_t)(crcRet>>8);    i++;
	  out[i]=crcRet;       						i++;
		return i;
}


//modbus ��bitλ�Ĵ���
uint8_t modbusReadBitReg(uint16_t slavAddr,uint16_t regAddr,uint16_t len,uint8_t * out)
{
		int i=0;
	  out[i]=slavAddr;					 			i++;
	  out[i]=READM_BIT;      					i++;
	  out[i]=(uint8_t)(regAddr>>8);   i++;
	  out[i]=(uint8_t) regAddr;       i++;
		out[i]=(uint8_t)(len>>8);       i++;
	  out[i]=(uint8_t) len;       		i++;
	  uint16_t crcRet=RTU_CRC(out ,i);
	  out[i]=(uint8_t)(crcRet>>8);    i++;
	  out[i]=crcRet;       						i++;
		return i;
}
//дһ���Ĵ���
uint8_t modbusWriteOneReg(uint16_t slavAddr,uint16_t regAddr,uint16_t value,uint8_t *out)
{
		int i=0;
	  out[i]=slavAddr;					 			i++;
	  out[i]=WRITE;      					 		i++;
	  out[i]=(uint8_t)(regAddr>>8);   i++;
	  out[i]=(uint8_t) regAddr;       i++;
		out[i]=(uint8_t)(value>>8);   	i++;
	  out[i]=(uint8_t) value;     		i++;
	  uint16_t crcRet=RTU_CRC(out ,i);
	  out[i]=(uint8_t)(crcRet>>8);    i++;
	  out[i]=crcRet;       						i++;	
    return i;	
}
//д����Ĵ���  len  ���ݳ��� len/2�Ĵ�������  OUT-�������
uint8_t modbusWriteMultReg(uint16_t slavAddr,uint16_t regAddr,uint16_t len,uint8_t *in,uint8_t *out)
{
		int i=0;
	  out[i]=slavAddr;					 			i++;
	  out[i]=WRITE_MUL;      					i++;
	  out[i]=(uint8_t)(regAddr>>8);   i++;
	  out[i]=(uint8_t) regAddr;       i++;
		out[i]=(uint8_t)((len/2)>>8);   i++;
	  out[i]=(uint8_t) len/2;       	i++; //�Ĵ�������
	  out[i]=(uint8_t) len;       		i++;//���ݳ���
	  for(int j=0;j<len;j++,i++){
				out[i]=in[j];
		}
	  uint16_t crcRet=RTU_CRC(out ,i);
	  out[i]=(uint8_t)(crcRet>>8);    i++;
	  out[i]=crcRet;       						i++;	
    return i;			
}
//modbus�ظ�����У��   readFLAG TRUE-��     FALSE-д
//0 succ  1 slave addr or bsp err    2 modbus uart err
int  modbusRespCheck(uint16_t slavAddr,uint8_t *buf,uint16_t len,rt_bool_t readFlag)
{
	  if(len<2){
				rt_kprintf("%sERR:no resp\r\n",sign);
				return 2;
		}
		if(buf[0]!=slavAddr){
				rt_kprintf("%sERR:slaveADDR\r\n",sign);
				return 1;
		}
		if(readFlag==RT_TRUE){
				if((buf[2]+2+1+2)!=len){
								rt_kprintf("%sERR:��������\r\n",sign);
						}
						len =buf[2]+2+1+2;//����ˢ�³���
		}
		else{
			#define  WR_RESP_LEN  8
				len =WR_RESP_LEN;//����ˢ�³���
		}
		uint16_t respCrc=(buf[len-2]<<8)+buf[len-1];
	  uint16_t checkCrc= RTU_CRC(buf,len-2);
		if(respCrc!=checkCrc){
				rt_kprintf("%sCRC check err 0x%04x  0x%04x\r\n",sign,respCrc,checkCrc);
				return 0;
		}
		return 0;
}








