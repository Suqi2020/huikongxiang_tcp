#ifndef  __UART_RECONFIG_H__
#define  __UART_RECONFIG_H__

#include "board.h"

#include "dataPack.h"
//�洢��Ϊ3������  1/modbus�������洢
//								 2/ip ���� acuid ģ�⴫���� ���� ����豸
//								 3/����,ģ�⴫������ֵ�洢


#define  LENTH   500
#define  MSGPOOL_LEN   LENTH //485���������  ����1k��Ҫ�޸Ĵ˴�

//typedef struct{
////		uint32_t bps;
////    uint16_t calTime;	
////    uint8_t  delayTime;//100ms��������  �˿��±߹��صĴ������ɼ����ʱ��  �ַ�2��
////	  uint8_t rev;
//}uartSaveStru;

//extern uartSaveStru  port[UART_NUM];




typedef struct{
		
	  uint8_t  localIp[4];
	  uint8_t  gateway[4];
	  uint8_t  remoteIp[4];
    uint16_t remotePort; 
	  uint8_t  macaddr;
	  uint8_t  rev;
}netIpFlashStru;

//#define  ANALOG_NUM   8//8·ģ����

typedef struct{
		char  devID[DEVID_LEN];
	  char  model[MODEL_LEN];
		char  name[NAME_LEN];
	
    uint8_t port; //1-8
	  uint8_t rev;//
	  uint16_t calTime; //�ɼ����ʱ��
	

}analogDevStru;

//typedef struct{
//		bool lowFlag;
//	  bool upFlag;
//}digitStru_p;
typedef struct{
	
		char  devID[DEVID_LEN];
	  char  model[MODEL_LEN];
		char  name[NAME_LEN];
    uint8_t port; //1-8
	  uint8_t workFlag;//RT_TRUE-
//		bool levelFlag;//����ֵ
	  uint8_t rev[2];
	//	bool upFlag;
}digitStru;//�����������
typedef struct{
//		uartSaveStru   port[UART_NUM];
		netIpFlashStru netIpFlash;        //�洢IP����
//	  analogDevStru  analog[ANALOG_NUM];//�洢ģ������
	  uint32_t       uartBps[UART_NUM];    //�洢��������
	  char     acuId[ACUID_LEN+1];      //�洢acuID
	  char rev;
		digitStru diginput[DI_NUM];   //��������
	  digitStru digoutput[DO_NUM];   //�������
		digitStru v33output[V33O_NUM]; //3V3��Դ���
		digitStru v5output[V5O_NUM];   //5V��Դ���
		digitStru v12output[V12O_NUM]; //12V��Դ���
	  uint64_t  utcTime;
//			//���õ���������ߵ͵�ƽ��Ч��Ҫ�洢
//		digitStru_p        digInput[DI_NUM];
//		digitStru_p        digOutput[DO_NUM];
//		digitStru_p        digV33Out[V33O_NUM];
//		digitStru_p        digV5out[V5O_NUM];
//		digitStru_p        digV12out[V12O_NUM];
}packIpUartStru;
extern packIpUartStru packFlash;

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////����������Ҫ�޸Ĵ˴�/////////////////////////////////////////



	
//typedef struct{
//	 // uint32_t bps;
//	//rt_bool_t offline;
////	  rt_mutex_t  uartMutex;
////	  struct  rt_messagequeue* uartMessque;
//}uartConfStru;


/////////////////////////////////////////////////////////////////////////////////////////////////////

//extern uartConfStru  uartDev[];
extern void rs485UartSend(uint8_t chanl,uint8_t *buf,int len);
extern void uartMutexQueueCfg(void);
extern struct  rt_messagequeue uartmque[UART_NUM];

rt_bool_t errConfigCheck(void);













#endif

