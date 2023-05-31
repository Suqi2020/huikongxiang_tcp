#include  "board.h"




extern  CIRCURStru  cirCurStru_p[CIRCULA_485_NUM];


static int dispHuanliuIndex=0;
int dispHuanliuTotlNum=0;



//��ʾ��������71.bmp����������
void  dispHuanliuData()
{
	  uint8_t buf[MODBID_LEN+2]={0};
		if(dispHuanliuTotlNum==0){//û�й����Ļ���
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=0;
				LCDWtite(DISP_DATA_HUANLIU_TOTALNUM_ADDR,buf,2);
				//��ʾid
				buf[0]=0xff;
				buf[1]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_ID_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_EARTH_A_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_EARTH_B_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_EARTH_C_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_RUN_A_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_RUN_B_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_RUN_C_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_LOADR_A_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_LOADR_B_ADDR,buf,2);
				LCDWtite(DISP_DATA_HUANLIU_LOADR_C_ADDR,buf,2);
		}
		else{
				//��ʾ��ҳ��
				buf[0]=0;
				buf[1]=dispHuanliuTotlNum;
				LCDWtite(DISP_DATA_HUANLIU_TOTALNUM_ADDR,buf,2);
				//��ʾidr
			  int len=0;
			  for(len=0;len<MODBID_LEN;len++){
						buf[len]=sheet.cirCula[dispHuanliuIndex].ID[len];
					  if(buf[len]==0){
								break;
						}
				}
				buf[len++]	=0xff;  
				buf[len++]  =0xff; 
				LCDWtite(DISP_DATA_HUANLIU_ID_ADDR,buf,len);
				
				sprintf((char *)buf,"%0.2f",cirCurStru_p[dispHuanliuIndex].circlCurA);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_EARTH_A_ADDR,buf,len);
				sprintf((char *)buf,"%0.2f",cirCurStru_p[dispHuanliuIndex].circlCurB);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_EARTH_B_ADDR,buf,len);
				sprintf((char *)buf,"%0.2f",cirCurStru_p[dispHuanliuIndex].circlCurC);
				len=strlen((char *)buf);
				buf[len++]=0xff;
				buf[len++]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_EARTH_C_ADDR,buf,len);
				buf[0]='0';
				buf[1]=0xff;
				buf[2]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_RUN_A_ADDR,buf,3);
				buf[0]='0';
				buf[1]=0xff;
				buf[2]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_RUN_B_ADDR,buf,3);
				buf[0]='0';
				buf[1]=0xff;
				buf[2]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_RUN_C_ADDR,buf,3);
				buf[0]='0';
				buf[1]=0xff;
				buf[2]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_LOADR_A_ADDR,buf,3);
				buf[0]='0';
				buf[1]=0xff;
				buf[2]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_LOADR_B_ADDR,buf,3);
				buf[0]='0';
				buf[1]=0xff;
				buf[2]=0xff;
				LCDWtite(DISP_DATA_HUANLIU_LOADR_C_ADDR,buf,3);
		}

}

//��һ�黷������
void  nextHuanliuIndex()
{
	if(dispHuanliuTotlNum==0)
		return;
	else{
		dispHuanliuIndex++;
		if(dispHuanliuIndex>=dispHuanliuTotlNum)
				dispHuanliuIndex=0;
	}	
}
//��һ�黷������
void  lastHuanliuIndex()
{
	if(dispHuanliuTotlNum==0)
		return;
	else{
		if(dispHuanliuIndex==0)
			dispHuanliuIndex=dispHuanliuTotlNum-1;
		else
			dispHuanliuIndex--;
	}
}
