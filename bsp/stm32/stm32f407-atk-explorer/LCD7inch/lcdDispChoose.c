#include "board.h"

int modbusChosIndex=0;
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

void  nextModName()
{
	modbusChosIndex++;
	if(modbusChosIndex==MODBUS_NUM)
		modbusChosIndex=0;
}

void  lastModName()
{
		if(modbusChosIndex==0)
			modbusChosIndex=MODBUS_NUM-1;
		else
			modbusChosIndex--;
}