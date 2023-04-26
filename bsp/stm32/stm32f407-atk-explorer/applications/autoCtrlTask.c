#include   "NetJsonDataTask.h"
#include   "board.h"

const static char sign[]="[autoCtrlTask]";


//ai�������ж���ֵ�����  ��λ��Ӧ��flag
void aiThresholdOutSetFlag()
{
//�ڸ���analog��������ȡ����ʱ���ж����
}

//�Զ������߼��Ĵ���
//1����ֵ���ж� �Լ���λ���  �������������豸
//2�����ݱ����ִ�е�������Ʊ��
//3����������Ǹ�ָ�� ʵ�ʸı����ָ��ָ��������3V3 5V 12V DO�����
void  autoCtrlRun()
{
		volatile int i,j,k;
	  bool inputflag;
		for(i=0;i<CRTL_TOTAL_NUM;i++){
			  //rt_kprintf("%srun %d\n",sign,i);
			  inputflag=true;;
				if(sheet.autoctrl[i].workFlag==true){
						for(j=0;j<CRTL_IN_NUM;j++){
								if((sheet.autoctrl[i].input[j].flag!=NULL)&&((uint32_t)(uint32_t*)(sheet.autoctrl[i].input[j].flag)!=0xFFFFFFFF)){//ָ��ȫ����Ϊ��
										if(*sheet.autoctrl[i].input[j].flag==false){//�����һ����ǲ����� ��������Ϊ���б�ǵĹ�ϵ���룩
												//rt_kprintf("%s ctrl[%d] input[%d] flag not ok \n",sign,i+1,j+1);
												inputflag=false;//��һ�����������Ͼͱ��false
											  break;
										}
										//else
											//rt_kprintf("%s ctrl[%d]  input[%d] flag ok\n",sign,i+1,j+1);
								}
						}
						if(inputflag==true){//��������ȫ��������  ִ����� �˴���������λ���λ  ��Ҫ����һ�������е���
							  for(k=0;k<CRTL_OUT_NUM;k++){
										if((sheet.autoctrl[i].output[k].flag!=NULL)&&((uint32_t)(uint32_t*)(sheet.autoctrl[i].output[k].flag)!=0xFFFFFFFF)){//ָ�벻Ϊ��
												*sheet.autoctrl[i].output[k].flag=true;//ִ��  ����ָ��ִ�е�flag���
											  //rt_kprintf("%s ctrl[%d]  output[%d] flag is set \n",sign,i+1,k+1);
										}
//										else
//												*sheet.autoctrl[i].output[k].flag=false;
								}
						}
						
				}
				
		}
}

//digital output �ø�  
//���� ͨ����
void digOutputONFun(char num)
{
	switch(num)
	{
			case 0:IOOUT1_ON;break;
			case 1:IOOUT2_ON;break;
			case 2:IOOUT3_ON;break;
			case 3:IOOUT4_ON;break;
			case 4:IOOUT5_ON;break;
			case 5:IOOUT6_ON;break;
			case 6:IOOUT7_ON;break;
			case 7:IOOUT8_ON;break;
	}
}
//digital output �õ�  
//���� ͨ����
void digOutputOFFFun(char num)
{
	switch(num)
	{
			case 0:IOOUT1_OFF;break;
			case 1:IOOUT2_OFF;break;
			case 2:IOOUT3_OFF;break;
			case 3:IOOUT4_OFF;break;
			case 4:IOOUT5_OFF;break;
			case 5:IOOUT6_OFF;break;
			case 6:IOOUT7_OFF;break;
			case 7:IOOUT8_OFF;break;
	}
}
//V3.3 output �ø�  
//���� ͨ����
void v33OutputONFun(char num)
{
	switch(num)
	{
			case 0:SPAKER1_ON;break;
			case 1:SPAKER3_ON;break;
	}
}
//V3.3 output �õ� 
//���� ͨ����
void v33OutputOFFFun(char num)
{
	switch(num)
	{
			case 0:SPAKER1_OFF;break;
			case 1:SPAKER3_OFF;break;
	}
}
//V5 output �ø�  
//���� ͨ����
void v5OutputONFun(char num)
{
	switch(num)
	{
			case 0:SPAKER2_ON;break;
			case 1:SPAKER4_ON;break;
	}
}
//V5 output �õ�  
//���� ͨ����
void v5OutputOFFFun(char num)
{
	switch(num)
	{
			case 0:SPAKER2_OFF;break;
			case 1:SPAKER4_OFF;break;
	}
}


