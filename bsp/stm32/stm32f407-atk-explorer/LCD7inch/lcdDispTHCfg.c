/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */
 
 #if 0

#include "7inchRegist.h"
const static char sign[]="[LCDDispTHCfg]";
char  dispTHTypeName[2][12]={"485������","ģ�⴫����"};
char  dispSubName[15];
#ifdef  USE_4GAS
//const static char  modbusName[MODBUS_NUM][NAME_LEN] ={"�ӵػ���","�ַ�","������","������","����","����","����","һ����̼","��ʪ��","ˮλ"};
const static char  circulaName[3][10]={"cirCurA","cirCurB","cirCurC"};
const static char  partDischagName[9][15]={"pdA","freqA","disChgDataA",
																					 "pdB","freqB","disChgDataB",
																					 "pdC","freqC","disChgDataC",};
const static  char  pressettleName[2][10]={"temputer","height"};
const static  char  threeAxisName[4][10]={"temputer","ACC-X","ACC-Y","ACC-Z"};		
const static  char  ch4Name[]="ch4";
const static  char  o2Name[] ="o2";
const static  char  h2sName[]="h2s";
const static  char  coName[] ="co";
const static  char  tempHum[][10]={"temp","humi"};
const static  char  waterLev[]={"depth"};

#endif
//analogStru  anaInput={0};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t  su8THTotalNum=0;//��ʾ��ҳ��
uint8_t  su8THTheNum=0;  //��ʾ�ڼ�ҳ
#define   THWORK_NUM  PRESSSETTL_485_NUM+10
uint8_t  su8THWork[THWORK_NUM]={0};//��¼�������ù��ĽǱ�  û�����ù��Ǽ�Ϊ0



uint8_t  su8THTypeNameNum=0;//��ʾ������
uint8_t  su8THNameNum=0;//��ʾ���Ƽ���
uint8_t  su8THSubNameNum=0;//��ʾ��ѡ�����
								 



		su8THSubNameNum=0;
					su8THNameNum++;
//��ʾʱ�����
static void  copyModbusSubName()
{
	  if(su8THTypeNameNum==1){
				rt_strcpy(dispSubName,tempHum[su8THSubNameNum]);
			
			
//					for(int i=0;i<CIRCULA_485_NUM;i++){
//				if(sheet.cirCula[i].workFlag==RT_TRUE){
//					su8THWork[su8THTotalNum]=i;	
				return;
		}


		switch(su8THNameNum)
		{
			case CIRCULA:
					rt_strcpy(dispSubName,circulaName[su8THSubNameNum]);
					break;
				case PARTDISCHAG:
					rt_strcpy(dispSubName,partDischagName[su8THSubNameNum]);
					break;
				case PRESSSETTL:
					rt_strcpy(dispSubName,pressettleName[su8THSubNameNum]);
					break;
				case THREEAXIS:
					rt_strcpy(dispSubName,threeAxisName[su8THSubNameNum]);
					break;
	#ifdef  USE_4GAS
				case CH4:
					rt_strcpy(dispSubName,ch4Name);
					break;
				case O2:
					rt_strcpy(dispSubName,o2Name);
					break;
				case H2S:
					rt_strcpy(dispSubName,h2sName);
					break;
				case CO:
					rt_strcpy(dispSubName,coName);
					break;
	#endif
				case TEMPHUM:
					rt_strcpy(dispSubName,tempHum[su8THSubNameNum]);
					break;
				case WATERDEPTH:
					rt_strcpy(dispSubName,waterLev);
					break;
				default:
					rt_kprintf("%s ERR:modbusThresholdConfig \n",sign);
					break;
		}

}
	

