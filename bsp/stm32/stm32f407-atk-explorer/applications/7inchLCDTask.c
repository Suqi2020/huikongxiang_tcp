
#include   "board.h"

extern struct  rt_messagequeue LCDmque;
extern void LCDDispIP(void);
extern void LCDDispUart(void);
extern void LCDDispMCUID(void);
extern void LCDDispModbusGet(void);
extern void LDCDispMosbusInfo(void);
//extern void LCDDispModInfoCpy(void);
extern void LCDDispConfig(uint8_t *recBuf,int len);
extern void firstNameDispInit(void);
extern uint8_t  recLCDBuf[LCD_BUF_LEN];



//char te1[5]={0xff,0xff,0xff,0xff,0xff};
//char te2[5]={0xff,0xff,0xff,0xff,0};
//char te3[5]={0xff,0xff,0xff,0xff,0};
//char te4[5]={0xff,0xff,0xff,0xff,0};
//char test[20];
//int testfun(void)
//{

//    strcpy(test,te1);
//	rt_kprintf("testfun:");
//		for(int i=0;i<20;i++){

//		rt_kprintf("%02x ",test[i]);
//	}
//		rt_kprintf("\n ");
//}
void  LCDTask(void *parameter)
{
	  extern void LCDDispErrMosbusState();
    extern void LCDDispNetErrState();
	  extern void LCDDispErrModbusGet();
		extern void LDCDispErrMosbusInfo();

	  rt_thread_mdelay(1000);//���������ʱ�ȴ�����������
	//testfun();
	  LCDDispIP();
	  LCDDispUart();
	  LCDDispMCUID();//LCD send:5a a5 15 82 12 10 ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 
	  LCDDispModbusGet();
	  //firstNameDispInit();
  	LDCDispMosbusInfo();
	  int revLen=0;
	  int dispCount=0;
	
    extern void LCDDispRstOK();
		LCDDispRstOK();
		while(1){
			
				if(rt_mq_recv(&LCDmque, recLCDBuf+revLen, 1, 1000) == RT_EOK){
						revLen++;
						while(rt_mq_recv(&LCDmque, recLCDBuf+revLen, 1, 2) == RT_EOK){
							 revLen++;
						}
				}
				if(revLen){
						 LCDDispConfig(recLCDBuf,revLen);
						 revLen=0;
				}
				if(++dispCount>=60){
						dispCount=0;
						LCDDispNetErrState();
						LCDDispErrModbusGet();
						LDCDispErrMosbusInfo();
						LCDDispErrMosbusState();
				}
#ifdef  USE_WDT
				rt_event_send(&WDTEvent,EVENT_WDT_LCDTASK);
#endif
		}
}

