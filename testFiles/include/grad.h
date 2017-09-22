/*--------------------------------------------------------------------------------------------------
�����Ϊ˽�еı����ļ���ֻ���ڷ���ͨ�ſƼ����޹�˾��Ȩ������·���ʹ�á�                            
(C) COPYRIGHT 2016 FIRSTECH INC. ALL RIGHTS RESERVED                                                
��Ŀ����     :     MRI                                                                           
�ļ�����     :     grad.h                                                                   
����         :     zhaoke                                                                       
������ϵ��ʽ :     zhaoke@afirstech.com                                                         
ʱ��         :     2016-01-11                                                                       
�汾         :     V1.0                                                                             
�ؼ���       :     Grad                                                                             
�ļ�����     :                                            
�޸����     :                                                                                      
ʱ��         �޸�����           �汾          �޸�˵��                                              
=========================================================                                           
2016-1-11    zhaoke             v1.1         ���� 
2016-10-28   zhaoke                          �ݶ���ת����ѡ����GradMatSel��������Ϊdouble��   
2017-2-22    zhaoke                          ��Ӻ���ע��    
2017-3-17    pengjing                        �޸������ݶȲ�����������ʱ���ڲ��������GradStartnew���� 
2017-3-17    pengjing                        ���ӿ���˫�ز�����λ����fastDualSeq()     
2017-5-6     zhaoke                          1.���GradRegStart��GradRamStart�궨�塣 
                                             2.GradScaleRam��ַ������Ϊint�ͣ���������ת�����ӵ�85��clk��ʱ 
                                             3.TrapelutzoidOneFixTrampTimeStart�� scaleRamAddr������Ϊint��                                        
=========================================================  */      
#ifndef GRAD_H
#define GRAD_H

#define GRAD_OUTPUT_SEL_ADDR 	        0x101
#define GRAD_DATA_SET_ADDR 	          0x102
#define GRAD_WAVE_CALC_SEL_ADDR_SLICE 0x103
#define GRAD_WAVE_CALC_SEL_ADDR_READ  0x222
#define GRAD_WAVE_CALC_SEL_ADDR_PHASE 0x242
#define GRAD_PARA_RAM_RD_ADDR         0x127
#define GRAD_SAMPLE_PERIOD_ADDR       0x112
#define GRAD_MAT_RAM_RD_ADDR 	        0x111
#define GRAD_SCALE_ADDR               432
#define GRAD_SCALE_RAM_ADDR           0x128
#define GRAD_CALC_SEL_ADDR           0x129

#define GRAD_SRP_SLICE                0x1
#define GRAD_SRP_READ          	      0x2
#define GRAD_SRP_PHASE                0x4
#define S_STEP_LENGTH_ADDR            0x1db
#define S_ADD_NO_ADDR                 0x1dc   
#define WAVE_GEN_TYPE_SEL_ADDR        0x1dd

/*�����ǿ���ֱ�Ӻ궨��ĺ���������������Ķ��弰˵������ݶ�ģ��⺯�����岿��,*/
/*���ú�ķ�ʽ�����������Դ������ɵ�����ָ�                             */
#define GradWaveCalcSelSlice(gradWaveCalcSel)		        setr(GRAD_WAVE_CALC_SEL_ADDR_SLICE,gradWaveCalcSel)
#define GradWaveCalcSelRead(gradWaveCalcSel)		        setr(GRAD_WAVE_CALC_SEL_ADDR_READ ,gradWaveCalcSel)
#define GradWaveCalcSelPhase(gradWaveCalcSel)		        setr(GRAD_WAVE_CALC_SEL_ADDR_PHASE,gradWaveCalcSel)

#define GradScaleReg(gradScale)                         setr(GRAD_SCALE_ADDR,gradScale)
 	
#define GradWaveTable(gradWaveNo)                       setr(GRAD_PARA_RAM_RD_ADDR,gradWaveNo)
#define GradScaleNext()                                 setr(GRAD_SCALE_RAM_ADDR,0x10000)
#define GradScaleRst()                                  setr(GRAD_SCALE_RAM_ADDR,0)

#define GradStart(gradWaveWidth)                        timer(1); \
                                                        setr(GRAD_OUTPUT_SEL_ADDR,1); \
                                                        timer(0,gradWaveWidth-24.0); \
                                                        timer(2)

#define GradStartnew(gradWaveWidth1,gradWaveWidth2)     timer(1); \
                                                        setr(GRAD_OUTPUT_SEL_ADDR,1); \
                                                        timer(0,(gradWaveWidth1+gradWaveWidth2)*US-24.0); \
                                                        timer(2)
//para1: ramp duration time,US
//para2: Hold time, US
//para3: gain
//para4: wave table NO.                                                        
#define GradGainRegStart(gradWaveWidth1,gradWaveWidth2,gain,waveNo)     timer(1); \
                                                        GradScaleReg(gain );\
                                                        GradWaveTable(waveNo);\
                                                        setr(GRAD_OUTPUT_SEL_ADDR,1); \
                                                        timer(0,(gradWaveWidth1+gradWaveWidth2)*US-6.0); \
                                                        timer(2)  
//para1: ramp duration time,US
//para2: Hold time, US
//para3: gain table address
//para4: wave table NO.                                                        
#define GradGainRamStart(gradWaveWidth1,gradWaveWidth2,scaleRamAddr,waveNo)     timer(1); \
                                                        GradScaleRam( scaleRamAddr);\
                                                        GradWaveTable(waveNo);\
                                                        setr(GRAD_OUTPUT_SEL_ADDR,1); \
                                                        timer(0,(gradWaveWidth1+gradWaveWidth2)*US-6.0); \
                                                        timer(2)                                                                                                               

