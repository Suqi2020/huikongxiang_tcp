#include   "NetJsonDataTask.h"
#include   "board.h"


rt_bool_t gbRegFlag = RT_FALSE;
extern struct rt_mailbox mbNetSendData;
extern uint8_t   packBuf[TX_RX_MAX_BUF_SIZE];
extern rt_bool_t gbNetState;
const static char task[]="[dataUp]";




extern void 	readPSTempHeight(int num);
extern void  	PSTempHeightPack(void);
extern void  	readThreeTempAcc(int num);
extern void		t3AxisTempAccPack(void);
//extern void 	devIDFlashRead(void);
extern void 	cirCurrConf(void);
#define TIM_NUM  MODBUS_NUM+3+10 //目前支持6路定时器  
typedef struct 
{
		uint16_t count;     //计数
	  uint16_t threshoVal;//阈值
}timerStru;
static timerStru tim[TIM_NUM];
//给个定时值


//启动从0开始计时
static void timeStart(upDataTimEnum num)
{
		tim[num].count=0;
}
//初始化后会自动运行
//num 第几个定时器
//value 定时器值
//firstCnt 第一次计数值  为了防止定时器值同时到达 
 void timeInit(upDataTimEnum num,int value,int firstCnt)
{
	  if(value==0){   // if((num>=TIM_NUM)||(value==0)){ 
				rt_kprintf("%stim[%d] inint failed \n",task,num);
				return;
		}
	//	rt_kprintf("tim init %d %d\n",num,value);
		tim[num].threshoVal=value;
		tim[num].count=firstCnt;
}
//每1秒递增一次
static void timeInc()
{
	  for(int i=0;i<TIM_NUM;i++){
			  if(tim[i].count!=0xFFFF)
						tim[i].count++;
		}
}

//停止
 void timeStop(upDataTimEnum num)
{
		tim[num].count=0xFFFF;
}
//void stopModbusDev(upDataTimEnum num)
//{
//	   timeStop(num);//偏移地址2
//}

//定时时间到
static int timeOut()
{
	  for(int i=0;i<TIM_NUM;i++){
				if(tim[i].count!=0xFFFF){
						if(tim[i].count>=tim[i].threshoVal){
	
							timeStart((upDataTimEnum)i);
							//rt_kprintf("tim out %d %d\n",i,10);
							return i;
						}
				}
		}
		return 0xff;
}



extern void pressSettRead2Send(rt_bool_t netStat,bool respFlag);
extern void threeAxisRead2Send(rt_bool_t netStat,bool respFlag);
extern void partDischagRead2Send(rt_bool_t netStat,bool respFlag);
extern void circulaRead2Send(rt_bool_t netStat,bool respFlag);
extern void waterDepthRead2Send(rt_bool_t netStat,bool respFlag);
extern void tempHumRead2Send(rt_bool_t netStat,bool respFlag);
extern void o2Read2Send(rt_bool_t netStat);
extern void h2sRead2Send(rt_bool_t netStat);	
extern void ch4Read2Send(rt_bool_t netStat);	
extern void coRead2Send(rt_bool_t netStat);	
//void analogTempHumJsonPack(uint8_t chanl);
#ifndef     ANA_MASK
extern void anaTempHumReadPack2Send(bool gbNetState,bool respFlag);
#endif
extern  uint16_t devRegJsonPack(void);
extern  uint16_t heartUpJsonPack(void);
//extern uint8_t analogTemChanl;
extern void gasJsonPack(rt_bool_t netStat,bool respFlag);
extern  uint16_t digitalInputReport(void);
extern  uint16_t digitalOutputReport(char *identify);
extern  void crackMeterRead2Send(rt_bool_t netStat,bool respFlag);




