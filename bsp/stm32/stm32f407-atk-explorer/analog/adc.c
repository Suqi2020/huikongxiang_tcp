#include  "board.h"

extern ADC_HandleTypeDef hadc1;


//���ADCֵ
//ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//����ֵ:ת�����
uint16_t Get_Adc(uint32_t ch)   
{
    ADC_ChannelConfTypeDef ADC1_ChanConf;
    
    ADC1_ChanConf.Channel=ch;                                   //ͨ��
    ADC1_ChanConf.Rank=1;                                       //��1�����У�����1
    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //����ʱ��
    ADC1_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&hadc1,&ADC1_ChanConf);        //ͨ������
	
    HAL_ADC_Start(&hadc1);                               //����ADC
	
    HAL_ADC_PollForConversion(&hadc1,10);                //��ѯת��
 
	return (uint16_t)HAL_ADC_GetValue(&hadc1);	        //�������һ��ADC1�������ת�����
}
//��ȡָ��ͨ����ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
uint16_t Get_Adc_Average(uint16_t ch,uint16_t times)
{
		uint16_t temp_val=0;
		uint16_t t;
		for(t=0;t<times;t++)
		{
				temp_val+=Get_Adc(ch);
				rt_thread_mdelay(5);
		}
		return temp_val/times;
} 

//��Ӧ�˿�1-8
uint32_t chanl[8]={ADC_CHANNEL_10,ADC_CHANNEL_11,ADC_CHANNEL_12,ADC_CHANNEL_13,\
										ADC_CHANNEL_14,ADC_CHANNEL_15,ADC_CHANNEL_8,ADC_CHANNEL_9};
void adcGetTest()
{

				int rt=Get_Adc_Average(ADC_CHANNEL_8,10);
				rt_kprintf("ADC_CHANNEL_8 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
				 rt=Get_Adc_Average(ADC_CHANNEL_9,10);
				rt_kprintf("ADC_CHANNEL_9 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
					 rt=Get_Adc_Average(ADC_CHANNEL_10,10);
				rt_kprintf("ADC_CHANNEL_10 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
					 rt=Get_Adc_Average(ADC_CHANNEL_11,10);
				rt_kprintf("ADC_CHANNEL_11 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
					 rt=Get_Adc_Average(ADC_CHANNEL_12,10);
				rt_kprintf("ADC_CHANNEL_12 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
					 rt=Get_Adc_Average(ADC_CHANNEL_13,10);
				rt_kprintf("ADC_CHANNEL_13 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
					 rt=Get_Adc_Average(ADC_CHANNEL_14,10);
				rt_kprintf("ADC_CHANNEL_14 ,adc tick:%d,voltgge ����100��:%dV\n",rt,rt*330/4096);
					 rt=Get_Adc_Average(ADC_CHANNEL_15,10);
				rt_kprintf("ADC_CHANNEL_15 ,adc tick:%d,voltgge ����100��:%dV\n\r\n\r\n",rt,rt*330/4096);
}
