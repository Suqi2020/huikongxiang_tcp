#include <board.h>
//#include "rs485PartDischag.h"
//#include "stmflash.h"
//<<�ַ����߼�� --GY-JF100-C01>>  GZPD-1000���¾ַ�
//��Ӧʱ�䲻ȷ�� �1.7�� ��ʱ�� ��ʱ���
//           Ĭ�ϲ�����115200

 typedef struct  
 { 
  unsigned a:1; 
  unsigned b:3; 
  unsigned c:4; 
 } bs; 
 
typedef struct{
		uint32_t amplitudeA;
	  uint32_t freqA;
	  uint32_t dischargeA;
	
		uint32_t amplitudeB;
		uint32_t freqB;
		uint32_t dischargeB;

		uint32_t amplitudeC;
		uint32_t freqC;
		uint32_t dischargeC;
	
	  bs alarm;  //bit0 A bit1 B bit2 C
	  uint8_t respStat;
}partDischargeStru;

const static char sign[]="[�ַ�]";
partDischargeStru partDiscStru_p[PARTDISCHAG_485_NUM];

static bool alarmFLag=false;


//�ַűȽ���ֵ��������Ӧ��flag���
static void partDischCheckSetFlag(int num)
{
	  alarmFLag=false;
	  //high
	  if(sheet.modbusPartDisChg[num].amplitudeAUpLimit!=0){
			if(partDiscStru_p[num].amplitudeA>=sheet.modbusPartDisChg[num].amplitudeAUpLimit)
					inpoutpFlag.modbusPartDisChg[num].amplitudeAUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].amplitudeBUpLimit!=0){
			if(partDiscStru_p[num].amplitudeB>=sheet.modbusPartDisChg[num].amplitudeBUpLimit)
					inpoutpFlag.modbusPartDisChg[num].amplitudeBUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].amplitudeCUpLimit!=0){
			if(partDiscStru_p[num].amplitudeC>=sheet.modbusPartDisChg[num].amplitudeCUpLimit)
					inpoutpFlag.modbusPartDisChg[num].amplitudeCUpFlag=true;alarmFLag=true;
		}
		//low
		if(sheet.modbusPartDisChg[num].amplitudeALowLimit!=0){
			if(partDiscStru_p[num].amplitudeA<=sheet.modbusPartDisChg[num].amplitudeALowLimit)
					inpoutpFlag.modbusPartDisChg[num].amplitudeALowFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].amplitudeBLowLimit!=0){
			if(partDiscStru_p[num].amplitudeB<=sheet.modbusPartDisChg[num].amplitudeBLowLimit)
					inpoutpFlag.modbusPartDisChg[num].amplitudeBLowFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].amplitudeCLowLimit!=0){
			if(partDiscStru_p[num].amplitudeC<=sheet.modbusPartDisChg[num].amplitudeCLowLimit)
					inpoutpFlag.modbusPartDisChg[num].amplitudeCLowFlag=true;alarmFLag=true;
		}
		//high
		if(sheet.modbusPartDisChg[num].dischargeAUpLimit!=0){
			if(partDiscStru_p[num].dischargeA>=sheet.modbusPartDisChg[num].dischargeAUpLimit)
					inpoutpFlag.modbusPartDisChg[num].dischargeAUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].dischargeBUpLimit!=0){
			if(partDiscStru_p[num].dischargeB>=sheet.modbusPartDisChg[num].dischargeBUpLimit)
					inpoutpFlag.modbusPartDisChg[num].dischargeBUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].dischargeCUpLimit!=0){
			if(partDiscStru_p[num].dischargeC>=sheet.modbusPartDisChg[num].dischargeCUpLimit)
					inpoutpFlag.modbusPartDisChg[num].dischargeCUpFlag=true;alarmFLag=true;
		}
		//low
		if(sheet.modbusPartDisChg[num].dischargeALowLimit!=0){
			if(partDiscStru_p[num].dischargeA<=sheet.modbusPartDisChg[num].dischargeALowLimit)
					inpoutpFlag.modbusPartDisChg[num].dischargeALowFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].dischargeBLowLimit!=0){
			if(partDiscStru_p[num].dischargeB<=sheet.modbusPartDisChg[num].dischargeBLowLimit)
					inpoutpFlag.modbusPartDisChg[num].dischargeBLowFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].dischargeCLowLimit!=0){
			if(partDiscStru_p[num].dischargeC<=sheet.modbusPartDisChg[num].dischargeCLowLimit)
					inpoutpFlag.modbusPartDisChg[num].dischargeCLowFlag=true;alarmFLag=true;
		}
		
		
		//high
		if(sheet.modbusPartDisChg[num].freqAUpLimit!=0){
			if(partDiscStru_p[num].freqA>=sheet.modbusPartDisChg[num].freqAUpLimit)
					inpoutpFlag.modbusPartDisChg[num].freqAUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].freqBUpLimit!=0){
			if(partDiscStru_p[num].freqB>=sheet.modbusPartDisChg[num].freqBUpLimit)
					inpoutpFlag.modbusPartDisChg[num].freqBUpFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].freqCUpLimit!=0){
			if(partDiscStru_p[num].freqC>=sheet.modbusPartDisChg[num].freqCUpLimit)
					inpoutpFlag.modbusPartDisChg[num].freqCUpFlag=true;alarmFLag=true;
		}
		
				//low
		if(sheet.modbusPartDisChg[num].freqALowLimit!=0){
			if(partDiscStru_p[num].freqA<=sheet.modbusPartDisChg[num].freqALowLimit)
					inpoutpFlag.modbusPartDisChg[num].freqALowFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].freqBLowLimit!=0){
			if(partDiscStru_p[num].freqB<=sheet.modbusPartDisChg[num].freqBLowLimit)
					inpoutpFlag.modbusPartDisChg[num].freqBLowFlag=true;alarmFLag=true;
		}
		if(sheet.modbusPartDisChg[num].freqCLowLimit!=0){
			if(partDiscStru_p[num].freqC<=sheet.modbusPartDisChg[num].freqCLowLimit)
					inpoutpFlag.modbusPartDisChg[num].freqCLowFlag=true;alarmFLag=true;
		}
}
//���ؾַŵ�ͨѶ״̬ true--ͨѶ�ɹ� false--ͨѶʧ��
int partDisState(int i)
{
		return partDiscStru_p[i].respStat;
}
//#define   SLAVE_ADDR     0X01
////#define   LENTH          1024  //���������õ���������buf����

