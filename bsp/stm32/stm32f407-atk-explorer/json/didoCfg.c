#include  "board.h"
//����������������Ŀ���
const static char sign[]="[dido]";
extern bool  diReadFun(char num);
//���������ź��ϴ�
uint16_t digitalInputReport()
{
	
		char* out = NULL;
		//��������
		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�
		

		cJSON_AddNumberToObject(root, "mid",mcu.upMessID);
		cJSON_AddStringToObject(root, "packetType","PROPERTIES_INPUT_REP");

		cJSON_AddStringToObject(root, "identifier","digital_input");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
			Array = cJSON_CreateArray();
			if (Array == NULL) return 0;
			cJSON_AddItemToObject(root, "params", Array);

			for(int j=0;j<DI_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
				if(packFlash.diginput[j].workFlag==RT_TRUE){//��
					nodeobj = cJSON_CreateObject();
					cJSON_AddItemToArray(Array, nodeobj);
					cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.diginput[j].devID));
				  cJSON_AddNumberToObject(nodeobj,"levelStatus",diReadFun(j));
					cJSON_AddNumberToObject(nodeobj,"port",packFlash.diginput[j].port);
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

		mcu.repDataMessID =mcu.upMessID;
		//mcu.devRegMessID =mcu.upMessID;
		upMessIdAdd();

		rt_free(sprinBuf);
		sprinBuf=RT_NULL;


	  return len;

}
//���������źŶ�ȡ��Ӧ
uint16_t digitalInputGetResp(cJSON *Json)
{
	
		char* out = NULL;
		//��������
		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�
		

		cJSON_AddNumberToObject(root, "mid",respMid);
		cJSON_AddStringToObject(root, "packetType","PROPERTIES_INPUT_GET_RESP");
		cJSON_AddNumberToObject(root, "code",0);
	

	
		cJSON_AddStringToObject(root, "identifier","digital_input");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);
		cJSON   *arrayGet=cJSON_GetObjectItem(Json,"params");
		int arrayGet_size = cJSON_GetArraySize(arrayGet);
		for(int i=0;i<arrayGet_size;i++){
				cJSON *item=cJSON_GetArrayItem(arrayGet,i);
				cJSON  *devID =cJSON_GetObjectItem(item,"deviceId");
				for(int j=0;j<DI_NUM;j++){//�˶���û�����ù�
						if(0==rt_strcmp(packFlash.diginput[j].devID ,devID->valuestring)){
								nodeobj = cJSON_CreateObject();
								cJSON_AddItemToArray(Array, nodeobj);
								cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.diginput[j].devID));
								cJSON_AddNumberToObject(nodeobj,"levelStatus",diReadFun(j));
								cJSON_AddNumberToObject(nodeobj,"port",packFlash.diginput[j].port);
						}
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

		rt_free(sprinBuf);
		sprinBuf=RT_NULL;


	  return len;

}


