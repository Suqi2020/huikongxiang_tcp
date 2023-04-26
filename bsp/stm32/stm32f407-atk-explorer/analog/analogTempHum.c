#include  "board.h"


//4-20ma ��Ӧ adc��0.6-3V ��Ӧ�¶���-40��--80��  ʪ��ֵ��0-100
// 0-3.3��Ӧ0-4096
const char *sign="[analogTempH]";
//num ��ʱ������ʱ���ҵ��Ķ�Ӧ��0-7ͨ��
//uint8_t analogTemChanl=0;

float temp =0.00;
float humi =0.00;

char copyID[MODBID_LEN];//��ȡana��ʪ��ʱ�� ˳���ID��������
//ģ�����ʪ�ȴ�������ȡ�¶�ʪ��ֵ������ֵ�Ƚ��������
#ifndef     ANA_MASK
bool anaTempHumWarn2Send();
void  anaTempHumiReadAndSetFlag()
{
		uint16_t  ADCtemp,ADChumi,porttest;
		float Vtemp,Vhumi;
		for (int i = 0; i < ANALOG_NUM; i++){		
			if(sheet.analog[i].workFlag==RT_TRUE){
				if(rt_strcmp(sheet.analog[i].name,analogName[0])==0){
						if(sheet.analog[i].subName==1){//�¶�  �ο��������modbus��������V0.4��
							  porttest=sheet.analog[i].port-1;
								ADCtemp=Get_Adc_Average(chanl[sheet.analog[i].port-1],5);
								Vtemp=ADCtemp*33*10/4096; //����100��
								temp=((Vtemp-60)*12/24)-40;////	temp=(10*Vtemp-6)*(80+40)/(30-6)-40;
								rt_kprintf("%stemp=%f\n",sign,temp);
								rt_strcpy(copyID,sheet.analog[i].ID);
								if(temp>=sheet.analogTempHum.tempUpLimit){
									  if(sheet.analogTempHum.tempUpLimit!=0){
												inpoutpFlag.analogTempHum.tempUpFlag=true;
										}
								}
								else
										inpoutpFlag.analogTempHum.tempUpFlag=false;
								if(temp<=sheet.analogTempHum.tempLowLimit){
										if(sheet.analogTempHum.tempLowLimit!=0){
												inpoutpFlag.analogTempHum.tempLowFlag=true;
										}
								}
								else
										inpoutpFlag.analogTempHum.tempLowFlag=false;
						}
						else if(sheet.analog[i].subName==2){//ʪ��
							  porttest=sheet.analog[i].port-1;
								ADChumi=Get_Adc_Average(chanl[sheet.analog[i].port-1],5);
								Vhumi=ADChumi*33*10/4096;//����100��
								humi=10*(Vhumi-60)/(30-6);
								rt_kprintf("%shumi=%f\n",sign,humi);
								rt_strcpy(copyID,sheet.analog[i].ID);
								if(humi>=sheet.analogTempHum.humUpLimit){
										if(sheet.analogTempHum.humUpLimit!=0){
												inpoutpFlag.analogTempHum.humUpFlag=true;
										}
								}
								else
										inpoutpFlag.analogTempHum.humUpFlag=false;
								if(humi<=sheet.analogTempHum.humLowLimit){
										if(sheet.analogTempHum.humUpLimit!=0){
												inpoutpFlag.analogTempHum.humLowFlag=true;
										}
								}
								else
										inpoutpFlag.analogTempHum.humLowFlag=false;
						}		
				}
			}
		}
}
//ģ���¶�ʪ��json���ݴ��
//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
uint16_t analogTempHumJsonPack(bool respFlag)
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
				cJSON_AddStringToObject(root, "packetType","PROPERTIES_ANADATA_GET_RESP");
				cJSON_AddNumberToObject(root, "code",0);
		}
		else
		{
				cJSON_AddNumberToObject(root, "mid",mcu.upMessID);
				cJSON_AddStringToObject(root, "packetType","PROPERTIES_ANADATA_REP");
		}
		cJSON_AddStringToObject(root, "identifier","temperature_and_humidity_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);

				nodeobj = cJSON_CreateObject();
				cJSON_AddItemToArray(Array, nodeobj);
			  cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(copyID));
				
				
				nodeobj_p= cJSON_CreateObject();
				cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
			
			
				sprintf(sprinBuf,"%02f",temp);
				cJSON_AddItemToObject(nodeobj_p,"�¶�",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%02f",humi );
				cJSON_AddItemToObject(nodeobj_p,"ʪ��",cJSON_CreateString(sprinBuf));

				sprintf(sprinBuf,"%llu",utcTime());
				cJSON_AddItemToObject(nodeobj_p,"monitoringTime",cJSON_CreateString(sprinBuf));
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




//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ
bool anaTempHumWarn2Send()
{
		if(inpoutpFlag.analogTempHum.humLowFlag==false){
				if(inpoutpFlag.analogTempHum.humUpFlag==false){
						if(inpoutpFlag.analogTempHum.tempLowFlag==false){
								if(inpoutpFlag.analogTempHum.tempUpFlag==false){
										return false;
								}
						}
				}
		}
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
		cJSON_AddStringToObject(root, "packetType","EVENTS_ANA_ALARM");

		cJSON_AddStringToObject(root, "identifier","temperature_and_humidity_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);

				nodeobj = cJSON_CreateObject();
				cJSON_AddItemToArray(Array, nodeobj);
			  cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(copyID));
				cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
				nodeobj_p= cJSON_CreateObject();
				cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
				cJSON_AddNumberToObject(nodeobj_p,"temperature_low_alarm",inpoutpFlag.analogTempHum.tempLowFlag);//cJSON_CreateNumber("10"));
		    cJSON_AddNumberToObject(nodeobj_p,"temperature_high_alarm",inpoutpFlag.analogTempHum.tempUpFlag);
			  cJSON_AddNumberToObject(nodeobj_p,"humidity_low_alarm",inpoutpFlag.analogTempHum.humLowFlag);
			  cJSON_AddNumberToObject(nodeobj_p,"humidity_high_alarm",inpoutpFlag.analogTempHum.humUpFlag);
				sprintf(sprinBuf,"%llu",utcTime());
				cJSON_AddItemToObject(nodeobj_p,"monitoringTime",cJSON_CreateString(sprinBuf));
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
		upMessIdAdd();
		rt_free(sprinBuf);
		sprinBuf=RT_NULL;

		return true;
		
}



//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ
void anaTempHumReadPack2Send(bool gbNetState,bool respFlag)
{
		anaTempHumiReadAndSetFlag();
	  analogTempHumJsonPack(respFlag);
		if(gbNetState==RT_TRUE)
						rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
		if(true ==anaTempHumWarn2Send()){
			    rt_thread_mdelay(500);//�����պ���
					rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);	
		}
}
#endif