//V12 output �ø�  
//���� ͨ����
void v12OutputONFun(char num)
{
	switch(num)
	{
			case 0:RELAY1_ON;break;
			case 1:RELAY2_ON;break;
			case 2:RELAY3_ON;break;
			case 3:RELAY4_ON;break;

	}
}
//V12 output �õ�  
//���� ͨ����
void v12OutputOFFFun(char num)
{
	switch(num)
	{
			case 0:RELAY1_OFF;break;
			case 1:RELAY2_OFF;break;
			case 2:RELAY3_OFF;break;
			case 3:RELAY4_OFF;break;

	}
}

bool digOutputReadFun(char num)
{
	switch(num)
	{
			case 0:return IOOUT1_READ;
			case 1:return IOOUT2_READ;
			case 2:return IOOUT3_READ;
			case 3:return IOOUT4_READ;
			case 4:return IOOUT5_READ;
			case 5:return IOOUT6_READ;
			case 6:return IOOUT7_READ;
			case 7:return IOOUT8_READ;
	}
	return false;
}

bool v33OutputReadFun(char num)
{
	switch(num)
	{
			case 0:return SPAKER1_READ;
			case 1:return SPAKER3_READ;
	}
	return false;
}

bool v5OutputReadFun(char num)
{
	switch(num)
	{
			case 0:return SPAKER2_READ;
			case 1:return SPAKER4_READ;
	}
	return false;
}
bool v12OutputReadFun(char num)
{
	switch(num)
	{
			case 0:return RELAY1_READ;
			case 1:return RELAY2_READ;
			case 2:return RELAY3_READ;
			case 3:return RELAY4_READ;

	}
	return false;
}
//�������õ�outputIO�ĸߵ͵�ƽ��Ч�������ϵ��ʼ��IO��ƽ		
//�ߵ�ƽ��Ч������� �����ʼ��Ϊ��
//�͵�ƽ��Ч�����  �����ʼ��Ϊ��

void  outIOInit()
{
		int k,z;
		for(int j=0;j<CRTL_TOTAL_NUM;j++){
				for(k=0;k<CRTL_OUT_NUM;k++){
						for(z=0;z<DO_NUM;z++){
								if(sheet.autoctrl[j].output[k].flag==&inpoutpFlag.digOutput[z].lowFlag){
										digOutputONFun(z);//Ĭ�ϵ���Ч  ��ʼ���ߵ�
										rt_kprintf("%s digoutput on %d\n",sign,z);
								}
								if(sheet.autoctrl[j].output[k].flag==&inpoutpFlag.digOutput[z].upFlag){
										digOutputOFFFun(z);//Ĭ�ϸ���Ч  ��ʼ���͵�
										rt_kprintf("%s digoutput off %d\n",sign,z);
								}
						}
						for(z=0;z<V33O_NUM;z++){
								if(sheet.autoctrl[j].output[k].flag==&inpoutpFlag.v33Output[z].lowFlag){
										v33OutputONFun(z);//Ĭ�ϵ���Ч  ��ʼ���ߵ�
										rt_kprintf("%s v33output on %d\n",sign,z);
								}
								if(sheet.autoctrl[j].output[k].flag==&inpoutpFlag.v33Output[z].upFlag){
										v33OutputOFFFun(z);//Ĭ�ϸ���Ч  ��ʼ���͵�
										rt_kprintf("%s v33output off %d\n",sign,z);
								}
						}
						for(z=0;z<V5O_NUM;z++){
								if(sheet.autoctrl[j].output[k].flag==&inpoutpFlag.v5Output[z].lowFlag){
										v5OutputONFun(z);//Ĭ�ϵ���Ч  ��ʼ���ߵ�
										rt_kprintf("%s v5output on %d\n",sign,z);
								}
								if(sheet.autoctrl[j].output[k].flag==&inpoutpFlag.v5Output[z].upFlag){
										v5OutputOFFFun(z);//Ĭ�ϸ���Ч  ��ʼ���͵�
										rt_kprintf("%s v5output off %d\n",sign,z);
								}
						}
						for(z=0;z<V12O_NUM;z++){
								if(sheet.autoctrl[j].output[z].flag==&inpoutpFlag.v12Output[z].lowFlag){
										v12OutputONFun(z);//Ĭ�ϵ���Ч  ��ʼ���ߵ�
										rt_kprintf("%s v12output on %d\n",sign,z);
								}
								if(sheet.autoctrl[j].output[z].flag==&inpoutpFlag.v12Output[z].upFlag){
										v12OutputOFFFun(z);//Ĭ�ϸ���Ч  ��ʼ���͵�
										rt_kprintf("%s v12output off %d\n",sign,z);
								}
						}
				}
		}
}




