#ifndef __MODBUSCONFIG_H__
#define __MODBUSCONFIG_H__
//#include "uartReconf.h"
#include  "board.h"


#define  MODL_LEN     8


typedef  enum{
		AIR_ENVIRONMENT=1,//(1, "��������"),  //������ʪ�� ����
    WATER_LEVEL,//(2, "ˮλ"),
    DISCHARGE,//(3, "�ַ�"),
    GROUNDING_CURRENT,//(4, "����"),
    OPTICAL_FIBER,//(5, "���˲���"),
    VIBRATION,//(6, "����"),
    SETTLEMENT,//(7, "����"),
    SWITCH_CONTROL,//(8, "���/ˮ��");
	  CRACK_TESTER,//(9,"�ѷ���");
	  MANHOLE_COVER//(10,"����");
}regTypeEnum;
typedef enum{
		USE_UART2=0,
	  USE_UART3,
	  USE_UART6,
	  USE_UART4,
	  USE_DIS_UART=0XFF
}uartEnum;////


typedef struct{
		bool 	workFlag;
 		uartEnum  	useUartNum;
		uint16_t  	slaveAddr; //0-255
		char  ID[MODBID_LEN];
		char  model[MODL_LEN];

}modbusStru;
//modbus��������ʪ��
typedef struct{
		float tempUpLimit;
		float tempLowLimit;
		float humUpLimit;
		float humLowLimit;

}tempHumStru_p;
typedef struct{
		
	  uint32_t  tempUpFlag;//��ֵ���޵ı��
	  uint32_t  tempLowFlag;
	  uint32_t  humUpFlag;
	  uint32_t  humLowFlag;
}tempHumFlagStru;
//modbus������������
typedef struct{
		float tempUpLimit;
	  float tempLowLimit;
	  uint16_t accXUpLimit;
	  uint16_t accXLowLimit;
	  uint16_t accYUpLimit;
	  uint16_t accYLowLimit;
	  uint16_t accZUpLimit;
	  uint16_t accZLowLimit;
}threeAxisStru_p;
typedef struct{
		uint32_t  tempUpFlag;//��ֵ���޵ı��
		uint32_t  tempLowFlag;
		uint32_t  accXUpFlag;
		uint32_t  accXLowFlag;
		uint32_t  accYUpFlag;
		uint32_t  accYLowFlag;
		uint32_t  accZUpFlag;
		uint32_t  accZLowFlag;
}threeAxisFlagStru;
//modbus���� ������
typedef struct{
	  float tempUpLimit;
		float tempLowLimit;
	  float heightUpLimit;
	  float heightLowLimit;
}pressSettlStru_p;
//modbus�����ѷ�����ֵ
typedef struct{
	  float tempUpLimit;
		float tempLowLimit;
	  float distancUpLimit;
	  float distancLowLimit;
}crackMeterStru_p;
//modbus������ֵ
typedef struct{
	  uint8_t inclineUpLimit;
	  uint8_t inclineLowLimit;
	  uint8_t switch1UpLimit;
	  uint8_t switch1LowLimit;
	  uint8_t vibrationUpLimit;
	  uint8_t vibrationLowLimit;
	  uint8_t switch2UpLimit;
	  uint8_t switch2LowLimit;
}coverStru_p;
typedef struct{
		uint32_t  tempUpFlag;//��ֵ���޵ı��
		uint32_t  tempLowFlag;
		uint32_t  heightUpFlag;
		uint32_t  heightLowFlag;
}pressSettlFlagStru;


typedef struct{
		uint32_t  tempUpFlag;//��ֵ���޵ı��
		uint32_t  tempLowFlag;
		uint32_t  distancUpFlag;
		uint32_t  distancLowFlag;
}crackMeterFlagStru;


