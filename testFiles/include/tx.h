/*--------------------------------------------------------------------------------------------------
�����Ϊ˽�еı����ļ���ֻ���ڷ���ͨ�ſƼ����޹�˾��Ȩ������·���ʹ�á�                            
(C) COPYRIGHT 2016 FIRSTECH INC. ALL RIGHTS RESERVED                                                
��Ŀ����     :     MRI                                                                           
�ļ�����     :     tx.h                                                                   
����         :     zhaoke                                                                       
������ϵ��ʽ :     zhaoke@afirstech.com                                                         
ʱ��         :     2016-01-11                                                                       
�汾         :     V1.0                                                                             
�ؼ���       :     TX                                                                             
�ļ�����     :                                            
�޸����     :                                                                                      
ʱ��         �޸�����           �汾          �޸�˵��                                              
=========================================================                                           
2016-1-11    zhaoke             v1.1         ���� 
2016-5-23    pengjing                        �������ְ汾��  TX_FILTER_DELAY ֵ      
2016-10-31   zhaoke                           deleteted TxPhaseOffsetReg ����rst    
2017-2-22    zhaoke                          ��Ӻ���ע��      
2017-3-17    pengjing                        TX_GRA_DELAY �޸� 15.11US ����TR3DMOTSAEnScanCnt����  
2017-5-9     zhaoke                          1.Ƶ�ʺ���λ���/����ѡ��ֿ����ơ��궨��TxFreqPhaseSel()���Ϊ TxFreqSel()��TxPhaseSel()
                                             2.����Ƶ�ʺ���λʱ����λ�ۼ�������λ
											 3.TxPhaseOffsetReg��λ����ȡ��                               
========================================================= */                                          
#ifndef TX_H

#define TX_H

#define TX_CHANNEL1_START    0x1
#define TX_CHANNEL2_START    0x2	
#define TX_CHANNEL3_START    0x4 
#define TX_CHANNEL4_START    0x8
#define TX_CHANNEL5_START    0x10
#define TX_CHANNEL6_START    0x20
#define TX_CHANNEL7_START    0x40
#define TX_CHANNEL8_START    0x80

#define TX_BRAM_NO1          0x0
#define TX_BRAM_NO2          0x1
#define TX_BRAM_NO3          0x2
#define TX_BRAM_NO4          0x3
#define TX_BRAM_NO5          0x4
#define TX_BRAM_NO6          0x5
#define TX_BRAM_NO7          0x6
#define TX_BRAM_NO8          0x7
#define TX_BRAM_NO9          0x8
#define TX_BRAM_NO10         0x9
#define TX_BRAM_NO11         0xA
#define TX_BRAM_NO12         0xB
#define TX_BRAM_NO13         0xC
#define TX_BRAM_NO14         0xD
#define TX_BRAM_NO15         0xE
#define TX_BRAM_NO16         0xF

#ifdef MARIX_VERSION
#define TX_FILTER_DELAY          191.994//190.01+1427*0.00125-0.2
#else

#define TX_FILTER_DELAY          95.04//260.49//185.49//260.50//259.95375//261.425//259.95375//247.58//
#endif
    

//#define TX_GRA_DELAY         15.11

//#ifdef MARIX_VERSION
//#define TX_GRA_FIS_RF_SEC_DELAY 160.2//118.0
//#else
//#define TX_GRA_FIS_RF_SEC_DELAY 199.95375//259.95375-60
//#endif

//#ifdef MARIX_VERSION
//#define TX_RF_FIS_GRA_SEC_DELAY 125.994
//#else
//#define TX_RF_FIS_GRA_SEC_DELAY 0//200//147//202.18375//264.32-61.34-1.58375//102//199.95375//259.95375-60
//#endif



