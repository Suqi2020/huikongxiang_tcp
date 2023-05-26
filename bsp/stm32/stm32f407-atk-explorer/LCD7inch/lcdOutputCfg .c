/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include "7inchRegist.h"
const static char sign[]="[LCDOutputCfg]";

static digitStru outputLCD={0};

//������������ֵ�outputLCD��
void lcdCopyOutputName(uint8_t *rec)
{
	for(int i=0;i<NAME_LEN;i++){
		outputLCD.name[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				outputLCD.name[i]=0;
				break;
		}
	}
}


//���������ID��outputLCD��
void lcdCopyOutputID(uint8_t *rec)
{
	for(int i=0;i<DEVID_LEN;i++){
		outputLCD.devID[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				outputLCD.devID[i]=0;
				break;
		}
	}
	if(devIDOKCheck(outputLCD.devID)!=true){//�˶�ID
			LCDDispSameID(DISP_OUTPUT_SAME_ID_MSG_ADDR);
		  rt_kprintf("%sERR:same ID\n",sign);
	}
	else 
		  LCDRstDispSameID(DISP_OUTPUT_SAME_ID_MSG_ADDR);
}
//���������type��outputLCD��
void lcdCopyOutputModel(uint8_t *rec)
{
	for(int i=0;i<MODEL_LEN;i++){
		outputLCD.model[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				outputLCD.model[i]=0;
				break;
		}
	}
}
//���������port��outputLCD��
void lcdCopyOutputPort(uint8_t *rec)
{

		outputLCD.port=rec[8];
}




uint8_t su8OutNameCfgIndex=0;//����˵�������
extern char outName[OUTNAME_NUM][INOUTNAME_LEN];

//������ö�ȡinterface�ӿ���һ��
void  dispoutConfigNext()
{

		su8OutNameCfgIndex++;
	  if(su8OutNameCfgIndex>=OUTNAME_NUM)
				su8OutNameCfgIndex=0;
}

//������ö�ȡinterface�ӿ���һ��
void  dispoutConfigLast()
{
		if(su8OutNameCfgIndex==0)
				su8OutNameCfgIndex=OUTNAME_NUM;
		su8OutNameCfgIndex--;
}
void  dispoutputNameInterf()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
		int Len=strlen(outName[su8OutNameCfgIndex]);
		for(int i=0;i<Len;i++){
				buf[i]=outName[su8OutNameCfgIndex][i];
		}
		int j=0;
		while((Len+j)<INOUTNAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_OUTPUT_INTERFACE_ADDR,buf,NAME_LEN);
		
		//��ʾ����ӿ� {"DO","V3O","V5O","V12O"}�е�һ��
}