#define GradGainRegStart_2(gradWavepoint,gradStepLength,platWidth,gain) do\
                                                       {\
                                                        double gradWavepoint_double;\
                                                        timer(1); \
                                                        setr(GRAD_CALC_SEL_ADDR,0);\
                                                        setr(WAVE_GEN_TYPE_SEL_ADDR,1);\
                                                        setr(S_STEP_LENGTH_ADDR,gradStepLength);\
                                                        setr(S_ADD_NO_ADDR,gradWavepoint);\
                                                        GradScaleReg(gain );\
                                                        setr(GRAD_OUTPUT_SEL_ADDR,1); \
                                                        gradWavepoint_double = gradWavepoint;\
                                                        timer(0,(gradWavepoint_double+platWidth)*US-42.0); \
                                                        timer(2);\
                                                      }while(0)                                                                                                                                                                       

#define GradGainRamStart_2(gradWavepoint,gradStepLength,platWidth,scaleRamAddr)     do\
                                                      {\
	                                                      double gradWavepoint_double;\
                                                        timer(1); \
                                                        setr(GRAD_CALC_SEL_ADDR,0);\
                                                        setr(WAVE_GEN_TYPE_SEL_ADDR,1);\
                                                        setr(S_STEP_LENGTH_ADDR,gradStepLength);\
                                                        setr(S_ADD_NO_ADDR,gradWavepoint);\
                                                        GradScaleRam(scaleRamAddr );\
                                                        setr(GRAD_OUTPUT_SEL_ADDR,1); \
                                                        gradWavepoint_double = gradWavepoint;\
                                                        timer(0,(gradWavepoint_double+platWidth)*US-42.0); \
                                                        timer(2);\
                                                      }while(0)  

                                                                                                                                                                                                                                
#define GradMatSel( gradRoatMatNO) do\
{\
		int  __gradRoatMatNO;\
		__gradRoatMatNO =gradRoatMatNO; \
    setr(GRAD_MAT_RAM_RD_ADDR,__gradRoatMatNO); \
}while(0)

#define GradScaleRam(scaleRamAddr)	 setr(GRAD_SCALE_RAM_ADDR, scaleRamAddr)

