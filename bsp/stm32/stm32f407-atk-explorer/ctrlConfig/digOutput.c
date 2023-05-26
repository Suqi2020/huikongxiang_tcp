#include <board.h>
//����8·ttl��ƽ�����2·3V3��ƽ���  2·5V��ƽ��� 4·12V���
const static char sign[]="[output]";


//��ӡdigital output����б�
void printfDOList()
{
		for(int j=0;j<DO_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
				if(packFlash.digoutput[j].workFlag==RT_TRUE){//��
						rt_kprintf("%s digOutput ",sign);
						rt_kprintf("%s ",packFlash.digoutput[j].name);
						rt_kprintf("%s ",packFlash.digoutput[j].devID);
						rt_kprintf("%s ",packFlash.digoutput[j].model);
						rt_kprintf("%d \n",packFlash.digoutput[j].port);
				}
		}
}

//����port����� 
//digital output ��������
//digOutput ˮ�� GYNJLXSD000000164 GY283 1
static void digOutput(int argc, char *argv[])
{
	  int port;
	  if(0==rt_strcmp((char *)"list", argv[1])){
				printfDOList();
				return;
		}
		if(argc!=5){
				goto ERR;
		}
		if(devIDOKCheck(argv[2])!=true){
				rt_kprintf("%sERR input the same ID\n",sign);
			  return;
		}
    port = atoi16(argv[4],10);
		if((port<=DO_NUM)&&(port>0)){//���
				packFlash.digoutput[port-1].workFlag=RT_TRUE;
				rt_strcpy(packFlash.digoutput[port-1].name, argv[1]);
				rt_strcpy(packFlash.digoutput[port-1].devID,argv[2]);
				rt_strcpy(packFlash.digoutput[port-1].model,argv[3]);
				packFlash.digoutput[port-1].port=port;
				rt_kprintf("%s add digOutput chanl %d\n",sign,port);
			  rt_kprintf("%s digOutput OK\n",sign);
		}
		else{//ɾ��
			 for(int j=0;j<DO_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(rt_strcmp(packFlash.digoutput[j].devID,argv[2])==0){
							packFlash.digoutput[j].workFlag=RT_FALSE;
							rt_kprintf("%s delete digOutput channel %d\n",sign,j+1);
					}
			 }
		}
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[digOutput ˮ�� GYNJLXSD000000162 GY281 1]\n",sign);
		rt_kprintf("%s[port1-8 ֮�������ӦID�����в���]\n",sign);

}
MSH_CMD_EXPORT(digOutput,digOutput config);//FINSH_FUNCTION_EXPORT_CMD



//��ӡ3V3����������б�
void printfPower3V3List()
{
		for(int j=0;j<V33O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
				if(packFlash.v33output[j].workFlag==RT_TRUE){//��
						rt_kprintf("%s power3V3 ",sign);
						rt_kprintf("%s ",packFlash.v33output[j].name);
						rt_kprintf("%s ",packFlash.v33output[j].devID);
						rt_kprintf("%s ",packFlash.v33output[j].model);
						rt_kprintf("%d \n",packFlash.v33output[j].port);
				}
		}
}

//����port����� 
//power3V3������� ��������
static void power3V3(int argc, char *argv[])
{
	  int port;
	  if(0==rt_strcmp((char *)"list", argv[1])){
				printfPower3V3List();
				return;
		}
		if(argc!=5){
				goto ERR;
		}
		if(devIDOKCheck(argv[2])!=true){
				rt_kprintf("%sERR input the same ID\n",sign);
			  return;
		}
    port = atoi16(argv[4],10);
		if((port<=V33O_NUM)&&(port>0)){//���
				packFlash.v33output[port-1].workFlag=RT_TRUE;
				rt_strcpy(packFlash.v33output[port-1].name, argv[1]);
				rt_strcpy(packFlash.v33output[port-1].devID,argv[2]);
				rt_strcpy(packFlash.v33output[port-1].model,argv[3]);
				packFlash.v33output[port-1].port=port;
				rt_kprintf("%s add 3V3Output chanl %d\n",sign,port);
			  rt_kprintf("%s 3V3Output OK\n",sign);
		}
		else{//ɾ��
			 for(int j=0;j<V33O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(rt_strcmp(packFlash.v33output[j].devID,argv[2])==0){
							packFlash.v33output[j].workFlag=RT_FALSE;
							rt_kprintf("%s delete 3V3Output channel %d\n",sign,j+1);
					}
			 }
		}
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[power3V3 ˮ�� GYNJLXSD000000162 GY281 1]\n",sign);
		rt_kprintf("%s[port1-8 ֮�������ӦID�����в���]\n",sign);

}
MSH_CMD_EXPORT(power3V3,power3V3 config);//FINSH_FUNCTION_EXPORT_CMD