typedef struct{
	  uint8_t inclineUpFlag;
	  uint8_t inclineLowFlag;
	  uint8_t switch2UpFlag;
	  uint8_t switch2LowFlag;
	  uint8_t vibrationUpFlag;
	  uint8_t vibrationLowFlag;
	
	  uint8_t switch1UpFlag;
	  uint8_t switch1LowFlag;
}coverFlagStru;
typedef struct
{
	  //����ֵ �Ŵ���100��
		float cirCurAUpLimit;
	  float cirCurALowLimit;
		float cirCurBUpLimit;
	  float cirCurBLowLimit;
		float cirCurCUpLimit;
	  float cirCurCLowLimit;
}circuStru_p;
typedef struct{
		uint32_t  cirCurAUpFlag;//��ֵ���޵ı��
		uint32_t  cirCurALowFlag;
		uint32_t  cirCurBUpFlag;
		uint32_t  cirCurBLowFlag;
		uint32_t  cirCurCUpFlag;
		uint32_t  cirCurCLowFlag;
}circuFlagStru;

//modbus������co
typedef struct{
		float coUpLimit;
		float coLowLimit;
}coStru_p;
typedef struct{
		uint32_t  coUpFlag;//��ֵ���޵ı��
		uint32_t  coLowFlag;
}coFlagStru;
//modbus������O2
typedef struct{
		float o2UpLimit;
		float o2LowLimit;
}o2Stru_p;
typedef struct{
	  uint32_t  o2UpFlag;//��ֵ���޵ı��
		uint32_t  o2LowFlag;
}o2FlagStru;
//modbus������ch4
typedef struct{
		float ch4UpLimit;
		float ch4LowLimit;
}ch4Stru_p;
typedef struct{
	  uint32_t  ch4UpFlag;//��ֵ���޵ı��
		uint32_t  ch4LowFlag;
}ch4FlagStru;
//modbus������h2s
typedef struct{
		float h2sUpLimit;
		float h2sLowLimit;
}h2sStru_p;
typedef  struct{
	  uint32_t  h2sUpFlag;//��ֵ���޵ı��
		uint32_t  h2sLowFlag;
}h2sFlagStru;
//modbus������waterLev
typedef struct{
		float depthUpLimit;
		float depthLowLimit;
}depthStru_p;
typedef struct{
	  uint32_t  depthUpFlag;//��ֵ���޵ı��
		uint32_t  depthLowFlag;
}depthFlagStru;

//modbus������partDischarg
typedef struct{
		uint32_t amplitudeAUpLimit;
		uint32_t amplitudeALowLimit;
		uint32_t freqAUpLimit;
		uint32_t freqALowLimit;
		uint32_t dischargeAUpLimit;
		uint32_t dischargeALowLimit;
	
		uint32_t amplitudeBUpLimit;
		uint32_t amplitudeBLowLimit;
		uint32_t freqBUpLimit;
		uint32_t freqBLowLimit;
		uint32_t dischargeBUpLimit;
		uint32_t dischargeBLowLimit;

		uint32_t amplitudeCUpLimit;
		uint32_t amplitudeCLowLimit;
		uint32_t freqCUpLimit;
		uint32_t freqCLowLimit;
		uint32_t dischargeCUpLimit;
		uint32_t dischargeCLowLimit;
}partDisChgStru_p;
typedef struct{
	  uint32_t  amplitudeAUpFlag;//��ֵ���޵ı��
		uint32_t  amplitudeALowFlag;
	  uint32_t  amplitudeBUpFlag;
		uint32_t  amplitudeBLowFlag;
		uint32_t  amplitudeCUpFlag;
		uint32_t  amplitudeCLowFlag;
		
	  uint32_t  freqAUpFlag;//��ֵ���޵ı��
		uint32_t  freqALowFlag;
	  uint32_t  freqBUpFlag;
		uint32_t  freqBLowFlag;
		uint32_t  freqCUpFlag;
		uint32_t  freqCLowFlag;

	  uint32_t  dischargeAUpFlag;//��ֵ���޵ı��
		uint32_t  dischargeALowFlag;
	  uint32_t  dischargeBUpFlag;
		uint32_t  dischargeBLowFlag;
		uint32_t  dischargeCUpFlag;
		uint32_t  dischargeCLowFlag;
}partDisChgFlagStru;



