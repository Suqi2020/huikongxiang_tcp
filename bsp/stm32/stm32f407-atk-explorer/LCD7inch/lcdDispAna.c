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
#ifndef     ANA_MASK
const static char sign[]="[LCDDispAna]";



analogStru  anaInput={0};








//���������ID��AnaInputLCD��
void lcdCopyAnaID(uint8_t *rec)
{
	for(int i=0;i<DEVID_LEN;i++){
		anaInput.ID[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				anaInput.ID[i]=0;
				break;
		}
	}
}
//���������type��AnaInputLCD��
void lcdCopyAnaModel(uint8_t *rec)
{
	for(int i=0;i<MODEL_LEN;i++){
		anaInput.model[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				anaInput.model[i]=0;
				break;
		}
	}
}
//���������port��AnadigInputLCD��
void lcdCopyAnaPort(uint8_t *rec)
{

		anaInput.port=rec[8];
}

//���������time��AnaInput��
void lcdCopyAnaTime(uint8_t *rec)
{

		anaInput.colTime=(uint32_t)(rec[7]<<24)+(rec[8]<<16)+(rec[9]<<8)+rec[10];
}

//��ȷ���������������
void  lcdAnaConfig()
{
		int port=anaInput.port;
		if((port<=ANALOG_NUM)&&(port>0)){//���
				sheet.analog[port-1].workFlag=RT_TRUE;
			  rt_strcpy(sheet.analog[port-1].name, analogName[0]);
				rt_strcpy(sheet.analog[port-1].ID,anaInput.ID);
				rt_strcpy(sheet.analog[port-1].model,anaInput.model);
				sheet.analog[port-1].port=port;
			  sheet.analog[port-1].subName =anaInput.subName;
			  sheet.analog[port-1].colTime=anaInput.colTime;
				rt_kprintf("%s add ana chanl %d\n",sign,port);
        rt_kprintf("%s ana OK\n",sign);
		}
}
uint8_t   su8AnaChoosNum=0;


void dispName()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
		int Len=strlen(analogName[0]);
		for(int i=0;i<Len;i++){
				buf[i]=analogName[0][i];
		}
		int j=0;
		while((Len+j)<NAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_ANA_NAME_ADDR,buf,NAME_LEN);
		
		rt_free(buf);
		buf=RT_NULL;

}
void dispSubName()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
		int Len=strlen(anaSubName1Val[su8AnaChoosNum]);
		for(int i=0;i<Len;i++){
				buf[i]=anaSubName1Val[su8AnaChoosNum][i];
		}
		int j=0;
		while((Len+j)<NAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_ANA_SUBNAME_ADDR,buf,NAME_LEN);
		
		rt_free(buf);
		buf=RT_NULL;
}