/*************************************************************/
//�������������ò���������һ�����β�                         
//��ڲ�����waveSel1��wave1��Ӧ�ı��                        
//          waveSel2��wave2��Ӧ�ı��                        
//          wave1Time��wave1������Ҫ��ʱ��                   
//          wave2Time��wave2������Ҫ��ʱ��                   
//          holdTime��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0
/*************************************************************/
void TrapezoidOneStart(int waveSel1, int waveSel2, double holdTime, double wave1Time, double wave2Time,double graGain)
{
	  double __waveTimeTemp;
	  double __waveTime1;
	  double __waveTime2;
	  double delay_tmp ;
	  timer(1);
	  delay_tmp=6.71;
	  TimerCmp(delay_tmp,US);
	  GradScaleReg(graGain);
	  	  
    /*ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(wave1Time,holdTime);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
//    GradStart(__waveTime2);
    GradStartnew(wave2Time,0);
}


/**************************************************************/
//�������������ò����� �����������β�                         
//��ڲ�����waveSel1�� wave1��Ӧ�ı��                        
//          waveSel2�� wave2��Ӧ�ı��                        
//          waveSel3�� wave3��Ӧ�ı��                        
//          waveSel4�� wave4��Ӧ�ı��                        
//          wave1Time��wave1������Ҫ��ʱ��                    
//          wave2Time��wave2������Ҫ��ʱ��                    
//          wave3Time��wave3������Ҫ��ʱ��                    
//          wave4Time��wave4������Ҫ��ʱ��                    
//          holdTime1��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0
//          holdTime2��wave2��wave3֮��ı���ʱ�䣬��Сֵ��Ϊ0
//          holdTime3��wave3��wave4֮��ı���ʱ�䣬��Сֵ��Ϊ0
/**************************************************************/
void TrapezoidConcatStart(int waveSel1,     int waveSel2,     int waveSel3,    int waveSel4,\
                          double holdTime1, double holdTime2, double holdTime3,double wave1Time,\
                          double wave2Time, double wave3Time, double wave4Time,double graGain1,double graGain2)
{
	  double __waveTimeTemp1;
	  double __waveTimeTemp2;
	  double __waveTimeTemp3;
	  double __waveTime1;
	  double __waveTime2;
	  double __waveTime3;
	  double __waveTime4;  
	  double delay_tmp ;
	  timer(1);
	  delay_tmp=3.35;
	  TimerCmp(delay_tmp,US);
	  GradScaleReg(graGain1);
    /*ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(wave1Time,holdTime1);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(wave2Time,holdTime2);
    /*���õڶ��β��κ͵����β���֮��ı���ʱ��*/
    GradScaleReg(graGain2);
    /*ѡ������β���*/
    GradWaveTable(waveSel3);
    /*��ʼ��������β���*/
    GradStartnew(wave3Time,holdTime3);
    /*���õ����β��κ͵��Ķβ���֮��ı���ʱ��*/
    /*ѡ����Ķβ���*/
    GradWaveTable(waveSel4);
    /*��ʼ������Ķβ���*/
    GradStartnew(wave4Time,0);
}

/**************************************************************/
//�������������ò����� �����������β�                         
//��ڲ�����waveSel1�� wave1��Ӧ�ı��                        
//          waveSel2�� wave2��Ӧ�ı��                        
//          waveSel3�� wave3��Ӧ�ı��                        
//          waveSel4�� wave4��Ӧ�ı��                        
//          waveSel5�� wave5��Ӧ�ı��                        
//          waveSel6�� wave6��Ӧ�ı��                        
//          wave1Time��wave1������Ҫ��ʱ��                    
//          wave2Time��wave2������Ҫ��ʱ��                    
//          wave3Time��wave3������Ҫ��ʱ��                    
//          wave4Time��wave4������Ҫ��ʱ��                    
//          wave5Time��wave5������Ҫ��ʱ��                    
//          wave6Time��wave6������Ҫ��ʱ��                    
//          holdTime1��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0
//          holdTime2��wave2��wave3֮��ı���ʱ�䣬��Сֵ��Ϊ0
//          holdTime3��wave3��wave4֮��ı���ʱ�䣬��Сֵ��Ϊ0
//          holdTime4��wave4��wave5֮��ı���ʱ�䣬��Сֵ��Ϊ0
//          holdTime5��wave5��wave6֮��ı���ʱ�䣬��Сֵ��Ϊ0
/**************************************************************/

void TrapezoidConcat3Start(int waveSel1, int waveSel2, int waveSel3, int waveSel4, int waveSel5, int waveSel6,\
                          double holdTime1, double holdTime2, double holdTime3, double holdTime4, double holdTime5, \
                          double wave1Time, double wave2Time, double wave3Time, double wave4Time, double wave5Time, double wave6Time, \
                          double graGain1,  double graGain2 , double graGain3 )
{
	  
	  double __waveTimeTemp1;
	  double __waveTimeTemp2;
	  double __waveTimeTemp3;
	  double __waveTimeTemp4;
	  double __waveTimeTemp5;
	  double __waveTime1;
	  double __waveTime2;
	  double __waveTime3;
	  double __waveTime4;
	  double __waveTime5;
	  double __waveTime6; 
	  double delay_tmp ;

    /*ѡ���һ�β���*/
    GradScaleReg(graGain1);//18
    GradWaveTable(waveSel1);//18
    /*��ʼ�����һ�β���*/
    GradStartnew(wave1Time,holdTime1);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(wave2Time,holdTime2);
    /*���õڶ��β��κ͵����β���֮��ı���ʱ��*/
    /*ѡ������β���*/
    GradScaleReg(graGain2);
    GradWaveTable(waveSel3);
    /*��ʼ��������β���*/
    GradStartnew(wave3Time,holdTime3);
    /*���õ����β��κ͵��Ķβ���֮��ı���ʱ��*/
    /*ѡ����Ķβ���*/
    GradWaveTable(waveSel4);
    /*��ʼ������Ķβ���*/
    GradStartnew(wave4Time,holdTime4);
    /*���õ��Ķβ��κ͵���β���֮��ı���ʱ��*/
    /*ѡ�����β���*/
    GradScaleReg(graGain3);
    GradWaveTable(waveSel5);
    /*��ʼ�������β���*/
    GradStartnew(wave5Time,holdTime5);
    /*���õ���β��κ͵����β���֮��ı���ʱ��*/
    /*ѡ������β���*/
    GradWaveTable(waveSel6);
    /*��ʼ��������β���*/
    GradStartnew(wave6Time,0);  
       
}
/*************************************************************/
/*�������������ò���������һ�����β� ,�̶������½�ʱ��       */
/*��ڲ�����waveSel1��wave1��Ӧ�ı��                        */
/*          waveSel2��wave2��Ӧ�ı��                        */
/*          trampTime��wave1��wave2������Ҫ��ʱ��            */
/*          holdTime��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*************************************************************/
void TrapezoidOneFixTrampTimeStart(int waveSel1, int waveSel2, double holdTime, double trampTime, double graGain)
{
	  double __waveTimeTemp;
	  double __waveTime1;
	  double __waveTime2;
	  double delay_tmp ;
	  timer(1);
	  delay_tmp=7.37;	  
	  GradScaleReg(graGain);
	  TimerCmp(delay_tmp,US);	  
    /*ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(trampTime,holdTime);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(trampTime,0);
}
/**************************************************************/
/*�������������ò����� �����������β�                         */
/*��ڲ�����waveSel1�� wave1��Ӧ�ı��                        */
/*          waveSel2�� wave2��Ӧ�ı��                        */
/*          waveSel3�� wave3��Ӧ�ı��                        */
/*          waveSel4�� wave4��Ӧ�ı��                        */
/*          trampTime  wave������Ҫ��ʱ��                     */
/*          holdTime1��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime2��wave2��wave3֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime3��wave3��wave4֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/**************************************************************/
void TrapezoidTwoFixTrampTimeStart(int waveSel1,     int waveSel2,     int waveSel3,    int waveSel4,\
                          double holdTime1, double holdTime2, double holdTime3,double trampTime,\
						  double graGain1,double graGain2)
{
	  double __waveTimeTemp1;
	  double __waveTimeTemp2;
	  double __waveTimeTemp3;
	  double __waveTime1;
	  double __waveTime2;
	  double __waveTime3;
	  double __waveTime4;  
	  double delay_tmp ;
	  timer(1);
	  delay_tmp=4.79;
	  TimerCmp(delay_tmp,US);
	GradScaleReg(graGain1);
    /*ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(trampTime,holdTime1);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(trampTime,holdTime2);
    /*���õڶ��β��κ͵����β���֮��ı���ʱ��*/
    GradScaleReg(graGain2);
    /*ѡ������β���*/
    GradWaveTable(waveSel3);
    /*��ʼ��������β���*/
    GradStartnew(trampTime,holdTime3);
    /*���õ����β��κ͵��Ķβ���֮��ı���ʱ��*/
    /*ѡ����Ķβ���*/
    GradWaveTable(waveSel4);
    /*��ʼ������Ķβ���*/
    GradStartnew(trampTime,0);
    	
}
/**************************************************************/
/*�������������ò����� �����������β�                         */
/*��ڲ�����waveSel1�� wave1��Ӧ�ı��                        */
/*          waveSel2�� wave2��Ӧ�ı��                        */
/*          waveSel3�� wave3��Ӧ�ı��                        */
/*          waveSel4�� wave4��Ӧ�ı��                        */
/*          waveSel5�� wave5��Ӧ�ı��                        */
/*          waveSel6�� wave6��Ӧ�ı��                        */
/*          trampTime  wave������Ҫ��ʱ��                     */
/*          holdTime1��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime2��wave2��wave3֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime3��wave3��wave4֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime4��wave4��wave5֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime5��wave5��wave6֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/**************************************************************/

void TrapezoidThreeFixTrampTimeStart(int waveSel1, int waveSel2, int waveSel3, int waveSel4, int waveSel5, int waveSel6,\
                          double holdTime1, double holdTime2, double holdTime3, double holdTime4, double holdTime5, \
                          double trampTime,double graGain1,  double graGain2 , double graGain3 )
{
	  
	  double __waveTimeTemp1;
	  double __waveTimeTemp2;
	  double __waveTimeTemp3;
	  double __waveTimeTemp4;
	  double __waveTimeTemp5;
	  double __waveTime1;
	  double __waveTime2;
	  double __waveTime3;
	  double __waveTime4;
	  double __waveTime5;
	  double __waveTime6; 
	  double delay_tmp ;
	  timer(1);
	  delay_tmp=2.39;
	  TimerCmp(delay_tmp,US);
    /*ѡ���һ�β���*/
    GradScaleReg(graGain1);
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(trampTime,holdTime1);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(trampTime,holdTime2);
    /*���õڶ��β��κ͵����β���֮��ı���ʱ��*/
    /*ѡ������β���*/
    GradScaleReg(graGain2);
    GradWaveTable(waveSel3);
    /*��ʼ��������β���*/
    GradStartnew(trampTime,holdTime3);
    /*���õ����β��κ͵��Ķβ���֮��ı���ʱ��*/
    /*ѡ����Ķβ���*/
    GradWaveTable(waveSel4);
    /*��ʼ������Ķβ���*/
    GradStartnew(trampTime,holdTime4);
    /*���õ��Ķβ��κ͵���β���֮��ı���ʱ��*/
    /*ѡ�����β���*/
    GradScaleReg(graGain3);
    GradWaveTable(waveSel5);
    /*��ʼ�������β���*/
    GradStartnew(trampTime,holdTime5);
    /*���õ���β��κ͵����β���֮��ı���ʱ��*/
    /*ѡ������β���*/
    GradWaveTable(waveSel6);
    /*��ʼ��������β���*/
    GradStartnew(trampTime,0);
       
}

/*************************************************************/
/*�������������ò���������һ�����β� ,�̶������½�ʱ��       */ 
/*          ����Ϊ���ֵ                                   */
/*��ڲ�����waveSel1��wave1��Ӧ�ı��                        */
/*          waveSel2��wave2��Ӧ�ı��                        */
/*          trampTime��wave1��wave2������Ҫ��ʱ��            */
/*          holdTime��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*************************************************************/
void TrapelutzoidOneFixTrampTimeStart(int waveSel1, int waveSel2, double holdTime, double trampTime, int scaleRamAddr)
{
	double delay_tmp ;
	timer(1);
	delay_tmp=7.37;	
	GradScaleRam(scaleRamAddr);
	TimerCmp(delay_tmp,US);
	  
    /*ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(trampTime,holdTime);
    /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(trampTime,0);
}

/**************************************************************/
/*�������������ò����� �����������β�                         */
/*��ڲ�����waveSel1�� wave1��Ӧ�ı��                        */
/*          waveSel2�� wave2��Ӧ�ı��                        */
/*          waveSel3�� wave3��Ӧ�ı��                        */
/*          waveSel4�� wave4��Ӧ�ı��                        */
/*          trampTime  wave������Ҫ��ʱ��                     */
/*          holdTime1��wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime2��wave2��wave3֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/*          holdTime3��wave3��wave4֮��ı���ʱ�䣬��Сֵ��Ϊ0*/
/**************************************************************/
// void TrapezoidTwoCycleStart(double noCycle,int waveSel1,     int waveSel2,     int waveSel3,    int waveSel4,\
                            // double holdTime1, double holdTime2, double holdTime3,double trampTime,\
						    // double graGain1,  double graGain2)
// {
	  // double __waveTimeTemp1;
	  // double __waveTimeTemp2;
	  // double __waveTimeTemp3;
	  // double __waveTime1;
	  // double __waveTime2;
	  // double __waveTime3;
	  // double __waveTime4;  
	  // double delay_tmp ;
	  // double count = 0.0;
	  // timer(1);
	  // delay_tmp=4.31;
	  // TimerCmp(delay_tmp,US);
	  
	// TrapezoidLoop:
	// GradScaleReg(graGain1);
    // /*ѡ���һ�β���*/
    // GradWaveTable(waveSel1);
    // /*��ʼ�����һ�β���*/
    // GradStartnew(trampTime,holdTime1);
    // /*���õ�һ�β��κ͵ڶ��β���֮��ı���ʱ��*/
    // /*ѡ��ڶ��β���*/
    // GradWaveTable(waveSel2);
    // /*��ʼ����ڶ��β���*/
    // GradStartnew(trampTime,holdTime2);
    // /*���õڶ��β��κ͵����β���֮��ı���ʱ��*/
    // GradScaleReg(graGain2);
    // /*ѡ������β���*/
    // GradWaveTable(waveSel3);
    // /*��ʼ��������β���*/
    // GradStartnew(trampTime,holdTime3);
    // /*���õ����β��κ͵��Ķβ���֮��ı���ʱ��*/
    // /*ѡ����Ķβ���*/
    // GradWaveTable(waveSel4);
    // /*��ʼ������Ķβ���*/
    // GradStartnew(trampTime,0);
	
	// count = count + 1.0;
    // if(count<noCycle)
    // goto TrapezoidLoop;		
// }


/**************************************************************/
/*�������������ò����� �����������β�                         */
/*��ڲ�����waveSel1�� wave1��Ӧ�ı��                        */
/*          waveSel2�� wave2��Ӧ�ı��                        */
/*          noCycle,   һ�������ݶȲ��ε�ѭ������             */
/*          graGain��  ����                                   */
/*          trampTime  wave������Ҫ��ʱ��                     */
/*          holdTime�� wave1��wave2֮��ı���ʱ�䣬��Сֵ��Ϊ1.66*/
/**************************************************************/
void epiReadStart(double noCycle,int waveSel1,int waveSel2,double holdTime,double trampTime,double graGain)
{
	  double __waveTimeTemp2;	     	  
	  double delay_tmp ;
	  double count = 1.0;
	  timer(1);
	    delay_tmp=6.35;	 
	  __waveTimeTemp2 =  holdTime- 1.66;
	  TimerCmp(delay_tmp,US);
	  GradScaleReg(graGain);
	
    /* ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(trampTime,holdTime);
    
    TrapezoidLoop: 
 	/* ѡ��ڶ��β���*/		       
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(trampTime,0);
    /*��ʼ��������β���*/
    GradWaveTable(waveSel2);
    /*��ʼ��������β���*/
    GradStartnew(trampTime,holdTime);
    /*ѡ����Ķβ���*/
    GradWaveTable(waveSel1);
    /*��ʼ������Ķβ���*/
    GradStartnew(trampTime,0);
	/*ѡ�����β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�������β���*/
    GradStartnew(trampTime,__waveTimeTemp2);
    /*ѭ������һ���ݶȲ���*/
    count = count + 1.0;
    if(count<noCycle) 
    {  
    goto TrapezoidLoop;	
    }

    /*ѡ������β���*/
    GradWaveTable(waveSel2);
    /*��ʼ��������β���*/
    GradStartnew(trampTime,0);
	/*ѡ����߶β���*/
    GradWaveTable(waveSel2);
    /*��ʼ������߶β���*/
    GradStartnew(trampTime,holdTime);    
	/*ѡ��ڰ˶β���*/
    GradWaveTable(waveSel1);
    /*��ʼ����ڰ˶β���*/
    GradStartnew(trampTime,0);

}
/**************************************************************/
/*�������������ò����� �����������β� �ú����������ݶȲ��εļ�*/
/*          ��ʱ������Ϊ(tplat+12)΢�룬���epiReadStartʹ�ã�*/
/*          ��ʱ(trampTime + tplat)΢�������һ�����ǲ���     */
/*��ڲ�����waveSel1�� wave1��Ӧ�ı��                        */
/*          waveSel2�� wave2��Ӧ�ı��                        */
/*          noCycle,   һ�����ǲ��ε�ѭ������                 */
/*          graGain��  ����                                   */
/*          trampTime  wave������Ҫ��ʱ��                     */
/*          tplat��    ���ǲ��εļ��ʱ��                     */
/**************************************************************/
void epiPhaseStart(double noCycle,int waveSel1,int waveSel2,double tplat,double trampTime,double graGain)
{	    
    double count = 0.0;
    double __waveTimeTemp1;
	double delay_tmp ;
	timer(1);	 
	delay_tmp = trampTime + tplat + 6.35;
	__waveTimeTemp1 = tplat-1.66;
	TimerCmp(delay_tmp,US);
	GradScaleReg(graGain);
	TrapezoidLoop:
    /*ѡ���һ�β���*/
    GradWaveTable(waveSel1);
    /*��ʼ�����һ�β���*/
    GradStartnew(trampTime,0);
    /*ѡ��ڶ��β���*/
    GradWaveTable(waveSel2);
    /*��ʼ����ڶ��β���*/
    GradStartnew(trampTime,__waveTimeTemp1);    
	count = count + 1.0;
	if(count<noCycle)
    goto TrapezoidLoop;	 
}
/**********************************************************/
/*�����������������ݶȵķ���ֵ                            */
/*��ڲ�����*/
/**********************************************************/
double GardSliceGain(double rfBandwidth,double thickSlice,double thickSliceRatioGain)
{

	double gradsgain;

    gradsgain = rfBandwidth/(thickSlice*thickSliceRatioGain);  
	
	return gradsgain;
}
/********************************************************************/
/*�����������������ݶȵ�Ԥ�����ݶȱ���ʱ�����ѡ���ݶ��ؾ����ݶȱ���ʱ�� */
/*��ڲ����� tref Ԥ���ݶȱ���ʱ��                                     */
/*         tsel180�� 180�����屣��ʱ�䣬GE�����ж˿ڸ�ֵ0               */
/*         tcrush�� GE�����ж˿ڸ�ֵ0                                 */
/********************************************************************/
double PreGardTime(double tcrush,double tsel90,double tsel180, double tref, double TE ,double trampTime)
{
	double tmp;
	double timeOut;

	tmp = TE*0.5 - tcrush - tsel90*0.5 -tsel180*0.5  - trampTime*4.0;
	if(tmp< tref)
		timeOut = tmp;
	else
		timeOut = tref;
	return timeOut;
}
/**********************************************************/
/*��������������ѡ���ݶȵ�crushʱ��                       */
/*��ڲ�����*/
/**********************************************************/
double TcrushGenerate(double tcrushIn,double gradsgain, double thickSlice,double thickSliceRatioGain,double trampTime)
{
	double tcrush_double;
    int tcrush_int;
	double tcrush;
	double tmp1;
	
	  tmp1 = 2.0/gradsgain/(thickSlice*thickSliceRatioGain);
	  tcrush_double=1000000.0*(tmp1-0.5*0.000001*trampTime)+tcrushIn;
    tcrush_int = tcrush_double;
    tcrush = tcrush_int;
	return tcrush;
}
/**********************************************************/
/*�����������������ݶȵķ���ֵ                            */
/*��ڲ�����*/
/**********************************************************/
double GardReadGain(double samplePeriod,double fovRead,double ratiaFreqOversampling)
{
	double read_bandwidth_tmp;
	double read_bandwidth;
	double gradrgain;
	read_bandwidth = AcquireDuration(samplePeriod,1.0);  
    read_bandwidth_tmp = 1000000.0/read_bandwidth;
    gradrgain = read_bandwidth_tmp/fovRead/ratiaFreqOversampling ;
	return gradrgain;
}
/**********************************************************/
/*����������������λ�����ݶȵı���ʱ��                    */
/*��ڲ�����*/
/**********************************************************/
double GardPhaseTime(double fovPhase,double gainEffPhase,double noScans , double noEchoes, double dummyShot,double trampTime)
{
	double no_View_Block;
	double timeOut;
	no_View_Block = (noScans - dummyShot)*noEchoes;
	timeOut=(no_View_Block-1)/2/fovPhase/gainEffPhase*1000000.0-trampTime;  
	return timeOut;
}

/**********************************************************/
/*����������������λ�����ݶȵ��������                    */
/*��ڲ�����*/
/**********************************************************/
double GainEffPhase(double fovPhase,double holdTime,double noScans , double noEchoes, double dummyShot,double trampTime)
{
	double no_View_Block;
	double gainEffPhase;
	no_View_Block = (noScans - dummyShot)*noEchoes;
	gainEffPhase = (no_View_Block-1)/2/fovPhase/(holdTime+trampTime)*1000000.0;
//	timeOut=(no_View_Block-1)/2/fovPhase/gainEffPhase*1000000.0-trampTime;  
	return gainEffPhase;
}
/**********************************************************/
/*��������������scan���                                  */
/*��ڲ�����*/
/**********************************************************/
double GradScanCnt (double noAverages) 
{
	static double AveCnt=0.0;
	static double scanCnt = 0.0;
	double scanCntOut;
      if(noAverages>1)
      {
           if(AveCnt==noAverages)
              AveCnt = 0.0;
            AveCnt =  AveCnt+1.0; 
            if(AveCnt == 1.0)
             scanCnt =  scanCnt+1.0;   
       }else
         scanCnt =  scanCnt+1.0;   	
	
	scanCntOut = scanCnt;
	return scanCntOut;
}
/**********************************************************/
/*��������������scan���                                  */
/*��ڲ�����*/
/**********************************************************/
double GradEnScanCnt(double noAverages) 
{
	static double AveCnt=0.0;
	static double scanCnt = 0.0;
	double scanCntOut;
      if(noAverages>1)
      {
           if(AveCnt==noAverages)
              AveCnt = 0.0;
            AveCnt =  AveCnt+1.0; 
            if(AveCnt == 1.0)
             scanCnt =  scanCnt+1.0;   
       }else
         scanCnt =  scanCnt+1.0;   	
	
	scanCntOut = scanCnt;
	return scanCntOut;
}

/**********************************************************/
/*��������������scan���                                  */
/*��ڲ�����*/
/**********************************************************/
double Grad3DEnScanCnt(double noAverages,double noScans) 
{
	static double AveCnt=0.0;
	static double scanCnt = 0.0;
	double scanCntOut;
	  if(scanCnt == noScans)
		  scanCnt = 0.0;
      if(noAverages>1.0)
      {
           if(AveCnt==noAverages)
              AveCnt = 0.0;
            AveCnt =  AveCnt+1.0; 
            if(AveCnt == 1.0)
             scanCnt =  scanCnt+1.0;   
       }else
         scanCnt =  scanCnt+1.0;   	
	
	scanCntOut = scanCnt;
	return scanCntOut;
}
/**********************************************************/
/*������������������DummyShot��ָʾ�źţ� �����20��DummyShotλ�ÿ�ѡ*/
/*��ڲ�����
/**********************************************************/
double DummyShotEn(double dummyShot,double noAverages,double dummy1,double dummy2,double dummy3,double dummy4,\
                 double dummy5,double dummy6,double dummy7,double dummy8,double dummy9,double dummy10,\
				 double dummy11,double dummy12,double dummy13,double dummy14,double dummy15,\
                 double dummy16,double dummy17,double dummy18,double dummy19,double dummy20)
{
	double dummyShotEn = 0.0;
	double dummyShotEn_out;
  double noScansCnt;
  
  noScansCnt = GradScanCnt ( noAverages) ;

  if(dummyShot ==0.0)
	  dummyShotEn = 0.0;
	else{

    if(noScansCnt == dummy1)
	    dummyShotEn = 1.0;
	  if(noScansCnt == dummy2)
		  dummyShotEn = 1.0;
	  if(noScansCnt == dummy3)
		  dummyShotEn = 1.0;
	  if(noScansCnt == dummy4)
		  dummyShotEn = 1.0;
	  if(noScansCnt == dummy5)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy6)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy7)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy8)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy9)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy10)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy11)
	  dummyShotEn = 1.0;
	  if(noScansCnt == dummy12)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy13)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy14)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy15)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy16)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy17)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy18)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy19)
		dummyShotEn = 1.0;
	  if(noScansCnt == dummy20)
		dummyShotEn = 1.0;
		
	}
	dummyShotEn_out = dummyShotEn;
	return dummyShotEn_out;
}

