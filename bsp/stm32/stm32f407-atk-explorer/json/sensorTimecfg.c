#include  "board.h"
//������ʱ�������
const static char sign[]="[timeCfg]";



//485�������ɼ�ʱ���ȡ�������json��ʽ
//���� string --identifier����  
//     modbusFlag-true modbus�豸
//                false  ģ���豸
void senseTimeReadJsonResp(char *string,bool  modbusFlag)
{
	  uint32_t caltime =0;
		char* out = NULL;
		//��������
//		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
//		cJSON* nodeobj = NULL;
//		cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return;
	
	  cJSON_AddNumberToObject(root,"mid",respMid);
	  bool result=false;
	  if(modbusFlag==true){
			  //rt_kprintf("modbusFlag=%d\n",modbusFlag);
				cJSON_AddStringToObject(root,"packetType","PROPERTIES_485TTIM_GET_RESP");
				  if(rt_strcmp(string,"partial_discharge_monitor")==0){
							result=true;
							caltime=sheet.partDischagColTime;
					}
					else if(rt_strcmp(string,"grounding_current_monitor")==0){
						result=true;
						caltime=sheet.cirCulaColTime;
					}
					else if(rt_strcmp(string,"water_level_monitor")==0){
						result=true;
						caltime=sheet.waterDepthColTime;
					}
					else if(rt_strcmp(string,"temperature_and_humidity_monitor")==0){
						result=true;
						caltime=sheet.tempHumColTime;
					}
					else if(rt_strcmp(string,"environment_monitor")==0){
						result=true;
						caltime=sheet.tempHumColTime;
					}
					else if(rt_strcmp(string,"vibration_monitor")==0){
						result=true;
						caltime=sheet.threeAxissColTime;
					}
					else if(rt_strcmp(string,"settlement_monitor")==0){
						result=true;
						caltime=sheet.pressSetlColTime;
					}
		}
		else{
			#ifndef     ANA_MASK
				cJSON_AddStringToObject(root,"packetType","PROPERTIES_ANATTIM_GET_RESP");
				if(rt_strcmp(string,"temperature_and_humidity_monitor")==0){
						result=true;
						for(int i=0;i<ANALOG_NUM;i++){
								if(rt_strcmp(sheet.analog[i].name,analogName[0])==0){//�� analogName[0]  ָ������ʪ��
										if(sheet.analog[i].workFlag==RT_TRUE){
												caltime=sheet.analog[i].colTime;
										}
										break;
								}
						}
					}
	  	#endif
		}
	  cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		cJSON_AddStringToObject(root, "identifier",string);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		if(result==true){
			
			cJSON_AddNumberToObject(root, "code",0);
		}
		else{
			cJSON_AddNumberToObject(root, "code",1);
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
		rt_free(sprinBuf);
		sprinBuf=RT_NULL;

}

//485�������ɼ�ʱ������
//     modbusFlag-true modbus�豸
//                false  ģ���豸
void senseTimeJsonSet(cJSON   *Json,bool  modbusFlag)
{
		char* out = NULL;
		//��������
//		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
//		cJSON* nodeobj = NULL;
//		cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return;

	  uint32_t	calTime=0;
	
		cJSON   *array=cJSON_GetObjectItem(Json,"params");
	  cJSON  *pkIdentf = cJSON_GetObjectItem(Json,"identifier");
		int array_size = cJSON_GetArraySize(array);
		if(array_size!=1)
				rt_kprintf("%serr array_size %d\n",sign,array_size);
		for(int i=0;i<array_size;i++)
		{
				cJSON *item=cJSON_GetArrayItem(array,i);
				cJSON  *calTimep =cJSON_GetObjectItem(item,"calTime");
				calTime =atol(calTimep->valuestring);

		}
	  char *string =pkIdentf->valuestring;
	  cJSON_AddNumberToObject(root,"mid",respMid);
	  bool result=false;
	  if(modbusFlag==true){
	
				cJSON_AddStringToObject(root,"packetType","PROPERTIES_485TTIM_SET_RESP");
				  if(rt_strcmp(pkIdentf->valuestring,"partial_discharge_monitor")==0){
							result=true;
							sheet.partDischagColTime = calTime;
					}
					else if(rt_strcmp(string,"grounding_current_monitor")==0){
						result=true;
						sheet.cirCulaColTime = calTime;
					}
					else if(rt_strcmp(string,"water_level_monitor")==0){
						result=true;
						sheet.waterDepthColTime = calTime;
					}
					else if(rt_strcmp(string,"temperature_and_humidity_monitor")==0){
						result=true;
						sheet.tempHumColTime = calTime;
					}
					else if(rt_strcmp(string,"environment_monitor")==0){
						result=true;
						sheet.tempHumColTime = calTime;
					}
					else if(rt_strcmp(string,"vibration_monitor")==0){
						result=true;
						sheet.threeAxissColTime = calTime;
					}
					else if(rt_strcmp(string,"settlement_monitor")==0){
						result=true;
						sheet.pressSetlColTime = calTime;
					}
		}
		else{
		#ifndef     ANA_MASK
				cJSON_AddStringToObject(root,"packetType","PROPERTIES_ANATTIM_SET_RESP");
				if(rt_strcmp(string,"temperature_and_humidity_monitor")==0){
						result=true;
						for(int i=0;i<ANALOG_NUM;i++){
								if(rt_strcmp(sheet.analog[i].name,analogName[0])==0){//�� analogName[0]  ָ������ʪ��
										if(sheet.analog[i].workFlag==RT_TRUE){
												sheet.analog[i].colTime=calTime;
										}
								}
						}
					}
			#endif
		}
	  cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		cJSON_AddStringToObject(root, "identifier",string);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		if(result==true){
			
			cJSON_AddNumberToObject(root, "code",0);

		}
		else{
			cJSON_AddNumberToObject(root, "code",1);
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
		rt_free(sprinBuf);
		sprinBuf=RT_NULL;
}
//ģ�⴫�����ɼ�ʱ������
//void senseTimeJsonSet()
//{
//	
//}

