#include "board.h"
//�ο� ��H-STCϵ��ѹ��ʽ������Modbus RTUЭ��˵��-20191031��
//<<ѹ��ʽ������ GY-STC-2000>> Ĭ�ϲ�����9600  modbus��ַ 0xb1(����) �������ǩ��2λ  Э���ĵ�����
//�޸��豸��ַ FF FF 03 0A���豸�����ĳ���ַ��01���̵�ַ 
//   FF FF 03 0A 6E 01 20 21 09 08 00 B1 01 01
//  24+��ɫ��24-��ɫ��A+��ɫ��B-��ɫ
const static char sign[]="[������]";
static  bool alarmFLag=false;
//#define   SLAVE_ADDR     0X02 
//#define   LENTH          50  //���������õ���������buf����

typedef struct{
	  float temp;//����100 ����float����  ��λ0C
	   union {
				float flotVal;
				int   intVal;
		} height;
		uint8_t respStat;
//float height;//����10 ����float����  ��λmm
}pressSettlStru;
pressSettlStru pressSettle[PRESSSETTL_485_NUM];
//���س����ǵ�ͨѶ״̬ true--ͨѶ�ɹ� false--ͨѶʧ��
int pressSettleState(int i)
{
		return pressSettle[i].respStat;
}
//������ڷ��� 
static void pressSettlUartSend(int num,uint8_t *buf,int len)
{
		rs485UartSend(sheet.pressSetl[num].useUartNum,buf, len);
}

///////////////////////////////////////��д�Ĵ�����ز���////////////////////////////////////////