//���������ȷ����������
void  lcdOutputConfig()
{
	  int port=outputLCD.port;
		if(devIDOKCheck(outputLCD.devID)!=true){//�˶�ID
				LCDDispSameID(DISP_OUTPUT_SAME_ID_MSG_ADDR);
				rt_kprintf("%sERR:same ID\n",sign);
		}
		switch(su8OutNameCfgIndex)
		{
			case 0:
				if((port<=DO_NUM)&&(port>0)){//���
						packFlash.digoutput[port-1].workFlag=RT_TRUE;
						rt_strcpy(packFlash.digoutput[port-1].name, outputLCD.name);
						rt_strcpy(packFlash.digoutput[port-1].devID,outputLCD.devID);
						rt_strcpy(packFlash.digoutput[port-1].model,outputLCD.model);
						packFlash.digoutput[port-1].port=port;
						rt_kprintf("%s add digoutput chanl %d\n",sign,port);
						rt_kprintf("%s digoutput OK\n",sign);
				}
				break;
			case 1:
				if((port<=V33O_NUM)&&(port>0)){//���
						packFlash.v33output[port-1].workFlag=RT_TRUE;
						rt_strcpy(packFlash.v33output[port-1].name, outputLCD.name);
						rt_strcpy(packFlash.v33output[port-1].devID,outputLCD.devID);
						rt_strcpy(packFlash.v33output[port-1].model,outputLCD.model);
						packFlash.v33output[port-1].port=port;
						rt_kprintf("%s add v33output chanl %d\n",sign,port);
						rt_kprintf("%s digoutput OK\n",sign);
				}
				break;
			case 2:
				if((port<=V5O_NUM)&&(port>0)){//���
						packFlash.v5output[port-1].workFlag=RT_TRUE;
						rt_strcpy(packFlash.v5output[port-1].name, outputLCD.name);
						rt_strcpy(packFlash.v5output[port-1].devID,outputLCD.devID);
						rt_strcpy(packFlash.v5output[port-1].model,outputLCD.model);
						packFlash.v5output[port-1].port=port;
						rt_kprintf("%s add v5output chanl %d\n",sign,port);
						rt_kprintf("%s digoutput OK\n",sign);
				}
				break;
			case 3:
				if((port<=V12O_NUM)&&(port>0)){//���
						packFlash.v12output[port-1].workFlag=RT_TRUE;
						rt_strcpy(packFlash.v12output[port-1].name, outputLCD.name);
						rt_strcpy(packFlash.v12output[port-1].devID,outputLCD.devID);
						rt_strcpy(packFlash.v12output[port-1].model,outputLCD.model);
						packFlash.v12output[port-1].port=port;
						rt_kprintf("%s add v12output chanl %d\n",sign,port);
						rt_kprintf("%s digoutput OK\n",sign);
				}
				break;
		}
}




uint8_t su8OutNameReadIndex=0;//��ʼָ�� DO

uint8_t  su8OutputTotalNum[OUTNAME_NUM]={0};//��ʾ��ҳ��
uint8_t  su8OutputTheNum[OUTNAME_NUM]={0};  //��ʾ�ڼ�ҳ
uint8_t  su8WorkOutput[OUTNAME_NUM][DI_NUM]={0};//��¼�������ù��ĽǱ�  û�����ù��Ǽ�Ϊ0





uint8_t  su8OutputSubNum=0;


//ÿ�ν�ȥ�����ɾ��ʱ����ô˺���
void getOutputTotalNum()
{
	  su8OutputSubNum=0;
	  for(int p=0;p<OUTNAME_NUM;p++)
				su8OutputTotalNum[p]=0;
		for(int i=0;i<DO_NUM;i++){
				if(packFlash.digoutput[i].workFlag==RT_TRUE){
						su8WorkOutput[0][su8OutputTotalNum[0]]=i;
					  su8OutputTotalNum[0]++;
						rt_kprintf("digoutputTotalNum:%d  %d\n",su8OutputTotalNum[0],i);
				}
		}

		for(int i=0;i<V33O_NUM;i++){
				if(packFlash.v33output[i].workFlag==RT_TRUE){
						su8WorkOutput[1][su8OutputTotalNum[1]]=i;
					  su8OutputTotalNum[1]++;
						rt_kprintf("v33outputTotalNum:%d  %d\n",su8OutputTotalNum[1],i);
				}
		}
		for(int i=0;i<V5O_NUM;i++){
				if(packFlash.v5output[i].workFlag==RT_TRUE){
						su8WorkOutput[2][su8OutputTotalNum[2]]=i;
					  su8OutputTotalNum[2]++;
						rt_kprintf("v5outputTotalNum:%d  %d\n",su8OutputTotalNum[2],i);
				}
		}

		for(int i=0;i<V12O_NUM;i++){
				if(packFlash.v12output[i].workFlag==RT_TRUE){
						su8WorkOutput[3][su8OutputTotalNum[3]]=i;
					  su8OutputTotalNum[3]++;
						rt_kprintf("v12outputTotalNum:%d  %d\n",su8OutputTotalNum[3],i);
				}
		}
		for(int i=0;i<OUTNAME_NUM;i++){
				for(int j=su8OutputTotalNum[i];j<DI_NUM-j;j++){////û�洢�ı�ǵľ���0
						su8WorkOutput[i][su8OutputTotalNum[i]+j]=0;
				}
		}
		
		
		for(int i=0;i<OUTNAME_NUM;i++){
				if(su8OutputTotalNum[i]>0){
						su8OutputTheNum[i]=1;
				}
				else{
						su8OutputTheNum[i]=0;
				}
		}
}