//�������õ�outputIO�ĸߵ͵�ƽ��Ч�������ϵ��ʼ��IO��ƽ		
//����Ҫ��ʼ�� ���ⲿ�������տ��ؿ�����
/*
void  inIOInit()
{
		int k,z;
		for(int j=0;j<CRTL_TOTAL_NUM;j++){
				for(k=0;k<CRTL_IN_NUM;k++){
						for(z=0;z<DI_NUM;z++){
								if(sheet.autoctrl[j].input[k].flag==&inpoutpFlag.digInput[z].lowFlag){
										digInputONFun(z);//Ĭ�ϵ���Ч  ��ʼ���ߵ�
										rt_kprintf("%s diginput on %d\n",sign,z);
								}
								if(sheet.autoctrl[j].input[k].flag==&inpoutpFlag.digInput[z].upFlag){
										digInputOFFFun(z);//Ĭ�ϸ���Ч  ��ʼ���͵�
										rt_kprintf("%s diginput off %d\n",sign,z);
								}
						}
				}
		}
}
*/
uint8_t doUpLowFlag[DO_NUM]={0};  //��Ǹ�����ֵΪ���жϵ͵�ƽ���Ǹߵ�ƽ��Ч�����ʧЧʱ��ִ����Ӧ����
uint8_t v33oUpLowFlag[V33O_NUM]={0};
uint8_t v5oUpLowFlag[V5O_NUM]={0};
uint8_t v12oUpLowFlag[V12O_NUM]={0};
//�����ƽִ��
void  ctrlOutSetIO()
{
			int i;
			for(i=0;i<DO_NUM;i++){
					if(inpoutpFlag.digOutput[i].lowFlag==true){
							digOutputOFFFun(i);
						  //rt_kprintf("%s ctrlOutSetIO DO off %d\n",sign,i);
						  doUpLowFlag[i]=1;
						  inpoutpFlag.digOutput[i].lowFlag=false;//zִ�������� ��һ�������ж�ִ������IO
					}
					else{
							if(doUpLowFlag[i]==1){
									digOutputONFun(i);
								 // rt_kprintf("%s DO on %d\n",sign,i);
							}
					}
					if(inpoutpFlag.digOutput[i].upFlag==true){
							digOutputONFun(i);
						  //rt_kprintf("%s ctrlOutSetIO DO on %d\n",sign,i);
						  doUpLowFlag[i]=2;
						  inpoutpFlag.digOutput[i].upFlag=false;
					}
					else{
							if(doUpLowFlag[i]==2){
									digOutputOFFFun(i);
								  //rt_kprintf("%s DO off %d\n",sign,i);
							}
					}
			}

			for(i=0;i<V33O_NUM;i++){
					if(inpoutpFlag.v33Output[i].lowFlag==true){
							v33OutputOFFFun(i);
						  //rt_kprintf("%s ctrlOutSetIO v33O off %d\n",sign,i);
						  v33oUpLowFlag[i]=1;
						  inpoutpFlag.v33Output[i].lowFlag=false;
					}
					else{
							if(v33oUpLowFlag[i]==1){
									v33OutputONFun(i);
							}
					}
					if(inpoutpFlag.v33Output[i].upFlag==true){
							v33OutputONFun(i);
						  //rt_kprintf("%s ctrlOutSetIO v33O on %d\n",sign,i);
						  v33oUpLowFlag[i]=2;
						  inpoutpFlag.v33Output[i].upFlag=false;
					}
					else{
							if(v33oUpLowFlag[i]==2){
									v33OutputOFFFun(i);
							}
					}
			}

			for(i=0;i<V5O_NUM;i++){
					if(inpoutpFlag.v5Output[i].lowFlag==true){
							v5OutputOFFFun(i);
						  //rt_kprintf("%s ctrlOutSetIO v5O off %d\n",sign,i);
						  v5oUpLowFlag[i]=1;
						  inpoutpFlag.v5Output[i].lowFlag=false;
					}
					else{
							if(v5oUpLowFlag[i]==1){
									v5OutputONFun(i);
							}
					}
					if(inpoutpFlag.v5Output[i].upFlag==true){
							v5OutputONFun(i);
						  //rt_kprintf("%s ctrlOutSetIO v5O on %d\n",sign,i);
						  v5oUpLowFlag[i]=2;
						 inpoutpFlag.v5Output[i].upFlag=false;
					}
					else{
							if(v5oUpLowFlag[i]==2){
									v5OutputOFFFun(i);
							}
					}
			}

			for(i=0;i<V12O_NUM;i++){
					if(inpoutpFlag.v12Output[i].lowFlag==true){
							v12OutputOFFFun(i);
						  //rt_kprintf("%s ctrlOutSetIO v12O off %d\n",sign,i);
						  v12oUpLowFlag[i]=1;
						  inpoutpFlag.v12Output[i].lowFlag=false;
					}
					else{
							if(v12oUpLowFlag[i]==1){
									v12OutputONFun(i);
							}
					}
					if(inpoutpFlag.v12Output[i].upFlag==true){
							v12OutputONFun(i);
						  //rt_kprintf("%s ctrlOutSetIO v12O on %d\n",sign,i);
						  v12oUpLowFlag[i]=2;
						  inpoutpFlag.v12Output[i].upFlag=false;
					}
					else{
							if(v12oUpLowFlag[i]==2){
									v12OutputOFFFun(i);
							}
					}
			}
}

