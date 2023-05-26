/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>

/*
=============================================================================================

    //Total RO  Size (Code + RO Data)               270044 ( 263.71kB)
    Total RW  Size (RW Data + ZI Data)             73696 (  71.97kB)
    Total ROM Size (Code + RO Data + RW Data)     270376 ( 264.04kB)
		[10:27:11.390]�ա���free
		total    : 57296
		used     : 13228
		maximum  : 23920
		available: 44068
		RAM:ռ�� 71.97�����������+12.92������ϵͳmalloc��=84.88k ʣ��43.03K  ʣ���� 33.6%
		ROM:ռ��:264.04k +��������ռ�����һ��128K �ܹ�392.04k  ʣ����61.8%
=============================================================================================


*/
//https://github.com/Suqi2020/huikongxiang_env.git
//0V1   20220919
//��ʼ��  û�м���汾���� 
//0V3   20220920
// ���˴���4�������Ĵ����շ�������  
//0V4   20220921
// ����io��������� adc uart�շ��Ѿ�����  
//0V5   20220921
//ȥ��menuconfig ����IO����   
//1��spiʱ��42MHZ �Ѿ�ȷ��
//2��w5500�ڲ�������32K�Ľ��ջ���
//0V6  W5500�ο�Ұ������ͨ�ųɹ�  20220923
//0V7  w5500 �жϽ�������OK  20220927
//0V9  shell������OK        20220927
//V0.11  ����4����Ҫtask    20220930
//			task1  w5500����״̬��ά�����Լ���������               w5500Task
//			task2  �������ݷ��͵�ά���������������� ע�� ���ݴ�� ��
//       		�Լ��ط� ����task3                              upKeepStateTask
//			task3  net����˵ķ���                                 netDataSednTask                      
//			task4  ���������ݵĽ����봦��                          netDataRecTask
//			task1  w5500����״̬��ά�����Լ���������               w5500Task
//			task2  �������ݷ��͵�ά���������������� ע�� ���ݴ�� ��
//       				�Լ��ط� ����task3                              upKeepStateTask
//			task3  net����˵ķ���                                 netDataSednTask                      
//			task4  ���������ݵĽ����봦��                          netDataRecTask
//			#define RT_CONSOLEBUF_SIZE 2048  //������Ҫ��С 512
//V0.12  ��������json�ͻظ�OK    																	20221008
//V0.13   ����dataup ��devreg easy timer													 20221009
//V0.14   �ֶ�����3����������OK  																		20221010
//        ����2346 modbus ����1 debug ����5 ������


//V0.15		rs485_���ڻ��� modbus ������ʽ��ȡ���ݳɹ�������ʵ���ϴ� 20221011
//        rt_sprintf float����������  ʹ��sprintf���� 
//V0.16   READ WRITE modbus OK   																			20221012
//V0.17   //Ѹ���л�����485�ӿ���ʹ�� ������ֻ��Ҫ�޸Ĵ��ڷ��ͽӿ� ���жϽ��սӿڼ���
//         rs485Circula.c-cirCurrUartSend(uint8_t *buf,int len) 
//         ��drv_uart.c-USART2_IRQHandler�� -rt_mq_send(&cirCurrmque, &Res, 1);    20221012
//V0.18    modbus�������������0       2022012
//V0.19    �ַŶ�ȡ����  ����modbus��ȡ����  ÿ�η��ͺ��ٶ�ȡ             
//         ���������ʱ�� ���Ծ߱���ʼ�� ��ʼ ֹͣ���� ��Ҫ1��Ļ�׼ 
//         ����modbus�豸��������ֵĸ��Ź��ˣ���modbus��ȡ������ ������
//         �߱���ʱ��ͬʱ��������´����͹���                          20221013
//V0.20    ����16K�������  MAX_SOCK_NUM Ϊ1ʱ�� �����16k��������  
//         TX_RX_MAX_BUF_SIZEΪʵ�ʷ��ͻ���buf��С(��MAX_SOCK_NUM����)                       20221017
//V0.21    ����ͳ�ƴ��룬���Լ�����ߴ����͵���ʱ�� ���� offline                    20221018
//V0.22    ���ӳ����Ǵ��� Ĭ�ϲ�����9600 �ĵ�����      20221018
//V0.23    ����������� Ĭ�ϲ�����9600 ��Ҫ�޸�����ĵ�ַΪ01  ͬ������  20221019
//V0.24 	 ����֧��modbus�豸ѡ�񴮿� UART2(1) UART3(2) UART6(3) UART1(debug) UART4(4)  δ����  20221020
//V0.25    ����4·485���������log��ӡ���                                     20221021
//V0.26    ����ip_from==IP_FROM_DHCP �����Զ�����ʵ������ip���� ���������Զ���ȡipʧ�ܣ� 20221025
//V0.27    1������utf8��ʽ���json��ʽ  nodepad++����Ϊutf8 �Լ� c++������ misc controls --no-multibyte-chars
//            ����json��ʽ�����ַ�Ҫ��dataPack.c������ �Ѿ����ļ���nodepad++����Ϊutf8��ʽ
//         2���޸����������������� ������json����û���ͷŵ�                      20221026
//         3������json��ʽ���devRegJsonPack  ��json�Դ�����sprintf �������ݰ� 465Byte���ӵ�586Byte ����ʹ��
//V0.28    �������ö��modbus��ͬһ��������  ��Ҫͬ���͵ķŵ�һ��  ���� �ַźͻ���  ����ͳ�����   20221027
//V0.29    �������ö���ļ��е�keil��      20221028
//V0.30    ����flash�洢  ���4K           20221028
//V0.31    ����atָ��������modbus  example[modbus �ӵػ��� uart5 12]
//				 mobus+�豸����+�˿�+�豸��ַ(0-�ر��豸)+�ɼ�ʱ��(��)           20221029
//V0.32    ����mdbus����ʱ�� ��鲻ͬ�����豸��ͬһ���˿�
//         ���ͬ�����豸��ͬһ���豸��ַ��ͬһ���˿�
//         ʵ��ip��ַ�����úʹ洢��flash��            20221031
//V0.33//4��������һ���ȡ ����ǰ������ʹ�� ֻ��CO��ʱ���ط���ȡ���������  �ر�ʱ��ֻ��Ҫ�ر�CO�Ϳ��԰���������ȫ���ر�
//         COĬ��������4  Ϊ�˷��������������ݴ����һ��    20221101
//V0.34    ������ʪ�Ⱥ�ˮλ��ȡ ÿ��������ֻ֧��һ��       20221102  
//V0.35    ����flash��д ����drv_falsh_f4.c�⺯��          20221103
//V0.36    ����modbus��ȡΪͨ��ɵ��ʽ��ȡ mcu������������ֺ���  20221103
//V0.37    ��������� devid�ظ� ������ͬһ�������±ߵ�modbus�豸��ͬ�����豸��ַ  
//         �ϵ��ӡmodbus���ù����豸      
//          ����128kflash�ռ����洢����modbus�豸(������С��λ��128K) Ŀǰ���֧��200��       20221104
//V0.38    �ַ�GY-JF100-C01�ͱ���豸������ͬһ�����ڵ������������ȡ�豸�ᵼ�¾ַŶ�ȡʧ�� 
//         ��������ȡ�豸�������Ҫ��ʱ2�������ȡ                   20221105
//V0.39    �޸Ĵ洢��������ͳһΪ flash save                      
//         ����ģ������                                            20221107
//         ����bug  uart ��MX_USART2_UART_Init(packFlash.port[i].bps); ��
//V0.40    �޸�ɵ��ʽΪָ��������       20221108
//V0.41    ���õ�������json��ʽ�Ѿ�������   20221109
//V0.42    ���봫�������� �޸�bug    ����ģ��������Ŀǰ֧����ʪ��δ��� 20221110
//V0.43    ���봫������Ӧ״̬�ϴ�  1-��������Ӧ  0-����������Ӧ  20221111
//V0.44    �޸�log��ʾ���� �Լ���ʾ������      20221117
//V0.45    ����7�紥����ʾ�����ַ����         20221201
//V0.46    ����7�紥�����ֽӿں��� ���Ӵ���5���� ����lcdtask ����       20221205
//V0.47    ������ʾ���硢���ڡ�mcuid ������������ѡ����         20221208
//V0.48    ���Ӵ�������ʾ ɾ������ �������� ����         20221209
//V0.49    ����������ߴ�����ʾ ��ʾ�������߹��ٵ��ߵ�ʱ��  һ��ʼ�ϵ�û�н���������²�����ʾ�˴ε���ʱ��  20221212
//v0.50    ���Ӵ��������ý���  ��ʱ���ȶ�   20221213
//V0.51    ���Ӵ��������ý��� ����OK    20221214
//V0.52    ���ӹ��ϴ�������ʾ����    20221215
//V0.53    ������ϴ�����������ʾ ��ҳ����    20221216
//V0.54    �޸���ʽ��RTCΪ��ֵ����� %d��Ϊu%  20221230
//V0.55    ����utf8��ʽ�Ĵ�����������ʾ  2023-1-4
//V0.56    �޸�json�����ʽ identify 2023-1-5
//V0.57    modbus������4������ ��������һ����̼����ʹ��ͬһ��ID
//         1��ȥ�����ں�LCD���ô�����ʱ��4������ĵ�deviceID����
//         2��ͳһ4�����嶨ʱ��Ϊco��ʱ��
//         3������4���������߼�  2023-1-7
//V0.58    utcTime()���json��ʽ����
//         sprintf(sprinBuf,"%u",utcTime()); 
//         ����Ϊ		sprintf(sprinBuf,"%llu",utcTime());
//         ����uint32_t utcTime() Ϊ uint64_t utcTime()  2023-1-10
//V0.59    �޸Ĵ�������modbus����������²���ɾ��������  2023-1-11
//V0.60		 ���Ӵ���digitalinput�����Լ��洢              2023-1-12
//V0.61    ���Ӵ���digital output �����Լ��洢 �ο��ĵ��������modbus��������V0.3�� 2023-1-17
//V0.62    ����digital output input ���ó���8������´�����ʾ����  2023-1-18
//V0.63    ����analog����������    2023-02-02
//V0.64    ���Ӵ�����threshold����   2023-02-05
//V0.65    ����3v3 5v 12voutput�������� 20230206
//V0.66    �����߼����� ��չ�ṹ�� ���ӱ���ָ�뵽flash��
//V0.67    ������������������ δ���� 20230212
//V0.68    ����autoctrltask ���� autoCtrlRun��ctrlOutSetIO����
//V0.69    ����modbus ai������������ֵ�����λ��� �Լ�diIOOutSetFlag() di��������λ���
//V0.70    ����autoctrl�������Լ����� 20230215
//V0.71    ����test IO���� ���ִ�����
//V0.72    ���еĶ���ӿڵ�AT����ȫ��ʵ�� ������Ե���� �򵥲������߼����Ƶ������Ŀ 20230217
//V0.73    ���tasklog����ʱ������ڴ�й©���� ��Ҫ�ȴ�����������ɾ������
//         ����ģ����ʪ�ȶ�ȡ��ֵ��׼ȷ  �Ѿ�ʵ�ֲ��Ҳ���
//V0.74    �޸�����threadshold ʱ��ߵ�ֵ�ŷ������� 
//V0.75    �޸��Զ����ó��ֵ�bug
//V0.76    ���ӿ��ؿ��ƵĽӿ���ʾV3O V12O V5O
//V0.77    ���ӿ��ؿ��ƶԽ�LCD��������OK
//V0.78    ���ӵ�ƽ��ʾ����Ĭ����ʾ��ƽֵ  20230312
//V0.79    �����������ò���OK
//V0.80    ���������ʾOK 
//         ����modbus����������������Լ�ģ�⴫���������ð��ն˿ں�����
//         �����µ���������˿ں���ͬ�ᵼ��ԭ����ʧЧ
//V0.81    ����ģ�⴫������ȡ�ɹ�
//V0.82    ����ģ�⴫��������ɾ���ɹ�
//V0.83    ������վ��ȡģ���485���������ݳɹ�
//V0.84    ���ö�ȡ������ʱ��������
//V0.85    ���Ӷ���վͨѶjson��ʽ ��ȡ��������ֵ���  20230323
//V0.86    ����485��ģ��澯�ϱ�    20230324
//V0.87    �������е�modbus�澯�ϱ� 20230325
//v0.88    ����������������Ŀ����ϱ����ȡ 20230327
//V0.89    ������վ�·�������������  20230328
//V0.90    ����crackMeter��modbus������ʾ ���ڳ��ҿ����޸�Э���ʽ  
//         �޸�lcd��ʾ�ĳ����ؼ���ַ����    20230330
//V0.91    �����Զ�����json���ݽ��� 20230404
//V0.92    �ѷ��ǳ��Ҹ���Ϊ��׼modbusЭ�� ���������� 20230407
//V1.00    ȥ��uartMutex������  ���Ӷ�ȡ485����ʱ��Ļ��Ᵽ����2���̵߳��ã� 20230418
//V1.01    ��uint16 send(SOCKET s, const uint8 * buf, uint16 len)������#if(MAX_SOCK_NUM!=8) break freesizeһֱΪ2048
//         �����жϽ���Ϊ��ѯ����ÿ��100ms��ѯһ�� �жϽ����ڴ���������ʱ���ְ� ����8k�����ݰ���ְ� 
//         Ŀǰ���8K���ݰ� ����8K�ᵼ���ڴ����
//V1.02    �޸��߼�����Զ�����ô���  ����autoCfgSure();λ��
//         �޸����������߼����Ƴ���20�����³������� logCrtlAddResp(cJSON *Json)�����߼����������ж�
//V1.03    �޸��������ݹ��ർ��rt_smem_free err������  LENTH <MSGPOOL_LEN ����buf���  
//         ����һ����ˢ��һ�δ�����״̬������״̬����ʾ LCDTask.C��
//V1.04    ����WDT
//V1.05    ����LCD��ʾ��λ�ͱ���ɹ�����
//V1.06    �޸��ڴ�������µ�(rt_object_get_type(&mq->parent.parent) == RT_Object_Class_MessageQueue) assertion failed at function:rt_mq_recv,
//					�ڴ�������� 
//			                 if(offLine.times<sizeof(offLine.relayTimer)/sizeof(offLine.relayTimer[0]))�����ӣ�
//                          {offLine.times++;
//					               	offLine.relayTimer[offLine.times]=rt_tick_get()/1000;}
//         ����LCDWtite �����ź�������
//         LCDDataSend�з����������5ms��ʱ ��2���������ݰ��ְ� ����lcd��ʶ�𲻳�
//V1.07    ����timeQuckIncSet() ��������һ����ʼֵ�����ٲ��Դ�����״̬ 2�����ڿ��Լ������ϴ���������ʾ
//V1.08    ���Ӿ���LCD��ʾ����     20230511
//V1.09    �޸�485_mutex �������������   20230514
//V1.10    �����������IOû������������ϵ���ϴ�״̬   20230516
//V1.11    ����ʱ���ͬ�����д��flash�н��д洢      20230523
//V1.12    ����ID���ظ����Ų� ��֤ID��Ψһ��  4������ֿ��ϴ� 
//V1.13    ��Ļ��������ID���ظ���ʾ ����LCD��ʾ�����¼ �Ķ�jsonע������ʽ
#define APP_VER       ((1<<8)+13)//0x0105 ��ʾ1.5�汾  20230516
//ע����������json��ʽ������UTF8_��ʽ���루GB2312��ʽ���ģ� �ᵼ�½���ʧ��
//    ��ӡlog���� ��[dataPhrs]err:json cannot phrase��  20230403
const char date[]="20230526";

