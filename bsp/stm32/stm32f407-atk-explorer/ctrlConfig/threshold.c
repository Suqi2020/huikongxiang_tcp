#include <board.h>
//��ֵ���òο� �������modbus��������V0.4.doc���� 8����ֵ���ã���Ҫ��modbus��ģ�⴫�����������ã�



const static char sign[]="[threshold]";



//������������²��ܵõ���ֵ  ��workFlagΪtrue
void printfThresholdList()
{
	  int i;
	#ifndef     ANA_MASK
		for(int j=0;j<ANALOG_NUM;j++){//��һ�� �ҵ� ��ʪ�ȵ�ģ����ֵ
			  if(sheet.analog[j].workFlag==RT_TRUE){
						//if(rt_strcmp(sheet.analog[j].name,analogName[i])==0){
								rt_kprintf("%s threshold ",sign);
								rt_kprintf("%s ",sheet.analog[j].name);
								rt_kprintf("%s ",sheet.analog[j].ID);
								rt_kprintf("2 ");
								rt_kprintf("%s ",sheet.analog[j].subName);
							  if(sheet.analog[j].subName==1){//�¶�
										
										rt_kprintf("%0.2f ",sheet.analogTempHum.tempLowLimit);
									  rt_kprintf("%0.2f \n",sheet.analogTempHum.tempUpLimit);
								}
								else if(sheet.analog[j].subName==2){//ʪ��
										
										rt_kprintf("%0.2f ",sheet.analogTempHum.humLowLimit);
									  rt_kprintf("%0.2f \n",sheet.analogTempHum.humUpLimit);

								}
						}
				
		}
		#endif
		
		for(i=0;i<CIRCULA_485_NUM;i++){
				if(sheet.cirCula[i].workFlag==RT_TRUE){//�ҵ��������豸  ������Ҫ������ӡ����
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CIRCULA]);
						rt_kprintf("%s ",sheet.cirCula[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusCircul[i].cirCurALowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCircul[i].cirCurAUpLimit);
	
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CIRCULA]);
						rt_kprintf("%s ",sheet.cirCula[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("2 ");
						rt_kprintf("%0.2f ",sheet.modbusCircul[i].cirCurBLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCircul[i].cirCurBUpLimit);
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CIRCULA]);
						rt_kprintf("%s ",sheet.cirCula[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("3 ");
						rt_kprintf("%0.2f ",sheet.modbusCircul[i].cirCurCLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCircul[i].cirCurCUpLimit);
						rt_kprintf("\n");
				}
				
		}

		for(i=0;i<PARTDISCHAG_485_NUM;i++){
				if(sheet.partDischag[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].amplitudeALowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].amplitudeAUpLimit);
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("2 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].freqALowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].freqAUpLimit);
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("3 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].dischargeALowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].dischargeAUpLimit);


						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("4 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].amplitudeBLowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].amplitudeBUpLimit);
						
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("5 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].freqBLowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].freqBUpLimit);
						
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("6 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].dischargeBLowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].dischargeBUpLimit);	


						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("7 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].amplitudeCLowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].amplitudeCUpLimit);	
						
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("8 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].freqCLowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].freqCUpLimit);	
						
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PARTDISCHAG]);
						rt_kprintf("%s ",sheet.partDischag[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("9 ");
						rt_kprintf("%u ",sheet.modbusPartDisChg[i].dischargeCLowLimit);
						rt_kprintf("%u \n",sheet.modbusPartDisChg[i].dischargeCUpLimit);
						rt_kprintf("\n");
				}
		}
		for(i=0;i<PRESSSETTL_485_NUM;i++){
				if(sheet.pressSetl[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PRESSSETTL]);
						rt_kprintf("%s ",sheet.pressSetl[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusPreSettl[i].tempLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusPreSettl[i].tempUpLimit);
					
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[PRESSSETTL]);
						rt_kprintf("%s ",sheet.pressSetl[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("2 ");
						rt_kprintf("%0.2f ",sheet.modbusPreSettl[i].heightLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusPreSettl[i].heightUpLimit);
						rt_kprintf("\n");

				}
		}

		for(i=0;i<THREEAXIS_485_NUM;i++){
				if(sheet.threeAxiss[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[THREEAXIS]);
						rt_kprintf("%s ",sheet.threeAxiss[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusThreAxis[i].tempLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusThreAxis[i].tempUpLimit);
		
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[THREEAXIS]);
						rt_kprintf("%s ",sheet.threeAxiss[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("2 ");
						rt_kprintf("%0.2f ",sheet.modbusThreAxis[i].accXLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusThreAxis[i].accXUpLimit);
	
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[THREEAXIS]);
						rt_kprintf("%s ",sheet.threeAxiss[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("3 ");
						rt_kprintf("%0.2f ",sheet.modbusThreAxis[i].accYLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusThreAxis[i].accYUpLimit);

						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[THREEAXIS]);
						rt_kprintf("%s ",sheet.threeAxiss[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("4 ");
						rt_kprintf("%0.2f ",sheet.modbusThreAxis[i].accZLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusThreAxis[i].accZUpLimit);
						rt_kprintf("\n");
				}

		}

#ifdef  USE_4GAS

		for(i=0;i<CH4_485_NUM;i++){
				if(sheet.ch4[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CH4]);
						rt_kprintf("%s ",sheet.ch4[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusCh4[i].ch4LowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCh4[i].ch4UpLimit);
					  rt_kprintf("\n");
				}
		}
		for(i=0;i<O2_485_NUM;i++){
				if(sheet.ch4[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[O2]);
						rt_kprintf("%s ",sheet.o2[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusO2[i].o2LowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusO2[i].o2UpLimit);
				
						rt_kprintf("\n");
				}
		}
		for(i=0;i<H2S_485_NUM;i++){
				if(sheet.ch4[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[H2S]);
						rt_kprintf("%s ",sheet.h2s[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusH2s[i].h2sLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusH2s[i].h2sUpLimit);
				
				    rt_kprintf("\n");
				}
		}
		for(i=0;i<CO_485_NUM;i++){
				if(sheet.co[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CO]);
						rt_kprintf("%s ",sheet.co[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusCo[i].coLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCo[i].coUpLimit);
					  rt_kprintf("\n");
				}
				
		}
#endif
		for(i=0;i<TEMPHUM_485_NUM;i++){
				if(sheet.tempHum[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[TEMPHUM]);
						rt_kprintf("%s ",sheet.tempHum[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusTempHum[i].tempLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusTempHum[i].tempUpLimit);
					  rt_kprintf("\n");
				}
				//rt_kprintf("\n");
		}
		for(i=0;i<WATERDEPTH_485_NUM;i++){
				if(sheet.waterDepth[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[WATERDEPTH]);
						rt_kprintf("%s ",sheet.waterDepth[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusWaterDepth[i].depthLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusWaterDepth[i].depthUpLimit);
					  rt_kprintf("\n");
				}
				//rt_kprintf("\n");
		}
		for(i=0;i<CRACKMETER_485_NUM;i++){
				if(sheet.crackMeter[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CRACKMETER]);
						rt_kprintf("%s ",sheet.crackMeter[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%0.2f ",sheet.modbusCrackMeter[i].tempLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCrackMeter[i].tempUpLimit);
					  rt_kprintf("\n");
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[CRACKMETER]);
						rt_kprintf("%s ",sheet.crackMeter[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("2 ");
						rt_kprintf("%0.2f ",sheet.modbusCrackMeter[i].distancLowLimit);
						rt_kprintf("%0.2f \n",sheet.modbusCrackMeter[i].distancUpLimit);
					  rt_kprintf("\n");
				}
				//rt_kprintf("\n");
		}
		for(i=0;i<COVER_485_NUM;i++){
				if(sheet.cover[i].workFlag==RT_TRUE){//�ҵ���ͬID��
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[COVER]);
						rt_kprintf("%s ",sheet.cover[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("1 ");
						rt_kprintf("%d ",sheet.modbusCover[i].inclineLowLimit);
						rt_kprintf("%d \n",sheet.modbusCover[i].inclineUpLimit);
					  rt_kprintf("\n");
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[COVER]);
						rt_kprintf("%s ",sheet.cover[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("2 ");
						rt_kprintf("%d ",sheet.modbusCover[i].switch2LowLimit);
						rt_kprintf("%d \n",sheet.modbusCover[i].switch2UpLimit);
					  rt_kprintf("\n");
					
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[COVER]);
						rt_kprintf("%s ",sheet.cover[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("3 ");
						rt_kprintf("%d ",sheet.modbusCover[i].vibrationLowLimit);
						rt_kprintf("%d \n",sheet.modbusCover[i].vibrationUpLimit);
					  rt_kprintf("\n");
						rt_kprintf("%s threshold ",sign);
						rt_kprintf("%s ",modbusName[COVER]);
						rt_kprintf("%s ",sheet.cover[i].ID);
						rt_kprintf("1 ");
						rt_kprintf("4 ");
						rt_kprintf("%d ",sheet.modbusCover[i].switch1LowLimit);
						rt_kprintf("%d \n",sheet.modbusCover[i].switch1UpLimit);
					  rt_kprintf("\n");
				}
				//rt_kprintf("\n");
		}
		//��ӡmodbus���õ���ֵ
}
//��modbus��������֮ͬ������ �����ж�ID����Ҫ�ж���ѡ��
//ģ�⴫������ֵ����
#ifndef     ANA_MASK
bool  analogThresholdConfig(int num,char *ID,int sensorSubName,float upLimit,float lowLimit)
{ 
		switch(num)
		{
			case  0://modbus ��ʪ��
				for(int i=0;i<ANALOG_NUM;i++){//
						if(rt_strcmp(sheet.analog[i].ID,ID)==0){//�Ⱥ˶�ID
								if(sheet.analog[i].subName==sensorSubName){
									 if(sensorSubName==1){//�¶�
											sheet.analogTempHum.tempLowLimit=lowLimit;
											sheet.analogTempHum.tempUpLimit=upLimit;
											return true;
									 }
									 else if(sensorSubName==2){//ʪ��
											sheet.analogTempHum.humLowLimit=lowLimit;
											sheet.analogTempHum.humUpLimit =upLimit;	
											return true;
									 }
								}
						}
				}
			break;
		}
		return false;
}
#endif
//modbus�豸  ��������Ϊ ���������� ID�� ����������  ������  ������
//modbus��������ֵ����
bool   modbusThresholdConfig(int num,char *ID,int sensorSubName,float upLimit,float lowLimit)
{
	  int i=0;
		switch(num)
		{
			case CIRCULA:
				for(i=0;i<CIRCULA_485_NUM;i++){
						if(rt_strcmp(sheet.cirCula[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusCircul[i].cirCurAUpLimit  = upLimit;
									  sheet.modbusCircul[i].cirCurALowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusCircul[i].cirCurBUpLimit  = upLimit;
										sheet.modbusCircul[i].cirCurBLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==3){
										sheet.modbusCircul[i].cirCurCUpLimit  = upLimit;
										sheet.modbusCircul[i].cirCurCLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
				break;
			case PARTDISCHAG:
				for(i=0;i<PARTDISCHAG_485_NUM;i++){
						if(rt_strcmp(sheet.partDischag[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusPartDisChg[i].amplitudeAUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].amplitudeALowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusPartDisChg[i].freqAUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].freqALowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==3){
										sheet.modbusPartDisChg[i].dischargeAUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].dischargeALowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==4){
										sheet.modbusPartDisChg[i].amplitudeBUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].amplitudeBLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==5){
										sheet.modbusPartDisChg[i].freqBUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].freqBLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==6){
										sheet.modbusPartDisChg[i].dischargeBUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].dischargeBLowLimit = lowLimit;
									  return  true;
								}
								if(sensorSubName==7){
										sheet.modbusPartDisChg[i].amplitudeCUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].amplitudeCLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==8){
										sheet.modbusPartDisChg[i].freqCUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].freqCLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==9){
										sheet.modbusPartDisChg[i].dischargeCUpLimit  = upLimit;
									  sheet.modbusPartDisChg[i].dischargeCLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
				break;
			case PRESSSETTL:
				for(i=0;i<PRESSSETTL_485_NUM;i++){
						if(rt_strcmp(sheet.pressSetl[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusPreSettl[i].tempUpLimit  = upLimit;
									  sheet.modbusPreSettl[i].tempLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusPreSettl[i].heightUpLimit = upLimit;
										sheet.modbusPreSettl[i].heightLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
				break;
			case THREEAXIS:
				for(i=0;i<THREEAXIS_485_NUM;i++){
						if(rt_strcmp(sheet.threeAxiss[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusThreAxis[i].tempUpLimit  = upLimit;
									  sheet.modbusThreAxis[i].tempLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusThreAxis[i].accXUpLimit  = upLimit;
										sheet.modbusThreAxis[i].accXLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==3){
										sheet.modbusThreAxis[i].accYUpLimit  = upLimit;
										sheet.modbusThreAxis[i].accYLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==4){
										sheet.modbusThreAxis[i].accZUpLimit  = upLimit;
										sheet.modbusThreAxis[i].accZLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
				break;
#ifdef  USE_4GAS
			case CH4:
				for(i=0;i<CH4_485_NUM;i++){
						if(rt_strcmp(sheet.ch4[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusCh4[i].ch4UpLimit  = upLimit;
									  sheet.modbusCh4[i].ch4LowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
			case O2:
				for(i=0;i<O2_485_NUM;i++){
						if(rt_strcmp(sheet.o2[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusO2[i].o2UpLimit  = upLimit;
									  sheet.modbusO2[i].o2LowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
			case H2S:
				for(i=0;i<H2S_485_NUM;i++){
						if(rt_strcmp(sheet.h2s[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusH2s[i].h2sUpLimit  = upLimit;
									  sheet.modbusH2s[i].h2sLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
			case CO:
				for(i=0;i<CO_485_NUM;i++){
						if(rt_strcmp(sheet.co[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusCo[i].coUpLimit  = upLimit;
									  sheet.modbusCo[i].coLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
#endif
			case TEMPHUM:
				for(i=0;i<TEMPHUM_485_NUM;i++){
						if(rt_strcmp(sheet.tempHum[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusTempHum[i].tempUpLimit  = upLimit;
									  sheet.modbusTempHum[i].tempLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusTempHum[i].humUpLimit  = upLimit;
									  sheet.modbusTempHum[i].humLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
			case WATERDEPTH:
				for(i=0;i<WATERDEPTH_485_NUM;i++){
						if(rt_strcmp(sheet.waterDepth[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusWaterDepth[i].depthUpLimit  = upLimit;
									  sheet.modbusWaterDepth[i].depthLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
			default:
				
			case CRACKMETER:
				for(i=0;i<CRACKMETER_485_NUM;i++){
						if(rt_strcmp(sheet.crackMeter[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusCrackMeter[i].tempUpLimit  = upLimit;
									  sheet.modbusCrackMeter[i].tempLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusCrackMeter[i].distancUpLimit  = upLimit;
									  sheet.modbusCrackMeter[i].distancLowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
				
				
			case COVER:
				for(i=0;i<COVER_485_NUM;i++){
						if(rt_strcmp(sheet.cover[i].ID,ID)==0){//�ҵ���ͬID��
								if(sensorSubName==1){
										sheet.modbusCover[i].inclineUpLimit  = upLimit;
									  sheet.modbusCover[i].inclineLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==2){
										sheet.modbusCover[i].switch2UpLimit  = upLimit;
									  sheet.modbusCover[i].switch2LowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==3){
										sheet.modbusCover[i].vibrationUpLimit  = upLimit;
									  sheet.modbusCover[i].vibrationLowLimit = lowLimit;
									  return  true;
								}
								else if(sensorSubName==4){
										sheet.modbusCover[i].switch1UpLimit  = upLimit;
									  sheet.modbusCover[i].switch1LowLimit = lowLimit;
									  return  true;
								}
								else
										return  false;
						}
				}
			  break;
				rt_kprintf("%s ERR:modbusThresholdConfig %d\n",sign,num);
				break;
		}
		return false;
}
/*
����(threshold+����+ID+����(1-modbus 2-analog)+ѡ��(1.2.3 ֻ��һ��ʱ������Ϊ1)+��ֵ����+��ֵ����)(��ֵΪ0����0xffffffffʱ����ֵ������)
threshold��ʪ�� GYNJLXSD000000164 1 1 10 80
��ֵ�����������
threshold���̶�ͷ��
���ƣ�modbus��ģ�⴫��������
���ͣ�(1-modbus 2-analog)  Ϊ0��255ʱ��ɾ����Ӧ����ֵ����
ѡ�����������ֻ��һ�������ֵΪ1���ж�����������ε���(1.2.3)����
     ģ����ʪ�ȣ�1-�¶�  2-ʪ��
	   modbus��ʪ�ȣ�1-�¶� 2-ʪ��
     modbus�����ƣ�1-�¶� 2-x������ٶ� 3-y������ٶ� 4-z������ٶ�
     modbus�����ǣ�1-�¶� 2-�߶�
     modbus������ 1-cirCurA 2-cirCurB 3-cirCurC
     modbus�ַţ�1-pdA 2-freqA 3-dischargeDataA            
				   4-pdB 5-freqB 6-dischargeDataB				
7-pdC 8-freqC 9-dischargeDataC 
��ֵ���ޣ�0-99999999(Ϊ0��ֵ������)
��ֵ���ޣ�0-99999999(Ϊ0��ֵ������)

*/
//��������ģ���485������ֵ����
static void threshold(int argc,char *argv[])
{
		float uplimit ;
		float lowlimit ;
		int sensorType;
		int sensorSubName;
	  if(0==rt_strcmp((char *)"list", argv[1])){
				printfThresholdList();
				return;
		}
		if(argc!=7){
				goto ERR;
		}
		sensorType= atoi32(argv[3],10);
		sensorSubName=atoi32(argv[4],10);
		if((sensorType!=1)&&(sensorType!=2)){
				rt_kprintf("%ssensorType argv[3] should be 1 or 2\n",sign);
			  goto ERR;
		}
		if(sensorSubName>100){
				rt_kprintf("%ssensorSubName argv[4] should be <100\n",sign);
			  goto ERR;
		}
		uplimit  = atof(argv[6]);
		lowlimit = atof(argv[5]);
		if(sensorType==1){//modbus������
			  int i=0;
			  for(i=0;i<MODBUS_NUM;i++){
						if(rt_strcmp(argv[1],modbusName[i])==0){
								if(true==modbusThresholdConfig(i,argv[2],sensorSubName,uplimit,lowlimit)){
									  rt_kprintf("%sthreshold mb cfg OK\n",sign);
										return;
								}
								else{
										goto ERR;
								}
						}
				}
		}
#ifndef     ANA_MASK
		if(sensorType==2){//analog������
			  int i=0;
			  for(i=0;i<ANALOGNAME_NUM;i++){
						if(rt_strcmp(argv[1],analogName[i])==0){
								if(true==analogThresholdConfig(i,argv[2],sensorSubName,uplimit,lowlimit)){
										rt_kprintf("%sthreshold ana cfg OK\n",sign);
										return;
								}
								else{
										goto ERR;
								}
						}
				}	
		}
#endif
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[threshold ��ʪ�� GYNJLXSD000000164 1 1 10 80]\n",sign);
		rt_kprintf("%s[��ֵ������Ϊ0ʱ�� ��������ֵ]\n",sign);

}
MSH_CMD_EXPORT(threshold,threshold config);

