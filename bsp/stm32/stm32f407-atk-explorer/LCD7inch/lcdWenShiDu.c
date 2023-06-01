#include  "board.h"


extern thStru thum[TEMPHUM_485_NUM];



static int dispWenshiduIndex=0;
int dispWenshiduTotlNum=0;



//��ʾ��������71.bmp����������
void  dispWenshiduData()
{
	  uint8_t buf[MODBID_LEN+2]={0};
		if(dispWenshiduTotlNum==0){//û�й����Ļ���
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_DATA_WENSHIDU_TOTALNUM_ADDR,buf,2);
				//��ʾid
				buf[0]=0xff;
				buf[1]=0xff;
				LCDWtite(DISP_DATA_WENSHIDU_ID_ADDR,buf,2);
				LCDWtite(DISP_DATA_WENSHIDU_TEMP_ADDR,buf,2);
				LCDWtite(DISP_DATA_WENSHIDU_HUMI_ADDR,buf,2);

		}
		else{
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=dispWenshiduTotlNum;
				LCDWtite(DISP_DATA_WENSHIDU_TOTALNUM_ADDR,buf,2);
				//��ʾidr
			  int len=0;
			  for(len=0;len<MODBID_LEN;len++){
						buf[len]=sheet.tempHum[dispWenshiduIndex].ID[len];
					  if(buf[len]==0){
								break;
						}
				}
				buf[len++]	=0xff;  
				buf[len++]  =0xff; 
				LCDWtite(DISP_DATA_WENSHIDU_ID_ADDR,buf,len);
				
				sprintf((char *)buf,"%0.2f",thum[dispWenshiduIndex].temp);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_WENSHIDU_TEMP_ADDR,buf,len);
				sprintf((char *)buf,"%0.2f",thum[dispWenshiduIndex].hum);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_WENSHIDU_HUMI_ADDR,buf,len);

		}

}

//��һ�黷������
void  nextWenshiduIndex()
{
	if(dispWenshiduTotlNum==0)
		return;
	else{
		dispWenshiduIndex++;
		if(dispWenshiduIndex>=dispWenshiduTotlNum)
				dispWenshiduIndex=0;
	}	
}
//��һ�黷������
void  lastWenshiduIndex()
{
	if(dispWenshiduTotlNum==0)
		return;
	else{
		if(dispWenshiduIndex==0)
			dispWenshiduIndex=dispWenshiduTotlNum-1;
		else
			dispWenshiduIndex--;
	}
}
