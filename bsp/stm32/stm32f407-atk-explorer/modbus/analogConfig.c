#include "board.h"

#ifndef     ANA_MASK
const static char sign[]="[analogConfig]";

//��ӡanalog�����豸
void prinfAnalogList()
{
		for(int j=0;j<ANALOG_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
				if(sheet.analog[j].workFlag==RT_TRUE){//��
						rt_kprintf("%s analog ",sign);
						rt_kprintf("%s ",sheet.analog[j].name);
						rt_kprintf("%s ",sheet.analog[j].ID);
						rt_kprintf("%s ",sheet.analog[j].model);
					  rt_kprintf("%d ",sheet.analog[j].subName);
						rt_kprintf("%d ",sheet.analog[j].port);
						rt_kprintf("%d\n",sheet.analog[j].colTime);
				}
		}
}
//analog  ��ʪ�� temperature    GYNJLXSD000000499 GY280 port1  120  
//analog  ��ʪ�� humidity       GYNJLXSD000000499 GY280 port2  120 
//analog  ��ʪ�� humidity       GYNJLXSD000000499 GY280 port2  120 
//
//const static char  analogName[20]="��ʪ��";
//const static char  analogName1Val[2][20]={"temperature","humidity"};
//const  static  char analogPort[ANALOG_NUM][10]={"port1","port2","port3","port4","port5","port6","port7","port8"};

//int analogPortCheck(char *port)
//{
//	  
//	  
//		for(int i=0;i<ANALOG_NUM;i++){
//			 // rt_kprintf("%s %s\n",analogPort[i],port);
//			  if(rt_strcmp(analogPort[i],port)==0){
//						return i+1;
//				}
//		}
//	  return 0;
//}
//note��ģ��������modbus�������õĲ�֮ͬ����ͨ���˿����������� 
//      ͬһ��ID�������ö���˿� ����ʪ����Ҫռ�������˿�
/*
����(analog+����+ID+ѡ��(1.2.3 ֻ��һ��ʱ������Ϊ1)+����+�˿�(1-8)+ʱ��)
analog ��ʪ��  GYNJLXSD000000499 1 GY280 1 120
analog ��ʪ��  GYNJLXSD000000499 2 GY280 2 120

*/
static void analog(int argc, char *argv[])
{
		if(0==rt_strcmp((char *)"list", argv[1])){
				prinfAnalogList();
				return;
		}
		if(argc!=7){
				goto ERR;
		}
		for(int i=0;i<ANALOGNAME_NUM;i++){
				if(rt_strcmp(argv[1],analogName[i])==0){
						
						 int port = atoi32(argv[5],10);
						 if((port>8)&&(port!=255)){
								rt_kprintf("%s,ERR:port should be 0-8 or 255\n",sign);
						 }
						 int subName=atoi32(argv[4],10);
						 if(port==0){//�ر� ��Ҫ�ж�ID��ѡ��Ե���ʱ����ܹر�
								for(int j=0;j<ANALOG_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
										if((rt_strcmp(sheet.analog[j].ID,argv[2])==0)&&(subName==sheet.analog[j].subName )){
												sheet.analog[j].workFlag=RT_FALSE;
												rt_kprintf("%s close chanl%d\n",sign,j+1);
												return;
										}
								 }
								 rt_kprintf("%s,ERR:not find off analog device\n",sign);
								 return;
						 }
						 else if(port==255){//ɾ�����豸 ��Ҫ�ж�ID��ѡ��Ե���ʱ�����ɾ��
								for(int j=0;j<ANALOG_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
										if((rt_strcmp(sheet.analog[j].ID,argv[2])==0)&&(subName==sheet.analog[j].subName )){
												sheet.analog[j].workFlag=RT_FALSE;
												rt_kprintf("%s delete chanl%d\n",sign,j+1);
												return;
										}
								 }
								 rt_kprintf("%s,ERR:not find delete analog device\n",sign);
						 }
						 else{//���ն˿�������
								sheet.analog[port-1].workFlag=RT_TRUE;
								rt_strcpy(sheet.analog[port-1].name,   argv[1]);
								rt_strcpy(sheet.analog[port-1].model,  argv[3]);
								rt_strcpy(sheet.analog[port-1].ID,     argv[2]);
								sheet.analog[port-1].port=port;
								sheet.analog[port-1].subName= subName;           
								sheet.analog[port-1].colTime = atoi16(argv[6],10);
								rt_kprintf("%s open port%d\n",sign,port);
								rt_kprintf("%s analog OK\n",sign);
								return;
						}
				}
		}

		rt_kprintf("analog 2\n");
		rt_kprintf("%sargv[1]!=%s\n",sign,analogName);
		goto ERR;

		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[analog  ��ʪ�� temperature    GYNJLXSD000000499 GY280 port1  120]\n",sign);
		rt_kprintf("%s[port0��255�����ӦID�����в���]\n",sign);

}
MSH_CMD_EXPORT(analog,analog config);//FINSH_FUNCTION_EXPORT_CMD



#endif

