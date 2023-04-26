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
const static char sign[]="[LCDKeyEvent]";



void dispInterFaceIndexFun(void);
//�ӿ���������
void dispInterFaceIndexAdd(void);
//�ӿ����Ƽ���
void dispInterFaceIndexReduc(void);


void	LCDDispIP(void);
void	LCDDispUart(void);
void	LCDDispMCUID(void);
void  LCDDispNetOffline(void);
void  offLineIndexAdd(void);
void  dispCinaName(uint8_t *buf);
void  dispChinaNameIndexLow(void);
void  dispChinaNameIndexAdd(void);
void  LDCDispMosbusInfo(void);
void  keyModbusCfgSure(void);
void  modbDevReadIndexLow(void);
void  modbDevReadIndexAdd(void);
void	modbErrDevReadIndexLow(void);
void	LDCDispErrMosbusInfo(void);
void  modbErrDevReadIndexAdd(void);
void	delModbusDevbyID_p(void);
void	LCDDispModbusGet(void);
void	LCDDispErrModbusGet(void);
void	offLineIndexLow(void);
void  dispPortIndexLow(void);
void  dispPortIndexFun(void);
void  rstPortIndexFun(void);
void  dispPortIndexAdd(void);
void  dispOutputNameIDType(void);
void  dispLevelState(char level);
bool levelRead(void);
void levelSet(char level);
void  lcdInputConfig(void);
void  dispInput(void);


void getInputTotalNum(void);
void 	dispInput(void);
void 	lastInput(void);
void 	nextInput(void);
void delOneInput(void);
void  dispoutputReadInterf(void);
//������ö�ȡinterface�ӿ���һ��
void  dispoutpReadInterfNext(void);
void  dispoutpReadInterfLast(void);
void  dispOutputRead(void);
void  getOutputTotalNum(void);
void  dispoutpReadNext(void);
void  dispoutpReadLast(void);
void	lcdOutputConfig(void);
void	dispoutConfigLast(void);
void	dispoutputNameInterf(void);
void	dispoutConfigNext(void);
void	delOneOutput(void);
void  getAnaTotalNum(void);
void  dispReadAna(void);
void  lastReadAna(void);
void  nextReadAna(void);