#define TX_FIR_RESET_TIME    300//ns
#define TX_START_ADDR                  0x86
#define SHAPE_NO_ADDR_INITIAL          0x8e
#define TX_CENTER_FRE_ADDR_INITIAL     0x13a
#define TX_FRE_OFFSET_ADDR_INITIAL     0xa5
#define TX_FRE_RAM_ADDR_INITIAL        0xfa
#define TX_PHASE_OFFSET_ADDR_INITIAL   0xb5
//#define TX_PHASE_OFFSET_ADDR_INITIAL   0x165
#define TX_PHASE_RAM_ADDR_INITIAL      0x112
#define TX_GAIN_ADDR_INITIAL           0xc6
#define TX_GAIN_RAM_ADDR_INITIAL       0x12a
#define TX_FIR_RESET_ADDR              0xd9
#define TX_FRE_INVERSE_EN_ADDR         0xda
#define TX_DUC_BYPASS_ADDR_INITIAL     0xef
#define TX_GATE_ADDR                   0x30
#define TX_FREQ_EN_ADDR                0xc7
#define TX_OFFSET_DISABLE_ADDR         0x13b
#define TX_GAIN_SEL_ADDR               0xfa
#define TX_FREQ_SEL_ADDR               0xf9
#define TX_PHASE_SEL_ADDR              0x178
#define TX_SQUARE_PERIOD_ADDR_INITIAL  0x153
#define TX_SQUARE_EN_ADDR              0x14b
#define TX_END_LAST_TIME_ADDR_INITIAL  0x15c

/*���ú�ķ�ʽ�����������Դ������ɵ�����ָ�                             */

#define TxChannelShapeSel(channelNo,shapeNo)                     do{ \
	                                                                int __shapeNoInt; \
	                                                                 __shapeNoInt = shapeNo;\
                                                                   setr(SHAPE_NO_ADDR_INITIAL + channelNo ,shapeNo );  \
                                                                   setr(TX_SQUARE_EN_ADDR + channelNo ,0 );\
                                                                 }while(0)
                                                                 
#define TxAttRam(channelNo,attRamAddr)                        do{\
                                                                   	int attRamAddrInt;\
                                                                   	attRamAddrInt = attRamAddr;\
                                                                   	setr(TX_GAIN_SEL_ADDR ,255 );\
                                                                    setr(TX_GAIN_RAM_ADDR_INITIAL + channelNo * 2 ,attRamAddrInt );\
                                                                  }while(0)
#define TxFreInverseEn(freInverseEn)                               setr(TX_FRE_INVERSE_EN_ADDR ,freInverseEn)

#define TxBypass(channelNo,ducBypass)                              setr(TX_DUC_BYPASS_ADDR_INITIAL + channelNo,ducBypass )

#define TxOffsetFreqDisable(disableEn)                             setr(TX_OFFSET_DISABLE_ADDR ,disableEn )

#define TxGainSel(gainSel)                                         setr(TX_GAIN_SEL_ADDR ,gainSel )	

#define TxFreqSel(freqSel)                                 setr(TX_FREQ_SEL_ADDR ,freqSel )
#define TxPhaseSel(phaseSel)                               setr(TX_PHASE_SEL_ADDR ,phaseSel )                                                                
#define TxNcoFreqEn(ncoFreqEn)                                     setr(TX_FREQ_EN_ADDR ,ncoFreqEn )
#define TxGateOut(voltageLevel)                                    setr(TX_GATE_ADDR ,voltageLevel )
                          

#define TxFreqOffsetReg(channelNo,offsetFreq,freqUnit) \
																									 do{ \
	                                                 double __temp; \
	                                                 int __freq;\
													 double __addrFloat;\
													 __addrFloat = TX_FRE_OFFSET_ADDR_INITIAL + channelNo * 2;\
													 __temp = offsetFreq * freqUnit; \
	                                                 __freq = __temp;\
	                                                 TxFreqSel(0);\
                                                   TxOffsetFreqDisable(0); \
	                                                 setr(__addrFloat,__freq); \
	                                                 setr(TX_FREQ_EN_ADDR ,65535 ); \
	                                                }while(0)

                                                                  