#define GAS_NUM               2
#define THREEAXIS_485_NUM     40
#define PRESSSETTL_485_NUM    40
#define CIRCULA_485_NUM   	  5
#define PARTDISCHAG_485_NUM   5
#define CRACKMETER_485_NUM    20
#define COVER_485_NUM         10
#ifdef  USE_4GAS
#define CH4_485_NUM   			  GAS_NUM
#define CO_485_NUM   				  GAS_NUM
#define H2S_485_NUM   			  GAS_NUM
#define O2_485_NUM   				  GAS_NUM
#endif
#define WATERDEPTH_485_NUM   	2
#define TEMPHUM_485_NUM   	  2
#ifdef  USE_4GAS
	#define TOTOLA_485_NUM     (THREEAXIS_485_NUM+\
														PRESSSETTL_485_NUM+\
														CIRCULA_485_NUM+\
														PARTDISCHAG_485_NUM+\
														CH4_485_NUM+\
														CO_485_NUM+\
														H2S_485_NUM+\
														O2_485_NUM+\
														WATERDEPTH_485_NUM+\
														TEMPHUM_485_NUM+\
														CRACKMETER_485_NUM+\
														COVER_485_NUM)
#else
	#define TOTOLA_485_NUM     (THREEAXIS_485_NUM+\
														PRESSSETTL_485_NUM+\
														CIRCULA_485_NUM+\
														PARTDISCHAG_485_NUM+\
														WATERDEPTH_485_NUM+\
														TEMPHUM_485_NUM+\
														CRACKMETER_485_NUM+\
														COVER_485_NUM)
#endif
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

//modbus+�豸����(������)+�˿�(port1-port4)+�豸��ַ(0-�ر��豸)+�ɼ����(��)
#ifdef  USE_4GAS
#define   MODBUS_NUM      11+1 //���뾮��
#else 
#define   MODBUS_NUM      7+1 //���뾮��
#endif
typedef struct{
	 void (* modbusRead)(void );
}modbusFunStru;
extern modbusFunStru modbusFun[MODBUS_NUM];
//////////////////////////////���Ӵ�������Ҫ�޸��±� һһ��Ӧ////////////////////////////////////////

//extern deviceFlashStru  modbusFlash[MODBUS_NUM];//��Ҫ�洢��flash���豸����
#ifdef  USE_4GAS
typedef enum{
     CIRCULA=0, 	PARTDISCHAG,			PRESSSETTL, 			THREEAXIS,		\
   	CH4,		O2		,H2S,			CO,			\
	  TEMPHUM,			WATERDEPTH,CRACKMETER,COVER
}modbNumEnum;
#else
typedef enum{
     CIRCULA=0, 	PARTDISCHAG,			PRESSSETTL, 			THREEAXIS,		\
	  TEMPHUM,			WATERDEPTH,CRACKMETER,COVER
}modbNumEnum;
#endif
#ifdef  USE_4GAS

#ifndef     ANA_MASK
typedef enum{
		CIRCULA_TIME=0,PARTDISCHAG_TIME,PRESSSETTL_TIME,THREEAXIS_TIME,\
	  CH4_TIME,O2_TIME,H2S_TIME,CO_TIME,\
	  TEMPHUM_TIME,WATERDEPTH_TIME,CRACKMETER_TIME,COVER_TIME,\
	  ANA_TEMPHUM_TIME,\
	HEART_TIME,REG_TIME
}upDataTimEnum;//��Ҫ��modbusName ����һһ��Ӧ ��ʵ�ִ��뾫���Ч
#else
typedef enum{
		CIRCULA_TIME=0,PARTDISCHAG_TIME,PRESSSETTL_TIME,THREEAXIS_TIME,\
	  CH4_TIME,O2_TIME,H2S_TIME,CO_TIME,\
	  TEMPHUM_TIME,WATERDEPTH_TIME,CRACKMETER_TIME,COVER_TIME,\
	HEART_TIME,REG_TIME
}upDataTimEnum;//��Ҫ��modbusName ����һһ��Ӧ ��ʵ�ִ��뾫���Ч
#endif
#else