//static char name[8000]="The Chinese economy started off the year with better-than-expected 4.5 percent year-on-year growth in the first quarter, laying a solid foundation for the full-year economic rebound in 2023 while providing stronger impetus for global economic recovery amid a volatile international environment.\
China's GDP 4.5 perct accordingqwertyuiopasdfghjkl;zxcvbnm1to don Tuesday.\
Overall, the economy showed month-on-month recovery trend in the first quarter, with total retail sales far beating market expectations in March, reflecting that consumer confidence has gradually been restored, Chen Fengying, an economist and former director of the Institute of World Economic Studies at the China Institutes of Contemporary International Relations, told the Global Times on Tuesday.\
The country's total retail sales grew by 5.8 percent year-on-year in the first quarter, reversing a downward trend of 2.7 percent year-on-year seen in the fourth quarter of 2022. Specifically, total retail sales increased by 10.6 percent year-on-year in March, according to NBS data.\
\"The first-quarter macroeconomic figures indicate notable optimization of China's economic structure, with continuous industrial transformation and upgrading,\" Wan Zhe, an economist and professor at the Belt and Road School of Beijing Normal University, told the Global Times on Tuesday.\
China's push for innovation in bottle-neck technologies promotes basic and applied research and accelerates digital transformation across various industries, consolidating the growth momentum of the Chinese economy, she said.\
While the fixed-asset investment grew 5.1 percent year-on-year in the first quarter, the investment in high-tech industries increased by 16 percent and the investment in e-commerce services surged by 51.5 percent, official data showed. \"This indicates China's economic transformation is accelerating, and we're ushering in a digital economy and high-tech transformation,\" Chen said.\
The Chinese economy started off the year with better-than-expected 4.5 percent year-on-year growth in the first quarter, laying a solid foundation for the full-year economic rebound in 2023 while providing stronger impetus for global economic recovery amid a volatile international environment.\
China's GDP in the first three months reached 28.5 trillion yuan ($4.15 trillion), up 4.5 percent year-on-year, or an increase of 2.2 percent compared with the fourth quarter of 2022, according to data released by the National Bureau of Statistics (NBS) on Tuesday.\
The growth is hard-won against grave and complex international environment, NBS Spokesperson Fu Linghui said, noting that positive factors kept accumulating in the first quarter, as multiple supportive policies and measures took effect early on.\
Overall, the economy showed month-on-month recovery trend in the first quarter, with total retail sales far beating market expectations in March, reflecting that consumer confidence has gradually been restored, Chen Fengying, an economist and former director of the Institute of World Economic Studies at the China Institutes of Contemporary International Relations, told the Global Times on Tuesday.\
The country's total retail sales grew by 5.8 percent year-on-year in the first quarter, reversing a downward trend of 2.7 percent year-on-year seen in the fourth quarter of 2022. Specifically, total retail sales increased by 10.6 percent year-on-year in March, according to NBS data.\
\"The first-quarter macroeconomic figures indicate notable optimization of China's economic structure, with continuous industrial transformation and upgrading,\" Wan Zhe, an economist and professor at the Belt and Road School of Beijing Normal University, told the Global Times on Tuesday.\
China's push for innovation in bottle-neck technologies promotes basic and applied research and accelerates digital transformation across various industries, consolidating the growth momentum of the Chinese economy, she said.\
While the fixed-asset investment grew 5.1 percent year-on-year in the first quarter, the investment in high-tech industries increased by 16 percent and the investment in e-commerce services surged by 51.5 percent, official data showed. \"This indicates China's economic transformation is accelerating, and we're ushering in a digital economy and high-tech transformation,\" Chen said.\
Despite external uncertainties and challenges, China's exports rose by 23.4 percent year-on-year in yuan-denominated terms in March, exceeding market expectations significantly.\
China's investment in green and low carbon development in advance under the high-quality development, high-standard opening-up and the Belt and Road Initiative ensures resilience in exports despite growing protectionism, potential economic recession in the US and the EU and other risks, Wan said.\
The better-than-expected macroeconomic figures have boosted international financial institutions' upbeat sentiment on China's economic growth this year.\
\"The macroeconomic data for the first quarter of 2023 implies the positive feedback from the Chinese economy on the optimization of COVID-19 prevention measures, and we maintain our optimistic attitude towards China's economic growth in 2023,\" Darius Tang, Associate Director of Corporates of Fitch Bohua, a subsidiary of Fitch Ratings, said in a note sent to the Global Times.\
In addition, JP Morgan upgraded their forecast for China to 6.4 percent year-on-year from a previous estimate of 6.0 percent year-on-year, according to media reports\
Looking ahead, China's economic performance will continue to see overall improvement on the back of strengthening internal momentum and stepped-up policies, Fu said, noting that China's economic growth will notably speed up in the second quarter.\
\"The economy will likely further rebound to as high as 8 percent between April and June given a lower base the same quarter last year,\" Chen said, noting that the full-year GDP growth rate will probably exceed the around 5 percent target set during this year's two sessions.\
However, we must be aware that the situation abroad is still complex and volatile, inadequate domestic demand remains prominent and the foundation for economic recovery is not solid yet, Wu Chaoming, deputy head of the Chasing Research Institute, told the Global Times on Tuesday.\
He said efforts should be made to further stimulate private investment and real estate while increasing residents' actual income for tapping the potential of the huge domestic market and bolstering full-fledged economic recovery this year.\
China's remarkable economic performance serves as \"a slap in the face\" of Western media that badmouth China's recovery in the post-COVID-19 era. For instance, some media have hyped about deflation worries while others are undermining China's export and consumption prospects regardless of facts.\
\"The current Chinese economy does not appear deflated and in the near future deflation is not likely,\" Fu said. Seasonal factors, price drop in international bulk commodities and geopolitics jointly contributed to domestic price drop but the price will recover to a reasonable level along with the disappearance of these factors in the second half of the year, he said.\
With promising prospect for full-year economic recovery, China will provide stronger impetus to the world economy and be a stabilizer in volatile international environment, analysts said.\
\"The robust rebound means China is set to account for around one third of global growth in 2023 - giving a welcome lift to the world economy,\" Kristalina Georgieva, Managing Director of the IMF, said at the China Development Forum in March.\
The robust rebound means China is set to account for around one third of global growth in 2023—giving a welcome lift to the world economy. And beyond the direct contribution to global growth, our analysis shows that a 1 percentage point increase in GDP growth in China leads to 0.3 percentage point increase in growth in other Asian economies, on average—a welcome boost.";