//��ʾ�ӿڵĽ��溯��   ��������ȥ ��һҳ ��һҳ����
void  dispoutputReadInterf()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
		int Len=strlen(outName[su8OutNameReadIndex]);
		for(int i=0;i<Len;i++){
				buf[i]=outName[su8OutNameReadIndex][i];
		}
		int j=0;
		while((Len+j)<INOUTNAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_OUTPUT_READ_INTERFACE_ADDR,buf,NAME_LEN);
		LCDWtite(DISP_OUTPUT_READ_INTERFACE_P_ADDR,buf,NAME_LEN);
		
		//��ʾ����ӿ� {"DO","V3O","V5O","V12O"}�е�һ��
}
//������ö�ȡinterface�ӿ���һ��
void  dispoutpReadInterfNext()
{
	  su8OutputSubNum=0;
		su8OutNameReadIndex++;
	  if(su8OutNameReadIndex>=OUTNAME_NUM)
				su8OutNameReadIndex=0;
}

//������ö�ȡinterface�ӿ���һ��
void  dispoutpReadInterfLast()
{
	  su8OutputSubNum=0;
		if(su8OutNameReadIndex==0)
				su8OutNameReadIndex=OUTNAME_NUM;
		su8OutNameReadIndex--;
}




//������ö�ȡ��ѡ����һ��
void  dispoutpReadLast()
{
		if(su8OutputSubNum==0)
				su8OutputSubNum=su8OutputTotalNum[su8OutNameReadIndex];
		su8OutputSubNum--;
		if(su8OutputTotalNum[su8OutNameReadIndex]==0)
				return;

		if(su8OutputTheNum[su8OutNameReadIndex]==1)
				su8OutputTheNum[su8OutNameReadIndex]=su8OutputTotalNum[su8OutNameReadIndex];
		else
				su8OutputTheNum[su8OutNameReadIndex]--;
}

//������ö�ȡ��ѡ����һ��
void  dispoutpReadNext()
{
		su8OutputSubNum++;
		if(su8OutputSubNum>=su8OutputTotalNum[su8OutNameReadIndex])
				su8OutputSubNum=0;
		
		if(su8OutputTotalNum[su8OutNameReadIndex]==0)
				return;
		
		su8OutputTheNum[su8OutNameReadIndex]++;
		if(su8OutputTheNum[su8OutNameReadIndex]>su8OutputTotalNum[su8OutNameReadIndex])
				su8OutputTheNum[su8OutNameReadIndex]=1;
}

digitStru  *outputp[DO_NUM]={0};//��digoutput v33output v5output v12output�����ֵ���

void  delOneOutput()
{
		uint8_t p=su8WorkOutput[su8OutNameReadIndex][su8OutputSubNum];
		if(outputp[p]!=NULL){
			outputp[p]->workFlag=RT_FALSE;
						rt_kprintf("del one:%s %s %s\n",outputp[p]->name,outputp[p]->devID);
		}
}

