#include "board.h"
//#include "stmflash.h"
//<<���ڻ��� GY-JDHL03>>  Ŀǰ����ֻ�ɼ�����ֵ
//��Ӧʱ�� 200ms  Ĭ�ϲ�����115200
//  1����ȡ����ֵ   
//  2����ȡ������־ 
//  3�����ñ�����ֵ 
//  4����ȡ������ֵ
//  5�����òɼ����
//  6����ȡ�ɼ����
//����RS485������Ҫ���� UART5_IRQHandler�Լ�HAL_UART_Transmit���ʹ���  
//����Ҫ������Ӧ���ڵĶ��� ���� char num=0;
// 9600������ ע���޸Ĵ˴� rt_mq_recv(uartDev[modbusFlash[CIRCULA].useUartNum].uartMessque, &buf, sizeof(buf), 2)
//Ѹ���л�����485�ӿ���ʹ�� ������ֻ��Ҫ�޸Ĵ��ڷ��ͽӿ� ���жϽ��սӿڼ���
// rs485Circula.c-cirCurrUartSend(uint8_t *buf,int len) ��drv_uart.c-USART2_IRQHandler��
// cirCurrUartSend(uint8_t *buf,int len)   cirCurrUartRec(uint8_t dat)
static  bool alarmFLag=false;
typedef struct
{
	  //����ֵ �Ŵ���100��
		float circlCurA;
		float circlCurB;
	  float circlCurC;
	  float circlCurD;//����
	  //��ֵ
	  //uint32_t thresholdVal;

	  
	  //����״̬  һ���ֽ��㹻 ����Խ�modbus��Ӧ
	  uint16_t warningA;
	  uint16_t warningB;
	  uint16_t warningC;
	  uint16_t warningD;
	  
	  //�ɼ���� ��λ��
		//uint16_t AcqInterv;
	//С���������ֵ
    uint16_t point; //��modbus��ʵֵ  �˴���ȡmodbus�󾭹���ת������ֱ�Ӽ���  0-ֵΪ100  1-2 ֵΪ10
	  uint8_t respStat;
} CIRCURStru;

const static char sign[]="[����]";

//#define   SLAVE_ADDR     0X02
//#define   LENTH          50  //���������õ���������buf����
extern uint8_t packBuf[TX_RX_MAX_BUF_SIZE];

 CIRCURStru  cirCurStru_p[CIRCULA_485_NUM];
//static uint16_t readAcqInterv(int num);
//static uint16_t readPoint(int num);
//static uint32_t readThresholdVal(int num);
//static rt_bool_t writeAcqInterv(uint16_t value);
//static rt_bool_t writeThresholdVal(uint32_t value);
//static rt_bool_t writePoint(uint16_t value);

