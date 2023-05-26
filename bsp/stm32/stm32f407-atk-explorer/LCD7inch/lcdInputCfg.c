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
const static char sign[]="[LCDInputCfg]";

static digitStru digInputLCD={0};





//������������ֵ�digInputLCD��
void lcdCopyInputName(uint8_t *rec)
{
	for(int i=0;i<NAME_LEN;i++){
		digInputLCD.name[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				digInputLCD.name[i]=0;
				break;
		}
	}
}


//���������ID��digInputLCD��
void lcdCopyInputID(uint8_t *rec)
{
	for(int i=0;i<DEVID_LEN;i++){
		digInputLCD.devID[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				digInputLCD.devID[i]=0;
				break;
		}
	}
	if(devIDOKCheck(digInputLCD.devID)!=true){//�˶�ID
			LCDDispSameID(DISP_INPUT_SAME_ID_MSG_ADDR);
		  rt_kprintf("%sERR:same ID\n",sign);
	}
	else 
		  LCDRstDispSameID(DISP_INPUT_SAME_ID_MSG_ADDR);
}
//���������type��digInputLCD��
void lcdCopyInputModel(uint8_t *rec)
{
	for(int i=0;i<MODEL_LEN;i++){
		digInputLCD.model[i]=rec[7+i];
		if((rec[7+i]==0xff)||(rec[7+i]==0)){
				digInputLCD.model[i]=0;
				break;
		}
	}
}
//���������port��digInputLCD��
void lcdCopyInputPort(uint8_t *rec)
{

		digInputLCD.port=rec[8];
}


//��ȷ����������������
void  lcdInputConfig()
{
		int port=digInputLCD.port;
		if(devIDOKCheck(digInputLCD.devID)!=true){//�˶�ID
				LCDDispSameID(DISP_INPUT_SAME_ID_MSG_ADDR);
			  rt_kprintf("%sERR:same ID\n",sign);
				return;
		}
		if((port<=DI_NUM)&&(port>0)){//���
				packFlash.diginput[port-1].workFlag=RT_TRUE;
				rt_strcpy(packFlash.diginput[port-1].name, digInputLCD.name);
				rt_strcpy(packFlash.diginput[port-1].devID,digInputLCD.devID);
				rt_strcpy(packFlash.diginput[port-1].model,digInputLCD.model);
				packFlash.diginput[port-1].port=port;
				rt_kprintf("%s add diginput chanl %d\n",sign,port);
        rt_kprintf("%s digInput OK\n",sign);
		}
}








uint8_t  su8inputTotalNum=0;//��ʾ��ҳ��
uint8_t  su8inputTheNum=0;  //��ʾ�ڼ�ҳ
uint8_t  su8WorkInput[DI_NUM]={0};//��¼�������ù��ĽǱ�  û�����ù��Ǽ�Ϊ0

//ÿ�ν�ȥ�����ɾ��ʱ����ô˺���
void getInputTotalNum()
{
		su8inputTotalNum=0;
		for(int i=0;i<DI_NUM;i++){
				if(packFlash.diginput[i].workFlag==RT_TRUE){
					su8WorkInput[su8inputTotalNum]=i;
					su8inputTotalNum++;
					rt_kprintf("su8inputTotalNum:%d  %d\n",su8inputTotalNum,packFlash.diginput[i].workFlag);
				}
		}
		for(int j=su8inputTotalNum;j<DI_NUM;j++)//û�洢�ı�ǵľ���0
				su8WorkInput[su8inputTotalNum+j]=0;
		if(su8inputTotalNum>0){
				su8inputTheNum=1;
		}
		else{
				su8inputTheNum=0;
		}
}

//��һҳ
void  lastInput()
{
	  if(su8inputTotalNum==0){
			return;
		}
		
		if(su8inputTheNum==1)
				su8inputTheNum=su8inputTotalNum;//4
		else
				su8inputTheNum--;
	rt_kprintf("last input:%d \n",su8inputTheNum);
}
//��һҳ
void  nextInput()
{
		if(su8inputTotalNum==0){
			return;
		}
		su8inputTheNum++;
		if(su8inputTheNum>su8inputTotalNum)
				su8inputTheNum=1;
		rt_kprintf("next input:%d \n",su8inputTheNum);

}
//ɾ��
void  delOneInput()
{
	 for(int p=0;p<DI_NUM;p++){
				if(rt_strcmp(packFlash.diginput[p].devID,packFlash.diginput[su8WorkInput[su8inputTheNum-1]].devID)==0){

						packFlash.diginput[p].workFlag=RT_FALSE;
						rt_kprintf("del one:%d %d %d\n",p,su8inputTotalNum,su8inputTheNum);
					  rt_kprintf("del one:%s %s %s\n",packFlash.diginput[p].name,packFlash.diginput[p].devID,packFlash.diginput[p].model);
				}
		}
}


//������ʾ�����ݸ�LCD
void  dispInput()
{
		uint8_t *buf=NULL;
	  buf=rt_malloc(50);
		if(su8inputTotalNum==0){
				buf[0]=0xff;
				buf[1]=0xff;
				//��ʾname
				LCDWtite(DISP_INPUT_NAME_ADDR,buf,2);
				//��ʾID
				LCDWtite(DISP_INPUT_ID_ADDR,buf,2);//7������ʾ18
				//��ʾmodel
				LCDWtite(DISP_INPUT_TYPE_ADDR,buf,2);
				//��ʾPORT
				LCDWtite(DISP_INPUT_PORT_ADDR,buf,2);
				//��ʾ�ܹ�ҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_INPUT_TOTALNUM_ADDR,buf,2);
				//��ʾ��ǰҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_INPUT_THENUM_ADDR,buf,2);

				return;
		}
	  //��ʾ������
		uint8_t p=su8WorkInput[su8inputTheNum-1];
	//if(packFlash.diginput[p].workFlag==RT_TRUE){
		int Len=strlen(packFlash.diginput[p].name);
		for(int i=0;i<Len;i++){
				buf[i]=packFlash.diginput[p].name[i];
		}
		int j=0;
		while((Len+j)<NAME_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_INPUT_NAME_ADDR,buf,NAME_LEN);
		//��ʾID
		 Len=strlen(packFlash.diginput[p].devID);
		for(int i=0;i<Len;i++){
				buf[i]=packFlash.diginput[p].devID[i];
		}
		 j=0;
		while((Len+j)<DEVID_LEN+2){
				buf[Len+j]=0xff;
				j++;
				if(j>=2)
					break;
		}
		LCDWtite(DISP_INPUT_ID_ADDR,buf,DEVID_LEN+2);//7������ʾ18
		//��ʾmodel
		Len=strlen(packFlash.diginput[p].model);
		for(int i=0;i<Len;i++){
				buf[i]=packFlash.diginput[p].model[i];
		}
		 j=0;
		while((Len+j)<MODEL_LEN){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_INPUT_TYPE_ADDR,buf,MODEL_LEN);
		//��ʾPORT
		buf[0]=0;
		buf[1]=packFlash.diginput[p].port;
		LCDWtite(DISP_INPUT_PORT_ADDR,buf,2);

		//��ʾ�ܹ�ҳ
		buf[0]=0;
		buf[1]=su8inputTotalNum;
		LCDWtite(DISP_INPUT_TOTALNUM_ADDR,buf,2);
		rt_kprintf("%s total %d\n",sign,su8inputTotalNum);
		//��ʾ��ǰҳ
		buf[0]=0;

		buf[1]=su8inputTheNum;
		LCDWtite(DISP_INPUT_THENUM_ADDR,buf,2);
			
		rt_free(buf);
		buf=RT_NULL;
}