//static    rt_thread_t tid 	= RT_NULL;
static    rt_thread_t tidW5500 	  = RT_NULL;
static    rt_thread_t tidNetRec 	= RT_NULL;
static    rt_thread_t tidNetSend 	= RT_NULL;
static    rt_thread_t tidUpkeep 	= RT_NULL;
static    rt_thread_t tidLCD      = RT_NULL;
static    rt_thread_t tidAutoCtrl = RT_NULL;


//�����ź�������
rt_mutex_t   read485_mutex=RT_NULL;//��ֹ����߳�ͬ�¶�ȡmodbus����
rt_mutex_t   lcdSend_mutex=RT_NULL;//��ֹ����߳�ͬ����lcd������
//����Ķ���
extern struct  rt_mailbox mbNetSendData;;
static char 	 mbSendPool[20];//���ͻ���20��
static char 	 mbRecPool[20];//���ͻ���20��
extern struct rt_mailbox mbNetRecData;



/* �¼����ƿ� */
struct rt_event mqttAckEvent;
 

#ifdef USE_WDT
struct rt_event WDTEvent;
#endif





//���еĶ���
struct  rt_messagequeue LCDmque;//= {RT_NULL} ;//����LCD����
uint8_t LCDQuePool[LCD_BUF_LEN];  //����lcd���г�
//����Ķ���
extern  void   netDataRecTask(void *para);//�������ݽ���
extern  void   netDataSendTask(void *para);//�������ݷ���
extern  void   upKeepStateTask(void *para);//��ʱ������� ���ڿ��ܼ��붨ʱ��ȡmodbus
extern  void   w5500Task(void *parameter);//w5500����״̬��ά��
extern  void   hardWareDriverTest(void);
extern  void   LCDTask(void *parameter);
extern  void   autoCtrlTask(void *para);