#ifndef     ANA_MASK
typedef enum{
		CIRCULA_TIME=0,PARTDISCHAG_TIME,PRESSSETTL_TIME,THREEAXIS_TIME,\
	  TEMPHUM_TIME,WATERDEPTH_TIME,\
	  ANA_TEMPHUM_TIME,HEART_TIME,REG_TIME
}upDataTimEnum;//��Ҫ��modbusName ����һһ��Ӧ ��ʵ�ִ��뾫���Ч
#else
typedef enum{
		CIRCULA_TIME=0,PARTDISCHAG_TIME,PRESSSETTL_TIME,THREEAXIS_TIME,\
	  TEMPHUM_TIME,WATERDEPTH_TIME,\
	  HEART_TIME,REG_TIME
}upDataTimEnum;//��Ҫ��modbusName ����һһ��Ӧ ��ʵ�ִ��뾫���Ч
#endif
#endif
#ifdef  USE_4GAS

#define GAS_TIME    CO_TIME  //4�����崫����ʹ�� ͬһ����ʱ��
#else
#define GAS_TIME    22      //ʹ��һ�ֻ�����崫����ʱ����˴�
#endif

#ifdef  USE_4GAS
const static char  modbusName[MODBUS_NUM][NAME_LEN] ={"HuanLiu","JuFang","FangChenJiang","FangWaiPo","JiaWan","YangQi","LiuHuaQing","YiYangHuaTan","WenShiDu","ShuiWei","LieFengYi","JingGai"};
const static int   modbusBps[MODBUS_NUM]      ={115200,   115200  ,9600,   9600,   9600,   9600,   9600,   9600,   9600,   9600,9600,9600};
#else
const static char  modbusName[MODBUS_NUM][NAME_LEN] ={"HuanLiu","JuFang","FangChenJiang","FangWaiPo","WenShiDu","ShuiWei","LieFengYi","JingGai"};
const static int   modbusBps[MODBUS_NUM]      ={115200,   115200  ,9600,   9600,     9600,   9600,9600,9600};

//const static char  modbusName[MODBUS_NUM][NAME_LEN] ={"�ӵػ���","�ַ�","������","������","����","����","����","һ����̼","��ʪ��","ˮλ","�ѷ���"};
//const static int   modbusBps[MODBUS_NUM]      ={115200,   115200  ,9600,   9600,   9600,   9600,   9600,   9600,   9600,   9600,9600};
//#else
//const static char  modbusName[MODBUS_NUM][NAME_LEN] ={"�ӵػ���","�ַ�","������","������","��ʪ��","ˮλ","�ѷ���"};
//const static int   modbusBps[MODBUS_NUM]      ={115200,   115200  ,9600,   9600,     9600,   9600,960};

