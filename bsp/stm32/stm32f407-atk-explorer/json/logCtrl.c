#include  "board.h"
//�߼����Ƶ�����
const static char sign[]="[logCtrl]";


//��ȡ AA CC 00 78 20 7B 0D 0A 20 20 22 6D 69 64 22 3A 20 32 32 2C 20 0D 0A 20 20 22 70 61 63 6B 65 74 54 79 70 65 22 3A 20 22 53 45 52 56 49 43 45 53 5F 43 54 52 4C 43 46 47 5F 52 45 41 44 22 2C 20 0D 0A 20 20 22 61 63 75 49 64 22 3A 20 22 31 30 30 30 30 30 30 30 30 30 30 30 31 22 2C 20 0D 0A 20 20 22 74 69 6D 65 73 74 61 6D 70 22 3A 20 22 32 33 31 30 33 37 22 0D 0A 7D 0D 0A 14 66 CC AA 
//ɾ��





//��վ��ȡ�߼����ƻ�Ӧ
uint16_t logCrtlReadResp(cJSON *Json)
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
		cJSON_AddStringToObject(root, "packetType","SERVICES_CTRLCFG_READ_RESP");
		cJSON_AddNumberToObject(root, "code",0);
	

	
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);

		for(int i=0;i<CRTL_TOTAL_NUM;i++){
				//rt_kprintf("%s,autoctrl list",sign);
				if(sheet.autoctrl[i].workFlag==true){
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddNumberToObject(nodeobj,"ctrlNum",i+1);
					  cJSON* ArrayInput = cJSON_CreateArray();
					  cJSON* ArrayOutput = cJSON_CreateArray();
					  cJSON_AddItemToObject(nodeobj, "inputCtrl", ArrayInput);
						cJSON_AddItemToObject(nodeobj, "outputCtrl", ArrayOutput);
						//rt_kprintf("%sautoctrl the [%d] inctrl\n",sign,i+1);
						for(int k=0;k<CRTL_IN_NUM;k++){
								if((sheet.autoctrl[i].input[k].flag!=NULL)&&((uint32_t)(uint32_t*)(sheet.autoctrl[i].input[k].flag)!=0xFFFFFFFF)){
										cJSON* nodeobjInput = cJSON_CreateObject();
										cJSON_AddItemToArray(ArrayInput, nodeobjInput);	
										cJSON_AddStringToObject(nodeobjInput, "sort",(char *)sheet.autoctrl[i].input[k].typeName);
										cJSON_AddStringToObject(nodeobjInput, "name",(char *)sheet.autoctrl[i].input[k].senseName);
										cJSON_AddStringToObject(nodeobjInput, "deviceId",(char *)sheet.autoctrl[i].input[k].ID);
										cJSON_AddStringToObject(nodeobjInput, "subSort",sheet.autoctrl[i].input[k].subName);
										cJSON_AddNumberToObject(nodeobjInput, "level",sheet.autoctrl[i].input[k].limit);

								}
						}
						for(int j=0;j<CRTL_OUT_NUM;j++){
														//	if((sheet.autoctrl[i].input[k].flag!=NULL)&&((uint32_t)(uint32_t*)(sheet.autoctrl[i].input[k].flag)!=0xFFFFFFFF)){
								if((sheet.autoctrl[i].output[j].flag!=NULL)&&((uint32_t)(uint32_t*)sheet.autoctrl[i].output[j].flag!=0xFFFFFFFF)){
										cJSON* nodeobjOutput = cJSON_CreateObject();;
									  cJSON_AddItemToArray(ArrayOutput, nodeobjOutput);	
										cJSON_AddStringToObject(nodeobjOutput, "sort",(char *)sheet.autoctrl[i].output[j].typeName);
										cJSON_AddStringToObject(nodeobjOutput, "name",(char *)sheet.autoctrl[i].output[j].senseName);
										cJSON_AddStringToObject(nodeobjOutput, "deviceId",(char *)sheet.autoctrl[i].output[j].ID);
										cJSON_AddStringToObject(nodeobjOutput, "subSort",sheet.autoctrl[i].output[j].subName);
										cJSON_AddNumberToObject(nodeobjOutput, "level",sheet.autoctrl[i].output[j].limit);
								}
						}	
						rt_kprintf("\n");
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


//��վ�����߼����ƻ�Ӧ
uint16_t logCrtlAddResp(cJSON *Json)
{
	
		char* out = NULL;
		//��������
//		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
//		cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�

		cJSON_AddNumberToObject(root, "mid",respMid);
		cJSON_AddStringToObject(root, "packetType","SERVICES_CTRLCFG_ADD_RESP");

		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
		int findCtrlIndex();
		if(findCtrlIndex()==255){
			cJSON_AddNumberToObject(root, "code",1);
		}
		else{
			cJSON_AddNumberToObject(root, "code",0);
			cJSON   *arrayGet=cJSON_GetObjectItem(Json,"params");
			int arrayGet_size = cJSON_GetArraySize(arrayGet);
				
			void checkIndex();
			checkIndex();
			for(int i=0;i<arrayGet_size;i++){
				cJSON *itemp=cJSON_GetArrayItem(arrayGet,i);
			
				cJSON  *arrayInputGet =cJSON_GetObjectItem(itemp,"inputCtrl");
		    int arrayInpuGet_size = cJSON_GetArraySize(arrayInputGet);
				for(int j=0;j<arrayInpuGet_size;j++){
						cJSON *itemIn=cJSON_GetArrayItem(arrayInputGet,j);
						char *argv[6]={NULL};

						argv[1]=cJSON_GetObjectItem(itemIn,"sort")->valuestring;
						argv[2]=cJSON_GetObjectItem(itemIn,"name")->valuestring;
						argv[3]=cJSON_GetObjectItem(itemIn,"deviceId")->valuestring;
					  argv[4] =cJSON_GetObjectItem(itemIn,"subSort")->valuestring;
					  int b =cJSON_GetObjectItem(itemIn,"level")->valueint;
			
						argv[5]=rt_malloc(3);

					  snprintf(argv[5],sizeof(argv[5])-1,"%d",b);
						extern  void autoctrlInputcfg(char*argv[]);
					  rt_kprintf("%s %s \n",cJSON_GetObjectItem(itemIn,"sort")->valuestring,argv[1]);
						rt_kprintf("%s %s \n",cJSON_GetObjectItem(itemIn,"name")->valuestring,argv[2]);
						rt_kprintf("%s %s \n",cJSON_GetObjectItem(itemIn,"deviceId")->valuestring,argv[3]);
						rt_kprintf("%s %s\n",cJSON_GetObjectItem(itemIn,"subSort")->valuestring,argv[4]);
						rt_kprintf("%d %s\n",cJSON_GetObjectItem(itemIn,"level")->valueint,argv[5]);
						rt_kprintf(" \n");
						autoctrlInputcfg(argv); 

						rt_free(argv[5]);
						argv[5]=NULL;

				}
				cJSON  *arrayOutputGet =cJSON_GetObjectItem(itemp,"outputCtrl");
				int arrayOutputGet_size = cJSON_GetArraySize(arrayOutputGet);
				for(int k=0;k<arrayOutputGet_size;k++){
						cJSON *itemOut=cJSON_GetArrayItem(arrayOutputGet,k);
					  char *argv[6]={NULL};
						argv[1]=cJSON_GetObjectItem(itemOut,"sort")->valuestring;
						argv[2]=cJSON_GetObjectItem(itemOut,"name")->valuestring;
						argv[3]=cJSON_GetObjectItem(itemOut,"deviceId")->valuestring;
						argv[4]=cJSON_GetObjectItem(itemOut,"subSort")->valuestring;
						int b =cJSON_GetObjectItem(itemOut,"level")->valueint;

						argv[5]=rt_malloc(3);

						snprintf(argv[5],sizeof(argv[5])-1,"%d",b);
						extern  void autoctrlOutputcfg(char*argv[]);
						autoctrlOutputcfg(argv);


						rt_free(argv[5]);
						argv[5]=NULL;

//										rt_kprintf("type %s",(char *)sheet.autoctrl[i].output[k].typeName);
//										rt_kprintf("name %s",(char *)sheet.autoctrl[i].output[k].senseName);
//										rt_kprintf("deviceId %s",(char *)sheet.autoctrl[i].output[k].ID);
//										rt_kprintf("subSort %d",sheet.autoctrl[i].output[k].subName);
//										rt_kprintf("level %d\n",sheet.autoctrl[i].output[k].limit);
				}
				void  autoCfgSure();
				autoCfgSure();
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


//��վɾ���߼�����
uint16_t logCtrlDel(cJSON *Json)
{
	
		char* out = NULL;
		//��������
//		cJSON* Array = NULL;
		// ����JSON Object  
		cJSON* root = NULL;
//		cJSON* nodeobj = NULL;
		//cJSON* nodeobj_p = NULL;
		root = cJSON_CreateObject();
		if (root == NULL) return 0;
		// ����ڵ㣨��ֵ�ԣ�
		

		cJSON_AddNumberToObject(root, "mid",respMid);
		cJSON_AddStringToObject(root, "packetType","SERVICES_CTRLCFG_DEL_RESP");
		cJSON_AddNumberToObject(root, "code",0);
	

		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{

		cJSON   *arrayGet=cJSON_GetObjectItem(Json,"params");
		int arrayGet_size = cJSON_GetArraySize(arrayGet);
		for(int i=0;i<arrayGet_size;i++){
				cJSON *item=cJSON_GetArrayItem(arrayGet,i);
				cJSON  *devID =cJSON_GetObjectItem(item,"ctrlNum");
				if((devID->valueint!=0)&&(devID->valueint<=CRTL_TOTAL_NUM)){
					void delAutoCfg(int num);
					delAutoCfg(devID->valueint);
					
				}
//				else		
//					cJSON_AddNumberToObject(root, "code",1);

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
//��վɾ���߼����ƻ�Ӧ
uint16_t logCrtlDelResp(cJSON *Json,char *identify)
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
						cJSON_AddNumberToObject(nodeobj,"levelStatus",(uint8_t)v5OutputReadFun(j));
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