uint8_t tongHeModbusRead(uint16_t slavAddr,uint16_t regAddr,uint16_t len,uint8_t * out)
{
		int i=0;
	  out[i]=slavAddr;					 			i++;
	  out[i]=0x04;      					 		i++;
	  out[i]=(uint8_t)(regAddr>>8);   i++;
	  out[i]=(uint8_t) regAddr;       i++;
		out[i]=(uint8_t)(len>>8);       i++;
	  out[i]=(uint8_t) len;       		i++;
	  uint16_t crcRet=RTU_CRC(out ,i);
	  out[i]=(uint8_t)(crcRet>>8);    i++;
	  out[i]=crcRet;       						i++;
		return i;
}
//�����ǱȽ���ֵ��������Ӧ��flag���
static void pressStlCheckSetFlag(int num)
{
		alarmFLag=false;
	  if(sheet.modbusPreSettl[num].tempUpLimit!=0){
			if(pressSettle[num].temp>=sheet.modbusPreSettl[num].tempUpLimit){
					inpoutpFlag.modbusPreSettl[num].tempUpFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusPreSettl[num].tempLowLimit!=0){
			if(pressSettle[num].temp<=sheet.modbusPreSettl[num].tempLowLimit){
					inpoutpFlag.modbusPreSettl[num].tempLowFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusPreSettl[num].heightUpLimit!=0){
			if(pressSettle[num].height.flotVal>=sheet.modbusPreSettl[num].heightUpLimit){
					inpoutpFlag.modbusPreSettl[num].heightUpFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusPreSettl[num].heightLowLimit!=0){
			if(pressSettle[num].height.flotVal<=sheet.modbusPreSettl[num].heightLowLimit){
					inpoutpFlag.modbusPreSettl[num].heightLowFlag=true;alarmFLag=true;
			}
		}

}


//�� 1A 04 00 01 00 02 23 E0
//�� 1A 04 04 0B 1B 00 1C 23 6F
//��ȡ�����ǵ��¶Ⱥ͸߶�
void readPSTempHeight(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = tongHeModbusRead(sheet.pressSetl[num].slaveAddr,0X0001,2,buf);
//		rt_mutex_take(uartDev[sheet.pressSetl[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		pressSettlUartSend(num,buf,len);
	  rt_kprintf("%spressSettl send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
    len=0;
		memset(buf,0,LENTH);
		
		while(rt_mq_recv(&uartmque[sheet.pressSetl[num].useUartNum], buf+len, 1, 500) == RT_EOK){//115200 ������1ms 10������
				len++;
		}
		if(len!=0){
				rt_kprintf("%srec:",sign);
				for(int j=0;j<len;j++){
						rt_kprintf("%x ",buf[j]);
				}
				rt_kprintf("\n");
		}
		//��ȡ����ֵ ��һ���ж�crc �ڶ�����ȡ
		int ret2=modbusRespCheck(sheet.pressSetl[num].slaveAddr,buf,len,RT_TRUE);
		if(0 == ret2){//ˢ�¶�ȡ����ֵ

        int temp	=(buf[offset]<<8)+buf[offset+1];offset+=2;
			  pressSettle[num].height.intVal=(buf[offset]<<8)+buf[offset+1];
			
				pressSettle[num].temp =temp/100;
				pressSettle[num].respStat=1;
				pressStlCheckSetFlag(num);
			
			  rt_kprintf("%stemp:%0.2f*C height:%0.1fmm read ok\n",sign,pressSettle[num].temp,pressSettle[num].height.flotVal);  
		} 
		else{//��������0
				if(ret2==2){
						//rt_kprintf("%sERR:����485���߻��߹���\r\n",sign);
				}
				pressSettle[num].respStat=0;
			  pressSettle[num].temp	=0;
			  pressSettle[num].height.intVal=0;
			  rt_kprintf("%stemp height read fail\n",sign);
		}
//		pressStlCheckSetFlag(num);
//	  rt_mutex_release(uartDev[sheet.pressSetl[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;

}


/////////////////////////////////////////JSON��ʽ���//////////////////////////////////////////
//�¶ȸ߶�ֵ���




//������json��ʽ���
//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
uint16_t pressSettlJsonPack(bool respFlag)
{
		char* out = NULL;
		//��������
		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		cJSON* nodeobj = NULL;
		cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		// ����ڵ㣨��ֵ�ԣ�
		
		if(respFlag==true){
				cJSON_AddNumberToObject(root, "mid",respMid);
				cJSON_AddStringToObject(root, "packetType","PROPERTIES_485DATA_GET_RESP");
				cJSON_AddNumberToObject(root, "code",0);
		}
		else
		{
				cJSON_AddNumberToObject(root, "mid",mcu.upMessID);
				cJSON_AddStringToObject(root, "packetType","PROPERTIES_485DATA_REP");
		}
		cJSON_AddStringToObject(root, "identifier","settlement_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		
		
		{
			Array = cJSON_CreateArray();
			if (Array == NULL) return 0;
			cJSON_AddItemToObject(root, "params", Array);
			for (int i = 0; i < PRESSSETTL_485_NUM; i++)
			{		
				if(sheet.pressSetl[i].workFlag==RT_TRUE){
					nodeobj = cJSON_CreateObject();
					cJSON_AddItemToArray(Array, nodeobj);
					cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.pressSetl[i].ID));
					//sprintf(sprinBuf,"%d",pressSettle[i].respStat);
					cJSON_AddNumberToObject(nodeobj,"responseStatus",pressSettle[i].respStat);
					
					nodeobj_p= cJSON_CreateObject();
					cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
					sprintf(sprinBuf,"%02f",pressSettle[i].temp);
					cJSON_AddItemToObject(nodeobj_p,"temperature",cJSON_CreateString(sprinBuf));

					sprintf(sprinBuf,"%02f",pressSettle[i].height.flotVal );
					cJSON_AddItemToObject(nodeobj_p,"height",cJSON_CreateString(sprinBuf));
					sprintf(sprinBuf,"%llu",utcTime());
					cJSON_AddItemToObject(nodeobj_p,"monitoringTime",cJSON_CreateString(sprinBuf));
				}
			}
		}
	
		sprintf(sprinBuf,"%llu",utcTime());
		cJSON_AddStringToObject(root,"timestamp",sprinBuf);
		// ��ӡJSON���ݰ�  


		//���
		int len=0;
		packBuf[len]= (uint8_t)(HEAD>>8); len++;
		packBuf[len]= (uint8_t)(HEAD);    len++;
		len+=LENTH_LEN;//json�����������д
		
		// �ͷ��ڴ�  
		
		
		out = cJSON_Print(root);
		rt_strcpy((char *)packBuf+len,out);
		len+=rt_strlen(out);
		if(out!=NULL){
				for(int i=0;i<rt_strlen(out);i++)
						rt_kprintf("%c",out[i]);
				rt_kprintf("\n");
				rt_free(out);
				out=NULL;
		}
		if(root!=NULL){
			cJSON_Delete(root);
			out=NULL;
		}
	

		//lenth
	  packBuf[2]=(uint8_t)((len-LENTH_LEN-HEAD_LEN)>>8);//����json����
	  packBuf[3]=(uint8_t)(len-LENTH_LEN-HEAD_LEN);
	  uint16_t jsonBodyCrc=RTU_CRC(packBuf+HEAD_LEN+LENTH_LEN,len-HEAD_LEN-LENTH_LEN);
	  //crc
	  packBuf[len]=(uint8_t)(jsonBodyCrc>>8); len++;//����crc
	  packBuf[len]=(uint8_t)(jsonBodyCrc);    len++;

		//tail
		packBuf[len]=(uint8_t)(TAIL>>8); len++;
		packBuf[len]=(uint8_t)(TAIL);    len++;
		packBuf[len]=0;//len++;//��β ��0
		if(respFlag==false){
				mcu.repDataMessID =mcu.upMessID;
				//mcu.devRegMessID =mcu.upMessID;
				upMessIdAdd();
		}
		rt_kprintf("%s len:%d\r\n",sign,len);
		rt_kprintf("\r\n%slen��%d str0:%x str1:%x str[2]:%d  str[3]:%d\r\n",sign,len,packBuf[0],packBuf[1],packBuf[2],packBuf[3]);

		rt_free(sprinBuf);
		sprinBuf=RT_NULL;

		return len;
}






//void pressSetlCheckSetFlag(int num)
//{
//	  alarmFLag=false;
//		
//		if(sheet.modbusPreSettl[num].tempUpLimit!=0){
//			  if(pressSettle[num].temp>=sheet.modbusPreSettl[num].tempUpLimit){
//					inpoutpFlag.modbusThreAxis[num].tempUpFlag=true;
//					alarmFLag=true;
//				}
//		}
//		
//		if(sheet.modbusPreSettl[num].tempLowLimit!=0){
//				if(pressSettle[num].temp<=sheet.modbusPreSettl[num].tempLowLimit){
//					inpoutpFlag.modbusThreAxis[num].tempLowFlag=true;
//					alarmFLag=true;
//				}
//		}
//		if(sheet.modbusPreSettl[num].heightUpLimit!=0){
//				if(pressSettle[num].height.flotVal>=sheet.modbusPreSettl[num].heightUpLimit){
//					inpoutpFlag.modbusThreAxis[num].accXUpFlag=true;
//					alarmFLag=true;
//				}
//		}
//		if(sheet.modbusPreSettl[num].heightLowLimit!=0){
//				if(pressSettle[num].height.flotVal<=sheet.modbusPreSettl[num].heightLowLimit){
//					inpoutpFlag.modbusThreAxis[num].accXLowFlag=true;
//					alarmFLag=true;
//				}
//		}


//}
//��λ��ʪ�ȵ�warn״ֵ̬
void resetPressSetlWarnFlag()
{
		for (int i = 0; i < PRESSSETTL_485_NUM; i++)
		{		
				inpoutpFlag.modbusPreSettl[i].tempUpFlag =false;
				inpoutpFlag.modbusPreSettl[i].tempLowFlag=false;
				inpoutpFlag.modbusPreSettl[i].heightLowFlag=false;
				inpoutpFlag.modbusPreSettl[i].heightUpFlag =false;
		}
}





//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ  ����true �и澯 false �޸澯
bool modPressSetlWarn2Send()
{
		if(alarmFLag==false)//TEST
			return false;
		char* out = NULL;
		//��������
		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		cJSON* nodeobj = NULL;
		cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return false;
		// ����ڵ㣨��ֵ�ԣ�
		cJSON_AddNumberToObject(root, "mid",mcu.upMessID);
		cJSON_AddStringToObject(root, "packetType","EVENTS_485_ALARM");
		cJSON_AddStringToObject(root, "identifier","settlement_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);
				for (int i = 0; i < PRESSSETTL_485_NUM; i++)
				{		
						if(sheet.pressSetl[i].workFlag==RT_TRUE){
							nodeobj = cJSON_CreateObject();
							cJSON_AddItemToArray(Array, nodeobj);
							cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.pressSetl[i].ID));
							cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
							nodeobj_p= cJSON_CreateObject();
							cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
							cJSON_AddNumberToObject(nodeobj_p,"temperature_low_alarm",inpoutpFlag.modbusPreSettl[i].tempLowFlag);//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"temperature_high_alarm",inpoutpFlag.modbusPreSettl[i].tempUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"height_low_alarm",inpoutpFlag.modbusPreSettl[i].tempLowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"height_high_alarm",inpoutpFlag.modbusPreSettl[i].tempUpFlag);		
							
							sprintf(sprinBuf,"%llu",utcTime());
							cJSON_AddItemToObject(nodeobj_p,"monitoringTime",cJSON_CreateString(sprinBuf));
						}
				}
		}
		sprintf(sprinBuf,"%llu",utcTime());
		cJSON_AddStringToObject(root,"timestamp",sprinBuf);
		//���
		int len=0;
		packBuf[len]= (uint8_t)(HEAD>>8); len++;
		packBuf[len]= (uint8_t)(HEAD);    len++;
		len+=LENTH_LEN;//json�����������д
		// �ͷ��ڴ�  
		out = cJSON_Print(root);
		rt_strcpy((char *)packBuf+len,out);
		len+=rt_strlen(out);
		if(out!=NULL){
				for(int i=0;i<rt_strlen(out);i++)
						rt_kprintf("%c",out[i]);
				rt_kprintf("\n");
				rt_free(out);
				out=NULL;
		}
		if(root!=NULL){
			cJSON_Delete(root);
			out=NULL;
		}
		//lenth
	  packBuf[2]=(uint8_t)((len-LENTH_LEN-HEAD_LEN)>>8);//����json����
	  packBuf[3]=(uint8_t)(len-LENTH_LEN-HEAD_LEN);
	  uint16_t jsonBodyCrc=RTU_CRC(packBuf+HEAD_LEN+LENTH_LEN,len-HEAD_LEN-LENTH_LEN);
	  //crc
	  packBuf[len]=(uint8_t)(jsonBodyCrc>>8); len++;//����crc
	  packBuf[len]=(uint8_t)(jsonBodyCrc);    len++;
		//tail
		packBuf[len]=(uint8_t)(TAIL>>8); len++;
		packBuf[len]=(uint8_t)(TAIL);    len++;
		packBuf[len]=0;//len++;//��β ��0
		mcu.repDataMessID =mcu.upMessID;
		//mcu.devRegMessID =mcu.upMessID;
		upMessIdAdd();
		rt_free(sprinBuf);
		sprinBuf=RT_NULL;
		return true;
}




//�����Ƕ�ȡ�����  ����ĺ�������
void pressSettRead2Send(rt_bool_t netStat,bool respFlag)
{
	  int workFlag=RT_FALSE;
		for(int i=0;i<PRESSSETTL_485_NUM;i++){
				if(sheet.pressSetl[i].workFlag==RT_TRUE){
						readPSTempHeight(i);
						workFlag=RT_TRUE;
				}
		}
		if(workFlag==RT_TRUE){
				rt_kprintf("%s����ɼ���PRESSSETTL����\r\n",sign);
				pressSettlJsonPack(respFlag);
				if(netStat==RT_TRUE)
						rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				rt_thread_mdelay(500);
				if(modPressSetlWarn2Send()==true){
							resetPressSetlWarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
							//rt_thread_mdelay(500);
							if(netStat==RT_TRUE)
									rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				}
		}
}
