#include   "NetJsonDataTask.h"
#include   "board.h"

const static char task[]="[dataRec]";
struct rt_mailbox mbNetRecData;
extern void AllDownPhrase(char *data,int lenth);
//���� ���ƴ��  ���������
void netDataCheckp(uint8_t *data)
{
	  uint16_t lenth=0;
	  uint16_t count=0;
	  while(1){
				if((data[count]==(uint8_t)((uint16_t)HEAD>>8))&&(data[count+1]==(uint8_t)(HEAD))){
						lenth = (data[count+2]<<8)+data[count+3]+HEAD_LEN+LENTH_LEN+CRC_LEN+TAIL_LEN;  
						if(lenth<=2048){
								for(int i=0;i<lenth;i++)
										rt_kprintf("%02x",data[i]);
								rt_kprintf("\r\n %sTASK rec  %d\r\n",task,lenth);
							  AllDownPhrase((char *)data+count,lenth);
						}
						else{
								rt_kprintf("%slenth  err��%d str0:%x str1:%x str[2]:%d  str[3]:%d\r\n",task,lenth,data[0],data[1],data[2],data[3]);
						}
				}
				if(count++>=2040){
						break;
				}
		}
}
//mailbox���յ����������ݽ������������Լ��ж�ͷ��β
uint16_t netDataCheck(uint8_t *data)
{
	  uint16_t lenth=0;
		if((data[0]==(uint8_t)((uint16_t)HEAD>>8))&&(data[1]==(uint8_t)(HEAD))){
			  lenth = (data[2]<<8)+data[3]+HEAD_LEN+LENTH_LEN+CRC_LEN+TAIL_LEN;  
				if(lenth<=2048){
//						for(int i=0;i<lenth;i++)
//								rt_kprintf("%02x",data[i]);
//						rt_kprintf("\r\n net rec  %d\r\n",lenth);
				}
				else{
						rt_kprintf("%slenth  err��%d str0:%x str1:%x str[2]:%d  str[3]:%d\r\n",task,lenth,data[0],data[1],data[2],data[3]);
				}
		}
		else{
				 rt_kprintf("%srec head  err\r\n",task);
		}	 
		return lenth;
}
//�������ݽ��յĴ��� 
void   netDataRecTask(void *para)
{
	
	  uint8_t *str=RT_NULL;
		while(1){
			 if (rt_mb_recv(&mbNetRecData, (rt_ubase_t *)&str, 1000) == RT_EOK)
			 {
		#if 1
					 uint16_t  lenth= netDataCheck(str);
					 if(lenth>0){
								AllDownPhrase((char *)str,lenth);
					 }
		#else
					 netDataCheckp(str);
		#endif	
			 }
#ifdef  USE_WDT
			rt_event_send(&WDTEvent,EVENT_WDT_RECTASK);
#endif

		}
}