#define TxNcoFreq(channelNo,ncoFreq,freqUnit)           \
																								 do{ \
	                                                 double __temp; \
	                                                 int __freq; \
													 double __addrFloat;\
													 __addrFloat = TX_CENTER_FRE_ADDR_INITIAL + channelNo * 2;\
	                                                 __temp = ncoFreq * freqUnit; \
	                                                 __freq = __temp; \
	                                                 TxOffsetFreqDisable(255); \
	                                                 setr(__addrFloat,__freq); \
	                                                 setr(TX_FREQ_EN_ADDR ,255 ); \
	                                                }while(0) 

#define TxAttReg(channelNo,txAtt)             do{ \
	                                                 double __temp;\
	                                                 int __gain;\
													 int __addrInt;\
													 double __addrFloat;\
													 __addrFloat = TX_GAIN_ADDR_INITIAL + channelNo * 2;\
													 __addrInt = __addrFloat;\
	                                                 __temp = txAtt * GAIN_FACTOR;\
	                                                 __gain = __temp;\
	                                                 TxGainSel(0);\
	                                                 setr(__addrFloat,__gain); \
	                                                }while(0)
                                            

#define TxPhaseOffsetRam(channelNo, phaseRamAddr)  do{\
                                                    int phaseRamAddrInt;\
													 double __addrFloat;\
													 __addrFloat = TX_PHASE_RAM_ADDR_INITIAL + channelNo * 3;\
                                                    phaseRamAddrInt = phaseRamAddr;\
                                                    TxPhaseSel(255);\
                                                    setr(__addrFloat,phaseRamAddrInt);\
	                                                  	 setr(TX_FREQ_EN_ADDR ,65535 );\
                                                    }while(0) 

#define TxFreqOffsetRam(channelNo, freNo)         do{\
                                                    int freNoInt;\
													 double __addrFloat;\
													 __addrFloat = TX_FRE_RAM_ADDR_INITIAL + channelNo * 3;\
                                                    freNoInt = freNo;\
                                                    TxFreqSel(255 ); \
                                                    TxOffsetFreqDisable(0);\
                                                    setr(__addrFloat,freNoInt);\
	                                                  setr(TX_FREQ_EN_ADDR ,65535 );\
	                                                   }while(0)
                                                    
#define TxFirReset()                                setr(TX_FIR_RESET_ADDR,255 ); \
                                                    delay(TX_FIR_RESET_TIME); \
                                                    setr(TX_FIR_RESET_ADDR,0 )
#define TxHardPulseShape(channelNo,pulsePeriod)   do{\
	                                                                int __temp;\
	                                                                __temp = pulsePeriod;\
	                                                                setr(TX_GAIN_SEL_ADDR ,0 );\
	                                                                setr(TX_SQUARE_PERIOD_ADDR_INITIAL + channelNo,__temp );\
	                                                                setr(TX_SQUARE_EN_ADDR + channelNo ,1 ); \
	                                                            }while(0)
#define TxEndLastTime(lastTime,timeUnit)          do{\
	                                                                double __temp1;\
	                                                                int __temp2;\
	                                                                __temp1 = lastTime * timeUnit;\
	                                                                __temp2 = __temp1;\
	                                                                setr(TX_END_LAST_TIME_ADDR_INITIAL,__temp2 );\
	                                                            }while(0)


/*********************************************************************/

/*��������������λƫ�ƼĴ���ֵ���ö�Ӧͨ������λƫ��ֵ               */ 

/*��ڲ�����channelNo������ͨ����,ȡֵ��Χ��1-8����ʾѡ��ͨ����ͨ����*/

/*          ncoPhase,��λֵ����λ���ȡ�                              */

/*********************************************************************/

 
void TxPhaseOffsetReg(int channelNo,double ncoPhase)