static void  getModbusTHTotalNum()
{
		switch(su8THNameNum)
		{
			case CIRCULA:
					for(int i=0;i<CIRCULA_485_NUM;i++){
							if(sheet.cirCula[i].workFlag==RT_TRUE){
								su8THWork[su8THTotalNum]=i;
								su8THTotalNum++;
								rt_kprintf("su8 CIR TotalNum:%d  %d\n",su8THTotalNum,sheet.cirCula[i].workFlag);
							}
					}
				
					break;
				case PARTDISCHAG:
					for(int i=0;i<PARTDISCHAG_485_NUM;i++){
						if(sheet.partDischag[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 part TotalNum:%d  %d\n",su8THTotalNum,sheet.partDischag[i].workFlag);
						}
					}
					break;
				case PRESSSETTL:
					for(int i=0;i<PRESSSETTL_485_NUM;i++){
						if(sheet.pressSetl[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 press TotalNum:%d  %d\n",su8THTotalNum,sheet.pressSetl[i].workFlag);
						}
					}
					break;
				case THREEAXIS:
					for(int i=0;i<THREEAXIS_485_NUM;i++){
						if(sheet.threeAxiss[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 three TotalNum:%d  %d\n",su8THTotalNum,sheet.threeAxiss[i].workFlag);
						}
					}
					break;
	#ifdef  USE_4GAS
				case CH4:
					for(int i=0;i<CH4_485_NUM;i++){
						if(sheet.ch4[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 ch4 TotalNum:%d  %d\n",su8THTotalNum,sheet.ch4[i].workFlag);
						}
					}
					break;
				case O2:
					for(int i=0;i<O2_485_NUM;i++){
						if(sheet.o2[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 o2 TotalNum:%d  %d\n",su8THTotalNum,sheet.o2[i].workFlag);
						}
					}

					break;
				case H2S:
					for(int i=0;i<H2S_485_NUM;i++){
						if(sheet.h2s[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 h2s TotalNum:%d  %d\n",su8THTotalNum,sheet.h2s[i].workFlag);
						}
					}
					break;

				case CO:
					for(int i=0;i<CO_485_NUM;i++){
						if(sheet.co[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 co TotalNum:%d  %d\n",su8THTotalNum,sheet.co[i].workFlag);
						}
					}
					break;
	#endif
				case TEMPHUM:
					for(int i=0;i<CO_485_NUM;i++){
						if(sheet.tempHum[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 temp TotalNum:%d  %d\n",su8THTotalNum,sheet.tempHum[i].workFlag);
						}
					}
					break;
				case WATERDEPTH:
					for(int i=0;i<WATERDEPTH_485_NUM;i++){
						if(sheet.waterDepth[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8 water TotalNum:%d  %d\n",su8THTotalNum,sheet.tempHum[i].workFlag);
						}
					}
					break;
				default:
					rt_kprintf("%s ERR:modbusThresholdConfig \n",sign);
					break;
		}

		for(int j=su8THTotalNum;j<THWORK_NUM;j++)//û�洢�ı�ǵľ���0
				su8THWork[su8THTotalNum+j]=0;
		if(su8THTotalNum>0){
				su8THTheNum=1;
		}
		else{
				su8THTheNum=0;
		}
}
//ÿ�ν�ȥ�����ɾ�� ��һҳ ��һҳ����ȡ�����ƶ�ȡʱ����ô˺���
void getTHTotalNum()
{
	  
		su8THTotalNum=0;
	  switch(su8THTypeNameNum)
		{
			case 0://485
				getModbusTHTotalNum();
				break;
			case 1://ģ��
				for(int i=0;i<ANALOG_NUM;i++){
						if(sheet.analog[i].workFlag==RT_TRUE){
							su8THWork[su8THTotalNum]=i;
							su8THTotalNum++;
							rt_kprintf("su8anaTotalNum:%d  %d\n",su8THTotalNum,sheet.analog[i].workFlag);
						}
				}
				for(int j=su8THTotalNum;j<DI_NUM;j++)//û�洢�ı�ǵľ���0
						su8THWork[su8THTotalNum+j]=0;
				if(su8THTotalNum>0){
						su8THTheNum=1;
				}
				else{
						su8THTheNum=0;
				}
				break;
		}
}

//�����һҳ
void  lastReadTypeNameTH()
{
	  if(su8THTypeNameNum==1)
			su8THTypeNameNum=0;
		else
			su8THTypeNameNum=1;
		 su8THSubNameNum=0;
		su8THNameNum=0;
}
//�����һҳ
void  nextReadTypeNameTH()
{
	  lastReadTypeNameTH();
	
}

//������һҳ
void  lastReadName()
{
	  su8THSubNameNum=0;
	  switch(su8THTypeNameNum)
		{
			case 0://485
				if(su8THNameNum==0)
						su8THNameNum=MODBUS_NUM;
				else
					  su8THNameNum--;
				break;
			case 1://ģ��
				su8THNameNum=0;
				break;
		}
}
//������һҳ
void  nextReadName()
{
	  su8THSubNameNum=0;
	  switch(su8THTypeNameNum)
		{
			case 0://485
				su8THNameNum++;
			  if(su8THNameNum==MODBUS_NUM)
					su8THNameNum=0;
				break;
			case 1://ģ��
				su8THNameNum=0;
				break;
		}
}


//��һҳ
void  lastReadTH()
{		
		lastReadName();
	  
		
}
//��һҳ
void  nextReadTH()
{
	  
	  if(su8THTypeNameNum==1){
			if(su8THNameNum==1)
				su8THNameNum=0;
			else
				su8THNameNum=1;
			return;
		}
		switch(su8THNameNum)
		{
			case CIRCULA:
					su8THSubNameNum++;
			    if(su8THSubNameNum>(sizeof(circulaName)/sizeof(circulaName[0]))){
							su8THSubNameNum=0;
							su8THNameNum++;
					}
					break;
				case PARTDISCHAG:
					su8THSubNameNum++;
			    if(su8THSubNameNum>(sizeof(partDischagName)/sizeof(partDischagName[0]))){
							su8THSubNameNum=0;
							su8THNameNum++;
					}
					break;
				case PRESSSETTL:
					su8THSubNameNum++;
			    if(su8THSubNameNum>(sizeof(pressettleName)/sizeof(pressettleName[0]))){
							su8THSubNameNum=0;
							su8THNameNum++;
					}
					break;
				case THREEAXIS:
					su8THSubNameNum++;
			    if(su8THSubNameNum>(sizeof(threeAxisName)/sizeof(threeAxisName[0]))){
							su8THSubNameNum=0;
							su8THNameNum++;
					}
					break;
	#ifdef  USE_4GAS
				case CH4:

					su8THSubNameNum=0;
					su8THNameNum++;

					break;
				case O2:
					su8THSubNameNum=0;
					su8THNameNum++;
					break;
				case H2S:
					su8THSubNameNum=0;
					su8THNameNum++;
					break;
				case CO:
					su8THSubNameNum=0;
					su8THNameNum++;
					break;
	#endif
				case TEMPHUM:
					su8THSubNameNum++;
			    if(su8THSubNameNum>(sizeof(tempHum)/sizeof(tempHum[0]))){
							su8THSubNameNum=0;
							su8THNameNum++;
					}
					break;
				case WATERDEPTH:
					su8THSubNameNum=0;
					su8THNameNum++;
					break;
				default:

					break;
		}

		  if(su8THNameNum==MODBUS_NUM)
					su8THNameNum=0;
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
		if(su8THTotalNum==0){
				buf[0]=0xff;
				buf[1]=0xff;
				//��ʾname
				LCDWtite(DISP_TH_READ_NAME_ADDR,buf,2);
			  //��ʾ��name
			  LCDWtite(DISP_TH_READ_SUBNAME_ADDR,buf,2);
				//��ʾID
				LCDWtite(DISP_TH_READ_ID_ADDR,buf,2);//7������ʾ18
				//��ʾTYPE
				LCDWtite(DISP_TH_READ_TYPE_ADDR,buf,2);
				//��ʾ����
				LCDWtite(DISP_TH_READ_UP_LIMIT_ADDR,buf,2);
			  //��ʾ����
			  LCDWtite(DISP_TH_READ_DOWN_LIMIT_ADDR,buf,2);
				//��ʾ�ܹ�ҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_TH_READ_TOTAL_PAGE_ADDR,buf,2);
				//��ʾ��ǰҳ
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_TH_READ_THE_PAGE_ADDR,buf,2);
				return;
		}
		
	//uint8_t p=su8AnaWork[su8AnaTheNum-1];
				//��ʾmodel
		int Len=strlen(dispTHTypeName[su8THTypeNameNum]);
		for(int i=0;i<Len;i++){
				buf[i]=(uint8_t)dispTHTypeName[i];
		}
		int j=0;
		while((Len+j)<(sizeof(dispTHTypeName[0])/sizeof(dispTHTypeName[0][0]))+2){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_TH_READ_TYPE_ADDR,buf,2);
	  //��ʾ������
		
		
		Len=strlen(modbusName[su8THNameNum]);
		for(int i=0;i<Len;i++){
				buf[i]= (uint8_t)modbusName[i];
		}
		j=0;
		while((Len+j)<sizeof(modbusName)){
				buf[Len+j]=0xff;
				j++;
		}
		LCDWtite(DISP_TH_READ_NAME_ADDR,buf,NAME_LEN);
		
		
		
		copyModbusSubName();

		//��ʾsub������
		Len=strlen(dispSubName);
		for(int i=0;i<Len;i++){
				buf[i]=dispSubName[i];
		}
		j=0;
		while((Len+j)<sizeof(dispSubName)){
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

		//��ʾ����
		buf[0]=0;
		buf[1]=sheet.analog[p].port;
		LCDWtite(DISP_ANAREAD_PORT_ADDR,buf,2);

		//��ʾ����
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