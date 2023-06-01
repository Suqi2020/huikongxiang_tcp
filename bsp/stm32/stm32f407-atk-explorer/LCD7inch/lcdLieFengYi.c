#include  "board.h"



extern  crackMeterStru crackMeter[CRACKMETER_485_NUM];

static int dispLiefengIndex=0;
int dispLiefengTotlNum=0;



//��ʾ��������71.bmp����������
void  dispLiefengData()
{
	  uint8_t buf[MODBID_LEN+2]={0};
		if(dispLiefengTotlNum==0){//û�й����Ļ���
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_DATA_LIEFENG_TOTALNUM_ADDR,buf,2);
				//��ʾid
				buf[0]=0xff;
				buf[1]=0xff;
				LCDWtite(DISP_DATA_LIEFENG_ID_ADDR,buf,2);
				LCDWtite(DISP_DATA_LIEFENG_TEMP_ADDR,buf,2);
				LCDWtite(DISP_DATA_LIEFENG_DISTANC_ADDR,buf,2);

		}
		else{
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=dispLiefengTotlNum;
				LCDWtite(DISP_DATA_LIEFENG_TOTALNUM_ADDR,buf,2);
				//��ʾidr
			  int len=0;
			  for(len=0;len<MODBID_LEN;len++){
						buf[len]=sheet.crackMeter[dispLiefengIndex].ID[len];
					  if(buf[len]==0){
								break;
						}
				}
				buf[len++]	=0xff;  
				buf[len++]  =0xff; 
				LCDWtite(DISP_DATA_LIEFENG_ID_ADDR,buf,len);
				
				sprintf((char *)buf,"%0.2f",crackMeter[dispLiefengIndex].temp.flotVal);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_LIEFENG_TEMP_ADDR,buf,len);
				sprintf((char *)buf,"%0.2f",crackMeter[dispLiefengIndex].distanc.flotVal);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_LIEFENG_DISTANC_ADDR,buf,len);
				
		}

}

//��һ�黷������
void  nextLiefengIndex()
{
	if(dispLiefengTotlNum==0)
		return;
	else{
		dispLiefengIndex++;
		if(dispLiefengIndex>=dispLiefengTotlNum)
				dispLiefengIndex=0;
	}	
}
//��һ�黷������
void  lastLiefengIndex()
{
	if(dispLiefengTotlNum==0)
		return;
	else{
		if(dispLiefengIndex==0)
			dispLiefengIndex=dispLiefengTotlNum-1;
		else
			dispLiefengIndex--;
	}
}