//�ַŶ�ȡ���ݵķ���  ����485����
static void partDischagUartSend(int num,uint8_t *buf,int len)
{
		rs485UartSend(sheet.partDischag[num].useUartNum,buf, len);
	
}

//��ȡ��ֵ Ƶ�� �ŵ�������
//01 03 0300 0006 C58C
//01 03 24 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 7B A1 
//��ȡ�ַŵķ�ֵ Ƶ��
void readPdFreqDischarge(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = modbusReadReg(sheet.partDischag[num].slaveAddr,0x0300,READ_03,18,buf);
//		rt_mutex_take(uartDev[sheet.partDischag[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		partDischagUartSend(num,buf,len);
	  rt_kprintf("%sPdFreqDiach send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
		memset(buf,0,LENTH);
    len=0;
		if(rt_mq_recv(&uartmque[sheet.partDischag[num].useUartNum], buf+len, 1, 3000) == RT_EOK){//��һ�ν���ʱ��ų���  ��Ӧʱ���п��ܱȽϾ�
				len++;
		}
		while(rt_mq_recv(&uartmque[sheet.partDischag[num].useUartNum], buf+len, 1, 10) == RT_EOK){//115200 ������1ms 10������
				len++;
		}
		if(len!=0){
				rt_kprintf("%srec:",sign);
				for(int j=0;j<len;j++){
						rt_kprintf("%x ",buf[j]);
				}
				rt_kprintf("\n");
		}
		int ret2= modbusRespCheck(sheet.partDischag[num].slaveAddr,buf,len,RT_TRUE);
		if(0 ==  ret2){//ˢ�¶�ȡ����ֵ
			
				partDiscStru_p[num].amplitudeA=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
				partDiscStru_p[num].freqA     =(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  partDiscStru_p[num].dischargeA=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			
				partDiscStru_p[num].amplitudeB=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
				partDiscStru_p[num].freqB     =(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  partDiscStru_p[num].dischargeB=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			
				partDiscStru_p[num].amplitudeC=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
				partDiscStru_p[num].freqC     =(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  partDiscStru_p[num].dischargeC=(buf[offset]<<24)+(buf[offset+1]<<16)+(buf[offset+2]<<8)+buf[offset+3];offset+=4;
			  rt_kprintf("%sPdFreqDiach read ok\n",sign);
			  partDiscStru_p[num].respStat=1;
				partDischCheckSetFlag(num);
		} 
		else{//��������0
				if(ret2==2){
						//rt_kprintf("%sERR:����485���߻��߹���\r\n",sign);
				}
				partDiscStru_p[num].respStat=0;
				partDiscStru_p[num].amplitudeA=0;
				partDiscStru_p[num].freqA     =0;
			  partDiscStru_p[num].dischargeA=0;
			
				partDiscStru_p[num].amplitudeB=0;
				partDiscStru_p[num].freqB     =0;
			  partDiscStru_p[num].dischargeB=0;
			
				partDiscStru_p[num].amplitudeC=0;
				partDiscStru_p[num].freqC     =0;
			  partDiscStru_p[num].dischargeC=0;
			  rt_kprintf("%sPdFreqDiach read fail\n",sign);
		}
    //partDischCheckSetFlag(num);//test only
//	  rt_mutex_release(uartDev[sheet.partDischag[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;

}

//��ȡ�ַű���״̬ 
//�� 01 01 0001 0008 6C0C
//�� 01 01 01 00 51 88 

rt_bool_t readPartDischgWarning(int num)
{
	  uint8_t offset=3;//add+regadd+len
	  uint8_t  *buf = RT_NULL;
		buf = rt_malloc(LENTH);
	  uint16_t len = modbusReadBitReg(sheet.partDischag[num].slaveAddr,0x0001,8,buf);//��ȡ8��bit
//		rt_mutex_take(uartDev[sheet.partDischag[num].useUartNum].uartMutex,RT_WAITING_FOREVER);
	  //485����buf  len  �ȴ�modbus��Ӧ
		partDischagUartSend(num,buf,len);
	  rt_kprintf("%sreadPd send:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
		memset(buf,0,LENTH);
    len=0;
		if(rt_mq_recv(&uartmque[sheet.partDischag[num].useUartNum], buf+len, 1, 2000) == RT_EOK){//��һ�ν���ʱ��ų���  ��Ӧʱ���п��ܱȽϾ�
				len++;
		}
		while(rt_mq_recv(&uartmque[sheet.partDischag[num].useUartNum], buf+len, 1, 10) == RT_EOK){//115200 ������1ms 10������
				len++;
		}
		rt_kprintf("%srec:",sign);
		for(int j=0;j<len;j++){
				rt_kprintf("%x ",buf[j]);
		}
		rt_kprintf("\n");
//		uartDev[modbusFlash[PARTDISCHAG].useUartNum].offline=RT_FALSE;
		//��ȡ����ֵ ��һ���ж�crc �ڶ�����ȡ
		int ret2=modbusRespCheck(sheet.partDischag[num].slaveAddr,buf,len,RT_TRUE);
		if(0 == ret2){//ˢ�¶�ȡ����ֵ
     
			  partDiscStru_p[num].alarm.a=(buf[offset]>>0)&0x01;
				partDiscStru_p[num].alarm.b=(buf[offset]>>1)&0x01;
			  partDiscStru_p[num].alarm.c=(buf[offset]>>2)&0x01;
			  rt_kprintf("%s��ȡalarm OK\r\n",sign);
			  partDiscStru_p[num].respStat=1;
		} 
		else{
				if(ret2==2){
				}
				partDiscStru_p[num].respStat=0;
				partDiscStru_p[num].alarm.a=0;
				partDiscStru_p[num].alarm.b=0;
				partDiscStru_p[num].alarm.c=0;
			  rt_kprintf("%s��ȡalarm fail\r\n",sign);
		}
   
//	  rt_mutex_release(uartDev[sheet.partDischag[num].useUartNum].uartMutex);
		rt_free(buf);
	  buf=RT_NULL;
		if(partDiscStru_p[num].alarm.a||partDiscStru_p[num].alarm.b||partDiscStru_p[num].alarm.c)
				return RT_TRUE;
		else 
			  return RT_FALSE;
}

void  partDisWaringEventPack()
{
		rt_kprintf("%slater add \n\r",sign);
		
}
//�ַŵ�json��ʽ���
//���� respFlag Ϊtrue���ǻ�Ӧ
//              Ϊfalse����report����
uint16_t partDischagJsonPack(bool respFlag)
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
		cJSON_AddStringToObject(root, "identifier","partial_discharge_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		
		{
		Array = cJSON_CreateArray();
		if (Array == NULL) return 0;
		cJSON_AddItemToObject(root, "params", Array);
		for (int i = 0; i < PARTDISCHAG_485_NUM; i++)
		{		
			
			if(sheet.partDischag[i].workFlag==RT_TRUE){
				nodeobj = cJSON_CreateObject();
				cJSON_AddItemToArray(Array, nodeobj);
			  cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.partDischag[i].ID));
//				sprintf(sprinBuf,"%d",partDiscStru_p[i].respStat);
				cJSON_AddNumberToObject(nodeobj,"responseStatus",partDiscStru_p[i].respStat);
//				sprintf(sprinBuf,"%d",partDiscStru_p[i].respStat);
//				cJSON_AddItemToObject(nodeobj,"responseStatus",cJSON_CreateString(sprinBuf));
				nodeobj_p= cJSON_CreateObject();
				cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);
				
				sprintf(sprinBuf,"%d",partDiscStru_p[i].amplitudeA);
				cJSON_AddItemToObject(nodeobj_p,"pdA",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%d",partDiscStru_p[i].freqA);
				cJSON_AddItemToObject(nodeobj_p,"freqA",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%d",partDiscStru_p[i].dischargeA);
				cJSON_AddItemToObject(nodeobj_p,"dischargeDataA",cJSON_CreateString(sprinBuf));
				cJSON_AddItemToObject(nodeobj_p,"prpdDataA",cJSON_CreateString(""));
				cJSON_AddItemToObject(nodeobj_p,"prpsDataA",cJSON_CreateString(""));
				
				
				sprintf(sprinBuf,"%d",partDiscStru_p[i].amplitudeB);
				cJSON_AddItemToObject(nodeobj_p,"pdB",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%d",partDiscStru_p[i].freqB);
				cJSON_AddItemToObject(nodeobj_p,"freqB",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%d",partDiscStru_p[i].dischargeB);
				cJSON_AddItemToObject(nodeobj_p,"dischargeDataB",cJSON_CreateString(sprinBuf));
				cJSON_AddItemToObject(nodeobj_p,"prpdDataB",cJSON_CreateString(""));
				cJSON_AddItemToObject(nodeobj_p,"prpsDataB",cJSON_CreateString(""));
				
				sprintf(sprinBuf,"%d",partDiscStru_p[i].amplitudeC);
				cJSON_AddItemToObject(nodeobj_p,"pdC",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%d",partDiscStru_p[i].freqC);
				cJSON_AddItemToObject(nodeobj_p,"freqC",cJSON_CreateString(sprinBuf));
				sprintf(sprinBuf,"%d",partDiscStru_p[i].dischargeC);
				cJSON_AddItemToObject(nodeobj_p,"dischargeDataC",cJSON_CreateString(sprinBuf));
				cJSON_AddItemToObject(nodeobj_p,"prpdDataC",cJSON_CreateString(""));
				cJSON_AddItemToObject(nodeobj_p,"prpsDataC",cJSON_CreateString(""));
				
				
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




//��λ��ʪ�ȵ�warn״ֵ̬
void resetPartDischagWarnFlag()
{
		for (int i = 0; i < PARTDISCHAG_485_NUM; i++)
		{		
				inpoutpFlag.modbusPartDisChg[i].amplitudeALowFlag =false;
				inpoutpFlag.modbusPartDisChg[i].amplitudeAUpFlag=false;
				inpoutpFlag.modbusPartDisChg[i].dischargeALowFlag=false;
				inpoutpFlag.modbusPartDisChg[i].dischargeAUpFlag =false;
				inpoutpFlag.modbusPartDisChg[i].freqALowFlag=false;
				inpoutpFlag.modbusPartDisChg[i].freqAUpFlag =false;

				inpoutpFlag.modbusPartDisChg[i].amplitudeBLowFlag =false;
				inpoutpFlag.modbusPartDisChg[i].amplitudeBUpFlag=false;
				inpoutpFlag.modbusPartDisChg[i].dischargeBLowFlag=false;
				inpoutpFlag.modbusPartDisChg[i].dischargeBUpFlag =false;
				inpoutpFlag.modbusPartDisChg[i].freqBLowFlag=false;
				inpoutpFlag.modbusPartDisChg[i].freqBUpFlag =false;
			
				inpoutpFlag.modbusPartDisChg[i].amplitudeCLowFlag =false;
				inpoutpFlag.modbusPartDisChg[i].amplitudeCUpFlag=false;
				inpoutpFlag.modbusPartDisChg[i].dischargeCLowFlag=false;
				inpoutpFlag.modbusPartDisChg[i].dischargeCUpFlag =false;
				inpoutpFlag.modbusPartDisChg[i].freqCLowFlag=false;
				inpoutpFlag.modbusPartDisChg[i].freqCUpFlag =false;
		}
}





//ģ���¶Ⱥ�ʪ��ֵ��ȡ�Լ������json��ʽ  ����true �и澯 false �޸澯
bool modPartDischagWarn2Send()
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
		cJSON_AddStringToObject(root, "identifier","partial_discharge_monitor");
		cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		char *sprinBuf=RT_NULL;
		sprinBuf=rt_malloc(20);//20���ַ������� ������
		{
				Array = cJSON_CreateArray();
				if (Array == NULL) return false;
				cJSON_AddItemToObject(root, "params", Array);
				for (int i = 0; i < PARTDISCHAG_485_NUM; i++)
				{		
						if(sheet.partDischag[i].workFlag==RT_TRUE){
							nodeobj = cJSON_CreateObject();
							cJSON_AddItemToArray(Array, nodeobj);
							cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.partDischag[i].ID));
							cJSON_AddNumberToObject(nodeobj,"alarmStatus",1);
							nodeobj_p= cJSON_CreateObject();
							cJSON_AddItemToObject(nodeobj, "data", nodeobj_p);

							cJSON_AddNumberToObject(nodeobj_p,"pdA_low_alarm",inpoutpFlag.modbusPartDisChg[i].amplitudeALowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"pdA_high_alarm",inpoutpFlag.modbusPartDisChg[i].amplitudeAUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"freqA_low_alarm",inpoutpFlag.modbusPartDisChg[i].freqALowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"freqA_high_alarm",inpoutpFlag.modbusPartDisChg[i].freqAUpFlag);		
							cJSON_AddNumberToObject(nodeobj_p,"dischargeDateA_low_alarm",inpoutpFlag.modbusPartDisChg[i].dischargeALowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"dischargeDateA_high_alarm",inpoutpFlag.modbusPartDisChg[i].dischargeAUpFlag);		
							
							cJSON_AddNumberToObject(nodeobj_p,"pdB_low_alarm",inpoutpFlag.modbusPartDisChg[i].amplitudeBLowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"pdB_high_alarm",inpoutpFlag.modbusPartDisChg[i].amplitudeBUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"freqB_low_alarm",inpoutpFlag.modbusPartDisChg[i].freqBLowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"freqB_high_alarm",inpoutpFlag.modbusPartDisChg[i].freqBUpFlag);		
							cJSON_AddNumberToObject(nodeobj_p,"dischargeDateB_low_alarm",inpoutpFlag.modbusPartDisChg[i].dischargeBLowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"dischargeDateB_high_alarm",inpoutpFlag.modbusPartDisChg[i].dischargeBUpFlag);	

							cJSON_AddNumberToObject(nodeobj_p,"pdC_low_alarm",inpoutpFlag.modbusPartDisChg[i].amplitudeCLowFlag );//cJSON_CreateNumber("10"));
							cJSON_AddNumberToObject(nodeobj_p,"pdC_high_alarm",inpoutpFlag.modbusPartDisChg[i].amplitudeCUpFlag);
							cJSON_AddNumberToObject(nodeobj_p,"freqC_low_alarm",inpoutpFlag.modbusPartDisChg[i].freqCLowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"freqC_high_alarm",inpoutpFlag.modbusPartDisChg[i].freqCUpFlag);		
							cJSON_AddNumberToObject(nodeobj_p,"dischargeDateC_low_alarm",inpoutpFlag.modbusPartDisChg[i].dischargeCLowFlag);
							cJSON_AddNumberToObject(nodeobj_p,"dischargeDateC_high_alarm",inpoutpFlag.modbusPartDisChg[i].dischargeCUpFlag);	
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

//�ַŵĶ�ȡ�ͷ���  ����������������
void partDischagRead2Send(rt_bool_t netStat,bool respFlag)
{
		int workFlag=RT_FALSE;
		for(int i=0;i<PARTDISCHAG_485_NUM;i++){
			 if(sheet.partDischag[i].workFlag==RT_TRUE){
				    rt_thread_mdelay(2000);
						readPdFreqDischarge(i);
						workFlag=RT_TRUE;
				}
		}
		if(workFlag==RT_TRUE){
				rt_kprintf("%s����ɼ���PARTDISCHAG����\r\n",sign);
				partDischagJsonPack(respFlag);//���ڼ���
				if(netStat==RT_TRUE)
						rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				rt_thread_mdelay(500);
				if(modPartDischagWarn2Send()==true){
						resetPartDischagWarnFlag();//ÿ���жϺ�λwarnflag״ֵ̬
						//rt_thread_mdelay(500);
						if(netStat==RT_TRUE)
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER);
				}
		}
}