//��ӡ5V����������б�
void printfPower5VList()
{
		for(int j=0;j<V5O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
				if(packFlash.v5output[j].workFlag==RT_TRUE){//��
						rt_kprintf("%s power5V ",sign);
						rt_kprintf("%s ",packFlash.v5output[j].name);
						rt_kprintf("%s ",packFlash.v5output[j].devID);
						rt_kprintf("%s ",packFlash.v5output[j].model);
						rt_kprintf("%d \n",packFlash.v5output[j].port);
				}
		}
}

//����port����� 
//power5V������� ��������
static void power5V(int argc, char *argv[])
{
    int port;
	 
	  if(0==rt_strcmp((char *)"list", argv[1])){
				printfDOList();
				return;
		}
		if(argc!=5){
				goto ERR;
		}
		if(devIDOKCheck(argv[2])!=true){
				rt_kprintf("%sERR input the same ID\n",sign);
			  return;
		}
    port = atoi16(argv[4],10);
		if((port<=V5O_NUM)&&(port>0)){//���
				packFlash.v5output[port-1].workFlag=RT_TRUE;
				rt_strcpy(packFlash.v5output[port-1].name, argv[1]);
				rt_strcpy(packFlash.v5output[port-1].devID,argv[2]);
				rt_strcpy(packFlash.v5output[port-1].model,argv[3]);
				packFlash.v5output[port-1].port=port;
				rt_kprintf("%s add 5VOutput chanl %d\n",sign,port);
			  rt_kprintf("%s 5VOutput OK\n",sign);
		}
		else{//ɾ��
			 for(int j=0;j<V5O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(rt_strcmp(packFlash.v5output[j].devID,argv[2])==0){
							packFlash.v5output[j].workFlag=RT_FALSE;
							rt_kprintf("%s delete 5VOutput channel %d\n",sign,j+1);
					}
			 }
		}
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[power5V ˮ�� GYNJLXSD000000162 GY281 1]\n",sign);
		rt_kprintf("%s[port1-8 ֮�������ӦID�����в���]\n",sign);

}
MSH_CMD_EXPORT(power5V,power5V config);//FINSH_FUNCTION_EXPORT_CMD

//��ӡ12V������б�
void printfPower12VList()
{
		for(int j=0;j<V12O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
				if(packFlash.v5output[j].workFlag==RT_TRUE){//��
						rt_kprintf("%s power12V ",sign);
						rt_kprintf("%s ",packFlash.v12output[j].name);
						rt_kprintf("%s ",packFlash.v12output[j].devID);
						rt_kprintf("%s ",packFlash.v12output[j].model);
						rt_kprintf("%d \n",packFlash.v12output[j].port);
				}
		}
}

//����port����� 
//power12V������� ��������
static void power12V(int argc, char *argv[])
{
		int port;
	  if(0==rt_strcmp((char *)"list", argv[1])){
				printfPower12VList();
				return;
		}
		if(argc!=5){
			
				goto ERR;
		}
		if(devIDOKCheck(argv[2])!=true){
				rt_kprintf("%sERR input the same ID\n",sign);
			  return;
		}
    port = atoi16(argv[4],10);
		if((port<=V12O_NUM)&&(port>0)){//���
				packFlash.v12output[port-1].workFlag=RT_TRUE;
				rt_strcpy(packFlash.v12output[port-1].name, argv[1]);
				rt_strcpy(packFlash.v12output[port-1].devID,argv[2]);
				rt_strcpy(packFlash.v12output[port-1].model,argv[3]);
				packFlash.v12output[port-1].port=port;
				rt_kprintf("%s add 12VOutput chanl %d\n",sign,port);
			  rt_kprintf("%s 12VOutput OK\n",sign);
		}
		else{//ɾ��
			 for(int j=0;j<V12O_NUM;j++){//��һ�� �ҵ� GYNJLXSD000000499  ���
					if(rt_strcmp(packFlash.v12output[j].devID,argv[2])==0){
							packFlash.v12output[j].workFlag=RT_FALSE;
							rt_kprintf("%s delete 12VOutput channel %d\n",sign,j+1);
					}
			 }
		}
		return;
		ERR:
		rt_kprintf("%sfor example\n",sign);
		rt_kprintf("%s[power12V ˮ�� GYNJLXSD000000162 GY281 1]\n",sign);
		rt_kprintf("%s[port1-4 ֮�������ӦID�����в���]\n",sign);

}
MSH_CMD_EXPORT(power12V,power12V config);//FINSH_FUNCTION_EXPORT_CMD


//��ӡ����������б�
//���� ��ӡdigital output 8·
//��ӡ3V3��� 2·
//��ӡ5V��� 2·
//��ӡ12V��� 4·
void printfOutputList()
{
		printfDOList();
	  printfPower3V3List();
	  printfPower5VList();
	  printfPower12VList();
}

