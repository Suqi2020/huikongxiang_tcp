
#ifndef  __MODBUS_DATA_H__
#define  __MODBUS_DATA_H__
#include  "stdint.h"
typedef struct
{
	  //����ֵ �Ŵ���100��
		float circlCurA;
		float circlCurB;
	  float circlCurC;
	  float circlCurD;//����
	  //��ֵ
	  //uint32_t thresholdVal;

	  
	  //����״̬  һ���ֽ��㹻 ����Խ�modbus��Ӧ
	  uint16_t warningA;
	  uint16_t warningB;
	  uint16_t warningC;
	  uint16_t warningD;
	  
	  //�ɼ���� ��λ��
		//uint16_t AcqInterv;
	//С���������ֵ
    uint16_t point; //��modbus��ʵֵ  �˴���ȡmodbus�󾭹���ת������ֱ�Ӽ���  0-ֵΪ100  1-2 ֵΪ10
	  uint8_t respStat;
} CIRCURStru;



 typedef struct  
 { 
  unsigned a:1; 
  unsigned b:3; 
  unsigned c:4; 
 } bs; 
 
//�ַŶ�ȡ�õ��Ĳ������� ������ͼ��
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
//������
typedef struct{
	  float temp;//����100 ����float����  ��λ0C
	   union {
				float flotVal;
				int   intVal;
		} height;
		uint8_t respStat;
//float height;//����10 ����float����  ��λmm
}pressSettlStru;

//������
typedef struct{
		float temp;
	  uint16_t acclrationX;
		uint16_t acclrationY;
		uint16_t acclrationZ;
	  uint8_t  respStat;
}threeAxisStru;
//��ʪ��
typedef struct{
	float temp;
	float hum; 
	uint8_t respStat;
}thStru;


//�ѷ���
typedef struct{
	  //float temp;//����100 ����float����  ��λ0C
	   union {
				float flotVal;
				uint32_t   intVal;
		} distanc;
		 union {
				float flotVal;
				uint32_t   intVal;
		} temp;
		uint8_t respStat;
//float height;//����10 ����float����  ��λmm
}crackMeterStru;
//����
typedef struct{
	uint8_t incline;//��б״̬ 1-��б
	uint8_t switch2p;//2��״̬ 1-��
	uint8_t	vibration;//�𶯱���  1-��
	uint8_t switch1p;//1��״̬ 1-��
	uint8_t respStat;
}coverStru;

#endif

