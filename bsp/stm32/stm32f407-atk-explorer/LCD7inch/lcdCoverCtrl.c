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
const static char sign[]="[LCDCover]";
extern char outName[OUTNAME_NUM][INOUTNAME_LEN];
static char nowIndex=0;
static char totalIndex=0;
static char index[COVER_485_NUM]={0};
extern bool  coverUartOnOff(char *ID,bool onOffFlag);


void LCDClearOpen()
{
	 uint8_t buf[2];
	 buf[0]=0xff;
	 buf[1]=0xff;
	
	 LCDWtite(TEXT_COVER_OPENRESP_ADDR,buf,2);
}
void LCDClearClose()
{
	 uint8_t buf[2];
	 buf[0]=0xff;
	 buf[1]=0xff;
	
	 LCDWtite(TEXT_COVER_CLOSERESP_ADDR,buf,2);
}
//�Ǽǵ�ǰ����index
static void signIndex()
{
	    totalIndex=0;
			for(int j=0;j<COVER_485_NUM;j++){//�˶���û�����ù�
				if(sheet.cover[j].workFlag==true){
					 
					 index[totalIndex]=j;
					 totalIndex++;
				}
		}
}
//������ʾ
static void coverDisp()
{
	  uint8_t  buf[MODBID_LEN+5];	
	//��ʾID
		int Len=strlen(sheet.cover[index[nowIndex]].ID);
		for(int i=0;i<Len;i++){
				buf[i]=sheet.cover[index[nowIndex]].ID[i];
		}
		int j1=0;
		while((Len+j1)<MODBID_LEN-2){
				buf[Len+j1]=0xff;
				j1++;
			  if(j1>=2)
					break;
		}
	  LCDWtite(TEXT_COVER_ID_ADDR,buf,MODBID_LEN-2);//7������ʾ18

		//��ʾaddr
		buf[0]=0;
		buf[1]=sheet.cover[index[nowIndex]].slaveAddr;
		LCDWtite(DATA_COVER_ADDR_ADDR,buf,2);
		
		//��ʾtotalIndex
		buf[0]=0;
		buf[1]=totalIndex;
		LCDWtite(DATA_COVER_TOTALPAGE_ADDR,buf,2);
		
		
		//��ʾnowIndex
		buf[0]=0;
		buf[1]=nowIndex+1;
		LCDWtite(DATA_COVER_NOWPAGE_ADDR,buf,2);

}
void coverNowDisp()
{
	 signIndex();//�õ����е�index����
   if(totalIndex==0)
		 return;
	 nowIndex=0;
	 coverDisp();
	 LCDClearOpen();
	 LCDClearClose();
}
//��һ������
void coverNextDisp()
{
	 if(totalIndex==0)
		 return;
	 nowIndex++;
	 if(nowIndex>=totalIndex)
		 nowIndex=0;
	 coverDisp();
	 LCDClearOpen();
	 LCDClearClose();
}
//��һ������
void coverLastDisp()
{
	  if(totalIndex==0)
		  return;
	 if(nowIndex==0)
		 nowIndex=totalIndex-1;
	 else
		 nowIndex--;
	 coverDisp();
	 LCDClearOpen();
	 LCDClearClose();
}




//����
void coverOpen()
{
		LCDClearOpen();
	 LCDClearClose();
	 uint8_t buf[10];

		if(coverUartOnOff(sheet.cover[index[nowIndex]].ID,true)==true){//�򿪳ɹ�
			strcpy((char *)buf,"ON SUCC");//����ע���ڴ����  �´��0��ȥ
		}
		else{
			strcpy((char *)buf,"ON FAIL");//����ע���ڴ����  �´��0��ȥ
		}
	  buf[7]=0xff;
	  buf[8]=0xff;
		LCDWtite(TEXT_COVER_OPENRESP_ADDR,buf,9);
}
//����
void coverClose()
{
	 LCDClearOpen();
	 LCDClearClose();
	 uint8_t buf[12];

		if(coverUartOnOff(sheet.cover[index[nowIndex]].ID,false)==true)//�رճɹ�
			strcpy((char *)buf,"OFF SUCC");
		else
			strcpy((char *)buf,"OFF FAIL");
	 buf[9]=0xff;
	 buf[10]=0xff;
		LCDWtite(TEXT_COVER_CLOSERESP_ADDR,buf,10);
}
