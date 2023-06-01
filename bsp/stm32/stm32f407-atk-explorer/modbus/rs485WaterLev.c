#include "board.h"
//#include "stmflash.h"
//ˮλĬ�ϵ�ַ02  ������9600  ����0~49��
//��ȡˮλ
const static char sign[]="[ˮλ]";

//#define   SLAVE_ADDR     0X01 
//#define   LENTH          50  //���������õ���������buf����

 float waterDepth[WATERDEPTH_485_NUM];
static uint8_t respStat[WATERDEPTH_485_NUM];
//������ڷ��� 
static void waterDepthUartSend(int num,uint8_t *buf,int len)
{
		rs485UartSend(sheet.waterDepth[num].useUartNum,buf, len);
}
//����ˮλ��ͨѶ״̬ true--ͨѶ�ɹ� false--ͨѶʧ��
int waterDepthState(int i)
{
		return respStat[i];
}
static  bool alarmFLag=false;

//ˮλ�������Ƚ���ֵ��������Ӧ��flag���
static void waterLevCheckSetFlag(int num)
{
	  alarmFLag=false;
		if(sheet.modbusWaterDepth[num].depthUpLimit!=0){
			if(waterDepth[num]>=sheet.modbusWaterDepth[num].depthUpLimit)
					inpoutpFlag.modbusWaterDepth[num].depthUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusWaterDepth[num].depthLowLimit!=0){
			if(waterDepth[num]<=sheet.modbusWaterDepth[num].depthLowLimit)
					inpoutpFlag.modbusWaterDepth[num].depthLowFlag=true;alarmFLag=true;
		}
}




//�� 1A 04 00 01 00 02 23 E0
//�� 1A 04 04 0B 1B 00 1C 23 6F
//��ȡˮλ
static void readWaterDepth(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = modbusReadReg(sheet.waterDepth[num].slaveAddr,0X0002,READ_04,2,buf);
//		rt_mutex_take(uartDev[sheet.waterDepth[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		waterDepthUartSend(num,buf,len);
	  rt_kprintf("%swater send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
    len=0;
		memset(buf,0,LENTH);
		

		while(rt_mq_recv(&uartmque[sheet.waterDepth[num].useUartNum], buf+len, 1, 500) == RT_EOK){//115200 ������1ms 10������
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
		int ret2=modbusRespCheck(sheet.waterDepth[num].slaveAddr,buf,len,RT_TRUE);
		if(0 == ret2){//ˢ�¶�ȡ����ֵ
        uint32_t read	=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
        extern float write_hex_to_float(uint32_t number);
			  float waterDepth_p= write_hex_to_float(read);
        waterDepth[num]=(float)(waterDepth_p	/9.8);
			  rt_kprintf("%sˮ��:%0.4f��\n",sign,waterDepth[num]);  
			  respStat[num]=1;
				waterLevCheckSetFlag(num);
		} 
		else{//��������0
				if(ret2==2){
						//rt_kprintf("%sERR:����485���߻��߹���\r\n",sign);
				}
				respStat[num]=0;
			  waterDepth[num]	=0;
			  rt_kprintf("%s read fail\n",sign);
		}
		//waterLevCheckSetFlag(num);
//	  rt_mutex_release(uartDev[sheet.waterDepth[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;

}



//ˮλֵ�����json��ʽ
//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
uint16_t waterDepthJsonPack(bool respFlag)
{
//		char *sprinBuf=RT_NULL;
//		sprinBuf=rt_malloc(20);//20���ַ������� ������
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
		cJSON_AddStringToObject(root, "identifier","water_level_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
//	  cJSON_AddItemToObject(root,"acuId",cJSON_CreateString(packFlash.acuId));
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������	
		
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);
		for (int i = 0; i < WATERDEPTH_485_NUM; i++)
		{		
			if(sheet.waterDepth[i].workFlag==RT_TRUE){
				nodeobj = cJSON_CreateObject();
				cJSON_AddItemToArray(Array, nodeobj);
			  cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.waterDepth[i].ID));
				//sprintf(sprinBuf,"%d",respStat[i]);
				cJSON_AddNumberToObject(nodeobj,"responseStatus",respStat[i]);
				
				nodeobj_p= cJSON_CreateObject();
				cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
				sprintf(sprinBuf,"%02f",waterDepth[i]);
				cJSON_AddItemToObject(nodeobj_p,"depth",cJSON_CreateString(sprinBuf));

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
			upMessIdAdd();
		}
		rt_kprintf("%s len:%d\r\n",sign,len);
		rt_kprintf("\r\n%slen��%d str0:%x str1:%x str[2]:%d  str[3]:%d\r\n",sign,len,packBuf[0],packBuf[1],packBuf[2],packBuf[3]);

		rt_free(sprinBuf);
		sprinBuf=RT_NULL;

		return len;
}

void resetWaterLevWarnFlag()
{
		for (int i = 0; i < WATERDEPTH_485_NUM; i++)
		{		
				inpoutpFlag.modbusWaterDepth[i].depthLowFlag =false;
				inpoutpFlag.modbusWaterDepth[i].depthUpFlag=false;
		}
}





//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ  ����true �и澯 false �޸澯
bool modPWaterLevWarn2Send()
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
		cJSON_AddStringToObject(root, "identifier","water_level_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);
				for (int i = 0; i < WATERDEPTH_485_NUM; i++)
				{		
						if(sheet.waterDepth[i].workFlag==RT_TRUE){
							nodeobj = cJSON_CreateObject();
							cJSON_AddItemToArray(Array, nodeobj);
							cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.waterDepth[i].ID));
							cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
							nodeobj_p= cJSON_CreateObject();
							cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
							cJSON_AddNumberToObject(nodeobj_p,"depth_high_alarm",inpoutpFlag.modbusWaterDepth[i].depthUpFlag);//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"depth_low_alarm",inpoutpFlag.modbusWaterDepth[i].depthLowFlag);
//							cJSON_AddNumberToObject(nodeobj_p,"height_low_alarm",inpoutpFlag.modbusPreSettl[i].tempLowFlag);
//							cJSON_AddNumberToObject(nodeobj_p,"height_high_alarm",inpoutpFlag.modbusPreSettl[i].tempUpFlag);		
							
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
extern int dispWaterTotlNum;
//ˮλֵ�Ķ�ȡ�ʹ������  ��������װ ����ĺ���������
void waterDepthRead2Send(rt_bool_t netStat,bool respFlag)
{
	 int workFlag=RT_FALSE;
	 dispWaterTotlNum=0;
			for(int i=0;i<WATERDEPTH_485_NUM;i++){
					if(sheet.waterDepth[i].workFlag==RT_TRUE){
							readWaterDepth(i);
							workFlag=RT_TRUE;
						  dispWaterTotlNum++;
					}
			}
			if(workFlag==RT_TRUE){
					rt_kprintf("%s����ɼ���waterdepth����\r\n",sign);
					waterDepthJsonPack(respFlag);
					if(netStat==RT_TRUE)
							rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
					
					rt_thread_mdelay(500);
					if(modPWaterLevWarn2Send()==true){
							resetWaterLevWarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
							//rt_thread_mdelay(500);
							if(netStat==RT_TRUE)
									rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
					}
			}
}