{

    double txPhaseAddrTemp;

   // int txPhaseAddr;

    double channelNoTemp;

    double ncoPhaseTemp;

    int phase;

    channelNoTemp = channelNo;

    txPhaseAddrTemp = TX_PHASE_OFFSET_ADDR_INITIAL + channelNoTemp * 2.0;

  //  txPhaseAddr = txPhaseAddrTemp;

    ncoPhaseTemp = ncoPhase * PHASE_CONVERSION_FACTOR;

  //  phase = 0-ncoPhaseTemp;
    phase = ncoPhaseTemp;
    
    TxPhaseSel(0); 
  //  setr(TX_PHASE_OFFSET_ADDR_INITIAL + channelNoTemp * 2.0 ,phase );
   setr(txPhaseAddrTemp ,phase );
    
//    if(rst==0.0)
      setr(TX_FREQ_EN_ADDR ,65535 );
//    else
//    	setr(TX_FREQ_EN_ADDR ,255 );
    	
   

}





/***************************************************************/

/*�������������ø�ͨ�����俪ʼ�źţ������¸�ͨ��Ƶ����λ������ */ 

/*          �˺������ڵ�ͨ��������ͨ���첽���������������� */

/*          ���������䲨�ν�����                               */

/*��ڲ�����txStart��Bram�������ݵ���ʼ�źţ����źſ��Ϊ8bit��*/

/*                   �ӵ͵������ζ�Ӧ������8��ͨ��           */

/***************************************************************/

void TxStartAsync(int txStart, double txGatePreTime)

{

//	  RfAmpOn(txStart);

//	  Delay(txGatePreTime,US);
    double __filterDelay;
    __filterDelay=TX_FILTER_DELAY;
	  timer(1);
    setr(TX_START_ADDR ,txStart );
    TimerCmp(__filterDelay-txGatePreTime,US);
    TxGateOut(txStart);
    TimerCmp(__filterDelay,US);
    /*�Ӳ��η��俪ʼ��������˲�������������ʱΪ20247��ʱ������*/

    /*Ϊʹ��λ�������ϸ��������ʱ20247��ʱ������ʹƵ����λ��Ч*/

//    Delay(TX_FILTER_DELAY,US);

    setr(TX_FREQ_EN_ADDR ,0 );
    timer(2);
}

/***************************************************************/

//�������������ø�ͨ�����俪ʼ�źţ������¸�ͨ��Ƶ����λ������  
//
//          �ú���һֱ���������η���������˺���ֻ�����ڵ�ͨ�� 
//
//          �����ͨ��ͬ������������                         
//
//��ڲ�����txStart��Bram�������ݵ���ʼ�źţ����źſ��Ϊ8bit��
//
//                   �ӵ͵������ζ�Ӧ������8��ͨ��           
//
//          rfWaveWidth������岨�γ�����ʱ�� ,��λus          
//
//          txGatePreTime,�����ſ���ǰ��ʱ�䣬��λus     
//          txGatePostTime�������ſ��ӳٹر�ʱ�䣬��λus 
/***************************************************************/

void TxStart(int txStart,double rfWaveWidth,double txGatePreTime,double txGatePostTime)
{
	  int __ampOff;

	  double __filterDelay;
	  double __txStartTemp;

	  double __temp;
    double txGateOff;
	  __filterDelay=TX_FILTER_DELAY;
    __txStartTemp = txStart;

	  timer(1);
    setr(TX_FREQ_EN_ADDR ,0 );
    setr(TX_START_ADDR ,txStart );
    TimerCmp(__filterDelay-txGatePreTime,US);
    TxGateOut(txStart);   
    __temp = 255.0-__txStartTemp;
    __ampOff = __temp;
     txGateOff = txGatePostTime+TX_FILTER_DELAY+rfWaveWidth;
    TimerCmp(txGateOff,US);    
    TxGateOut(__ampOff);
    timer(2);
    TxFirReset(); //�����˲������㣬�����ſ��źŹر��Ժ����ݲ�Ϊ0������ 2016.4.19
}
/*********************************************************************/

