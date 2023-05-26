#include "board.h"
//#include "stmflash.h"
//һ����̼Ĭ�ϵ�ַ04 ������9600
//04 03 00 02 00 02 65 9E
//04 03 04 00 00 00 00 AF 33 
#ifdef USE_4GAS
const static char sign[]="[����]";

//#define   SLAVE_ADDR     0X01 
//#define   LENTH          50  //���������õ���������buf����


//concentrationStru gas;
//#define CH4_485_NUM   				10

 float ch4[CH4_485_NUM];
static uint8_t respStat[CH4_485_NUM];
extern bool gasAlarmFlag;
//������ڷ��� 
static void ch4UartSend(int num,uint8_t *buf,int len)
{
		rs485UartSend(sheet.ch4[num].useUartNum,buf, len);
}
//����ch4��ͨѶ״̬ true--ͨѶ�ɹ� false--ͨѶʧ��
int ch4State(int i)
{
		return respStat[i];
}
//ch4�Ƚ���ֵ��������Ӧ��flag���
static void ch4CheckSetFlag(int num)
{
		gasAlarmFlag=false;
		if(sheet.modbusCh4[num].ch4UpLimit!=0){
			if(ch4[num]>=sheet.modbusCh4[num].ch4UpLimit){
					inpoutpFlag.modbusCh4[num].ch4UpFlag=true;gasAlarmFlag=true;
			}
		}
		if(sheet.modbusCh4[num].ch4LowLimit!=0){
			if(ch4[num]<=sheet.modbusCh4[num].ch4LowLimit){
					inpoutpFlag.modbusCh4[num].ch4LowFlag=true;gasAlarmFlag=true;
			}
		}

}
//�� 1A 04 00 01 00 02 23 E0
//�� 1A 04 04 0B 1B 00 1C 23 6F
//��ȡch4��Ũ��ֵ
void readCH4(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = modbusReadReg(sheet.ch4[num].slaveAddr,0X0002,READ_03,2,buf);
	 //rt_kprintf("%sCH4 take %d\n",modbusFlash[CH4].useUartNum);
//		rt_mutex_take(uartDev[sheet.ch4[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		ch4UartSend(num,buf,len);
	  rt_kprintf("%sCH4 send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
    len=0;
		memset(buf,0,LENTH);
		
		while(rt_mq_recv(&uartmque[sheet.ch4[num].useUartNum], buf+len, 1, 500) == RT_EOK){//115200 ������1ms 10������
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
		int ret2=modbusRespCheck(sheet.ch4[num].slaveAddr,buf,len,RT_TRUE);
		if(0 == ret2){//ˢ�¶�ȡ����ֵ
        int val	=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;

        ch4[num]=(float)((float)val	/1000);
			  respStat[num]=1;
			  ch4CheckSetFlag(num);
			  rt_kprintf("%sŨ��ֵ:%0.2fmol/Lread ok\n",sign,ch4[num]);  
		} 
		else{//��������0
				if(ret2==2){
						//rt_kprintf("%sERR:����485���߻��߹���\r\n",sign);
				}
				respStat[num]=0;
			  ch4[num]=0;
			  rt_kprintf("%s read fail\n",sign);
		}
		//ch4CheckSetFlag(num);
//	  rt_mutex_release(uartDev[sheet.ch4[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;

}


//��ȡcoֵ





//4��������
//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
#if 1
static uint16_t ch4Pack(bool respFlag)
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
		cJSON_AddStringToObject(root, "identifier","ch4_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		
		
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);
		for (int i = 0; i < CH4_485_NUM; i++)
		{		

			if(sheet.ch4[i].workFlag==RT_TRUE){
				nodeobj = cJSON_CreateObject();
				cJSON_AddItemToArray(Array, nodeobj);
			  cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.ch4[i].ID));
				cJSON_AddNumberToObject(nodeobj,"responseStatus",respStat[i]);
				
				nodeobj_p= cJSON_CreateObject();
				cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);

				sprintf(sprinBuf,"%02f",ch4[i]);
				cJSON_AddItemToObject(nodeobj_p,"methane",cJSON_CreateString(sprinBuf));

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

#endif

//��λ��ʪ�ȵ�warn״ֵ̬
void resetCh4WarnFlag()
{
		for (int i = 0; i < CH4_485_NUM; i++)
		{		
//				inpoutpFlag.modbusCo[i].coLowFlag =false;
//			  inpoutpFlag.modbusCo[i].coUpFlag  =false;
//				inpoutpFlag.modbusO2[i].o2LowFlag =false;
//			  inpoutpFlag.modbusO2[i].o2UpFlag  =false;
//				inpoutpFlag.modbusH2s[i].h2sLowFlag =false;
//			  inpoutpFlag.modbusH2s[i].h2sUpFlag  =false;
				inpoutpFlag.modbusCh4[i].ch4LowFlag =false;
			  inpoutpFlag.modbusCh4[i].ch4UpFlag  =false;
		}
}





//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ  ����true �и澯 false �޸澯
bool modCh4Warn2Send()
{
		if(gasAlarmFlag==false)//TEST
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
		cJSON_AddStringToObject(root, "identifier","ch4_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);
				for (int i = 0; i < CH4_485_NUM; i++)
				{		
						if(sheet.ch4[i].workFlag==RT_TRUE){
							nodeobj = cJSON_CreateObject();
							cJSON_AddItemToArray(Array, nodeobj);
							cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.ch4[i].ID));
							cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
							nodeobj_p= cJSON_CreateObject();
							cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
		
							cJSON_AddNumberToObject(nodeobj_p,"methane_low_alarm",inpoutpFlag.modbusCh4[i].ch4LowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"methane_high_alarm",inpoutpFlag.modbusCh4[i].ch4UpFlag);
														
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
//4������json����Ķ��η�װ
//void  ch4JsonPack(rt_bool_t netStat,bool respFlag)
//{
//		rt_kprintf("%s����ɼ���ch4����\r\n",sign);

//				ch4Pack(respFlag);
//			if(netStat==RT_TRUE)
//				rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
//				rt_thread_mdelay(500);
//				if(modCh4Warn2Send()==true){
//						resetCh4WarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
//						if(netStat==RT_TRUE)
//								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
//				}


//}
//ch4����json����Ķ��η�װ
void  ch4Read2Send(rt_bool_t netStat,bool respFlag)
{
		rt_kprintf("%s����ɼ���ch4����\r\n",sign);
		 int workFlag=RT_FALSE;
	 for(int i=0;i<CH4_485_NUM;i++){
		if(sheet.ch4[i].workFlag==RT_TRUE){
					readCH4(i);
					workFlag=RT_TRUE;
			}
	}
	if(workFlag==RT_TRUE){
				ch4Pack(respFlag);
			if(netStat==RT_TRUE)
				rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				rt_thread_mdelay(500);
				if(modCh4Warn2Send()==true){
						resetCh4WarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
						if(netStat==RT_TRUE)
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				}
			}

}



#endif