extern  void   WDTTask(void *parameter);
const  static char sign[]="[main]";
extern rt_bool_t gbNetState;

/* ��ʱ���Ŀ��ƿ� */
static rt_timer_t timer1;

//static int cnt = 0;
/* ��ʱ��1��ʱ���� */
//10������һ�� uart offline״̬
static void timeout1(void *parameter)
{
		static int count=0;
	  static int alarmTick=10;
		extern rt_bool_t gbNetState;
	  extern void timeInc();
	  //extern void modbusWorkErrCheck(void);
	  count++;
	  if(count%10==0)
				timeInc();
		if(gbNetState==RT_TRUE){
				if(count%10==0){
						HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
				}
		}
		else
				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		if(count%alarmTick==0){
			  alarmTick+=20;
			  if(alarmTick>=100){
						alarmTick=100;// 1 2 3 ����10������һ��
				}

//				modbusWorkErrCheck();//modbus ������״̬��ӡ
//				errConfigCheck();//	modbusWorkErrCheck();//errConfigCheck();
				//modbusPrintRead();
//				if(gbNetState ==RT_FALSE){
//						rt_kprintf("%sERR:�������\n",sign);
//				}
		}
}
char *strnum="1234.5678";
//double atof(const char *s);

//char testNum[4]={1,2,3,4};
void  outIOInit(void);
int main(void)
{

//		RELAY1_ON;
//		RELAY2_ON;
//		RELAY3_ON;
//		RELAY4_ON;//�ϵ���ⲿ485ȫ����

		
		
	  rt_kprintf("\n%\n",sign,date,(uint8_t)(APP_VER>>8),(uint8_t)APP_VER);
    rt_kprintf("\n%s%s  ver=%02d.%02d\n",sign,date,(uint8_t)(APP_VER>>8),(uint8_t)APP_VER);
//	if(1.00001==1)
//		rt_kprintf("(1.00001==1)\n");
//	if(1.0000000==1)
//		rt_kprintf("(1.00000==1)\n");
	 // rt_kprintf("[%s %f]\n",strnum,atof(strnum));
	  //rt_kprintf("name %s  %s\n",modbusName[0],modbusName_utf8[0]);
	  rt_err_t result;
		stm32_flash_read(FLASH_IP_SAVE_ADDR,    (uint8_t*)&packFlash,sizeof(packFlash));
		stm32_flash_read(FLASH_MODBUS_SAVE_ADDR,(uint8_t*)&sheet,    sizeof(sheet));
	  outIOInit();
	
		if(packFlash.acuId[0]>=0x7F){
				rt_strcpy(packFlash.acuId,"000000000000001");//������� ִ��cJSON_AddStringToObject(root, "acuId",(char *)packFlash.acuId);
		}    
		if(packFlash.utcTime==0xffffffffffffffff){
				packFlash.utcTime=0;
		}

		
		  /* ������ʱ�� ���ڶ�ʱ�� */
    timer1 = rt_timer_create("timer1", timeout1,
                             RT_NULL, 100,
                             RT_TIMER_FLAG_PERIODIC);
		if (timer1 != RT_NULL)
        rt_timer_start(timer1);
		//����485�豸�õ��Ļ��� ����
		read485_mutex= rt_mutex_create("read485_mutex", RT_IPC_FLAG_FIFO);
		if (read485_mutex == RT_NULL)
    {
        rt_kprintf("%screate read485_mutex failed\n",sign);
    }
		lcdSend_mutex= rt_mutex_create("lcdSend_mutex", RT_IPC_FLAG_FIFO);
		if (lcdSend_mutex == RT_NULL)
    {
        rt_kprintf("%screate lcdSend_mutex failed\n",sign);
    }
		int ret = rt_mq_init(&LCDmque,"LCDrecBuf",&LCDQuePool[0],1,LCD_BUF_LEN,RT_IPC_FLAG_FIFO);       
		if (ret != RT_EOK)
		{
				rt_kprintf("%sinit LCD msgque failed.\n",sign);
				return -1;
		}
		extern void 	uartMutexQueueCreate();
		uartMutexQueueCreate();
////////////////////////////////////����//////////////////////////////////
		

    result = rt_mb_init(&mbNetRecData,"mbRec",&mbRecPool[0],sizeof(mbRecPool)/4,RT_IPC_FLAG_FIFO);         
    if (result != RT_EOK)
    {
        rt_kprintf("%sinit mailbox NetRecData failed.\n",sign);
        return -1;
    }
    result = rt_mb_init(&mbNetSendData,"mbSend",&mbSendPool[0],sizeof(mbSendPool)/4,RT_IPC_FLAG_FIFO);         
    if (result != RT_EOK)
    {
        rt_kprintf("%sinit mailbox NetSend failed.\n",sign);
        return -1;
    }
#ifdef  USE_WDT   
		if (rt_event_init(&WDTEvent, "WDTEvent", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        rt_kprintf("%sinit WDTEvent failed.\n",sign);

    }
#endif
		

////////////////////////////////����////////////////////////////////////
    tidW5500 =  rt_thread_create("w5500",w5500Task,RT_NULL,1024,3, 10 );
		if(tidW5500!=NULL){
				rt_thread_startup(tidW5500);													 
				rt_kprintf("%sRTcreat w5500Task task\r\n",sign);
		}
		tidNetRec =  rt_thread_create("netRec",netDataRecTask,RT_NULL,1024,2, 10 );
		if(tidNetRec!=NULL){
				rt_thread_startup(tidNetRec);													 
				rt_kprintf("%sRTcreat netDataRecTask \r\n",sign);
		}
		tidNetSend =  rt_thread_create("netSend",netDataSendTask,RT_NULL,1024,2, 10 );
		if(tidNetSend!=NULL){
				rt_thread_startup(tidNetSend);													 
				rt_kprintf("%sRTcreat netDataSendTask \r\n",sign);
		}

		
		tidUpkeep 	=  rt_thread_create("upKeep",upKeepStateTask,RT_NULL,512*3,4, 10 );
		if(tidUpkeep!=NULL){
				rt_thread_startup(tidUpkeep);													 
				rt_kprintf("%sRTcreat upKeepStateTask \r\n",sign);
		}
		tidLCD    =  rt_thread_create("LCD",LCDTask,RT_NULL,512*3,2, 10 );
		if(tidLCD!=NULL){
				rt_thread_startup(tidLCD);													 
				rt_kprintf("%sRTcreat LCDStateTask \r\n",sign);
		}
		tidAutoCtrl =  rt_thread_create("autoCtrl",autoCtrlTask,RT_NULL,1024,5, 10 );
		if(tidAutoCtrl!=NULL){
				rt_thread_startup(tidAutoCtrl);													 
				rt_kprintf("%sRTcreat autoCtrlTask\r\n",sign);
		}
#ifdef  USE_WDT
		extern IWDG_HandleTypeDef hiwdg;
		static    rt_thread_t tidWDT      = RT_NULL;
		tidWDT =  rt_thread_create("WDT",WDTTask,RT_NULL,256,10, 10 );
		if(tidWDT!=NULL){
				rt_thread_startup(tidWDT);													 
				rt_kprintf("%sRTcreat WDTTask\r\n",sign);
		}
	

		HAL_IWDG_Refresh(&hiwdg);
#endif	
		//���г�ʼ��֮���ٿ��������жϽ���
//		char test[50]={0};
//			uint32_t a=4294967290;
//			sprintf(test,"long:%u", a);//"monitoringTime":"1655172531937"
//			rt_kprintf("%s %s \r\n",sign,test);
//////////////////////////////����//////////////////////////////////////
    while (0)//task���ڲ��� �Լ����Ʋ���
    {
				hardWareDriverTest();
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
				rt_thread_mdelay(250);
			  extern rt_bool_t gbNetState;
			  if(gbNetState==RT_TRUE){
					  rt_thread_mdelay(250);
						
				}
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
				rt_thread_mdelay(250);
				if(gbNetState==RT_TRUE){
					  rt_thread_mdelay(250);	
				}
    }
}
//tasklog delete  �̹߳���ʱ�����ɾ��   
void  tasklog(int argc, char *argv[])
{
		if(argc!=2){
				goto ERR;
		}
		if(rt_strcmp("delete",argv[1])==0){
			  if((tidW5500->stat & RT_THREAD_STAT_MASK)==RT_THREAD_SUSPEND)
						rt_thread_delete(tidW5500);
				if((tidNetRec->stat & RT_THREAD_STAT_MASK)==RT_THREAD_SUSPEND)
						rt_thread_delete(tidNetRec);
				if((tidNetSend->stat & RT_THREAD_STAT_MASK)==RT_THREAD_SUSPEND)
						rt_thread_delete(tidNetSend);
				if((tidUpkeep->stat & RT_THREAD_STAT_MASK)==RT_THREAD_SUSPEND)
						rt_thread_delete(tidUpkeep);
				if((tidAutoCtrl->stat & RT_THREAD_STAT_MASK)==RT_THREAD_SUSPEND)
						rt_thread_delete(tidAutoCtrl);
			  rt_kprintf("%s[tasklog delete OK]\n",sign);
			  return;
		}
		ERR:
		rt_kprintf("%serr for example:\n",sign);
		rt_kprintf("%s[tasklog delete]\n",sign);
}
MSH_CMD_EXPORT(tasklog,tasklog del);//FINSH_FUNCTION_EXPORT_CMD

