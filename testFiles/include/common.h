/*--------------------------------------------------------------------------------------------------
�����Ϊ˽�еı����ļ���ֻ���ڷ���ͨ�ſƼ����޹�˾��Ȩ������·���ʹ�á�                            
(C) COPYRIGHT 2016 FIRSTECH INC. ALL RIGHTS RESERVED                                                
��Ŀ����     :     MRI                                                                           
�ļ�����     :     common.h                                                                   
����         :     zhaoke                                                                       
������ϵ��ʽ :     zhaoke@afirstech.com                                                         
ʱ��         :     2016-01-11                                                                       
�汾         :     V1.0                                                                             
�ؼ���       :     Common                                                                             
�ļ�����     :                                            
�޸����     :                                                                                      
ʱ��         �޸�����           �汾          �޸�˵��                                              
=========================================================                                           
2016-1-11    zhaoke             v1.1         ���� 
2016-5-25    pengjing                        �޸�  PHASE_CONVERSION_FACTORֵ  
2017-2-22    zhaoke                          ��Ӻ���ע��                                                                                         
=========================================================    */    
#ifndef COMMON_H
#define COMMON_H
//100MHz clk 10ns period
#define REFClk                   10.0

#define NS                       0.1
#define US                       100.0
#define MS                       100000.0
#define S                        100000000.0
//#define FREQ_CONVERSION_FACTOR   1342177.28
#define MHZ                      2684354.56
#define KHZ                      2684.35456
#define  HZ                      2.68435456
#define PHASE_CONVERSION_FACTOR  745654.0444444
#define GAIN_FACTOR              32.0
#define ONE_CYCLE 1.0
#define CHECK      0
#define INTERNAL_TRIGGER 0

#define CHANNEL1             1
#define CHANNEL2             2
#define CHANNEL3             3
#define CHANNEL4             4
#define CHANNEL5             5
#define CHANNEL6             6
#define CHANNEL7             7
#define CHANNEL8             8

/*��һ��Trigger����ʱ����ִ�б�������;�ڶ���Trigger����ʱ�������¼�������*/
#define WaitTrigger()	                  wait(1,1); \
  				                              update;\
  				                              wait(1,1)


#define Delay(delayValue , delayUnit)            do {\
	                                                     double __realDelayTime;\
	                                                     double __delayValueTemp;\
	                                                     __delayValueTemp = delayValue;\
	                                                     __realDelayTime = __delayValueTemp*delayUnit-222.0;\
	                                                     delay(__realDelayTime);\
	                                                 }while(0)

#define TimerCmp(timerValue , timerUnit)         timer(0,(timerValue)*timerUnit)


/**************************************************/
/*������������ʱ��ת��Ϊ��ʱ������Ϊ��λ          */
/*��ڲ�����timeValue:ʱ��ֵ��                    */
/*          timeUnit:ns,us,ms,s��Ӧ��ʱ���������� */
/**************************************************/
double TimeToClkCycle(double timeValue, double timeUnit)
{
    double __clkNo;
    __clkNo = timeValue * timeUnit;
    return __clkNo;

}

/**************************************************/
/*�����������������ʱ��                           */
/*��ڲ�����__samplePeriod:�����������λus��      */
/*          __samplePoint:��������                */
/*����ֵ������ʱ�䣬��λus                         */
/*CAUTION:�˺�����ͬ��RxChannelAcquirePara()!!!!!!!!!!!!!       */
/**************************************************/
double AcquireDuration(double __samplePeriod, double __samplePoint)
{

    double __waveReceiveTime;
   //������ղ�������Ҫ��ʱ��

    __waveReceiveTime = __samplePoint * __samplePeriod;
    return __waveReceiveTime;
    
}    
#endif
