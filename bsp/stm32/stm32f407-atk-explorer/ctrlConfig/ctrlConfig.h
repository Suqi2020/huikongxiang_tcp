#ifndef __CRTL_CONFIG_H__
#define __CRTL_CONFIG_H__


#include "board.h"






#define INOUTNAME_LEN    8

//typedef struct{
//	
//}thresholdStru;

#define CRTL_IN_NUM      10   //ÿ���߼�����֧��10������
#define CRTL_OUT_NUM     5   //ÿ���߼�����֧��5���������
#define CRTL_TOTAL_NUM   20  //�ܹ�10���߼�����

typedef struct{
	  char  typeName[INOUTNAME_LEN];//������ȴ���  8
	  char  senseName[20]; 
	  char  ID[MODBID_LEN];//20
	  char  subName[20];
	  int  limit;
	  //char  rev[2];
	  uint32_t  *flag;
}ctrlInOutStru;//���ṹ��洢Ϊ�˲鿴�Ѿ����óɹ����߼������б�

typedef struct{
		ctrlInOutStru input[CRTL_IN_NUM];
		ctrlInOutStru output[CRTL_OUT_NUM];
		uint8_t workFlag; //1 ���óɹ�  ����-ʧ��
}autoCtrl_stru;












#endif
