#include "board.h"
static char  *sign="[LCDCHOOSE]";
int modbusChosIndex=0;
//��ʾѡ���modbus����
void dispChooseModbusName()
{

	 uint8_t buf[NAME_LEN]="";
		for(int i=0;i<NAME_LEN;i++){
			  if(modbusName[modbusChosIndex][i]==0){
					buf[i]=0xff;
					buf[i+1]=0xff;
					break;
				}
				buf[i]=modbusName[modbusChosIndex][i];
			  
		}
	  LCDWtite(TEST_CHOOSE_MODBUS_ADDR,buf,strlen((char *)buf));

}
//��һ��modbus����
void  nextModName()
{
	modbusChosIndex++;
	if(modbusChosIndex==MODBUS_NUM)
		modbusChosIndex=0;
}
//��һ��modbusname
void  lastModName()
{
		if(modbusChosIndex==0)
			modbusChosIndex=MODBUS_NUM-1;
		else
			modbusChosIndex--;
}

void dispHuanliuData();
void  dispJufangData();
void  dispChenjiangData();
void  dispWaipoData();
//�л�������Ŀ¼�� ��ȷ��������ʾ��ǰmodbus������
void  dispCurrentModData()
{
		//"HuanLiu","JuFang","FangChenJiang","FangWaiPo","JiaWan","YangQi","LiuHuaQing","YiYangHuaTan","WenShiDu","ShuiWei","LieFengYi","JingGai"};

		switch(modbusChosIndex){ 
			case 0://����
				dispHuanliuData();
				break;
			case 1://"JuFang",
				dispJufangData();
				break;
			case 2://"FangChenJiang",
				dispChenjiangData();
				break;
			case 3://"FangWaiPo"
				dispWaipoData();
				break;
			case 4://"JiaWan"
				break;
			case 5://"YangQi",
				break;
			case 6://"LiuHuaQing",
				break;
			case 7://"YiYangHuaTan",
				break;
			case 8://"WenShiDu"
				break;
			case 9://"ShuiWei"
				break;
			case 10://"LieFengYi"
				break;
			case 11://"JingGai"
				break;
			default:
        rt_kprintf("%s ERR:dispCurrentModData \n",sign);
				break;
		}
}