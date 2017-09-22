/*--------------------------------------------------------------------------------------------------
�����Ϊ˽�еı����ļ���ֻ���ڷ���ͨ�ſƼ����޹�˾��Ȩ������·���ʹ�á�                            
(C) COPYRIGHT 2016 FIRSTECH INC. ALL RIGHTS RESERVED                                                
��Ŀ����     :     MRI                                                                           
�ļ�����     :     rx.h                                                                   
����         :     zhaoke                                                                       
������ϵ��ʽ :     zhaoke@afirstech.com                                                         
ʱ��         :     2016-01-11                                                                       
�汾         :     V1.0                                                                             
�ؼ���       :     rx                                                                             
�ļ�����     :                                            
�޸����     :                                                                                      
ʱ��         �޸�����           �汾          �޸�˵��                                              
=========================================================                                           
2016-1-11    zhaoke             v1.1         ���� 
2016-5-23    pengjing                        �޸�  RxChannelAcquirePara������� 
2016-10-31   zhaoke                           deleteted RxPhaseOffsetReg ����rst    
2017-2-22    zhaoke                          ��Ӻ���ע�� 
2017-5-9     zhaoke                          1.Ƶ�ʺ���λ���/����ѡ��ֿ����ơ��궨��RxFreqPhaseSel()���Ϊ RxFreqSel()��RxPhaseSel()
                                             2.����Ƶ�ʺ���λʱ����λ�ۼ�������λ                                                                                          
=========================================================        */
#define RX_CHANNEL1_START    0x1
#define RX_CHANNEL2_START    0x2	
#define RX_CHANNEL3_START    0x4 
#define RX_CHANNEL4_START    0x8
#define RX_CHANNEL5_START    0x10
#define RX_CHANNEL6_START    0x20
#define RX_CHANNEL7_START    0x40
#define RX_CHANNEL8_START    0x80
#define RX_FILTER_DELAY      20233.0

#define RX_START_ADDR                   0x7d
#define RX_BW_TYPE_ADDR_INITIAL         0x43
#define RX_SAMPLE_POINT_ADDR_INITIAL    0x6b
#define RX_CENTER_FRE_ADDR_INITIAL      0xb7
#define RX_FRE_OFFSET_ADDR_INITIAL      0x4a
#define RX_FRE_RAM_ADDR_INITIAL         0x87
#define RX_PHASE_OFFSET_ADDR_INITIAL    0x5a
#define RX_PHASE_RAM_ADDR_INITIAL       0x9f
#define RX_FREQ_EN_ADDR                 0x6c
#define RX_GAIN_ADDR_INITIAL            0x7d
#define RX_FIR_RESET_ADDR               0x43
#define RX_BYPASS_ADDR                  0x86
#define RX_ANALOG_CTRL_ADDR_INITIAL     0x04
#define ADC_OFFSET_ADDR_INITIAL         0xc8
#define AMP_GAIN1_ADDR_INITIAL          0xd0
#define AMP_GAIN2_ADDR_INITIAL          0xd8
#define AMP_GAIN3_ADDR_INITIAL          0xe0
#define ATT_ADDR_INITIAL                0xe8
#define RX_FREQ_SEL_ADDR                0x87
#define RX_PHASE_SEL_ADDR               0x113
#define RX_OFFSET_DISABLE_ADDR          0xb8

/*�����ǿ���ֱ�Ӻ궨��ĺ���������������Ķ��弰˵������ݶ�ģ��⺯�����岿��,*/
/*���ú�ķ�ʽ�����������Դ������ɵ�����ָ�                             */
#define RxFirReset()                                              setr(RX_FIR_RESET_ADDR ,255 );\
                                                                  setr(RX_FIR_RESET_ADDR ,0 )
                                                                  
#define RxFreqOffsetRam(channelNo,freNo)                        do{\
                                                                  int freNoInt;\
																  double __addrFloat;\
																  __addrFloat = RX_FRE_RAM_ADDR_INITIAL + channelNo * 3;\
                                                                  freNoInt = freNo;\
                                                                  setr(RX_FREQ_SEL_ADDR ,255 );\
                                                                  setr(RX_OFFSET_DISABLE_ADDR ,0 );\
                                                                  setr( __addrFloat,freNoInt);\
                                                                  setr(RX_FREQ_EN_ADDR ,65535);\
                                                                 }while(0) 
                                                                  
                                                                    
#define RxPhaseOffsetRam(channelNo,phaseRamAddr)                  do{\
                                                                   int phaseRamAddrInt;\
																  double __addrFloat;\
																  __addrFloat = RX_PHASE_RAM_ADDR_INITIAL + channelNo * 3;\
                                                                  phaseRamAddrInt = phaseRamAddr;\
                                                                  setr(RX_PHASE_SEL_ADDR ,255 );\
                                                                  setr( __addrFloat,phaseRamAddrInt);\
	                                                  	              setr(RX_FREQ_EN_ADDR ,65535 );\
                                                                  }while(0)
                                                                  
                                                                  
                              

