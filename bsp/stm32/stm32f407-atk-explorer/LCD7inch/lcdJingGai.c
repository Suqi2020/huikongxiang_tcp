#include  "board.h"




extern coverStru cover[COVER_485_NUM];


static int dispJinggaiIndex=0;
int dispJinggaiTotlNum=0;



//��ʾ��������71.bmp����������
void  dispJinggaiData()
{
	  uint8_t buf[MODBID_LEN+2]={0};
		if(dispJinggaiTotlNum==0){//û�й����Ļ���
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_DATA_COVER_TOTALNUM_ADDR,buf,2);
				//��ʾid
				buf[0]=0xff;
				buf[1]=0xff;
				LCDWtite(DISP_DATA_COVER_ID_ADDR,buf,2);
				LCDWtite(DISP_DATA_COVER_INCLINE_ADDR,buf,2);
				LCDWtite(DISP_DATA_COVER_SWITCH2P_ADDR,buf,2);
				LCDWtite(DISP_DATA_COVER_VIBRATION_ADDR,buf,2);
				LCDWtite(DISP_DATA_COVER_SWITCH1P_ADDR,buf,2);
	
		}
		else{
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=dispJinggaiTotlNum;
				LCDWtite(DISP_DATA_COVER_TOTALNUM_ADDR,buf,2);
				//��ʾidr
			  int len=0;
			  for(len=0;len<MODBID_LEN;len++){
						buf[len]=sheet.cover[dispJinggaiIndex].ID[len];
					  if(buf[len]==0){
								break;
						}
				}
				buf[len++]	=0xff;  
				buf[len++]  =0xff; 
				LCDWtite(DISP_DATA_COVER_ID_ADDR,buf,len);
				
				sprintf((char *)buf,"%d",cover[dispJinggaiIndex].incline);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_COVER_INCLINE_ADDR,buf,len);
				sprintf((char *)buf,"%d",cover[dispJinggaiIndex].switch2p);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_COVER_SWITCH2P_ADDR,buf,len);
				sprintf((char *)buf,"%d",cover[dispJinggaiIndex].vibration);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_COVER_VIBRATION_ADDR,buf,len);
				sprintf((char *)buf,"%d",cover[dispJinggaiIndex].switch1p);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_COVER_SWITCH1P_ADDR,buf,len);
				
		}

}

//��һ�黷������
void  nextJinggaiIndex()
{
	if(dispJinggaiTotlNum==0)
		return;
	else{
		dispJinggaiIndex++;
		if(dispJinggaiIndex>=dispJinggaiTotlNum)
				dispJinggaiIndex=0;
	}	
}
//��һ�黷������
void  lastJinggaiIndex()
{
	if(dispJinggaiTotlNum==0)
		return;
	else{
		if(dispJinggaiIndex==0)
			dispJinggaiIndex=dispJinggaiTotlNum-1;
		else
			dispJinggaiIndex--;
	}
}