bool v33OutputReadFun(char num);
bool v5OutputReadFun(char num);
bool v12OutputReadFun(char num);
bool digOutputReadFun(char num);
void digOutputONFun(char num);
void digOutputOFFFun(char num);
void v33OutputONFun(char num);
void v33OutputOFFFun(char num);
void v5OutputONFun(char num);
void v5OutputOFFFun(char num);
void v12OutputONFun(char num);
void v12OutputOFFFun(char num);
//����������ź��ϴ�
uint16_t digitalOutputReport(char *identify)
{
		char* out = NULL;
		//��������
		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�
		cJSON_AddNumberToObject(root, "mid",mcu.upMessID);
		cJSON_AddStringToObject(root, "packetType","PROPERTIES_OUTPUT_REP");
		cJSON_AddStringToObject(root, "identifier",identify);
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
			Array = cJSON_CreateArray();
			if (Array == NULL) return 0;
			cJSON_AddItemToObject(root, "params", Array);
			if(rt_strcmp(identify,"3v3_output")==0){
				for(int j=0;j<V33O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(packFlash.v33output[j].workFlag==RT_TRUE){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.v33output[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",v33OutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.v33output[j].port);
					}
				}
			}
			else if(rt_strcmp(identify,"5v_output")==0){
				for(int j=0;j<V5O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(packFlash.v5output[j].workFlag==RT_TRUE){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.v5output[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",v5OutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.v5output[j].port);
					}
				}
			}
			else if(rt_strcmp(identify,"12v_output")==0){
				for(int j=0;j<V12O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(packFlash.v12output[j].workFlag==RT_TRUE){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.v12output[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",v12OutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.v12output[j].port);
					}
				}
			}
			else if(rt_strcmp(identify,"digital_output")==0){
				for(int j=0;j<DO_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(packFlash.digoutput[j].workFlag==RT_TRUE){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.digoutput[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",digOutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.digoutput[j].port);
					}
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
		mcu.repDataMessID =mcu.upMessID;
		//mcu.devRegMessID =mcu.upMessID;
		upMessIdAdd();
		rt_free(sprinBuf);
		sprinBuf=RT_NULL;
	  return len;

}
//������chu �źŶ�ȡ��Ӧ
uint16_t digitalOutputGetResp(cJSON *Json,char *identify)
{
	
		char* out = NULL;
		//��������
		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�
		

		cJSON_AddNumberToObject(root, "mid",respMid);
		cJSON_AddStringToObject(root, "packetType","PROPERTIES_OUTPUT_GET_RESP");
		cJSON_AddNumberToObject(root, "code",0);
	

	
		cJSON_AddStringToObject(root, "identifier",identify);
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);
		cJSON   *arrayGet=cJSON_GetObjectItem(Json,"params");
		int arrayGet_size = cJSON_GetArraySize(arrayGet);
		for(int i=0;i<arrayGet_size;i++){
				cJSON *item=cJSON_GetArrayItem(arrayGet,i);
				cJSON  *devID =cJSON_GetObjectItem(item,"deviceId");
		
				
			if(rt_strcmp(identify,"3v3_output")==0){
				for(int j=0;j<V33O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(0==rt_strcmp(packFlash.v33output[j].devID ,devID->valuestring)){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.v33output[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",v33OutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.v33output[j].port);
					}
				}
			}
			else if(rt_strcmp(identify,"5v_output")==0){
				for(int j=0;j<V5O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(0==rt_strcmp(packFlash.v5output[j].devID ,devID->valuestring)){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.v5output[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",v5OutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.v5output[j].port);
					}
				}
			}
			else if(rt_strcmp(identify,"12v_output")==0){
				for(int j=0;j<V12O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(0==rt_strcmp(packFlash.v12output[j].devID ,devID->valuestring)){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.v12output[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",v12OutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.v12output[j].port);
					}
				}
			}
			else if(rt_strcmp(identify,"digital_output")==0){
				for(int j=0;j<DO_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(0==rt_strcmp(packFlash.digoutput[j].devID ,devID->valuestring)){//��
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(packFlash.digoutput[j].devID));
						cJSON_AddNumberToObject(nodeobj,"levelStatus",digOutputReadFun(j));
						cJSON_AddNumberToObject(nodeobj,"port",packFlash.digoutput[j].port);
					}
				}
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
		rt_free(sprinBuf);
		sprinBuf=RT_NULL;
	  return len;
}





//���������źŶ�ȡ��Ӧ
uint16_t digitalOutputSetResp(cJSON *Json,char *identify)
{
	
		char* out = NULL;
		//��������
//		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
		//cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�
		bool rspFlag=false;

		cJSON_AddNumberToObject(root, "mid",respMid);
		cJSON_AddStringToObject(root, "packetType","PROPERTIES_OUTPUT_SET_RESP");
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
//		Array = cJSON_CreateArray();
//		if (Array == NULL) return 0;
//		cJSON_AddItemToObject(root, "params", Array);
		cJSON   *arrayGet=cJSON_GetObjectItem(Json,"params");
		int arrayGet_size = cJSON_GetArraySize(arrayGet);
		for(int i=0;i<arrayGet_size;i++){
				cJSON *item=cJSON_GetArrayItem(arrayGet,i);
				cJSON  *levelStat =cJSON_GetObjectItem(item,"levelStatus");
				cJSON  *devID =cJSON_GetObjectItem(item,"deviceId");
				if(rt_strcmp(identify,"3v3_output")==0){
						for(int j=0;j<V33O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
							if(0==rt_strcmp(packFlash.v33output[j].devID ,devID->valuestring)){//��
								rspFlag=true;
								if(levelStat->valueint==0)
										v33OutputOFFFun(j);
								else
										v33OutputONFun(j);

							}
						}
					}
					else if(rt_strcmp(identify,"5v_output")==0){
						for(int j=0;j<V5O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
							if(0==rt_strcmp(packFlash.v5output[j].devID ,devID->valuestring)){//��
								rspFlag=true;
								if(levelStat->valueint==0)
										v5OutputOFFFun(j);
								else
										v5OutputONFun(j);
							}
						}
					}
					else if(rt_strcmp(identify,"12v_output")==0){
						for(int j=0;j<V12O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
							if(0==rt_strcmp(packFlash.v12output[j].devID ,devID->valuestring)){//��
								rspFlag=true;
								if(levelStat->valueint==0)
										v12OutputOFFFun(j);
								else
										v12OutputONFun(j);
							}
						}
					}
					else if(rt_strcmp(identify,"digital_output")==0){
						for(int j=0;j<DO_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
							if(0==rt_strcmp(packFlash.digoutput[j].devID ,devID->valuestring)){//��
								rspFlag=true;
								if(levelStat->valueint==0)
										digOutputOFFFun(j);
								else
										digOutputONFun(j);
							}
						}
					}
		}
		}
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		cJSON_AddStringToObject(root, "identifier","digital_output");
	  if(rspFlag==false)
			cJSON_AddNumberToObject(root, "code",1);
		else
			cJSON_AddNumberToObject(root, "code",0);

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

		rt_free(sprinBuf);
		sprinBuf=RT_NULL;


	  return len;

}
