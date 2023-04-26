#include "board.h"
//#include "stmflash.h"
//ˮλĬ�ϵ�ַ02  ������9600  ����0~49��

const static char sign[]="[��ʪ��]";

//#define   SLAVE_ADDR     0X01 
//#define   LENTH          50  //���������õ���������buf����
static bool alarmFLag=false;
typedef struct{
	float temp;
	float hum; 
	uint8_t respStat;
}thStru;
thStru thum[TEMPHUM_485_NUM];

//float temp[TEMPHUM_485_NUM];
//float hum[TEMPHUM_485_NUM]; 
//������ڷ��� 
static void tempHumUartSend(int num,uint8_t *buf,int len)
{
		rs485UartSend(sheet.tempHum[num].useUartNum,buf, len);
}
//����485��ʪ�ȴ���������Ӧ״̬
int tempHumState(int i)
{
		return thum[i].respStat;
}


//��ʪ�ȴ�������ȡֵ����ֵ�Ƚϲ�����flag
 void tempHumCheckSetFlag(int num)
{
	  alarmFLag=false;
		if(sheet.modbusTempHum[num].tempUpLimit!=0){
				if(thum[num].temp>=sheet.modbusTempHum[num].tempUpLimit){
					inpoutpFlag.modbusTempHum[num].tempUpFlag=true;
					alarmFLag=true;
				}
		}
		if(sheet.modbusTempHum[num].tempLowLimit!=0){
				if(thum[num].temp<=sheet.modbusTempHum[num].tempLowLimit){
					inpoutpFlag.modbusTempHum[num].tempLowFlag=true;
					alarmFLag=true;
				}
		}
		if(sheet.modbusTempHum[num].humUpLimit!=0){
				if(thum[num].hum>=sheet.modbusTempHum[num].humUpLimit){
					inpoutpFlag.modbusTempHum[num].humUpFlag=true;
					alarmFLag=true;
				}
		}
		if(sheet.modbusTempHum[num].humLowLimit!=0){
				if(thum[num].temp<=sheet.modbusTempHum[num].humLowLimit){	
					inpoutpFlag.modbusTempHum[num].humLowFlag=true;
					alarmFLag=true;
				}
		}
}
//��λ��ʪ�ȵ�warn״ֵ̬
void resetTempHumWarnFlag()
{
		for (int i = 0; i < TEMPHUM_485_NUM; i++)
		{		
				inpoutpFlag.modbusTempHum[i].tempUpFlag =false;
				inpoutpFlag.modbusTempHum[i].tempLowFlag=false;
				inpoutpFlag.modbusTempHum[i].humUpFlag  =false;
				inpoutpFlag.modbusTempHum[i].humLowFlag =false;
		}
}