void dispName(void);
void dispSubName(void);
void nextSubName(void);
void lastSubName(void);
#ifndef     ANA_MASK
void lcdAnaConfig(void);
void  delOneAna(void);
#endif
//���������ܽӿ�
void  keyReturn(uint16_t keyAddr)
{
	  uint8_t *buf=NULL;
	  buf=rt_malloc(50);
	  bool ret;
	 // int nameLen=0;
		switch(keyAddr)
		{
			case	KEY_MODBUS_CFG_NAME_ADDR://�������������������ʾ����� ģ������  ��ʾ��1380
				//5A A5 1182 1380 C9CF BAA3 B9C8 D4AA BFC6 BCBC FFFF
        dispCinaName(buf);
				break;
			case	KEY_MODBUS_LASTNAME_ADDR:
				dispChinaNameIndexLow();
				dispCinaName(buf);
				break;
			case	KEY_MODBUS_NEXTNAME_ADDR:
				dispChinaNameIndexAdd();
				dispCinaName(buf);
				break;
			case	KEY_MODBUS_SURENAME_ADDR:// ��ʾ��1360
				break;	
			case  KEY_IP_READ_ADDR:
				LCDDispIP();
				break;
			case KEY_PORT_READ_ADDR:
				LCDDispUart();
				break;
			case KEY_MCUID_READ_ADDR:
				LCDDispMCUID();
				break;
			case KEY_SAVE_ADDR://����
				
				rt_kprintf("%sflash save OK\n",sign);
				stm32_flash_erase(FLASH_IP_SAVE_ADDR, sizeof(packFlash));//ÿ�β���128k�ֽ����� �洢ʱ����Ҫһ��洢
				stm32_flash_write(FLASH_IP_SAVE_ADDR,(uint8_t*)&packFlash,sizeof(packFlash));
				stm32_flash_write(FLASH_MODBUS_SAVE_ADDR,(uint8_t*)&sheet,sizeof(sheet));
				break;
			case KEY_RESET_ADDR://��λ
				rt_hw_cpu_reset();
				break;
			case KEY_MODBUS_CFG_WATCH_ADDR:

				LDCDispMosbusInfo();
				break;
			case KEY_MODBUS_CFG_SURE_ADDR:
				keyModbusCfgSure();
				break;
			case KEY_MODBUSDISP_LAST_ADDR:
				modbDevReadIndexLow();
				LDCDispMosbusInfo();
				break;

			case  KEY_MODBUSDISP_NEXT_ADDR:
				modbDevReadIndexAdd();
				LDCDispMosbusInfo();
			  break;
			

//////////////////////////////////////////////////

			case KEY_MODBUSDISP_ERRLAST_ADDR:
				modbErrDevReadIndexLow();
				LDCDispErrMosbusInfo();
				break;
			case KEY_MODBUSDISP_ERRNEXT_ADDR:
				modbErrDevReadIndexAdd();
				LDCDispErrMosbusInfo();
				break;
			case  KEY_MODBUSDISP_DEL_ADDR:
				delModbusDevbyID_p();
			  LCDDispModbusGet();
			  LDCDispMosbusInfo();
				break;
			case  KEY_NETERROR_ADDR:
				//rt_kprintf("%s��������\n",sign);
				LCDDispNetOffline();
				break;
			case  KEY_MODBUSERR_ADDR:{
				LCDDispErrModbusGet();
				LDCDispErrMosbusInfo();
				void  LCDDispErrMosbusState();
				LCDDispErrMosbusState();}
				break;
			case	NET_OFFLINE_LAST_ADDR:
				offLineIndexLow();
				LCDDispNetOffline();
				break;
			case  NET_OFFLINE_NEXT_ADDR:

				offLineIndexAdd();
				LCDDispNetOffline();
				break;
			case  KEY_SWITCH_INTERFACE_ADDR:
				rt_kprintf("%sKEY_SWITCH_INTERFACE_ADDR \n",sign);
				dispInterFaceIndexFun();
			  dispPortIndexFun();
				break;
			case KEY_SWITCH_PORT_ADDR:
				break;
			case KEY_SWITCH_LEVEL_ADDR:
				break;
			
			case KEY_SWITCH_SURE_ADDR:
				break;
			
			case KEY_SWITCH_RETURN_ADDR:
				break;
			

			case KEY_SWITCHINTERF_SURE_ADDR://do nothing
				break;
			case KEY_SWITCHINTERF_NEXT_ADDR:
				rt_kprintf("%sKEY_SWITCHINTERF_NEXT_ADDR \n",sign);
				dispInterFaceIndexAdd();
			  dispInterFaceIndexFun();
				rstPortIndexFun();
			  dispPortIndexFun();
			  dispOutputNameIDType();
			  ret=levelRead();
			  dispLevelState(ret);
			  levelSet(ret);
				break;
			case KEY_SWITCHINTERF_LAST_ADDR:
				rt_kprintf("%sKEY_SWITCHINTERF_LAST_ADDR \n",sign);
				dispInterFaceIndexReduc();
			  dispInterFaceIndexFun();
			  rstPortIndexFun();
			  dispPortIndexFun();
			  dispOutputNameIDType();
			  ret=levelRead();
			  dispLevelState(ret);
			  levelSet(ret);
				break;
			case KEY_SWITCHINTERF_RETURN_ADDR://
				
				break;
			case KEY_SWITCHPORT_SURE_ADDR:
				break;
			case KEY_SWITCHPORT_NEXT_ADDR:
				dispPortIndexAdd();
			  dispPortIndexFun();
			  dispOutputNameIDType();
				ret=levelRead();
			  dispLevelState(ret);
			  levelSet(ret);
				break;
			case KEY_SWITCHPORT_LAST_ADDR:
				dispPortIndexLow();
			  dispPortIndexFun();
			  dispOutputNameIDType();
				ret=levelRead();
			  dispLevelState(ret);
			  levelSet(ret);
				break;
			case KEY_SWITCHPORT_RETURN_ADDR:
				//dispOutputNameIDType();
				break;
			case KEY_SWITCHLEVEL_ON_ADDR:
				rt_kprintf("%s ON\n",sign);
			  dispLevelState(1);
			  levelSet(1);
				break;
			case KEY_SWITCHLEVEL_OFF_ADDR:
				rt_kprintf("%s OFF\n",sign);
			  dispLevelState(0);
			  levelSet(0);
				break;
			case KEY_SWITCHLEVEL_SURE_ADDR:
				break;
			case KEY_SWITCHLEVEL_RETURN_ADDR:
				break;
			///////////input_start///////////////
			case KEY_INPUTCFG_SURE_ADDR:
				lcdInputConfig();
				break;
			case KEY_INPUTCFG_LOOK_ADDR:
				getInputTotalNum();
				dispInput();
				break;
			case  KEY_INPUT_LAST_ADDR:
				lastInput();
				dispInput();
				break;
			case  KEY_INPUT_NEXT_ADDR:
				nextInput();
				dispInput();
				break;
			case  KEY_INPUT_DEL_ADDR:
				delOneInput();
			  getInputTotalNum();
				dispInput();
				break;
			case  KEY_INPUT_RETURN_ADDR:
				break;

			case KEY_OUTPUT_SURE_ADDR://
				lcdOutputConfig();
				break;
			case KEY_OUTPUT_LAST_ADDR:
				dispoutConfigLast();
				dispoutputNameInterf();
				break;
			case KEY_OUTPUT_NEXT_ADDR:
				dispoutConfigNext();
				dispoutputNameInterf();
				break;
			case KEY_OUTPUT_INTERFACE_ADDR:
				dispoutputNameInterf();
				break;
			case  KEY_OUTPUT_READ_LAST_ADDR:
				dispoutpReadLast();
			  dispOutputRead();
				break;
			case  KEY_OUTPUT_READ_NEXT_ADDR:
				dispoutpReadNext();
			  dispOutputRead();
				break;

			case  KEY_OUTPUT_READ_DELETE_ADDR:
			  delOneOutput();
				getOutputTotalNum();
//				dispoutputReadInterf();
			  dispOutputRead();
				break;
			case  KEY_OUTPUT_LOOK_ADDR:
				getOutputTotalNum();
				dispoutputReadInterf();
			  dispOutputRead();
			
				break;
			case  KEY_OUTPUT_READ_INTERFACE_ADDR://��ȥ�ӿ�
				dispoutputReadInterf();
				dispOutputRead();
				break;
			case  KEY_OUTPUT_READ_LAST_P_ADDR://�ӿڹ���  
				dispoutpReadInterfLast();
			  dispoutputReadInterf();
			  dispOutputRead();
				break;
			case  KEY_OUTPUT_READ_NEXT_P_ADDR:    //�ӿڹ��� 
				dispoutpReadInterfNext();
			  dispoutputReadInterf();
			  dispOutputRead();
				break;

			case  KEY_OUTPUT_READ_RETURN_P_ADDR:
				break;
			///////////output_end///////////////
//#define        KEY_ANA_SUBNAME_INTERFACE_ADDR     0x522C
//#define        KEY_ANA_SURE_ADDR     0x522E
	#ifndef     ANA_MASK
			case   KEY_ANA_LOOK_ADDR :
				getAnaTotalNum();
			  dispReadAna();
				break;
			case  KEY_ANA_NAME_INTERFACE_ADDR:
				dispName();
				break;
			case  KEY_ANA_SUBNAME_INTERFACE_ADDR:
				dispSubName();
				break;
			case  KEY_ANA_SURE_ADDR:
				lcdAnaConfig();
				break;
			case	KEY_ANA_LAST_ADDR:
				lastSubName();
				dispSubName();
				break;
			
			case  KEY_ANA_NEXT_ADDR:
				nextSubName();
				dispSubName();
				break;
			case   KEY_ANAREAD_LAST_ADDR:
				lastReadAna();
			  dispReadAna();
				break;
			case   KEY_ANAREAD_NEXT_ADDR:
				nextReadAna();
			  dispReadAna();
				break;
			case   KEY_ANAREAD_DEL_ADDR:
				delOneAna();
				getAnaTotalNum();
			  dispReadAna();
				break;
		#endif
		//���ؿ���end
		}
		rt_free(buf);
		buf=RT_NULL;
		
}