//static char name2[1000]="The Chinese economy started off the year with better-than-expected 4.5 percent year-on-year growth in the first quarter, laying a solid foundation for the full-year economic rebound in 2023 while providing stronger impetus for global economic recovery amid a volatile international environment.\
China's GDP in the first three months reached 28.5 trillion yuan ($4.15 trillion), up 4.5 percent year-on-year, or an increase of 2.2 percent compared with the fourth quarter of 2022, according to data released by the National Bureau of Statistics (NBS) on Tuesday.\
The robust rebound means China is set to account for around one third of global growth in 2023—giving a welcome lift to the world economy. And beyond the direct contribution to global growth, our analysis shows that a 1 percentage point increase in GDP growth in China leads to 0.3 percentage point increase in growth in other Asian economies, on average—a welcome boost.";


//{
//			"model":	"GY299",
//			"name":	"FangChenJiang",
//			"deviceId":	"GYNJLXSD000000677"
//		}
//void jsonBufPackTest()
//{
//	 

//			sprintf((char *)packBuf,"%s",name);

//	
//}

//定时时间到  执行相应事件
static void  timeOutRunFun()
{

		rt_mutex_take(read485_mutex,RT_WAITING_FOREVER);
		switch(timeOut()){
			case HEART_TIME://心跳
				heartUpJsonPack();
				//jsonBufPackTest();
			  if(gbNetState==RT_TRUE)
						rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
			  rt_kprintf("%sheart timer out\r\n",task);
				break;
			case REG_TIME://注册 注册成功后定时器就关闭 输入输出状态跟谁注册信息上发
			  if(gbRegFlag==RT_FALSE){
//					 jsonBufPackTest();
//					rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
//					break;//suqi
					  devRegJsonPack();//devRegJsonPack();
					  if(gbNetState==RT_TRUE)
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
					  timeStop(REG_TIME);//正式使用时候需要去掉
						if(gbNetState==RT_TRUE){
							  digitalInputReport();//数字输入上报
								rt_thread_delay(500);
								
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
								digitalOutputReport("3v3_output");
								rt_thread_delay(500);
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
								digitalOutputReport("5v_output");
								rt_thread_delay(500);
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
								digitalOutputReport("12v_output");
								rt_thread_delay(500);
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
								digitalOutputReport("digital_output");
								rt_thread_delay(500);
								rt_mb_send_wait(&mbNetSendData, (rt_ubase_t)&packBuf,RT_WAITING_FOREVER); 
						}
				}
				else
						timeStop(REG_TIME);
				rt_kprintf("%sreg timer out\r\n",task);
				break;
			case CIRCULA_TIME://读取环流
				circulaRead2Send(gbNetState,false);
				rt_kprintf("%sCIRCULA_TIME out\r\n",task);
				break;
			case PARTDISCHAG_TIME://读取局放
				partDischagRead2Send(gbNetState,false);
				rt_kprintf("%sPARTDISCHAG_TIME out\r\n",task);
				break;
			case PRESSSETTL_TIME:
        pressSettRead2Send(gbNetState,false);
				rt_kprintf("%sPRESSSETTL_TIME out\r\n",task);
				break;
			case THREEAXIS_TIME:
				threeAxisRead2Send(gbNetState,false);
				rt_kprintf("%sTHREEAXIS_TIMEout\r\n",task);
				break;

//			case  CH4_TIME:
//				ch4Read2Send(gbNetState);
//				break;
//			case  O2_TIME:
//				o2Read2Send(gbNetState);
//				break;
//			case  H2S_TIME:
//				h2sRead2Send(gbNetState);
//				break;
			case  GAS_TIME://4种气体在一起读取 所以前三个不使用 只在此处读取并打包发送  关闭时候只需要关闭CO就可以把所有气体全部关闭
		#ifdef USE_4GAS 	
   			ch4Read2Send(gbNetState);
				o2Read2Send(gbNetState);
				h2sRead2Send(gbNetState);
			  coRead2Send(gbNetState);
			  gasJsonPack(gbNetState,false);
		#endif
				break;
			case  TEMPHUM_TIME:
				tempHumRead2Send(gbNetState,false);
				break;
			case  WATERDEPTH_TIME:
				waterDepthRead2Send(gbNetState,false);
				break;
			case CRACKMETER_TIME:
				crackMeterRead2Send(gbNetState,false);
				rt_kprintf("%sTHREEAXIS_TIMEout\r\n",task);
				break;
#ifndef     ANA_MASK
			case  ANA_TEMPHUM_TIME:
//				analogTempHumJsonPack(analogTemChanl);
			  anaTempHumReadPack2Send(gbNetState,false);
		
				break;
#endif
			rt_mutex_release(read485_mutex);
			default:
				break;
		}
}