//���ػ�����ͨѶ״̬ true--ͨѶ�ɹ� false--ͨѶʧ��
int cirCurrtState(int i)
{
		return cirCurStru_p[i].respStat;
}
//������ڷ��� 
void cirCurrUartSend(int num,uint8_t *buf,int len)
{

		rs485UartSend(sheet.cirCula[num].useUartNum,buf, len);

}
//�����Ƚ���ֵ��������Ӧ��flag���
static void circulaCheckSetFlag(int num)
{
	  alarmFLag=false;
	  if(sheet.modbusCircul[num].cirCurAUpLimit!=0){
			if(cirCurStru_p[num].circlCurA>=sheet.modbusCircul[num].cirCurAUpLimit){
					inpoutpFlag.modbusCircul[num].cirCurAUpFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusCircul[num].cirCurALowLimit!=0){
			if(cirCurStru_p[num].circlCurA<=sheet.modbusCircul[num].cirCurALowLimit){
					inpoutpFlag.modbusCircul[num].cirCurALowFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusCircul[num].cirCurBUpLimit!=0){
			if(cirCurStru_p[num].circlCurB>=sheet.modbusCircul[num].cirCurBUpLimit){
					inpoutpFlag.modbusCircul[num].cirCurBUpFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusCircul[num].cirCurBLowLimit!=0){
			if(cirCurStru_p[num].circlCurB<=sheet.modbusCircul[num].cirCurBLowLimit){
					inpoutpFlag.modbusCircul[num].cirCurBLowFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusCircul[num].cirCurCUpLimit!=0){
			if(cirCurStru_p[num].circlCurC>=sheet.modbusCircul[num].cirCurCUpLimit){
					inpoutpFlag.modbusCircul[num].cirCurCUpFlag=true;alarmFLag=true;
			}
		}
		if(sheet.modbusCircul[num].cirCurCUpLimit!=0){
			if(cirCurStru_p[num].circlCurC<=sheet.modbusCircul[num].cirCurCLowLimit){
					inpoutpFlag.modbusCircul[num].cirCurCLowFlag=true;alarmFLag=true;
			}
		}

}
///////////////////////////////////////��д�Ĵ�����ز���////////////////////////////////////////
//��ȡ����ֵ�ͱ�����Ϣ �Ĵ�����ַ 0x0023 ����12
void readCirCurrAndWaring(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  //uint8_t   buf[100]
	  uint16_t len = modbusReadReg(sheet.cirCula[num].slaveAddr,0x0023,READ_03,12,buf);
	  //485����buf  len  �ȴ�modbus��Ӧ
	  //recFlag = RT_TRUE;
	  cirCurrUartSend(num,buf,len);

	  rt_kprintf("%sreadCirCurrAndWaring send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
//	  rt_mutex_take(uartDev[sheet.cirCula[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
		memset(buf,0,LENTH);
    len=0;
		while(rt_mq_recv(&uartmque[sheet.cirCula[num].useUartNum], buf+len, 1, 500) == RT_EOK){//115200 ������1ms 10������
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
		int ret=modbusRespCheck(sheet.cirCula[num].slaveAddr,buf,len,RT_TRUE);
		if(0 ==  ret){//ˢ�¶�ȡ����ֵ
			  int cula=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
		    cirCurStru_p[num].circlCurA=(float)cula/cirCurStru_p[num].point;
			  cula=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  cirCurStru_p[num].circlCurB=(float)cula/cirCurStru_p[num].point;
				cula=cirCurStru_p[num].circlCurC=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  cirCurStru_p[num].circlCurC=(float)cula/cirCurStru_p[num].point;
				cula=cirCurStru_p[num].circlCurD=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  cirCurStru_p[num].circlCurD=(float)cula/cirCurStru_p[num].point;
			  cirCurStru_p[num].warningA	=(buf[offset]<<8)	+buf[offset+1];	offset+=2;
			  cirCurStru_p[num].warningB	=(buf[offset]<<8)	+buf[offset+1];	offset+=2;
			  cirCurStru_p[num].warningC	=(buf[offset]<<8)	+buf[offset+1];	offset+=2;
			  cirCurStru_p[num].warningD	=(buf[offset]<<8)	+buf[offset+1];	offset+=2;
			  rt_kprintf("%s��ȡ����������ֵ�ɹ�\r\n",sign);
			  cirCurStru_p[num].respStat=1;
				circulaCheckSetFlag(num);
		} 
		else{//��������0
			  if(ret==2){
						//rt_kprintf("%sERR:����485���߻��߹���\r\n",sign);
				}
				cirCurStru_p[num].respStat=0;
				cirCurStru_p[num].circlCurA=0;
				cirCurStru_p[num].circlCurB=0;
				cirCurStru_p[num].circlCurC=0;
				cirCurStru_p[num].circlCurD=0;
			  cirCurStru_p[num].warningA	=0;
			  cirCurStru_p[num].warningB	=0;
			  cirCurStru_p[num].warningC	=0;
			  cirCurStru_p[num].warningD	=0;
			  rt_kprintf("%s��ȡ����������ֵfail\r\n",sign);
		}

//		circulaCheckSetFlag(num);
		//recFlag = RT_FALSE;
//	  rt_mutex_release(uartDev[sheet.cirCula[num].useUartNum].uartMutex);
	//	 rt_kprintf("release\r\n");
		rt_free(buf);
	//	 rt_kprintf("free\r\n");
	  buf=RT_NULL;
		
}

//��ȡС������ʽ
static uint16_t readPoint(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = modbusReadReg(sheet.cirCula[num].slaveAddr,0x000B,READ_03,1,buf);
	  uint16_t ret =0;
	//	recFlag = RT_TRUE;
//		rt_mutex_take(uartDev[sheet.cirCula[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		cirCurrUartSend(num,buf,len);
	  rt_kprintf("%sreadPoint send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
		memset(buf,0,LENTH);
    len=0;
		while(rt_mq_recv(&uartmque[sheet.cirCula[num].useUartNum], buf+len, 1, 500) == RT_EOK){//115200 ������1ms 10������
				len++;
		}
		rt_kprintf("%srec:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
		//��ȡ����ֵ ��һ���ж�crc �ڶ�����ȡ
		int ret2=modbusRespCheck(sheet.cirCula[num].slaveAddr,buf,len,RT_TRUE);
		if(0 == ret2){//ˢ�¶�ȡ����ֵ

			  ret	=(buf[offset]<<8)	+buf[offset+1];	//offset+=2;
			  if(ret==0)
						cirCurStru_p[num].point =100;
				else
						cirCurStru_p[num].point =10;
			  rt_kprintf("%s��ȡС���� %d\r\n",sign,cirCurStru_p[num].point);
		} 
		else{
			  cirCurStru_p[num].point =100;//����Ĭ��ֵ

		}
//	  rt_mutex_release(uartDev[sheet.cirCula[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;
		return ret;
}
//��ȡ��·С���㴦��ʽ
void readMultiCirCulaPoint()
{
		for (int i = 0; i < CIRCULA_485_NUM; i++)
		{		
				if(sheet.cirCula[i].workFlag==RT_TRUE){
						readPoint(i);
				}
		}
}




//����json��ʽ���
	//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
uint16_t circulaJsonPack(bool respFlag)
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
		cJSON_AddStringToObject(root, "identifier","grounding_current_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
			Array = cJSON_CreateArray();
			if (Array == NULL) return 0;
			cJSON_AddItemToObject(root, "params", Array);
			for (int i = 0; i < CIRCULA_485_NUM; i++)
			{		

				if(sheet.cirCula[i].workFlag==RT_TRUE){
					nodeobj = cJSON_CreateObject();
					cJSON_AddItemToArray(Array, nodeobj);
					cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.cirCula[i].ID));
			
				  cJSON_AddNumberToObject(nodeobj,"responseStatus",cirCurStru_p[i].respStat);
					
					nodeobj_p= cJSON_CreateObject();
					cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
					
					sprintf(sprinBuf,"%02f",cirCurStru_p[i].circlCurA);
					cJSON_AddItemToObject(nodeobj_p,"earthCurA",cJSON_CreateString(sprinBuf));
					cJSON_AddItemToObject(nodeobj_p,"runCurA",cJSON_CreateString(""));
					cJSON_AddItemToObject(nodeobj_p,"loadRatioA",cJSON_CreateString(""));
					
					sprintf(sprinBuf,"%02f",cirCurStru_p[i].circlCurB);
					cJSON_AddItemToObject(nodeobj_p,"earthCurB",cJSON_CreateString(sprinBuf));
					cJSON_AddItemToObject(nodeobj_p,"runCurB",cJSON_CreateString(""));
					cJSON_AddItemToObject(nodeobj_p,"loadRatioB",cJSON_CreateString(""));
					
					sprintf(sprinBuf,"%02f",cirCurStru_p[i].circlCurC);
					cJSON_AddItemToObject(nodeobj_p,"earthCurC",cJSON_CreateString(sprinBuf));
					cJSON_AddItemToObject(nodeobj_p,"runCurC",cJSON_CreateString(""));
					cJSON_AddItemToObject(nodeobj_p,"loadRatioC",cJSON_CreateString(""));
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
		rt_kprintf("%scirCula len:%d\r\n",sign,len);
		rt_kprintf("\r\n%slen��%d str0:%x str1:%x str[2]:%d  str[3]:%d\r\n",sign,len,packBuf[0],packBuf[1],packBuf[2],packBuf[3]);

		rt_free(sprinBuf);
		sprinBuf=RT_NULL;

		return len;
}



//�ж��Ƿ��б��� ��Ҫ��readCirCurrAndWaring()���ʹ��
rt_bool_t cirCurrWaringcheck(int num)
{
		if((cirCurStru_p[num].warningA)||(cirCurStru_p[num].warningA)||(cirCurStru_p[num].warningA)|(cirCurStru_p[num].warningA)){
			 rt_kprintf("%sERR:����ֵ���� �������� \n\r",sign);
				return RT_TRUE;
		}
		return RT_FALSE;
}


//�澯��Ϣ�Ĵ��  readCirCurrAndWaring()
void  cirCurrWaringEventPack()
{
		rt_kprintf("%s���ڼ��� \n\r",sign);
		
}








//��λ��ʪ�ȵ�warn״ֵ̬
void resetCirCurrlWarnFlag()
{
		for (int i = 0; i < CIRCULA_485_NUM; i++)
		{		
				inpoutpFlag.modbusCircul[i].cirCurALowFlag =false;
				inpoutpFlag.modbusCircul[i].cirCurAUpFlag=false;
				inpoutpFlag.modbusCircul[i].cirCurBLowFlag=false;
				inpoutpFlag.modbusCircul[i].cirCurBUpFlag =false;
				inpoutpFlag.modbusCircul[i].cirCurCLowFlag=false;
				inpoutpFlag.modbusCircul[i].cirCurCUpFlag =false;
		}
}





//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ  ����true �и澯 false �޸澯
bool modCirCurrWarn2Send()
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
		cJSON_AddStringToObject(root, "identifier","grounding_current_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);
				for (int i = 0; i < CIRCULA_485_NUM; i++)
				{		
						if(sheet.cirCula[i].workFlag==RT_TRUE){
							nodeobj = cJSON_CreateObject();
							cJSON_AddItemToArray(Array, nodeobj);
							cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.cirCula[i].ID));
							cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
							nodeobj_p= cJSON_CreateObject();
							cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
							
							cJSON_AddNumberToObject(nodeobj_p,"earthCurA_low_alarm",inpoutpFlag.modbusCircul[i].cirCurALowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"earthCurA_high_alarm",inpoutpFlag.modbusCircul[i].cirCurAUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"runCurA_low_alarm",0);
							cJSON_AddNumberToObject(nodeobj_p,"runCurA_high_alarm",0);		
							cJSON_AddNumberToObject(nodeobj_p,"loadRatioA_low_alarm",0);
							cJSON_AddNumberToObject(nodeobj_p,"loadRatioA_high_alarm",0);		
							cJSON_AddNumberToObject(nodeobj_p,"earthCurB_low_alarm",inpoutpFlag.modbusCircul[i].cirCurBLowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"earthCurB_high_alarm",inpoutpFlag.modbusCircul[i].cirCurBUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"runCurB_low_alarm",0);
							cJSON_AddNumberToObject(nodeobj_p,"runCurB_high_alarm",0);		
							cJSON_AddNumberToObject(nodeobj_p,"loadRatioB_low_alarm",0);
							cJSON_AddNumberToObject(nodeobj_p,"loadRatioB_high_alarm",0);	
							cJSON_AddNumberToObject(nodeobj_p,"earthCurC_low_alarm",inpoutpFlag.modbusCircul[i].cirCurCLowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"earthCurC_high_alarm",inpoutpFlag.modbusCircul[i].cirCurCUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"runCurC_low_alarm",0);
							cJSON_AddNumberToObject(nodeobj_p,"runCurC_high_alarm",0);		
							cJSON_AddNumberToObject(nodeobj_p,"loadRatioC_low_alarm",0);
							cJSON_AddNumberToObject(nodeobj_p,"loadRatioC_high_alarm",0);								
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



//������ȡ���������  ��������װ����
	//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
void circulaRead2Send(rt_bool_t netStat,bool respFlag)
{					
		int workFlag=RT_FALSE;
		for(int i=0;i<CIRCULA_485_NUM;i++){
			if(sheet.cirCula[i].workFlag==RT_TRUE){
						readCirCurrAndWaring(i);
						workFlag=RT_TRUE;
				}
		}
		if(workFlag==RT_TRUE){
				rt_kprintf("%s����ɼ���circula����\r\n",sign);
				circulaJsonPack(respFlag);
				if(netStat==RT_TRUE)
						rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				rt_thread_mdelay(500);
				if(modCirCurrWarn2Send()==true){
							resetCirCurrlWarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
							//rt_thread_mdelay(500);
							if(netStat==RT_TRUE)
									rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				}
		}
}