//������������Ƶ��ƫ�ƼĴ���ֵ���ö�Ӧͨ����Ƶ��ƫ��ֵ 
//          ����λƫ�ƼĴ���ֵ���ö�Ӧͨ������λƫ��ֵ               
//		Ƶ��ƫ�ƺ���λƫ��ͬʱ��Ч                               
//
//��ڲ�����channelNo������ͨ����,ȡֵ��Χ��1-8����ʾѡ��ͨ����ͨ����
//          offsetFreq,ƫ��Ƶ��
//          ncoPhase,��λֵ����λ���ȡ�                              
//          freqUnit��Ƶ��ƫ�Ƶ�λ��HZ��KHZ��MHZ�ֱ��Ӧ1Hz��1000Hz��1000,000Hz
/*********************************************************************/

void TxFreqPhaseOffsetReg(int channelNo,double offsetFreq ,double ncoPhase,double freqUnit)

{

    double txPhaseAddrTemp;

   // int txPhaseAddr;

    double channelNoTemp;

    double ncoPhaseTemp;
	
	double offsetFreqTemp;
	
	double txOffsetFreqAddrTemp;

    int phase;
	
    int freq;
	
    channelNoTemp = channelNo;

    txPhaseAddrTemp = TX_PHASE_OFFSET_ADDR_INITIAL + channelNoTemp * 2.0;

	txOffsetFreqAddrTemp = TX_FRE_OFFSET_ADDR_INITIAL + channelNoTemp * 2.0;

    ncoPhaseTemp = ncoPhase * PHASE_CONVERSION_FACTOR;
    offsetFreqTemp = offsetFreq * freqUnit;

    phase = ncoPhaseTemp;
    freq = offsetFreqTemp;
	
    TxPhaseSel(0); 
    TxFreqSel(0); 
    setr(txPhaseAddrTemp ,phase );
    TxOffsetFreqDisable(0);
   	setr(txOffsetFreqAddrTemp,freq);
	
//    if(rst==0.0)
      setr(TX_FREQ_EN_ADDR ,65535 );
//    else
//    	setr(TX_FREQ_EN_ADDR ,255 );
    	
}

/*********************************************************************/

/*��������������ƽ��������ѭ��������ţ����TxAvePhaseʹ�ò�����ͬ����λ

/*��ڲ�����noAverages��ƽ������                                     */

/*���ز��������                                                     */

/*********************************************************************/
double TxAvePhaseCnt(double noAverages)
{	
	static double TxAvePhase_cnt1 = 0.0;	  
  double averagesCnt;
  
  if(noAverages>1.0)
  {
     if(TxAvePhase_cnt1==noAverages)
        TxAvePhase_cnt1 = 0.0;
           
     TxAvePhase_cnt1 =  TxAvePhase_cnt1+1.0;   
  }else
     TxAvePhase_cnt1 = 0.0;
     
	averagesCnt = TxAvePhase_cnt1;
	
	return averagesCnt;
}

/*****************************************************************************/
/*����������3D����ʱ����ƽ��������ѭ��������ţ����TxAvePhaseʹ�ò�����ͬ����λ  */
/*��ڲ����� noAverages��ƽ������                                              */
/*         noViewsSec,ѡ���ݶ���λ�������                                    */
/*���ز��������                                                             */
/****************************************************************************/

double TR3DMOTSAEnScanCnt(double noAverages,double noScans,double noViewsSec) 
{
	static double noviewsCnt=0.0;
	static double scanCnt = 1.0;
	double scanCntOut;
	double noviewstmp;
	
	noviewstmp = noScans * noViewsSec *noAverages;
	noviewsCnt = noviewsCnt+1.0;
	if(noviewsCnt > noviewstmp)
		scanCnt =  scanCnt+1.0;   	
    else
        scanCnt =  scanCnt;   	
	
	scanCntOut = scanCnt;
	return scanCntOut;
}