//�� 1A 04 00 01 00 02 23 E0
//�� 1A 04 04 0B 1B 00 1C 23 6F
//ͨ��485�ӿڶ�ȡ��ʪ��
void readTempHum(int num)
{
	  
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = modbusReadReg(sheet.tempHum[num].slaveAddr,0X0000,READ_04,2,buf);
//		rt_mutex_take(uartDev[sheet.tempHum[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		tempHumUartSend(num,(uint8_t *)buf,len);
	  rt_kprintf("%stemphum send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
    len=0;
		memset(buf,0,LENTH);

		while(rt_mq_recv(&uartmque[sheet.tempHum[num].useUartNum], buf+len, 1, 500) == RT_EOK){//115200 ������1ms 10������
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
		//uartDev[modbusFlash[TEMPHUM].useUartNum].offline=RT_FALSE;
		int ret2=modbusRespCheck(sheet.tempHum[num].slaveAddr,buf,len,RT_TRUE);
		if(0 == ret2){//ˢ�¶�ȡ����ֵ
        uint16_t read_temp	=(buf[offset]<<8)+buf[offset+1];offset+=2;
			  uint16_t read_hum	=(buf[offset]<<8)+buf[offset+1];offset+=2;
			  rt_bool_t sig=RT_FALSE;
        if(read_temp&0x8000){//����
						read_temp=read_temp&0x7fff;
						read_temp=0xffff-read_temp+1;
					  sig=RT_TRUE;
				}
				thum[num].temp=(float)read_temp/10;
				thum[num].hum=(float)read_hum/10;
				thum[num].respStat=1;
				if(sig==RT_TRUE)
					rt_kprintf("%s�¶�:-%0.1fC ʪ��:%0.1f\n",sign,thum[num].temp,thum[num].hum); 
				else
					rt_kprintf("%s�¶�:%0.1fC ʪ��:%0.1f\n",sign,thum[num].temp,thum[num].hum);   
				tempHumCheckSetFlag(num);

		} 
		else{//��������0
				if(ret2==2){
						//rt_kprintf("%sERR:����485���߻��߹���\r\n",sign);
//					  uartDev[modbusFlash[TEMPHUM].useUartNum].offline=RT_TRUE;
				}
				thum[num].respStat=0;
				thum[num].temp=0;
				thum[num].hum=0;
			  rt_kprintf("%s read fail\n",sign);
		}
	//	tempHumCheckSetFlag(num);//TEST ONLY
//	  rt_mutex_release(uartDev[sheet.tempHum[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;				
}


//��ʪ��ֵͨ��json��ʽ���
//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
static uint16_t tempHumJsonPack(bool respFlag)
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
		cJSON_AddStringToObject(root, "identifier","temperature_and_humidity_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);
		for (int i = 0; i < TEMPHUM_485_NUM; i++)
		{		
			if(sheet.tempHum[i].workFlag==RT_TRUE){
				nodeobj = cJSON_CreateObject();
				cJSON_AddItemToArray(Array, nodeobj);
			  cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.tempHum[i].ID));
				//sprintf(sprinBuf,"%d",thum[i].respStat);
				cJSON_AddNumberToObject(nodeobj,"responseStatus",thum[i].respStat);
				
				nodeobj_p= cJSON_CreateObject();
				cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
				sprintf(sprinBuf,"%02f",thum[i].temp);
				cJSON_AddItemToObject(nodeobj_p,"temperature",cJSON_CreateString(sprinBuf));

				sprintf(sprinBuf,"%02f",thum[i].hum );
				cJSON_AddItemToObject(nodeobj_p,"humidity",cJSON_CreateString(sprinBuf));
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





//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ  ����true �и澯 false �޸澯
bool modTempHumWarn2Send()
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
		cJSON_AddStringToObject(root, "identifier","temperature_and_humidity_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);
				for (int i = 0; i < TEMPHUM_485_NUM; i++)
				{		
						if(sheet.tempHum[i].workFlag==RT_TRUE){
							nodeobj = cJSON_CreateObject();
							cJSON_AddItemToArray(Array, nodeobj);
							cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.tempHum[i].ID));
							cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
							nodeobj_p= cJSON_CreateObject();
							cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
							cJSON_AddNumberToObject(nodeobj_p,"temperature_low_alarm",inpoutpFlag.modbusTempHum[i].tempLowFlag);//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"temperature_high_alarm",inpoutpFlag.modbusTempHum[i].tempUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"humidity_low_alarm",inpoutpFlag.modbusTempHum[i].humLowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"humidity_high_alarm",inpoutpFlag.modbusTempHum[i].humUpFlag);
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




//��ʪ��ֵ��ȡ�����json��ʽ
void tempHumRead2Send(rt_bool_t netStat,bool respFlag)
{
	 int workFlag=RT_FALSE;
	 for(int i=0;i<TEMPHUM_485_NUM;i++){
		if(sheet.tempHum[i].workFlag==RT_TRUE){
					readTempHum(i);
					workFlag=RT_TRUE;
			}
	}
	if(workFlag==RT_TRUE){
			rt_kprintf("%s����ɼ���temphum����\r\n",sign);
			tempHumJsonPack(respFlag);
			if(netStat==RT_TRUE)
					rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
					rt_thread_mdelay(500);
			if(modTempHumWarn2Send()==true){
					resetTempHumWarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
					if(netStat==RT_TRUE)
							rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
			}
	}
}


