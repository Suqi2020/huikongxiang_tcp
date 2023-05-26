#include "board.h"
const static char sign[]="[modbusConfig]";

const static char     UartName[UART_NUM][6] ={"port1", "port2",  "port3",  "port4"};//��ӳ��һ������
const  uartEnum UartNum[UART_NUM]     ={USE_UART2,USE_UART3,USE_UART6,USE_UART4};//��ӳ��һ������

		
//��ӡ�������ӵ�modbus�豸�б�
void printModbusDevList()
{
	  rt_kprintf("%s printf modbus device list\n",sign);
		for(int i=0;i<MODBUS_NUM;i++){
			switch(i)
			{
				case CIRCULA:
					for(int j=0;j<CIRCULA_485_NUM;j++){//�˶���û�����ù�
							if(sheet.cirCula[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.cirCula[j].ID);
									rt_kprintf("%s ",sheet.cirCula[j].model);
									rt_kprintf("%s ",UartName[sheet.cirCula[j].useUartNum]);
									rt_kprintf("%d ",sheet.cirCula[j].slaveAddr);
									rt_kprintf("%d \n",sheet.cirCulaColTime);
							}
					}
				break;
				case PARTDISCHAG:
					for(int j=0;j<PARTDISCHAG_485_NUM;j++){//�˶���û�����ù�
							if(sheet.partDischag[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
									rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.partDischag[j].ID);
									rt_kprintf("%s ",sheet.partDischag[j].model);
									rt_kprintf("%s ",UartName[sheet.partDischag[j].useUartNum]);
									rt_kprintf("%d ",sheet.partDischag[j].slaveAddr);
									rt_kprintf("%d \n",sheet.partDischagColTime);
							}
					}
				break;
				case PRESSSETTL:
					for(int j=0;j<PRESSSETTL_485_NUM;j++){//�˶���û�����ù�
							if(sheet.pressSetl[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.pressSetl[j].ID);
									rt_kprintf("%s ",sheet.pressSetl[j].model);
									rt_kprintf("%s ",UartName[sheet.pressSetl[j].useUartNum]);
									rt_kprintf("%d ",sheet.pressSetl[j].slaveAddr);
									rt_kprintf("%d \n",sheet.pressSetlColTime);
							}
					}
				break;
				case THREEAXIS:
					for(int j=0;j<THREEAXIS_485_NUM;j++){//�˶���û�����ù�
							if(sheet.threeAxiss[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.threeAxiss[j].ID);
									rt_kprintf("%s ",sheet.threeAxiss[j].model);
									rt_kprintf("%s ",UartName[sheet.threeAxiss[j].useUartNum]);
									rt_kprintf("%d ",sheet.threeAxiss[j].slaveAddr);
									rt_kprintf("%d \n",sheet.threeAxissColTime);
							}
					}
				break;
	#ifdef USE_4GAS 
				case CH4:
					for(int j=0;j<CH4_485_NUM;j++){//�˶���û�����ù�
							if(sheet.ch4[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.ch4[j].ID);
									rt_kprintf("%s ",sheet.ch4[j].model);
									rt_kprintf("%s ",UartName[sheet.ch4[j].useUartNum]);
									rt_kprintf("%d ",sheet.ch4[j].slaveAddr);
									rt_kprintf("%d \n",sheet.ch4ColTime);//sheet.ch4ColTime);
							}
					}
				break;
				case O2:
					for(int j=0;j<O2_485_NUM;j++){//�˶���û�����ù�
							if(sheet.o2[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.o2[j].ID);
									rt_kprintf("%s ",sheet.o2[j].model);
									rt_kprintf("%s ",UartName[sheet.o2[j].useUartNum]);
									rt_kprintf("%d ",sheet.o2[j].slaveAddr);
									rt_kprintf("%d \n",sheet.o2ColTime);//sheet.o2ColTime);
							}
					}
				break;
				case H2S:
					for(int j=0;j<H2S_485_NUM;j++){//�˶���û�����ù�
							if(sheet.h2s[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.h2s[j].ID);
									rt_kprintf("%s ",sheet.h2s[j].model);
									rt_kprintf("%s ",UartName[sheet.h2s[j].useUartNum]);
									rt_kprintf("%d ",sheet.h2s[j].slaveAddr);
									rt_kprintf("%d \n",sheet.h2sColTime);//sheet.h2sColTime);
							}
					}
				break;
				case CO:
					for(int j=0;j<CO_485_NUM;j++){//�˶���û�����ù�
							if(sheet.co[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.co[j].ID);
									rt_kprintf("%s ",sheet.co[j].model);
									rt_kprintf("%s ",UartName[sheet.co[j].useUartNum]);
									rt_kprintf("%d ",sheet.co[j].slaveAddr);
									rt_kprintf("%d \n",sheet.coColTime);
							}
					}
				break;
	#endif
				case TEMPHUM:
					for(int j=0;j<TEMPHUM_485_NUM;j++){//�˶���û�����ù�
							if(sheet.tempHum[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s ",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
									rt_kprintf("%s ",sheet.tempHum[j].ID);
									rt_kprintf("%s ",sheet.tempHum[j].model);
									rt_kprintf("%s ",UartName[sheet.tempHum[j].useUartNum]);
									rt_kprintf("%d ",sheet.tempHum[j].slaveAddr);
									rt_kprintf("%d \n",sheet.tempHumColTime);
							}
					}
				break;
				case WATERDEPTH:
					for(int j=0;j<WATERDEPTH_485_NUM;j++){//�˶���û�����ù�
							if(sheet.waterDepth[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
			
									rt_kprintf("%s ",sheet.waterDepth[j].ID);
									rt_kprintf("%s ",sheet.waterDepth[j].model);
									rt_kprintf("%s ",UartName[sheet.waterDepth[j].useUartNum]);
									rt_kprintf("%d ",sheet.waterDepth[j].slaveAddr);
									rt_kprintf("%d \n",sheet.waterDepthColTime);
							}
					}
				break;
				case CRACKMETER:
					for(int j=0;j<CRACKMETER_485_NUM;j++){//�˶���û�����ù�
							if(sheet.crackMeter[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
			
									rt_kprintf("%s ",sheet.crackMeter[j].ID);
									rt_kprintf("%s ",sheet.crackMeter[j].model);
									rt_kprintf("%s ",UartName[sheet.crackMeter[j].useUartNum]);
									rt_kprintf("%d ",sheet.crackMeter[j].slaveAddr);
									rt_kprintf("%d \n",sheet.crackMeterColTime);
							}
					}
				break;
				case COVER://���Ӿ���
					for(int j=0;j<COVER_485_NUM;j++){//�˶���û�����ù�
							if(sheet.cover[j].workFlag==RT_TRUE){
									rt_kprintf("%s modbus ",sign);
									rt_kprintf("%10s",modbusName[i]);
								  rt_kprintf("(%d)",modbusBps[i]);
			
									rt_kprintf("%s ",sheet.cover[j].ID);
									rt_kprintf("%s ",sheet.cover[j].model);
									rt_kprintf("%s ",UartName[sheet.cover[j].useUartNum]);
									rt_kprintf("%d ",sheet.cover[j].slaveAddr);
									rt_kprintf("%d \n",sheet.coverColTime);
							}
					}
				break;
				default:
				break;
			}
		}
}
//����������
static int circulaConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.cirCulaColTime=atoi32(argv[6],10);
	for( i=0;i<CIRCULA_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.cirCula[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.cirCula[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del circula ok\n",sign);
						  return 1;
					}
					else{
							sheet.cirCula[i].workFlag=RT_TRUE;//��
					}
					sheet.cirCula[i].slaveAddr=slaveAddr;	
					sheet.cirCula[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.cirCula[i].model,argv[3]);
					rt_kprintf("%s circula reconfig %d\n",sign,i);
					rt_kprintf("%s circula OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==CIRCULA_485_NUM){//û�����ù�
			for(int j=0;j<CIRCULA_485_NUM;j++){
					if(sheet.cirCula[j].workFlag!=RT_TRUE){
							sheet.cirCula[j].workFlag=RT_TRUE;//��
							sheet.cirCula[j].slaveAddr=slaveAddr;	
							sheet.cirCula[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.cirCula[j].model,argv[3]);
							rt_strcpy(sheet.cirCula[j].ID,argv[2]);
							rt_kprintf("%s circula config %d\n",sign,j);
						  rt_kprintf("%s circula OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//�ַŵ�����
static int partDischagConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.partDischagColTime=atoi32(argv[6],10);
	for( i=0;i<PARTDISCHAG_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.partDischag[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.partDischag[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del partDischarge\n",sign);
							return 1;
					}
					else{
							sheet.partDischag[i].workFlag=RT_TRUE;//��
					}
					sheet.partDischag[i].slaveAddr=slaveAddr;	
					sheet.partDischag[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.partDischag[i].model,argv[3]);
					rt_kprintf("%s partDischag reconfig %d\n",sign,i);
					rt_kprintf("%s partDischag OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==PARTDISCHAG_485_NUM){//û�����ù�
			for(int j=0;j<PARTDISCHAG_485_NUM;j++){
					if(sheet.partDischag[j].workFlag!=RT_TRUE){
							sheet.partDischag[j].workFlag=RT_TRUE;//��
							sheet.partDischag[j].slaveAddr=slaveAddr;	
							sheet.partDischag[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.partDischag[j].model,argv[3]);
							rt_strcpy(sheet.partDischag[j].ID,argv[2]);
							rt_kprintf("%s partDischag config %d\n",sign,j);
						  rt_kprintf("%s partDischag OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//�����ǵ�����
static int pressSettlConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.pressSetlColTime=atoi32(argv[6],10);
	for( i=0;i<PRESSSETTL_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.pressSetl[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.pressSetl[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del pressSettle\n",sign);
						  return 1;
					}
					else{
							sheet.pressSetl[i].workFlag=RT_TRUE;//��
					}
					sheet.pressSetl[i].slaveAddr=slaveAddr;	
					sheet.pressSetl[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.pressSetl[i].model,argv[3]);
					rt_kprintf("%s pressSettl reconfig %d\n",sign,i);
					rt_kprintf("%s pressSettl OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==PRESSSETTL_485_NUM){//û�����ù�
			for(int j=0;j<PRESSSETTL_485_NUM;j++){
					if(sheet.pressSetl[j].workFlag!=RT_TRUE){
							sheet.pressSetl[j].workFlag=RT_TRUE;//��
							sheet.pressSetl[j].slaveAddr=slaveAddr;	
							sheet.pressSetl[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.pressSetl[j].model,argv[3]);
							rt_strcpy(sheet.pressSetl[j].ID,argv[2]);
							rt_kprintf("%s pressSettl config %d\n",sign,j);
						  rt_kprintf("%s pressSettl OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//crackmeter ����
static int crackMeterConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.crackMeterColTime=atoi32(argv[6],10);
	for( i=0;i<CRACKMETER_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.crackMeter[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.crackMeter[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del cover\n",sign);
						  return 1;
					}
					else{
							sheet.crackMeter[i].workFlag=RT_TRUE;//��
					}
					sheet.crackMeter[i].slaveAddr=slaveAddr;	
					sheet.crackMeter[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.crackMeter[i].model,argv[3]);
					rt_kprintf("%s cover reconfig %d\n",sign,i);
					rt_kprintf("%s cover OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==CRACKMETER_485_NUM){//û�����ù�
			for(int j=0;j<CRACKMETER_485_NUM;j++){
					if(sheet.crackMeter[j].workFlag!=RT_TRUE){
							sheet.crackMeter[j].workFlag=RT_TRUE;//��
							sheet.crackMeter[j].slaveAddr=slaveAddr;	
							sheet.crackMeter[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.crackMeter[j].model,argv[3]);
							rt_strcpy(sheet.crackMeter[j].ID,argv[2]);
							rt_kprintf("%s crackMeter config %d\n",sign,j);
						  rt_kprintf("%s crackMeter OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}



static int coverConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.coverColTime=atoi32(argv[6],10);
	for( i=0;i<COVER_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.cover[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.cover[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del crackMeter\n",sign);
						  return 1;
					}
					else{
							sheet.cover[i].workFlag=RT_TRUE;//��
					}
					sheet.cover[i].slaveAddr=slaveAddr;	
					sheet.cover[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.cover[i].model,argv[3]);
					rt_kprintf("%s crackMeter reconfig %d\n",sign,i);
					rt_kprintf("%s crackMeter OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==COVER_485_NUM){//û�����ù�
			for(int j=0;j<COVER_485_NUM;j++){
					if(sheet.cover[j].workFlag!=RT_TRUE){
							sheet.cover[j].workFlag=RT_TRUE;//��
							sheet.cover[j].slaveAddr=slaveAddr;	
							sheet.cover[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.cover[j].model,argv[3]);
							rt_strcpy(sheet.cover[j].ID,argv[2]);
							rt_kprintf("%s cover config %d\n",sign,j);
						  rt_kprintf("%s cover OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//���������
static int threeAxisConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.threeAxissColTime =atoi32(argv[6],10);
	for( i=0;i<THREEAXIS_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.threeAxiss[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.threeAxiss[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del threeAxis\n",sign);
						  return 1;
					}
					else{
							sheet.threeAxiss[i].workFlag=RT_TRUE;//��
					}
					sheet.threeAxiss[i].slaveAddr=slaveAddr;	
					sheet.threeAxiss[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.threeAxiss[i].model,argv[3]);
					rt_kprintf("%s threeaxis reconfig %d\n",sign,i);
					rt_kprintf("%s threeaxis OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==THREEAXIS_485_NUM){//û�����ù�
			for(int j=0;j<THREEAXIS_485_NUM;j++){
					if(sheet.threeAxiss[j].workFlag!=RT_TRUE){
							sheet.threeAxiss[j].workFlag=RT_TRUE;//��
							sheet.threeAxiss[j].slaveAddr=slaveAddr;	
							sheet.threeAxiss[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.threeAxiss[j].model,argv[3]);
							rt_strcpy(sheet.threeAxiss[j].ID,argv[2]);
							rt_kprintf("%s threeaxis config %d\n",sign,j);
						  rt_kprintf("%s threeaxis OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
#ifdef USE_4GAS
//ch4������
static int ch4Conf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.ch4ColTime=atoi32(argv[6],10);
	for( i=0;i<CH4_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.ch4[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.ch4[i].workFlag=RT_FALSE;//�ر�
							rt_kprintf("%s del ch4\n",sign);
						  return 1;
					}
					else{
							sheet.ch4[i].workFlag=RT_TRUE;//��
					}
					sheet.ch4[i].slaveAddr=slaveAddr;	
					sheet.ch4[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.ch4[i].model,argv[3]);
					rt_kprintf("%s ch4 reconfig %d\n",sign,i);
					rt_kprintf("%s ch4 OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==CH4_485_NUM){//û�����ù�
			for(int j=0;j<CH4_485_NUM;j++){
					if(sheet.ch4[j].workFlag!=RT_TRUE){
							sheet.ch4[j].workFlag=RT_TRUE;//��
							sheet.ch4[j].slaveAddr=slaveAddr;	
							sheet.ch4[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.ch4[j].model,argv[3]);
							rt_strcpy(sheet.ch4[j].ID,argv[2]);
							rt_kprintf("%s ch4 config %d\n",sign,j);
						  rt_kprintf("%s ch4 OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//co������
static int coConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.coColTime=atoi32(argv[6],10);
	for( i=0;i<CO_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.co[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.co[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del co\n",sign);
						  return 1;
					}
					else{
							sheet.co[i].workFlag=RT_TRUE;//��
					}
					sheet.co[i].slaveAddr=slaveAddr;	
					sheet.co[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.co[i].model,argv[3]);
					rt_kprintf("%s co reconfig %d\n",sign,i);
					rt_kprintf("%s co OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==CO_485_NUM){//û�����ù�
			for(int j=0;j<CO_485_NUM;j++){
					if(sheet.co[j].workFlag!=RT_TRUE){
							sheet.co[j].workFlag=RT_TRUE;//��
							sheet.co[j].slaveAddr=slaveAddr;	
							sheet.co[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.co[j].model,argv[3]);
							rt_strcpy(sheet.co[j].ID,argv[2]);
							rt_kprintf("%s co config %d\n",sign,j);
						  rt_kprintf("%s co OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//h2s������
static int h2sConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.h2sColTime=atoi32(argv[6],10);
	for( i=0;i<H2S_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.h2s[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.h2s[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del h2s\n",sign);
						  return 1;
					}
					else{
							sheet.h2s[i].workFlag=RT_TRUE;//��
					}
					sheet.h2s[i].slaveAddr=slaveAddr;	
					sheet.h2s[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.h2s[i].model,argv[3]);
					rt_kprintf("%s h2s reconfig %d\n",sign,i);
					rt_kprintf("%s h2s OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==H2S_485_NUM){//û�����ù�
			for(int j=0;j<H2S_485_NUM;j++){
					if(sheet.h2s[j].workFlag!=RT_TRUE){
							sheet.h2s[j].workFlag=RT_TRUE;//��
							sheet.h2s[j].slaveAddr=slaveAddr;	
							sheet.h2s[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.h2s[j].model,argv[3]);
							rt_strcpy(sheet.h2s[j].ID,argv[2]);
							rt_kprintf("%s h2s config %d\n",sign,j);
						  rt_kprintf("%s h2s OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//o2������
static int o2Conf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.cirCulaColTime=atoi32(argv[6],10);
	sheet.o2ColTime=atoi32(argv[6],10);
	for( i=0;i<O2_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.o2[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.o2[i].workFlag=RT_FALSE;//�ر�
						  rt_kprintf("%s del o2\n",sign);
						  return 1;
					}
					else{
							sheet.o2[i].workFlag=RT_TRUE;//��
					}
					sheet.o2[i].slaveAddr=slaveAddr;	
					sheet.o2[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.o2[i].model,argv[3]);
					rt_kprintf("%s o2 reconfig %d\n",sign,i);
					rt_kprintf("%s o2 OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==O2_485_NUM){//û�����ù�
			for(int j=0;j<O2_485_NUM;j++){
					if(sheet.o2[j].workFlag!=RT_TRUE){
							sheet.o2[j].workFlag=RT_TRUE;//��
							sheet.o2[j].slaveAddr=slaveAddr;	
							sheet.o2[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.o2[j].model,argv[3]);
							rt_strcpy(sheet.o2[j].ID,argv[2]);
							rt_kprintf("%s o2 config %d\n",sign,j);
						  rt_kprintf("%s o2 OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
#endif
//ˮλ������
static int waterDepthConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.waterDepthColTime=atoi32(argv[6],10);
	for( i=0;i<WATERDEPTH_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.waterDepth[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.waterDepth[i].workFlag=RT_FALSE;//�ر�
							rt_kprintf("%s del waterdepth\n",sign);
						  return 1;
					}
					else{
							sheet.waterDepth[i].workFlag=RT_TRUE;//��
					}
					sheet.waterDepth[i].slaveAddr=slaveAddr;	
					sheet.waterDepth[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.waterDepth[i].model,argv[3]);
					rt_kprintf("%s waterDepth reconfig %d\n",sign,i);
					rt_kprintf("%s waterDepth OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==WATERDEPTH_485_NUM){//û�����ù�
			for(int j=0;j<WATERDEPTH_485_NUM;j++){
					if(sheet.waterDepth[j].workFlag!=RT_TRUE){
							sheet.waterDepth[j].workFlag=RT_TRUE;//��
							sheet.waterDepth[j].slaveAddr=slaveAddr;	
							sheet.waterDepth[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.waterDepth[j].model,argv[3]);
							rt_strcpy(sheet.waterDepth[j].ID,argv[2]);
							rt_kprintf("%s waterDepth config %d\n",sign,j);
						  rt_kprintf("%s waterDepth OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//��ʪ�ȵ�����
static int tempHumConf(int uartnum,char *argv[])
{
	int i=0;
	int ret=0;
	int slaveAddr=atoi32(argv[5],10);
	sheet.tempHumColTime=atoi32(argv[6],10);
	for( i=0;i<TEMPHUM_485_NUM;i++){//�˶���û�����ù�
			if(rt_strcmp(sheet.tempHum[i].ID,argv[2])==0){//���ù�
					if((slaveAddr==0)||(slaveAddr==255)){//�ر�
							sheet.tempHum[i].workFlag=RT_FALSE;//�ر�
							rt_kprintf("%s del temp humi\n",sign);
						  return 1;
					}
					else{
							sheet.tempHum[i].workFlag=RT_TRUE;//��
					}
					sheet.tempHum[i].slaveAddr=slaveAddr;	
					sheet.tempHum[i].useUartNum=UartNum[uartnum];
					rt_strcpy(sheet.tempHum[i].model,argv[3]);
					rt_kprintf("%s tempHum reconfig %d\n",sign,i);
					rt_kprintf("%s tempHum OK\n",sign);
					ret =1;
					break;
			}
	}
	if((slaveAddr==0)||(slaveAddr==255)){
			return 0;
	}
	if(i==TEMPHUM_485_NUM){//û�����ù�
			for(int j=0;j<TEMPHUM_485_NUM;j++){
					if(sheet.tempHum[j].workFlag!=RT_TRUE){
							sheet.tempHum[j].workFlag=RT_TRUE;//��
							sheet.tempHum[j].slaveAddr=slaveAddr;	
							sheet.tempHum[j].useUartNum=UartNum[uartnum];
							rt_strcpy(sheet.tempHum[j].model,argv[3]);
							rt_strcpy(sheet.tempHum[j].ID,argv[2]);
							rt_kprintf("%s tempHum config %d\n",sign,j);
						  rt_kprintf("%s tempHum OK\n",sign);
							ret =1;
							break;
					}
			}
	}
	return ret;
}
//modbus�豸������
static int modbusConf(int modbusnum,int uartnum,char *argv[])
{
	  int ret=0;
	  //int slaveAddr=atoi32(argv[5],10);//��ȡ�豸��ַ ǰ���Ѿ��˶Թ�
//		rt_kprintf("conf:%d %d\n",modbusnum,uartnum);
		switch(modbusnum)
		{
			case CIRCULA:
				ret =circulaConf(uartnum,argv);
			break;
			case PARTDISCHAG:
				ret=partDischagConf(uartnum,argv);
			break;
			case PRESSSETTL:
				ret=pressSettlConf(uartnum,argv);
			break;
			case THREEAXIS:
				ret=threeAxisConf(uartnum,argv);
			break;
#ifdef USE_4GAS
			case CH4:
				ret=ch4Conf(uartnum,argv);
			break;
			case O2:
				ret=o2Conf(uartnum,argv);
			break;
			case H2S:
				ret=h2sConf(uartnum,argv);
      break;
      case CO:
				ret=coConf(uartnum,argv);
      break;
#endif
      case TEMPHUM:
				ret=tempHumConf(uartnum,argv);
      break;
      case WATERDEPTH:
				ret=waterDepthConf(uartnum,argv);
			break;
			case CRACKMETER:
				ret=crackMeterConf(uartnum,argv);
			break;
			case COVER:
				ret=coverConf(uartnum,argv);
			default:
			break;
		}
		return ret;
}
//����ǰ���ID��û���ظ��� �еĻ�ɾ���ظ���ID
//int modbusConfIDCheck(char *inputID)
//{
//		for(int i=0;i<MODBUS_NUM;i++){
//			switch(i)
//			{
//				case CIRCULA:
//					for(int j=0;j<CIRCULA_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.cirCula[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.cirCula[j].ID,inputID)==0){
//											rt_kprintf("del cirCula same ID\n");
//											sheet.cirCula[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				case PARTDISCHAG:
//					for(int j=0;j<PARTDISCHAG_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.partDischag[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.partDischag[j].ID,inputID)==0){
//											rt_kprintf("del partDischag same ID\n");
//											sheet.partDischag[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				case PRESSSETTL:
//					for(int j=0;j<PRESSSETTL_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.pressSetl[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.pressSetl[j].ID,inputID)==0){
//											rt_kprintf("del pressSetl same ID\n");
//											sheet.pressSetl[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				case THREEAXIS:
//					for(int j=0;j<THREEAXIS_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.threeAxiss[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.threeAxiss[j].ID,inputID)==0){
//											rt_kprintf("del threeAxiss same ID\n");
//											sheet.threeAxiss[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//	#ifdef 	 USE_4GAS 	
//				case CH4:
////					for(int j=0;j<CH4_485_NUM;j++){//�˶���û�����ù�
////							if(sheet.ch4[j].workFlag==RT_TRUE){
////									if(rt_strcmp(sheet.ch4[j].ID,inputID)==0){
////											rt_kprintf("del ch4 same ID\n");
////											sheet.ch4[j].workFlag=RT_FALSE;
////										  return 1;
////									}
////								}
////					}
//				break;
//				case O2:
////					for(int j=0;j<O2_485_NUM;j++){//�˶���û�����ù�
////							if(sheet.o2[j].workFlag==RT_TRUE){
////									if(rt_strcmp(sheet.o2[j].ID,inputID)==0){
////											rt_kprintf("del o2 same ID\n");
////											sheet.o2[j].workFlag=RT_FALSE;
////										  return 1;
////									}
////							}
////					}
//				break;
//				case H2S:
////					for(int j=0;j<H2S_485_NUM;j++){//�˶���û�����ù�
////							if(sheet.h2s[j].workFlag==RT_TRUE){
////									if(rt_strcmp(sheet.h2s[j].ID,inputID)==0){
////											rt_kprintf("del h2s same ID\n");
////											sheet.h2s[j].workFlag=RT_FALSE;
////										  return 1;
////									}
////							}
////					}
//				break;
//				case CO:
////					for(int j=0;j<CO_485_NUM;j++){//�˶���û�����ù�
////							if(sheet.co[j].workFlag==RT_TRUE){
////									if(rt_strcmp(sheet.co[j].ID,inputID)==0){
////											rt_kprintf("del co same ID\n");
////											sheet.co[j].workFlag=RT_FALSE;
////										  return 1;
////									}
////							}
////					}
//				break;
//	#endif
//				case TEMPHUM:
//					for(int j=0;j<TEMPHUM_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.tempHum[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.tempHum[j].ID,inputID)==0){
//											rt_kprintf("del TEMPHUM same ID\n");
//											sheet.tempHum[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				case WATERDEPTH:
//					for(int j=0;j<WATERDEPTH_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.waterDepth[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.waterDepth[j].ID,inputID)==0){
//											rt_kprintf("del waterDepth same ID\n");
//											sheet.waterDepth[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				case CRACKMETER:
//					for(int j=0;j<CRACKMETER_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.crackMeter[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.crackMeter[j].ID,inputID)==0){
//											rt_kprintf("del crackMeter same ID\n");
//											sheet.crackMeter[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				case COVER:
//					for(int j=0;j<COVER_485_NUM;j++){//�˶���û�����ù�
//							if(sheet.cover[j].workFlag==RT_TRUE){
//									if(rt_strcmp(sheet.cover[j].ID,inputID)==0){
//											rt_kprintf("del cover same ID\n");
//											sheet.cover[j].workFlag=RT_FALSE;
//										  return 1;
//									}
//							}
//					}
//				break;
//				default:
//				break;
//			}
//		}
//		
//		
//		
//		return 0;
//}
//��ͬ����Ĵ���������ҵ�ͬһ��port�±�
//ÿ�ִ��������һ������Ĳɼ�ʱ��Ϊ���ղɼ�ʱ��
//modbus   �ַ� port2 2 60
//ʹ��ǰ��������������upKeepStateTask�в����Լ��ص�������ʼ������ʹ��
//�˶����� �˶Ե�ַ �˶�port����д��
//modbus+�豸����(������)+ID+model+�˿�(port1-port4)+�豸��ַ(0/255-�ر��豸)+�ɼ����(��)
static void modbus(int argc, char *argv[])
{
	  extern void timeStop(upDataTimEnum num);
	  extern void timeInit(upDataTimEnum num,int value,int firstCnt);
	  int i,j;
		if ((argc != 7)&&(argc != 2))
		{
				rt_kprintf("%sERR input argc\n",sign);
				goto ERR;
		}
		if(devIDOKCheck(argv[2])!=true){
				rt_kprintf("%sERR input the same ID\n",sign);
			  return;
		}
		if(argc==2){
				if(0==rt_strcmp((char *)"list", argv[1])){
						printModbusDevList();
						return;
				}
		}
		else{
				uint8_t slaveaddr=atoi16(argv[5],10);
				int setTime =atoi16(argv[6],10);
				if(setTime<60){
						rt_kprintf("%serr:argv[6] �ɼ�ʱ��>60 now is%d\n",sign,setTime);
						goto ERR;
				}
				if(slaveaddr>255){
						rt_kprintf("%serr:argv[5] between 0 and 255 %d\n",sign,argv[5]);
						goto ERR;
				}
				for(i=0;i<MODBUS_NUM;i++){
						if(0==rt_strcmp((char *)modbusName[i], argv[1])){
								for(j=0;j<UART_NUM;j++){
										if(0==rt_strcmp((char *)UartName[j], argv[4])){//���� �Ϸ�
												break;
										}
								}
								break;
						}
				}
				if(i>=MODBUS_NUM){
						rt_kprintf("%serr:argv[1]\n",sign);
						for(int j=0;j<MODBUS_NUM;j++)
								rt_kprintf("%s ",modbusName[j]);
						rt_kprintf("\n ");
						goto ERR;
				}
				if(j>=UART_NUM){
						rt_kprintf("%serr:argv[2]\n",sign);
						for(int j=0;j<UART_NUM;j++)
								rt_kprintf("%s ",UartName[j]);
						rt_kprintf("\n ");
						goto ERR;
				}
				if(1==modbusConf(i,j,argv)){//����modbus����������
						return;//��ȷ����
				}
				else{
						rt_kprintf("%smodbus exit delete first\n",sign);
				}
		}
		ERR:
		rt_kprintf("%sfor example:modbus+�豸����(������)+ID+model+�˿�(port1-port4)+�豸��ַ(0/255-�ر��豸)+�ɼ����(��)\n",sign);
		rt_kprintf("%sNOTE:�����ڶԲ������н���,����Ҫ����\n",sign);
		rt_kprintf("%smodbus list\n",sign);
}
//FINSH_FUNCTION_EXPORT(modbus, offline finsh);//FINSH_FUNCTION_EXPORT_CMD
MSH_CMD_EXPORT(modbus,port slaveaddr config);//FINSH_FUNCTION_EXPORT_CMD


#if 1
//���ID���Ƿ��ظ�  true -���ظ�  false-�ظ�
//�������� Ϊ�˱�ֵID���õ�Ψһ��
bool  devIDOKCheck(char *inputID)
{
		for(int i=0;i<MODBUS_NUM;i++){
			switch(i)
			{
				case CIRCULA:
					for(int j=0;j<CIRCULA_485_NUM;j++){//�˶���û�����ù�
							if(sheet.cirCula[j].workFlag==RT_TRUE){
									if(strcmp(inputID,sheet.cirCula[j].ID)==0)
										return false;
							}
					}
				break;
				case PARTDISCHAG:
					for(int j=0;j<PARTDISCHAG_485_NUM;j++){//�˶���û�����ù�
							if(sheet.partDischag[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.partDischag[j].ID)==0)
										return false;
							}
					}
				break;
				case PRESSSETTL:
					for(int j=0;j<PRESSSETTL_485_NUM;j++){//�˶���û�����ù�
							if(sheet.pressSetl[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.pressSetl[j].ID)==0)
										return false;
							}
					}
				break;
				case THREEAXIS:
					for(int j=0;j<THREEAXIS_485_NUM;j++){//�˶���û�����ù�
							if(sheet.threeAxiss[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.threeAxiss[j].ID)==0)
										return false;
							}
					}
				break;
#ifdef USE_4GAS
				case CH4:
					for(int j=0;j<CH4_485_NUM;j++){//�˶���û�����ù�
							if(sheet.ch4[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.ch4[j].ID)==0)
										return false;
							}
					}
				break;
				case O2:
					for(int j=0;j<O2_485_NUM;j++){//�˶���û�����ù�
							if(sheet.o2[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.o2[j].ID)==0)
										return false;
							}
					}
				break;
				case H2S:
					for(int j=0;j<H2S_485_NUM;j++){//�˶���û�����ù�
							if(sheet.h2s[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.h2s[j].ID)==0)
										return false;
							}
					}
				break;
				case CO:
					for(int j=0;j<CO_485_NUM;j++){//�˶���û�����ù�
							if(sheet.co[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.co[j].ID)==0)
										return false;
							}
					}
				break;
#endif
				case TEMPHUM:
					for(int j=0;j<TEMPHUM_485_NUM;j++){//�˶���û�����ù�
							if(sheet.tempHum[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.tempHum[j].ID)==0)
										return false;
							}
					}
				break;
				case WATERDEPTH:
					for(int j=0;j<WATERDEPTH_485_NUM;j++){//�˶���û�����ù�
							if(sheet.waterDepth[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.waterDepth[j].ID)==0)
										return false;
							}
					}
				break;
				case CRACKMETER:
					for(int j=0;j<CRACKMETER_485_NUM;j++){//�˶���û�����ù�
							if(sheet.crackMeter[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.crackMeter[j].ID)==0)
										return false;
							}
					}
				break;
				case COVER:
					for(int j=0;j<COVER_485_NUM;j++){//�˶���û�����ù�
							if(sheet.cover[j].workFlag==RT_TRUE){
								if(strcmp(inputID,sheet.cover[j].ID)==0)
										return false;
							}
					}
				break;
				default:
				break;
			}	
		}

		int i;
		bool  add=true;
////////////////////////////////////////////////ģ�����ݴ��////////////////////////////////////////////////////
#ifndef     ANA_MASK
		for(i=0;i<ANALOG_NUM;i++){
			  add=true;
				if(i>=1){
						for(j=0;j<i;j++){
								if(rt_strcmp(sheet.analog[i].ID,sheet.analog[j].ID)==0){
										add=false;//�ҵ����ظ��� �����˴�i�ļ���
									  break;
								}
						}
				}
				if(add==false){
					  continue;//�����˴�ѭ�� ִ����һ��
				}
				if(sheet.analog[i].workFlag==RT_TRUE){
						nodeobj = cJSON_CreateObject();
						cJSON_AddItemToArray(Array, nodeobj);
						cJSON_AddItemToObject(nodeobj,"model",cJSON_CreateString(sheet.analog[i].model));
						cJSON_AddItemToObject(nodeobj,"name",cJSON_CreateString(sheet.analog[i].name));
						cJSON_AddItemToObject(nodeobj,"deviceId",cJSON_CreateString(sheet.analog[i].ID));
				}
		 }
#endif
////////////////////////////////////////////////����������////////////////////////////////////////////////////
		 for(i=0;i<DI_NUM;i++){
				if(packFlash.diginput[i].workFlag==RT_TRUE){
						if(strcmp(inputID,packFlash.diginput[i].devID)==0)
								return false;
	
				}
		 }
////////////////////////////////////////////////����������////////////////////////////////////////////////////
		 for(i=0;i<DO_NUM;i++){
				if(packFlash.digoutput[i].workFlag==RT_TRUE){
						if(strcmp(inputID,packFlash.digoutput[i].devID)==0)
								return false;
				}
		 }
////////////////////////////////////////////////���3V3���////////////////////////////////////////////////////
		 for(i=0;i<V33O_NUM;i++){
				if(packFlash.v33output[i].workFlag==RT_TRUE){
						if(strcmp(inputID,packFlash.v33output[i].devID)==0)
								return false;
				}
		 }
////////////////////////////////////////////////���5Vע����////////////////////////////////////////////////////
		 for(i=0;i<V5O_NUM;i++){
				if(packFlash.v5output[i].workFlag==RT_TRUE){
						if(strcmp(inputID,packFlash.v5output[i].devID)==0)
								return false;
				}
		 }
////////////////////////////////////////////////���12Vע����////////////////////////////////////////////////////
		 for(i=0;i<V12O_NUM;i++){
				if(packFlash.v12output[i].workFlag==RT_TRUE){
						if(strcmp(inputID,packFlash.v12output[i].devID)==0)
								return false;
				}
		 }
		 return true;
}
#endif