void nextSubName()
{
		su8AnaChoosNum++;
		if(su8AnaChoosNum>=ANA_SUBNAME_LEN)
				su8AnaChoosNum=0;
}
void lastSubName()
{
		if(su8AnaChoosNum==0)
				su8AnaChoosNum=ANA_SUBNAME_LEN;
		su8AnaChoosNum--;
		
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t  su8AnaTotalNum=0;//��ʾ��ҳ��
uint8_t  su8AnaTheNum=0;  //��ʾ�ڼ�ҳ
uint8_t  su8AnaWork[ANALOG_NUM]={0};//��¼�������ù��ĽǱ�  û�����ù��Ǽ�Ϊ0



//						for(int j=0;j<ANALOG_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
//										if((rt_strcmp(sheet.analog[j].ID,argv[2])==0)&&(subName==sheet.analog[j].subName )){
//												sheet.analog[j].workFlag=RT_FALSE;
//												rt_kprintf("%s close chanl%d\n",sign,j+1);
//												return;
//										}
//								 }
						
								 
								 
//ÿ�ν�ȥ�����ɾ��ʱ����ô˺���
void getAnaTotalNum()
{
	
		su8AnaTotalNum=0;
		for(int i=0;i<ANALOG_NUM;i++){
				if(sheet.analog[i].workFlag==RT_TRUE){
					su8AnaWork[su8AnaTotalNum]=i;
					su8AnaTotalNum++;
					rt_kprintf("su8anaTotalNum:%d  %d\n",su8AnaTotalNum,sheet.analog[i].workFlag);
				}
		}
		for(int j=su8AnaTotalNum;j<DI_NUM;j++)//û�洢�ı�ǵľ���0
				su8AnaWork[su8AnaTotalNum+j]=0;
		if(su8AnaTotalNum>0){
				su8AnaTheNum=1;
		}
		else{
				su8AnaTheNum=0;
		}
}



//��һҳ
void  lastReadAna()
{
	  if(su8AnaTotalNum==0){
				return;
		}
		
		if(su8AnaTheNum==1)
				su8AnaTheNum=su8AnaTotalNum;//4
		else
				su8AnaTheNum--;
	rt_kprintf("last input:%d \n",su8AnaTheNum);
}
//��һҳ
void  nextReadAna()
{
		if(su8AnaTotalNum==0){
				return;
		}
		su8AnaTheNum++;
		if(su8AnaTheNum>su8AnaTotalNum)
				su8AnaTheNum=1;
		rt_kprintf("next input:%d \n",su8AnaTheNum);

}
//ɾ��
void  delOneAna()
{
	 for(int p=0;p<DI_NUM;p++){
				if(rt_strcmp(sheet.analog[p].ID,sheet.analog[su8AnaWork[su8AnaTheNum-1]].ID)==0){

						sheet.analog[p].workFlag=RT_FALSE;
						rt_kprintf("del one:%d %d %d\n",p,su8AnaTotalNum,su8AnaTheNum);
					  rt_kprintf("del one:%s %s %s\n",sheet.analog[p].name,sheet.analog[p].ID,sheet.analog[p].model);
				}
		}
}


//������ʾ�����ݸ�LCD
void  dispReadAna()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
		if(su8AnaTotalNum==0){
				buf[0]=0xff;
				buf[1]=0xff;
				//��ʾname
				LCDWtite(DISP_ANAREAD_NAME_ADDR,buf,2);
			  //��ʾ��name
			  LCDWtite(DISP_ANAREAD_SUBNAME_ADDR,buf,2);
				//��ʾID
				LCDWtite(DISP_ANAREAD_ID_ADDR,buf,2);//7������ʾ18
				//��ʾmodel
				LCDWtite(DISP_ANAREAD_TYPE_ADDR,buf,2);
				//��ʾPORT
				LCDWtite(DISP_ANAREAD_PORT_ADDR,buf,2);
			  //��ʾtme
			  LCDWtite(DISP_ANAREAD_TIME_ADDR,buf,2);
				//��ʾ�ܹ�ҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_ANAREAD_TOTALNUM_ADDR,buf,2);
				//��ʾ��ǰҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_ANAREAD_THENUM_ADDR,buf,2);

				return;
		}
	  //��ʾ������
		uint8_t p=su8AnaWork[su8AnaTheNum-1];

		int Len=strlen(sheet.analog[p].name);
		for(int i=0;i<Len;i++){
				buf[i]=sheet.analog[p].name[i];
		}
		int j=0;
		while((Len+j)<NAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_ANAREAD_NAME_ADDR,buf,NAME_LEN);
		if((sheet.analog[p].subName>2)||(sheet.analog[p].subName==0)){
			sheet.analog[p].subName=1;
		}

		//��ʾsub������
		Len=strlen(anaSubName1Val[sheet.analog[p].subName-1]);
		for(int i=0;i<Len;i++){
				buf[i]=anaSubName1Val[sheet.analog[p].subName-1][i];
		}
		j=0;
		while((Len+j)<NAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_ANAREAD_SUBNAME_ADDR,buf,NAME_LEN);
		//��ʾID
		 Len=strlen(sheet.analog[p].ID);
		for(int i=0;i<Len;i++){
				buf[i]=sheet.analog[p].ID[i];
		}
		 j=0;
		while((Len+j)<DEVID_LEN+2){
				buf[Len+j]=0xff;
				j++;
				if(j>=2)
					break;
		}
		LCDWtite(DISP_ANAREAD_ID_ADDR,buf,DEVID_LEN+2);//7������ʾ18
		//��ʾmodel
		Len=strlen(sheet.analog[p].model);
		for(int i=0;i<Len;i++){
				buf[i]=sheet.analog[p].model[i];
		}
		 j=0;
		while((Len+j)<MODEL_LEN+2){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_ANAREAD_TYPE_ADDR,buf,MODEL_LEN+2);
		//��ʾPORT
		buf[0]=0;
		buf[1]=sheet.analog[p].port;
		LCDWtite(DISP_ANAREAD_PORT_ADDR,buf,2);

		//��ʾtime
		buf[3]=(uint8_t)sheet.analog[p].colTime;
		buf[2]=(uint8_t)(sheet.analog[p].colTime>>8);
		buf[1]=(uint8_t)(sheet.analog[p].colTime>>16);
		buf[0]=(uint8_t)(sheet.analog[p].colTime>>24);
		LCDWtite(DISP_ANAREAD_TIME_ADDR,buf,4);

		//��ʾ�ܹ�ҳ
		buf[0]=0;
		buf[1]=su8AnaTotalNum;
		LCDWtite(DISP_ANAREAD_TOTALNUM_ADDR,buf,2);
		rt_kprintf("%s total %d\n",sign,su8AnaTotalNum);
		//��ʾ��ǰҳ
		buf[0]=0;

		buf[1]=su8AnaTheNum;
		LCDWtite(DISP_ANAREAD_THENUM_ADDR,buf,2);
			
		rt_free(buf);
		buf=RT_NULL;
}

#endif