//������ʾ�����ݸ�LCD
//����ֵ����outName[OUTNAME_NUM][INOUTNAME_LEN]={"DO","V3O","V5O","V12O"};
//          ʵ��������ȷ�� ���и��� ��Ҫ���Ĵ˺���
void  dispOutputRead()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
	  
		switch(su8OutNameReadIndex)
		{
			case 0://DO��ʾ
				for(int i=0;i<DO_NUM;i++){
						outputp[i]=&packFlash.digoutput[i];
				}
				break;
			case 1://V3O��ʾ
				for(int i=0;i<V33O_NUM;i++){
						outputp[i]=&packFlash.v33output[i];
				}
				break;
			case 2://V5O��ʾ
				for(int i=0;i<V5O_NUM;i++){
						outputp[i]=&packFlash.v5output[i];
				}
				break;
			case 3://V12O��ʾ
				for(int i=0;i<V12O_NUM;i++){
						outputp[i]=&packFlash.v12output[i];
				}
				break;
			default:
				rt_kprintf("%s input outNameIndex err\n",sign);
				break;
		}
		
		

	//if(packFlash.diginput[p].workFlag==RT_TRUE){

		if(su8OutputTotalNum[su8OutNameReadIndex]==0){
				buf[0]=0xff;
				buf[1]=0xff;
				//��ʾname
				LCDWtite(DISP_OUTPUT_READ_NAME_ADDR,buf,2);
				//��ʾID
				LCDWtite(DISP_OUTPUT_READ_ID_ADDR,buf,2);//7������ʾ18
				//��ʾmodel
				LCDWtite(DISP_OUTPUT_READ_TYPE_ADDR,buf,2);
				//��ʾPORT
				LCDWtite(DISP_OUTPUT_READ_PORT_ADDR,buf,2);
				//��ʾ�ܹ�ҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_OUTPUT_READ_TOTALNUM_ADDR,buf,2);
				//��ʾ��ǰҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_OUTPUT_READ_THENUM_ADDR,buf,2);

				return;
		}
	  //��ʾ������
		uint8_t p=su8WorkOutput[su8OutNameReadIndex][su8OutputSubNum];
	//if(packFlash.diginput[p].workFlag==RT_TRUE){
		int Len=strlen(outputp[p]->name);
		for(int i=0;i<Len;i++){
				buf[i]=outputp[p]->name[i];
		}
		int j=0;
		while((Len+j)<NAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_OUTPUT_READ_NAME_ADDR,buf,NAME_LEN);
		
		//��ʾ����ӿ� {"DO","V3O","V5O","V12O"}�е�һ��
		
		//��ʾID
		 Len=strlen(outputp[p]->devID);
			for(int i=0;i<Len;i++){
					buf[i]=outputp[p]->devID[i];
			}
		 j=0;
		while((Len+j)<DEVID_LEN+2){
				buf[Len+j]=0xff;
				j++;
				if(j>=2)
					break;
		}
		LCDWtite(DISP_OUTPUT_READ_ID_ADDR,buf,DEVID_LEN+2);//7������ʾ18
		//��ʾmodel
		Len=strlen(outputp[p]->model);
		for(int i=0;i<Len;i++){
				buf[i]=outputp[p]->model[i];
		}
		 j=0;
		while((Len+j)<MODEL_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_OUTPUT_READ_TYPE_ADDR,buf,MODEL_LEN);
		//��ʾPORT
		buf[0]=0;
		buf[1]=outputp[p]->port;
		LCDWtite(DISP_OUTPUT_READ_PORT_ADDR,buf,2);

		//��ʾ�ܹ�ҳ
		buf[0]=0;
		buf[1]=su8OutputTotalNum[su8OutNameReadIndex];
		LCDWtite(DISP_OUTPUT_READ_TOTALNUM_ADDR,buf,2);
		rt_kprintf("%s %s total %d\n",sign,outName[su8OutNameReadIndex],su8OutputTotalNum[su8OutNameReadIndex]);
		//��ʾ��ǰҳ
		buf[0]=0;
		buf[1]=su8OutputTheNum[su8OutNameReadIndex];
		LCDWtite(DISP_OUTPUT_READ_THENUM_ADDR,buf,2);
			
		
		
		rt_free(buf);
		buf=RT_NULL;
}



