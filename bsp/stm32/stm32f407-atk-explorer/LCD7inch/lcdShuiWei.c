#include "board.h"

extern float waterDepth[WATERDEPTH_485_NUM];
static int dispWaterIndex=0;
int dispWaterTotlNum=0;
//��ʾ��������71.bmp����������
void  dispWaterData()
{
	  uint8_t buf[MODBID_LEN+2]={0};
		if(dispWaterTotlNum==0){//û�й����Ļ���
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_DATA_WATER_TOTALNUM_ADDR,buf,2);
				//��ʾid
				buf[0]=0xff;
				buf[1]=0xff;
				LCDWtite(DISP_DATA_WATER_ID_ADDR,buf,2);
				LCDWtite(DISP_DATA_WATER_DEPTH_ADDR,buf,2);
		}
		else{
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=dispWaterTotlNum;
				LCDWtite(DISP_DATA_WATER_TOTALNUM_ADDR,buf,2);
				//��ʾidr
			  int len=0;
			  for(len=0;len<MODBID_LEN;len++){
						buf[len]=sheet.waterDepth[dispWaterIndex].ID[len];
					  if(buf[len]==0){
								break;
						}
				}
				buf[len++]	=0xff;  
				buf[len++]  =0xff; 
				LCDWtite(DISP_DATA_WATER_ID_ADDR,buf,len);
				sprintf((char *)buf,"%0.2f",waterDepth[dispWaterIndex]);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_WATER_DEPTH_ADDR,buf,len);
		}
}

//��һ��Water����
void  nextWaterIndex()
{
		if(dispWaterTotlNum==0)
				return;
		else{
				dispWaterTotlNum++;
				if(dispWaterIndex>=dispWaterTotlNum)
						dispWaterIndex=0;
		}	
}
//��һ��Water����
void  lastWaterIndex()
{
		if(dispWaterTotlNum==0)
				return;
		else{
			if(dispWaterIndex==0)
					dispWaterIndex=dispWaterTotlNum-1;
			else
					dispWaterIndex--;
		}
}