#endif
//const static int   modbusType[MODBUS_NUM]     ={1,        1,       2,      2, 		 3,  			3,  		3,  		3,  		3,  		3};//��ͬ���͵�modbus�豸������ͬ
//extern char modbusName_UTF8[MODBUS_NUM][30];
extern const  char  modbusName_utf8[MODBUS_NUM][30];
typedef struct{
///////////////////////////////////////////////////
			modbusStru  cirCula[CIRCULA_485_NUM];
			modbusStru  partDischag[PARTDISCHAG_485_NUM];
			modbusStru  pressSetl[PRESSSETTL_485_NUM];
	    modbusStru  threeAxiss[THREEAXIS_485_NUM];
#ifdef  USE_4GAS
			modbusStru  ch4[CH4_485_NUM];
	    modbusStru  o2[O2_485_NUM];
			modbusStru  h2s[H2S_485_NUM];
			modbusStru  co[CO_485_NUM];
#endif
			modbusStru  tempHum[TEMPHUM_485_NUM];
			modbusStru  waterDepth[WATERDEPTH_485_NUM];
			modbusStru  crackMeter[CRACKMETER_485_NUM];
	    modbusStru  cover[COVER_485_NUM];
///////////////////////////////////////////////////
			uint32_t  cirCulaColTime;
			uint32_t  partDischagColTime;
			uint32_t  pressSetlColTime;
	    uint32_t  threeAxissColTime;
#ifdef  USE_4GAS
	    uint32_t  REV[3]; //�˴�����ʡ�� Ϊ��lcd��ʾָ������������
			uint32_t  ch4ColTime;
	    uint32_t  o2ColTime;
			uint32_t  h2sColTime;
			uint32_t  coColTime;//��co�Ķ�ʱ�����ɼ���Ϣ  ȥ�������������嶨ʱ��  �ϲ�����ϴ�
#endif
			uint32_t  tempHumColTime;
			uint32_t  waterDepthColTime;
			uint32_t  crackMeterColTime;
			uint32_t  coverColTime;
///////////////////////////////////////////////////
#ifndef     ANA_MASK
			analogStru analog[ANALOG_NUM];
#endif
///////////////////////////////////////////////////
//������ִ�������������ֵ start  ��modbusStru һһ��Ӧ
			circuStru_p      modbusCircul[CIRCULA_485_NUM];
			partDisChgStru_p modbusPartDisChg[PARTDISCHAG_485_NUM];
			pressSettlStru_p modbusPreSettl[PRESSSETTL_485_NUM];
			threeAxisStru_p  modbusThreAxis[THREEAXIS_485_NUM];
#ifdef  USE_4GAS
			ch4Stru_p        modbusCh4[CH4_485_NUM];
			o2Stru_p         modbusO2[O2_485_NUM];
			h2sStru_p        modbusH2s[H2S_485_NUM];
			coStru_p         modbusCo[CO_485_NUM];
#endif
			tempHumStru_p	   modbusTempHum[TEMPHUM_485_NUM];
			depthStru_p			 modbusWaterDepth[WATERDEPTH_485_NUM];
			crackMeterStru_p modbusCrackMeter[CRACKMETER_485_NUM];
			coverStru_p      modbusCover[COVER_485_NUM];
		#ifndef     ANA_MASK
			tempHumStru_p    analogTempHum;//��֧�ֶ�·ģ���¶ȴ�����
		#endif
//������ִ�������������ֵ end
			
			autoCtrl_stru		 autoctrl[CRTL_TOTAL_NUM];
			
			//uint32_t         autoCrtl
			




	    
}deviceFlashStru;//�洢��flash��

typedef struct{
		uint32_t lowFlag;//�͵�ƽ
	  uint32_t upFlag;//�ߵ�ƽ
}digputFlagStru;


typedef struct{
			circuFlagStru      modbusCircul[CIRCULA_485_NUM];
			partDisChgFlagStru modbusPartDisChg[PARTDISCHAG_485_NUM];
			pressSettlFlagStru modbusPreSettl[PRESSSETTL_485_NUM];
			threeAxisFlagStru  modbusThreAxis[THREEAXIS_485_NUM];
#ifdef  USE_4GAS
			ch4FlagStru        modbusCh4[CH4_485_NUM];
			o2FlagStru         modbusO2[O2_485_NUM];
			h2sFlagStru        modbusH2s[H2S_485_NUM];
			coFlagStru         modbusCo[CO_485_NUM];
#endif
			tempHumFlagStru	   modbusTempHum[TEMPHUM_485_NUM];
			depthFlagStru			 modbusWaterDepth[WATERDEPTH_485_NUM];
	    crackMeterFlagStru modbusCrackMeter[CRACKMETER_485_NUM];
	    coverFlagStru      modbusCover[COVER_485_NUM];
			tempHumFlagStru    analogTempHum;//��֧�ֶ�·ģ���¶ȴ�����
		  digputFlagStru     digInput[DI_NUM];
	    digputFlagStru     digOutput[DO_NUM];
	    digputFlagStru     v33Output[V33O_NUM];
	    digputFlagStru     v5Output[V5O_NUM];
	    digputFlagStru     v12Output[V12O_NUM];
}inoutDevStru;
//DI���ø���Ч
extern rt_err_t uartDataRec( uartEnum uartNum,uint8_t dat);
extern deviceFlashStru sheet;
extern inoutDevStru inpoutpFlag;


//extern rt_err_t uartDataRec( uartEnum uartNum,uint8_t dat);


















#endif