#define RxBypass(rxBypass)                                        setr(RX_BYPASS_ADDR ,rxBypass )
#define RxGateOut(voltageLevel)                                   setr(RX_ANALOG_CTRL_ADDR_INITIAL,voltageLevel )
                                                                
#define RxOffsetFreqSel(freqSel)                                  setr(RX_FREQ_SEL_ADDR ,freqSel )
#define RxOffsetPhaseSel(phaseSel)                                setr(RX_PHASE_SEL_ADDR ,phaseSel )
#define RxOffsetFreqDisable(disableEn)                            setr(RX_OFFSET_DISABLE_ADDR ,disableEn )
// 

#define RxGainReg(channelNo,rxGain)                           do{          \
	                                                                      double __temp; \
	                                                                      int __gain;     \
																  double __addrFloat;\
																  __addrFloat = RX_GAIN_ADDR_INITIAL + channelNo;\
	                                                                      __temp = rxGain * GAIN_FACTOR;\
	                                                                      __gain = __temp; \
	                                                                      setr(__addrFloat,__gain); \
	                                                                  }while(0)
                                                          
#define RxFreqOffsetReg(channelNo,offsetFreq,freqUnit)                    do{\
	                                                                   double __temp;\
	                                                                   int __freq;\
																       double __addrFloat;\
																       __addrFloat = RX_FRE_OFFSET_ADDR_INITIAL + channelNo*2;\
	                                                                   __temp = offsetFreq * freqUnit;\
	                                                                   __freq = __temp;\
	                                                                   RxOffsetFreqDisable(0);\
	                                                                   RxOffsetFreqSel(0);\
	                                                                   setr(__addrFloat,__freq);\
	                                                                   setr(RX_FREQ_EN_ADDR ,65535);\
	                                                                 }while(0)
#define RxNcoFreq(channelNo,ncoFreq,freqUnit)           \
																								 do{ \
	                                                 double __temp; \
	                                                 int __freq; \
													 double __addrFloat;\
													 __addrFloat = RX_CENTER_FRE_ADDR_INITIAL + channelNo * 2;\
	                                                 __temp = ncoFreq * freqUnit; \
	                                                 __freq = __temp; \
	                                                 RxOffsetFreqDisable(255); \
	                                                 setr(__addrFloat,__freq); \
	                                                 setr(RX_FREQ_EN_ADDR ,65535 ); \
	                                                }while(0) 
/*==========================================�ݶ�ģ��⺯������====================================*/

/***************************************************
//�������������øú�����1.���ſ��ź�;                                                
//          2. ��ЧNCOʹ���ź�;                                                          
//          2. ��Ӧ�Ľ��հ��ͨ����ʼ�ɼ�.                                               
//��ڲ�����rxStart�������źſ�ʼ����������źſ��Ϊ8bit���ӵ͵������ζ�Ӧ������8��ͨ��.
//         rxGatePreTime�������ſ���ǰ��ʱ�䣬��λus                                   
//         rxGatePostTime�������ſ��Ƴٹر�ʱ�䣬��λus                                  
//         rxWaveTime�����ղɼ�ʱ�䣬��λus   
 CAUTION: 
        1.Ƶ�����ã��˲�����λ����ʼ�ɼ���������˳���ܸı䣬������н�Ծʹ��ͼ��0��λ���и���
        2. rxGatePreTime�������1us,����ᵼ��ǰ1us�źŶ�ʧ                                    
***************************************************/
void RxStart(int rxStart, double rxGatePreTime, double rxGatePostTime, double rxWaveTime)
{
	  int __ampOff;
	  double __rxStartTemp;
	  double __temp;
	  timer(1);
	  RxGateOut(1);
     
	  TimerCmp(rxGatePreTime,US);	  
	   setr(RX_FREQ_EN_ADDR ,0 );
	   RxFirReset();
    setr(RX_START_ADDR ,rxStart ); 
    TimerCmp(rxGatePostTime+rxWaveTime+rxGatePreTime,US);
    RxGateOut(0);
    timer(2);
}