extern  modbusStru LCDInput;
extern  uint32_t   LCDInputTime;


void lcdCopyInputName(uint8_t *rec);
//MODEL_LEN
void lcdCopyInputID(uint8_t *rec);
void lcdCopyInputModel(uint8_t *rec);
void lcdCopyInputPort(uint8_t *rec);
void	lcdCopyOutputName(uint8_t *rec);
void	lcdCopyOutputID(uint8_t *rec);
void	lcdCopyOutputModel(uint8_t *rec);
void	lcdCopyOutputPort(uint8_t *rec);



void lcdCopyAnaID(uint8_t *rec);
//���������type��AnaInputLCD��
void lcdCopyAnaModel(uint8_t *rec);
//���������port��AnadigInputLCD��
void lcdCopyAnaPort(uint8_t *rec);
//���������time��AnaInput��
void lcdCopyAnaTime(uint8_t *rec);
//lcd ���������ý���
void LCDDispConfig(uint8_t *recBuf,int len)
{
	  
		if((uint16_t)((recBuf[0]<<8)+recBuf[1])!=LCD_HEAD){
				rt_kprintf("%s head err\n",sign);
				return;
		}			
		if((uint16_t)(recBuf[2]+2+1)!=len){//+2+1  ͷ������2 ���ݳ���1
			  rt_kprintf("%s lenth err\n",sign);
				return;
		}	
		if(recBuf[3]!=LCD_READ){//+2+1  ͷ������2 ���ݳ���1
			  rt_kprintf("%s 0x83 err\n",sign);
				return;
		}				
		uint16_t CMD_ADDR=(uint16_t)(recBuf[4]<<8)+recBuf[5];
		switch(CMD_ADDR){
			case  LOCAL_IP1_ADDR:
				packFlash.netIpFlash.localIp[0]=recBuf[8];
				break;
			case LOCAL_IP2_ADDR:
				packFlash.netIpFlash.localIp[1]=recBuf[8];
				break;       
			case LOCAL_IP3_ADDR:
				packFlash.netIpFlash.localIp[2]=recBuf[8];
				break;        
			case LOCAL_IP4_ADDR:
				packFlash.netIpFlash.localIp[3]=recBuf[8];
				break;        
			case PHY_PORT_ADDR:
				packFlash.netIpFlash.macaddr=recBuf[8];
				break;        
			case REMOTE_IP1_ADDR:
				packFlash.netIpFlash.remoteIp[0]=recBuf[8];
				break;       
			case REMOTE_IP2_ADDR:
				packFlash.netIpFlash.remoteIp[1]=recBuf[8];
				break;        
			case REMOTE_IP3_ADDR:
				packFlash.netIpFlash.remoteIp[2]=recBuf[8];
				break;        
			case REMOTE_IP4_ADDR:
				packFlash.netIpFlash.remoteIp[3]=recBuf[8];
				break;    		 
			case   GATEWAY_IP1_ADDR:
				packFlash.netIpFlash.gateway[0]=recBuf[8];
				break;
			case   GATEWAY_IP2_ADDR:
				packFlash.netIpFlash.gateway[1]=recBuf[8];
				break;
			case   GATEWAY_IP3_ADDR:
				packFlash.netIpFlash.gateway[2]=recBuf[8];
				break;
			case   GATEWAY_IP4_ADDR:
				packFlash.netIpFlash.gateway[3]=recBuf[8];
				break;

			case REMOTE_PORT_ADDR:
				packFlash.netIpFlash.remotePort=(uint16_t)(recBuf[9]<<8)+recBuf[10];
				break;   		 

			case PORT1_ADDR:
				packFlash.uartBps[0]=(uint32_t)(recBuf[7]<<24)+(uint32_t)(recBuf[8]<<16)+(uint32_t)(recBuf[9]<<8)+recBuf[10];
				break;     		 			
			case PORT2_ADDR:
				packFlash.uartBps[1]=(uint32_t)(recBuf[7]<<24)+(uint32_t)(recBuf[8]<<16)+(uint32_t)(recBuf[9]<<8)+recBuf[10];
				break;     		 			
			case PORT3_ADDR:
				packFlash.uartBps[2]=(uint32_t)(recBuf[7]<<24)+(uint32_t)(recBuf[8]<<16)+(uint32_t)(recBuf[9]<<8)+recBuf[10];
				break;     		 			
			case PORT4_ADDR:
				packFlash.uartBps[3]=(uint32_t)(recBuf[7]<<24)+(uint32_t)(recBuf[8]<<16)+(uint32_t)(recBuf[9]<<8)+recBuf[10];
				break;     		 			

			//MCUID
			case MCUID_ADDR:
				for(int i=0;i<ACUID_LEN+1;i++){
					packFlash.acuId[i]=recBuf[7+i];
					if((recBuf[7+i]==0xff)||(recBuf[7+i]==0)){
							packFlash.acuId[i]=0;
							break;
					}
				}
				break;         			

			case MODBUS_CFG_ID_ADDR:
				for(int i=0;i<20;i++){
					LCDInput.ID[i]=recBuf[7+i];
					if((recBuf[7+i]==0xff)||(recBuf[7+i]==0)){
							LCDInput.ID[i]=0;
							break;
					}
				}
				break;    		
			case MODBUS_CFG_SORT_ADDR:
				//LCDInput.
				break; 		
			case MODBUS_CFG_TYPE_ADDR:
				for(int i=0;i<8;i++){
					LCDInput.model[i]=recBuf[7+i];
					if((recBuf[7+i]==0xff)||(recBuf[7+i]==0)){
							LCDInput.model[i]=0;
							break;
					}
				}
				break;  		
			case MODBUS_CFG_PORT_ADDR:
				LCDInput.useUartNum=(uartEnum)recBuf[8]-1;
				break;  		
			case MODBUS_CFG_ADDR_ADDR:
				LCDInput.slaveAddr=recBuf[8];
				break;  		
			case MODBUS_CFG_TIME_ADDR:
				LCDInputTime=(uint32_t)(recBuf[7]<<24)+(uint32_t)(recBuf[8]<<16)+(uint32_t)(recBuf[9]<<8)+recBuf[10];
				break; 		
			case MODBUS_CFG_NAME2_ADDR:
				break;	
			case KEY_ADDR:
				keyReturn((uint16_t)(recBuf[7]<<8)+recBuf[8]);
				break;
			case DISP_INPUTCFG_NAME_ADDR:
				lcdCopyInputName(recBuf);
				break;
			case DISP_INPUTCFG_ID_ADDR:
				lcdCopyInputID(recBuf);
				break;
			case DISP_INPUTCFG_TYPE_ADDR:
				lcdCopyInputModel(recBuf);
				break;
			case DISP_INPUTCFG_PORT_ADDR:
				lcdCopyInputPort(recBuf);
				break;
			case DISP_OUTPUT_NAME_ADDR:
				lcdCopyOutputName(recBuf);
				break;
			case DISP_OUTPUT_ID_ADDR:
				lcdCopyOutputID(recBuf);
				break;

			case DISP_OUTPUT_TYPE_ADDR:
				lcdCopyOutputModel(recBuf);
				break;
			case DISP_OUTPUT_PORT_ADDR:
				lcdCopyOutputPort(recBuf);
				break;
#ifndef     ANA_MASK
			case DISP_ANA_ID_ADDR:
				lcdCopyAnaID(recBuf);
				break;
			case DISP_ANA_TYPE_ADDR:
				lcdCopyAnaModel(recBuf);
				break;
			case DISP_ANA_PORT_ADDR:
				lcdCopyAnaPort(recBuf);
				break;
			case DISP_ANA_TIME_ADDR:
				lcdCopyAnaTime(recBuf);
				break;
#endif
		}
}