/**********************************************************/
/*������������λ����˳����ͬ�ĳ���ʱ�䣬�ı��ݶȷ���ֵʵ����λ����
/*��ڲ�����effectiveEcho ��Ч�ز���ţ����ز�ʱΪ1.����λ�����TR��ĿeffectiveNoScans = noScans - dummyShot . 
            echoCnt ����TR�Ļز�����ţ����ز�ʱΪ1
            echoBlockCnt ��ЧTR���
/**********************************************************/
double ModePhaseCodeGain(double modePhaseCode,double effectiveEcho,double noScans,double noEchoes,double dummyShot,\
                         double orderPhaseCode,double modePartialPhaseSampling,double partialPhaseSampling,\
                         double echoBlockCnt,double echoCnt,double graGain)
{
	double PhaseCodeGain = 0.0;
	double PhaseCodeGain_tmp = 0.0;
	double grad_tmp = 0.0;
	double grad_tmp1 = 0.0;
	double echoBlockCntOdd = 0.0;
	double partialPhaseSamplingHalf = 0.0;
	double comp1;
	double comp2;
	double tmp;
	int tmp1;
	double tmp2;
	double echoBlockCntOdd_tmp1;
	int echoBlockCntOdd_tmp2;
	double echoBlockCntOdd_tmp3;
	double effNoViewsOddTmp1;
	int effNoViewsOddTmp2;
	double effNoViewsOddTmp3;
	double effNoViewsOdd;
	double effectiveNoScans;//����λ�����TR��ĿeffectiveNoScans = noScans - dummyShot . 
	double effNoViewsHalf; //effNoViewsHalf = (effectiveNoScans * noEchoes +partialPhaseSampling)* 0.5 

	effectiveNoScans = noScans - dummyShot ;
	effNoViewsHalf = (effectiveNoScans * noEchoes +partialPhaseSampling)* 0.5 ;
	if(modePhaseCode == 1.0)
	    grad_tmp=(echoBlockCnt-(effectiveNoScans+1.0)*0.5)+(echoCnt-effectiveEcho)*effectiveNoScans;
    else if (modePhaseCode == 2.0)
		grad_tmp=((effectiveNoScans+1)*0.5- echoBlockCnt)+(echoCnt-effectiveEcho)*effectiveNoScans;
	else if (modePhaseCode == 3.0)
	{
		echoBlockCntOdd_tmp1 = echoBlockCnt/2.0;
		echoBlockCntOdd_tmp2 = echoBlockCntOdd_tmp1;
		echoBlockCntOdd_tmp3 = echoBlockCntOdd_tmp2;
		echoBlockCntOdd = echoBlockCntOdd_tmp1 - echoBlockCntOdd_tmp3;

		effNoViewsOddTmp1 = effNoViewsHalf;
		effNoViewsOddTmp2 = effNoViewsOddTmp1;
		effNoViewsOddTmp3 = effNoViewsOddTmp2;
		effNoViewsOdd = effNoViewsOddTmp1 - effNoViewsOddTmp3;

		if(effNoViewsOdd==0.0)
		{
			tmp = (echoBlockCnt-1.0)/2;
			tmp1 = tmp;
			tmp2 = tmp1;
			if(echoBlockCntOdd==0.0)
		    {
			    grad_tmp = (-1.0)*(0.5+tmp2)+(echoCnt-effectiveEcho)*effectiveNoScans;
		    }else{
				grad_tmp = (0.5+tmp2)+(echoCnt-effectiveEcho)*effectiveNoScans;
			}
		}else{
			tmp = echoBlockCnt/2.0;
			tmp1 = tmp;
			tmp2 = tmp1;
			if(echoBlockCntOdd==0.0)
		    {
			    grad_tmp = (-1.0)*tmp2+(echoCnt-effectiveEcho)*effectiveNoScans;
		    }else{
				grad_tmp = tmp2+(echoCnt-effectiveEcho)*effectiveNoScans;
			}
		}

	}
	
    grad_tmp1 = 0.0-grad_tmp;
    if (grad_tmp>effNoViewsHalf)
        grad_tmp=grad_tmp-effNoViewsHalf*2.0;
    if (grad_tmp1>effNoViewsHalf)
        grad_tmp=grad_tmp+effNoViewsHalf*2.0;
	
	partialPhaseSamplingHalf = partialPhaseSampling/2.0;
	if(partialPhaseSampling>0.0)
	{
	if(noEchoes  == 1.0)
	{
		if(modePhaseCode <3.0)
		{
			if(modePartialPhaseSampling==1.0)
                grad_tmp=grad_tmp-partialPhaseSamplingHalf;
            else
            	if(modePartialPhaseSampling==2)
                    grad_tmp=partialPhaseSamplingHalf-grad_tmp;
		}else{
					
			if(modePartialPhaseSampling==1.0)
			{
				comp1 = grad_tmp - effNoViewsHalf + partialPhaseSamplingHalf;	
				if(comp1>0.0)
					grad_tmp = 0.0-grad_tmp-partialPhaseSamplingHalf;
			}else{
				if(modePartialPhaseSampling==2)
				{
				    comp2 = grad_tmp + effNoViewsHalf - partialPhaseSamplingHalf;
				    if(comp2<0.0)
				    	grad_tmp = 0.0-grad_tmp+partialPhaseSamplingHalf;
				}
			}
				
		}
			
	}else{
		if(modePartialPhaseSampling>0.0)
		{
			if(modePartialPhaseSampling==1.0)
			{
				comp1 = grad_tmp - effNoViewsHalf + partialPhaseSamplingHalf;
				if(comp1>0.0)
					grad_tmp = 0.0-grad_tmp-partialPhaseSamplingHalf;
			}else{
				if(modePartialPhaseSampling==2)
				{
				    comp2 = grad_tmp + effNoViewsHalf - partialPhaseSamplingHalf;
				    if(comp2<0.0)
				    	grad_tmp = 0.0-grad_tmp+partialPhaseSamplingHalf;
				}
			}
		}
	}
    }
	PhaseCodeGain = graGain*grad_tmp/effNoViewsHalf;

	return PhaseCodeGain;
}

