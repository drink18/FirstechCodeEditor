/*--------------------------------------------------------------------------------------------------
�����Ϊ˽�еı����ļ���ֻ���ڷ���ͨ�ſƼ����޹�˾��Ȩ������·���ʹ�á�                            
(C) COPYRIGHT 2016 FIRSTECH INC. ALL RIGHTS RESERVED                                                
��Ŀ����     :     MRI                                                                           
�ļ�����     :     var.h                                                                   
����         :     zhaoke                                                                       
������ϵ��ʽ :     zhaoke@afirstech.com                                                         
ʱ��         :     2016-01-11                                                                       
�汾         :     V1.0                                                                             
�ؼ���       :     var                                                                             
�ļ�����     :                                            
�޸����     :                                                                                      
ʱ��         �޸�����           �汾          �޸�˵��                                              
=========================================================                                           
2016-1-11    zhaoke             v1.1         ���� 
2016-1=14    yuanjian           V1.2         ����gradScaleRamAddr                                                                                                   
=========================================================                                           
--------------------------------------------------------------------------------------------------*/

int gradScaleRamAddr ;
int noEchoes      ;
int noSlices      ;
int noSliceBlock  ;
int noViewBlock   ;
int noAverages    ;
int noViews       ;
int noViewsSec    ;
int noSamples     ;
int noScans       ;
int bandWidthNo   ;
int noDiscard     ;
double repetitionDelay  ;//us
double echoDelay        ;//us
double receiverGain     ;//total dB
double sysFrequency     ;//nco frequency?
//tx
double txAtt           ;
int rfShape            ;
double rf90Scale       ;
double rf180Scale      ;

int rfSpoil            ;
double seAsmmetry      ;

int inGating           ;
double cardiacDelay    ;

//Gradient
double sliceThickness  ;//mm
double sliceSeparation ;//mm
double rampTime        ;//us
int    graOrientation     ;// 0: 1: 2: 3: 4: 5:?
int    offsetX            ;//DAC unit
int    offsetY            ;//DAC unit
int    offsetZ            ;//DAC unit
int    offsetBzero        ;//DAC unit
int    gateSlice          ;
int    gateRead           ;
int    gatePhase          ;
int    rephaseLobe        ; //us
int    sliceGraComp       ; //us
int    readGraComp        ; //us
int    phaseGraComp       ; //us
double crusherPiFID           ;
double sliceRehpase           ;
double crusherPresatDur       ;
double crusherPresatAmp       ;
double presatOrientation      ;
double presatRF               ;
double presatRFShape          ;
double presatScale            ;
double mtcPulse               ;
double mtcScale               ;
double mtcCrusherDur          ;
double mtcCrusherAmp          ;
double mtcpulseoffset         ;
double mtcPulseDela           ;


