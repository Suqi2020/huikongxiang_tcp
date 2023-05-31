
#ifndef  __MODBUS_DATA_H__
#define  __MODBUS_DATA_H__
#include  "stdint.h"
typedef struct
{
	  //环流值 放大了100倍
		float circlCurA;
		float circlCurB;
	  float circlCurC;
	  float circlCurD;//备用
	  //阈值
	  //uint32_t thresholdVal;

	  
	  //报警状态  一个字节足够 方便对接modbus回应
	  uint16_t warningA;
	  uint16_t warningB;
	  uint16_t warningC;
	  uint16_t warningD;
	  
	  //采集间隔 单位秒
		//uint16_t AcqInterv;
	//小数点计算数值
    uint16_t point; //非modbus真实值  此处读取modbus后经过了转换便于直接计算  0-值为100  1-2 值为10
	  uint8_t respStat;
} CIRCURStru;



 typedef struct  
 { 
  unsigned a:1; 
  unsigned b:3; 
  unsigned c:4; 
 } bs; 
 
//局放读取用到的参数定义 不包括图谱
typedef struct{
		uint32_t amplitudeA;
	  uint32_t freqA;
	  uint32_t dischargeA;
	
		uint32_t amplitudeB;
		uint32_t freqB;
		uint32_t dischargeB;

		uint32_t amplitudeC;
		uint32_t freqC;
		uint32_t dischargeC;
	
	  bs alarm;  //bit0 A bit1 B bit2 C
	  uint8_t respStat;
}partDischargeStru;
//沉降仪
typedef struct{
	  float temp;//除以100 传输float类型  单位0C
	   union {
				float flotVal;
				int   intVal;
		} height;
		uint8_t respStat;
//float height;//除以10 传输float类型  单位mm
}pressSettlStru;

//防外破
typedef struct{
		float temp;
	  uint16_t acclrationX;
		uint16_t acclrationY;
		uint16_t acclrationZ;
	  uint8_t  respStat;
}threeAxisStru;
#endif