/**********************************************************/
//�������������㲻ͬѡ���Ƶ��           */
//��ڲ�����thickSliceRatioGain ѡ��������������ѡ��ʵ�ʺ��ΪthickSlice*thickSliceRatioGain*/  
//orderSlice��ѡ��֯��ʽ������    
//distanceSlice1:ԭʼ�����е�һ��������Դ������ģ�ISOCENTER���ľ��룬��λmm
//seperationSlice�����࣬��λmm 
//rf90Bandwidth:90�����������λHz                          
//SliceCnt:ѡ�����                                   
//thickSliceRatioGain:ѡ��������������ѡ��ʵ�ʺ��ΪthickSlice*thickSliceRatioGain 
//thickSlice:��񣬵�λmm
//channelNo:����ͨ����,ȡֵ��Χ��1-8����ʾѡ��ͨ����ͨ����
/**********************************************************/
void TxFreqSet(double orderSlice, double distanceSlice1,
               double seperationSlice,double thickSlice, double SliceCnt,\
               double rf90Bandwidth, int channelNo, double thickSliceRatioGain)
{
	double freqtmp;
	double channelNotmp;
  freqtmp = rf90Bandwidth/(thickSlice*thickSliceRatioGain) * (distanceSlice1 + (SliceCnt-1.0) * seperationSlice);
	channelNotmp = channelNo;
	TxFreqPhaseOffsetReg(channelNo,freqtmp ,0.0,HZ);
}

/*********************************************************************/

//��������������TxAvePhaseCnt�����ı�ţ��ڲ�ͬmodeAverage�����ò�ͬ
//          �ľ�����λƫ��
//
//��ڲ�����noAverages��ƽ������ 
//          modeAverage ƽ����ʽ ,����������б���ֲ�                                  
//          offsetFreq��Ƶ��ƫ��ֵ                                       
//           ncoPhase����λƫ��ֵ                                         
//           freqUnit��Ƶ��ƫ�Ƶ�λ��HZ��KHZ��MHZ�ֱ��Ӧ1Hz��1000Hz��1000,000Hz     
//           channelNo������ͨ����,ȡֵ��Χ��1-8����ʾѡ��ͨ����ͨ����
//
/*********************************************************************/

void TxAvePhase(double modeAverage,double noAverages,double offsetFreq,double ncoPhase,double freqUnit,int channelNo)
{
	static double phase180 = 0.0;
	double phase;
	double TxAvePhase_cnt1;
	
//	TxAvePhase_cnt1 = TxAvePhaseCnt( noAverages);
  if(noAverages<2.0)
  { 
  	TxFreqPhaseOffsetReg( channelNo, offsetFreq , ncoPhase, freqUnit);
  }else{
  	if(modeAverage==0.0)	{
	   TxFreqPhaseOffsetReg( channelNo, offsetFreq , ncoPhase, freqUnit);
	  }
    if(modeAverage==1.0)	{
	   TxFreqPhaseOffsetReg( channelNo, offsetFreq , ncoPhase, freqUnit);
	  }
	  if(modeAverage==2.0){
	   phase = phase180+ncoPhase;
     TxFreqPhaseOffsetReg( channelNo, offsetFreq , phase, freqUnit);
     if(phase180 == 0.0)
  	   phase180 = 180.0;
  	   else
  	 	 phase180 = 0.0;
  	}
  }
}

/**********************************************************/
//�������������ݹ涨��ѡ��˳����㲻ͬѡ���λ�ñ��           */
//��ڲ�����orderSlice��noSliceBlock������������б���ֲ�
//          slicecont ������ѡ��˳���                         
//
/**********************************************************/