extern void diIOSetFlag(void);
void  autoCtrlTask(void *para)
{
	
//	  ctrlPrintf();
	
//		for(int i=0;i<4;i++){
//			v12OutputONFun(i);
//		}
//		rt_thread_mdelay(1000);
//		for(int i=0;i<4;i++){
//			v12OutputOFFFun(i);
//		}
//		rt_thread_mdelay(1000);
	  extern void printModbusDevList();
	#ifndef     ANA_MASK
	  extern void prinfAnalogList();
	#endif
	  extern void printfDIList();
	  extern void printfOutputList();
		extern void printfThresholdList();
		extern void printfCtrl();
	  extern void printAcuid();
	  printAcuid();
		printModbusDevList();
	#ifndef     ANA_MASK
	  prinfAnalogList();
	#endif
	  printfDIList();
	  printfOutputList();
		printfThresholdList();
		printfCtrl();
	  rt_kprintf("%sautoCtrlTask start\n",sign);
//		int i;
//		rt_kprintf("%sDI addr\n",sign);
//		for(i=0;i<DI_NUM;i++){
//			rt_kprintf("0x%x 0x%x\n",&inpoutpFlag.digInput[i].lowFlag,&inpoutpFlag.digInput[i].upFlag);
//		}
//		rt_kprintf("\n");
//		rt_kprintf("%sDO addr\n",sign);
//		for(i=0;i<DO_NUM;i++){
//			rt_kprintf("0x%x 0x%x\n",&inpoutpFlag.digOutput[i].lowFlag,&inpoutpFlag.digOutput[i].upFlag);
//		}
//		rt_kprintf("\n");
//		rt_kprintf("%sV33 addr\n",sign);
//		for(i=0;i<V33O_NUM;i++){
//			rt_kprintf("0x%x 0x%x\n",&inpoutpFlag.v33Output[i].lowFlag,&inpoutpFlag.v33Output[i].upFlag);
//		}
//		rt_kprintf("\n");
//		rt_kprintf("%sV5 addr\n",sign);
//			for(i=0;i<V5O_NUM;i++){
//			rt_kprintf("0x%x 0x%x\n",&inpoutpFlag.v5Output[i].lowFlag,&inpoutpFlag.v5Output[i].upFlag);
//		}
//			rt_kprintf("\n");
//		rt_kprintf("%sV12 addr\n",sign);
//			for(i=0;i<V12O_NUM;i++){
//			rt_kprintf("0x%x 0x%x\n",&inpoutpFlag.v12Output[i].lowFlag,&inpoutpFlag.v12Output[i].upFlag);
//		}
//			rt_kprintf("\n");
//		inpoutpFlag.analogTempHum.humUpFlag=1;
//		inpoutpFlag.analogTempHum.tempUpFlag=1;
//		inpoutpFlag.modbusCh4[0].ch4UpFlag=1;
//		inpoutpFlag.modbusH2s[0].h2sUpFlag=1;
		while(1){	
			  diIOSetFlag();
			  autoCtrlRun();
			  ctrlOutSetIO();
				rt_thread_mdelay(1000);
		}
}