/***********************************************************/
//��������������ͨ������������������������(���)���������� 
//          ������ղ�������Ҫ��ʱ�䣬��λus               
//��ڲ�����samplePeriod: ���հ�ͨ���Ĳ�������  ����29��   
//          samplePoint:�������ղ�������                   
//          channelNo:ѡ��ͨ�� ��1-8�ֱ��ӦC1 - C8        
//����ֵ����������ʱ�䣬��λus                             
//CAUTION:�˺�����ͬ��AcquireDuration()!!!!!!!!!!!!!       
/***********************************************************/
double RxChannelAcquirePara(double __samplePeriod,double __samplePoint)
{
  //  int samplePointAddr;
  //  int bwTypeAddr;
    double __samplePointAddrTemp;
    //double __bwTypeAddrTemp;
    double __channelNoTemp;
   // double __samplePoint;
    double __waveReceiveTime;
   // double __samplePeriod;
   // double __bwType;
   // int __bwTypeInt;
    int __samplePointInt;
//    __channelNoTemp = channelNo;
    __samplePointInt = __samplePoint;
  // __bwTypeInt = __bwType;
    setr(0x6d ,__samplePointInt );
    //setr(0x44 ,__bwTypeInt );
    setr(0x6f ,__samplePointInt );
   // setr(0x45 ,__bwTypeInt );    
    setr(0x71 ,__samplePointInt );
   // setr(0x46 ,__bwTypeInt );    
    setr(0x73 ,__samplePointInt );
   // setr(0x47 ,__bwTypeInt );    
    setr(0x75 ,__samplePointInt );
   // setr(0x48 ,__bwTypeInt );    
    setr(0x77 ,__samplePointInt );
   // setr(0x49 ,__bwTypeInt );    
    setr(0x79 ,__samplePointInt );
   // setr(0x4a ,__bwTypeInt );    
    setr(0x7b ,__samplePointInt );
   // setr(0x4b ,__bwTypeInt );

   //������ղ�������Ҫ��ʱ��
   // __dsamplePeriod=__samplePeriod;
    __waveReceiveTime = __samplePoint * __samplePeriod;
    return __waveReceiveTime;
    
}




/*******************************************************/
//��������������λƫ�ƼĴ���ֵ���ö�Ӧͨ������λƫ��ֵ 
//��ڲ�����ncoPhase: ��λֵ����λ����                 
//          channelNo:ѡ��ͨ�� ��1-8�ֱ��ӦC1 - C8    
/*******************************************************/

void RxPhaseOffsetReg(int channelNo,double ncoPhase)
{
   // int rxPhaseAddr;
    double rxPhaseAddrTemp;
    double channelNoTemp;
    double ncoPhaseTemp;
    
    int phase;
    channelNoTemp = channelNo;
  
    rxPhaseAddrTemp = RX_PHASE_OFFSET_ADDR_INITIAL + channelNoTemp * 2.0;
   // rxPhaseAddr = rxPhaseAddrTemp;
    ncoPhaseTemp = ncoPhase * PHASE_CONVERSION_FACTOR;
    phase = ncoPhaseTemp;
    RxOffsetPhaseSel(0);
    setr(rxPhaseAddrTemp ,phase );
    
//    if(rst==0.0)
      setr(RX_FREQ_EN_ADDR ,65535 );
     
//    else
//    	setr(RX_FREQ_EN_ADDR ,255 );

}

/*********************************************************************/
//
//��������������ƽ��������ѭ��������ţ��ڲ�ͬphaseCycle�����ò�ͬ
//          ����Ե���λƫ��
//
//��ڲ�����noAverages��ƽ������ 
//          phaseCycle  ��λѭ�� 0,180,0,180...                      
//
/*********************************************************************/

void RxPhaseCycle(int channelNo, double phaseCycle,double noAverages)
{
	 static double RxPhaseCycleCnt_cnt1 = 0.0;
   static double RxPhaseCycleCnt_phase = 0.0;

	 if(phaseCycle==1.0)
   {
	  RxPhaseCycleCnt_cnt1 = RxPhaseCycleCnt_cnt1 + 1.0;
   	  RxPhaseOffsetReg(channelNo,RxPhaseCycleCnt_phase);
   	  if(RxPhaseCycleCnt_cnt1 == noAverages)
      {
         RxPhaseCycleCnt_cnt1 = 0.0;
         if(RxPhaseCycleCnt_phase == 0.0)
         RxPhaseCycleCnt_phase = 180.0;
         else
         RxPhaseCycleCnt_phase = 0.0;
        }

   }
}
/*********************************************************************/

//��������������ƽ��������ѭ���������
//
//��ڲ�����noAverages��ƽ������                                    
//
//���ز��������                                                    
//
/*********************************************************************/
double RxAvePhaseCnt(double noAverages)
{	
	static double RxAvePhase_cnt1 = 0.0;	  
  double averagesCnt;
  
  if(noAverages>1.0)
  {
     if(RxAvePhase_cnt1==noAverages)
        RxAvePhase_cnt1 = 0.0;
           
     RxAvePhase_cnt1 =  RxAvePhase_cnt1+1.0;   
  }else
     RxAvePhase_cnt1 = 0.0;
     
	averagesCnt = RxAvePhase_cnt1;
	
	return averagesCnt;
}