double TxSliceCount(double orderSlice, double noSliceBlock,double slicecont)
{
	static double txSliceCnt_cnt = 0.0;
  static double txSliceCnt_cyccont = 1.0;
  static double txSliceCnt_sign = 1.0;
  static double txSliceCnt_doublecont = 0.0;
	double noSlice;
	double noSliceBlockhalf;
	int noSliceBlockhalf_int;
  double noSliceBlockhalf_double;
  double txSliceCnt_cnt_tmp;

  noSliceBlockhalf = noSliceBlock*0.5;
  noSliceBlockhalf_int = noSliceBlockhalf;
  noSliceBlockhalf_double = noSliceBlockhalf_int;
         
  if(noSliceBlockhalf>noSliceBlockhalf_double)
     txSliceCnt_cnt_tmp = noSliceBlockhalf_double + 1.0;
  else
     txSliceCnt_cnt_tmp = noSliceBlockhalf_double;
            	
  if(orderSlice<1.0)
  	orderSlice = 1.0;
  	          	
	if(slicecont==0.0)
	{
          if(orderSlice==4.0)
          {
            txSliceCnt_sign = 1.0;
            txSliceCnt_doublecont = 0.0;
            txSliceCnt_cnt= txSliceCnt_cnt_tmp ;
          }else
              txSliceCnt_cnt = 1.0;     
        txSliceCnt_cyccont = 1.0;
       }else{
         
          if(orderSlice==4.0)
          {
              if(txSliceCnt_sign==1.0)
                  txSliceCnt_doublecont = txSliceCnt_doublecont + 1.0;
              txSliceCnt_cnt = txSliceCnt_cnt_tmp + txSliceCnt_doublecont * txSliceCnt_sign;
              txSliceCnt_sign = (-1.0)*txSliceCnt_sign;
           }else 
               if(orderSlice<4.0)
               {

                   txSliceCnt_cnt = txSliceCnt_cnt+orderSlice;
                   if(txSliceCnt_cnt>noSliceBlock)
                   {
                       txSliceCnt_cyccont = txSliceCnt_cyccont+1.0;
                       txSliceCnt_cnt = txSliceCnt_cyccont;
                    }

               
                }
	}
	noSlice = txSliceCnt_cnt;
	return noSlice;
	
}

/*********************************************************************/
//
//��������������ƽ��������ѭ��������ţ��ڲ�ͬphaseCycle�����ò�ͬ
//          ����Ե���λƫ��
//
//��ڲ�����noAverages��ƽ������ 
//          phaseCycle  ��λѭ��                                   */
//           tag��       �µ�slice��ʼ��־
/*********************************************************************/

void TxPhaseCycle(int channelNo,double phaseCycle,double noAverages,double tag)
{
	 static double TxPhaseCycleCnt_cnt1 = 0.0;
   static double TxPhaseCycleCnt_phase = 180.0;

	 if(phaseCycle==1.0)
   {

	   if(tag==0)
	  TxPhaseCycleCnt_cnt1 = TxPhaseCycleCnt_cnt1 + 1.0;

   	  if(TxPhaseCycleCnt_cnt1 == noAverages)
      {
         TxPhaseCycleCnt_cnt1 = 0.0;
         if(TxPhaseCycleCnt_phase == 180.0)
         TxPhaseCycleCnt_phase = 0.0;
         else
         TxPhaseCycleCnt_phase = 180.0;
        }

   	TxPhaseOffsetReg(channelNo,TxPhaseCycleCnt_phase);
   }

}

/*
void TxPhaseCycle180(int channelNo,double phaseCycle,double noAverages,double tag)
{
	 static double TxPhaseCycleCnt_cnt1 = 0.0;
   static double TxPhaseCycleCnt_phase = -180.0;

	 if(phaseCycle==1.0)
   {
   	if(tag==0.0){

      TxPhaseCycleCnt_cnt1 = TxPhaseCycleCnt_cnt1 + 1.0;
   	}

   	  if(TxPhaseCycleCnt_cnt1 == noAverages)
      {
         TxPhaseCycleCnt_cnt1 = 0.0;
         if(TxPhaseCycleCnt_phase == -180.0)
             TxPhaseCycleCnt_phase = 0.0;
         else
             TxPhaseCycleCnt_phase = -180.0;
        }
   	TxPhaseOffsetReg(channelNo,TxPhaseCycleCnt_phase);
   }

}
*/
#endif