/**********************************************************/
/*��������������˫�ز�����λ����
/*��ڲ�����views_per_seg ��noEchoes
            shared_echoes ����ͼ��ɼ�����ز���
            te PDWI������ЧTE
			te_2 T2WI������ЧTE
			gp_loc ��ЧTR���
			echo_cnt ����TR�Ļز������
/**********************************************************/
double fastDualSeq(double no_views,double views_per_seg,double shared_echoes,double te,double te_2,double gp_loc,double echo_cnt)
{
	static int echo_centre, echo_location, echo_location0,extra_echo;
	int views_per_echo, phase_count;
	int no_views_eff, u_echoes, echo_sum, extra_val;
	int te_eff,l_limit,jump;
	static int array_count = 0;
	static int array_count1 = 0;
	static int phase_offset;
	static int gp_loc_tmp=0;
	int gp_cnt_tmp,echo_gain;
	static int current_view = 0;
	int gp_mul;
	double out;

	te_eff = te_2/te; 
	u_echoes = (views_per_seg-shared_echoes)/2; 
	echo_sum = u_echoes+shared_echoes; 
	no_views_eff = (no_views*(views_per_seg-u_echoes))/views_per_seg; 
	if (u_echoes > 1) 
	{	l_limit = echo_sum+1;//7
		jump = 0;
	}else {	l_limit = 2;
		jump = 1;
	}

	views_per_echo = no_views/(2*views_per_seg); 
	phase_count = views_per_echo/2; 
	
	if(gp_loc == gp_loc_tmp)
		gp_loc_tmp = gp_loc_tmp;
    else{
		gp_loc_tmp = gp_loc;
		if(gp_loc==1)
	    phase_offset = phase_count/2;
	//echo_location
    if(gp_loc<=phase_count)
	{
		array_count = array_count+1;
		echo_location = phase_count-array_count+phase_offset;
		echo_location0 = phase_count-array_count;
		phase_offset = phase_offset-1;
	    if(phase_offset < 0) 
			phase_offset = 0;
	
	}		
	else if(gp_loc<=views_per_echo)
	{
		if(array_count <= phase_count/2) 
			phase_offset = phase_offset+1;
		echo_location = array_count-phase_count-phase_offset-1;
		echo_location0 = array_count-phase_count-1;
		array_count = array_count-1;		
	}	    
    else if(gp_loc<=views_per_echo+phase_count)
	{
		array_count = array_count+1;
		echo_location = phase_count-array_count+phase_offset;
		echo_location0 = phase_count*2.0-array_count+phase_offset;
		phase_offset = phase_offset-1;
	    if(phase_offset < 0) 
			phase_offset = 0;
	}
	else{
		if(array_count <= phase_count/2) 
			phase_offset = phase_offset+1;	
		echo_location = array_count-phase_count-phase_offset-1;
		echo_location0 = array_count-phase_count*2.0-phase_offset-1;
		array_count = array_count-1;			
	}
	
	}

//echo_centre
    if (current_view > (no_views/2)-1)	
		gp_cnt_tmp = echo_cnt+1+views_per_seg;
	else
		gp_cnt_tmp = echo_cnt+1;	
	
	current_view = current_view+1;
	
	if(array_count1==views_per_seg)
		array_count1 = 0;
	array_count1 = array_count1+1;	
	
	if(gp_cnt_tmp<=views_per_seg)
	    echo_gain = 1;
    else
	    echo_gain = -1;

	if(array_count1==1){
		echo_centre = 0;
		extra_echo = 0;
	}else{
		if(array_count1==te_eff){
			echo_centre = 0;	
            extra_echo = 1; 		
		}else{
			echo_centre = ((views_per_echo*(array_count1-1)) + phase_count)*echo_gain;
			if(array_count1<te_eff){	
			    if (array_count1 > echo_sum) 			
					echo_centre = (views_per_echo*(te_eff-array_count1)+ phase_count)*echo_gain;
			}else{
				if (array_count1 > echo_sum+1) 
					echo_centre = (views_per_echo*(array_count1-echo_sum-1)+ phase_count)*echo_gain;
			}
			if(array_count1>u_echoes){
				if(array_count1<=echo_sum+jump)
				    echo_centre= ((array_count1-extra_echo)*views_per_echo - phase_count)*echo_gain;	                    
			}
			
		}
	}
	
	if (echo_cnt == 0 | echo_cnt == te_eff-1)	{
		gp_mul = echo_centre + echo_location0 ;
		}
	else	{
		gp_mul = echo_centre + echo_location;
		}
	if(gp_mul < (-no_views_eff/2)) gp_mul = gp_mul + no_views_eff;
	if((gp_mul+1) > (no_views_eff/2)) gp_mul = gp_mul - no_views_eff;
	out = gp_mul;
	
	return out;
}

#endif 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      