modbusFunStru modbusFun[MODBUS_NUM];
//启动定时器列表
void startTimeList()
{
    for(int k=0;k<TIM_NUM;k++){
			timeStop((upDataTimEnum)k);
		}
		
		#if 0
		timeInit(HEART_TIME,      120,2);//心跳定时  定时30秒 第一次28秒就来
		timeInit(REG_TIME,        5,0);//注册 注册成功后定时器就关闭
		timeInit(CIRCULA_TIME, 		5,5);
		timeInit(PARTDISCHAG_TIME,5,10);
		timeInit(PRESSSETTL_TIME, 8,15);
		timeInit(THREEAXIS_TIME,  8,20);
//	  timeInit(H2S_TIME, 				sheet.h2sColTime,24);
//		timeInit(CH4_TIME, 				sheet.ch4ColTime,28);
//		timeInit(O2_TIME, 				sheet.o2ColTime,30);

		timeInit(GAS_TIME, 				10,35);

		timeInit(TEMPHUM_TIME, 		12,40);
		timeInit(WATERDEPTH_TIME, 15,45);
		timeInit(CRACKMETER_TIME, 16,50);
		#else 
		timeInit(HEART_TIME,      120,2);//心跳定时  定时30秒 第一次28秒就来
		timeInit(REG_TIME,        5,0);//注册 注册成功后定时器就关闭
		timeInit(CIRCULA_TIME, 		sheet.cirCulaColTime,5);
		timeInit(PARTDISCHAG_TIME,sheet.partDischagColTime,10);
		timeInit(PRESSSETTL_TIME, sheet.pressSetlColTime,15);
		timeInit(THREEAXIS_TIME,  sheet.threeAxissColTime,20);
//	  timeInit(H2S_TIME, 				sheet.h2sColTime,24);
//		timeInit(CH4_TIME, 				sheet.ch4ColTime,28);
//		timeInit(O2_TIME, 				sheet.o2ColTime,30);

		timeInit(GAS_TIME, 				sheet.gasColTime,35);

		timeInit(TEMPHUM_TIME, 		sheet.tempHumColTime,40);
		timeInit(WATERDEPTH_TIME, sheet.waterDepthColTime,45);
		timeInit(CRACKMETER_TIME, sheet.crackMeterColTime,50);
		#endif
	  //启动温湿度
#ifndef     ANA_MASK
	  for(int i=0;i<ANALOG_NUM;i++){
				if(rt_strcmp(sheet.analog[i].name,analogName[0])==0){//用 analogName[0]  指明是温湿度
					  if(sheet.analog[i].workFlag==RT_TRUE){
								timeInit(ANA_TEMPHUM_TIME,sheet.analog[i].colTime,30);
								//timeInit(ANA_TEMPHUM_TIME,10,30);
//								analogTemChanl=i;
						}
						break;
				}
		}
#endif
}

//char nihao[]="你好局放防沉降防外破";
//


#if 1
//上行数据的维护以及重发
void   upKeepStateTask(void *para)
{
		//extern void modbusPrintRead();
		extern void uartReconfig();
		extern void uartIrqEnaAfterQueue();
	  extern void clearUartData();
//	  extern void printModbusDevList();
	  extern void readMultiCirCulaPoint();
//	  extern void prinfAnalogList();
//	  extern void printfDIList();
//	  extern void printfOutputList();
//		extern void printfThresholdList();
//		extern void printfCtrl();
	//  uartMutexQueueCfg();//根据flash存储重新配置串口
//		modbusPrintRead();//modbus配置从flash中读取
	  uartReconfig();//串口重新配置
		uartIrqEnaAfterQueue();//串口中断中用到了队列  开启中断需要放到后边
    startTimeList();//开启计时器列表
	  clearUartData();
	  readMultiCirCulaPoint();//对于环流来讲 运行前需要提取扩大方式
		while(1){
				timeOutRunFun();
				timeInc();
				rt_thread_mdelay(1000);
#ifdef  USE_WDT
			  rt_event_send(&WDTEvent,EVENT_WDT_UPTASK);
#endif		  
		}
}


#endif

