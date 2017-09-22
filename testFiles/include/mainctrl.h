/*--------------------------------------------------------------------------------------------------
�����Ϊ˽�еı����ļ���ֻ���ڷ���ͨ�ſƼ����޹�˾��Ȩ������·���ʹ�á�                            
(C) COPYRIGHT 2016 FIRSTECH INC. ALL RIGHTS RESERVED                                                
��Ŀ����     :     MRI                                                                           
�ļ�����     :     mainctrl.h                                                                   
����         :     zhaoke                                                                       
������ϵ��ʽ :     zhaoke@afirstech.com                                                         
ʱ��         :     2016-01-11                                                                       
�汾         :     V1.0                                                                             
�ؼ���       :     mainctrl                                                                             
�ļ�����     :                                            
�޸����     :                                                                                      
ʱ��         �޸�����           �汾          �޸�˵��                                              
=========================================================                                           
2016-1-11    zhaoke             v1.1         ���� 
2017-2-22    zhaoke                          ��Ӻ���ע��                                                                                                  
=========================================================   */     
#ifndef MAINCTRL_H
#define MAINCTRL_H
#define INNER_TRIGGER               0
#define EXTERNAL_TRIGGER            1
#define MAIN_CTRL_TRIGGER_SEL_ADDR  0X91

/*************************************************************/
/*�����������ȴ��ض���ʱ�䷢��                                 */ 
/*��ڲ�����eventNo,�¼���(0-31)                              */
/*          eventLevel:�ȴ��¼�����ʲô״̬����2�֣��ߵ͵�ƽ.  */
/* Port     eventNO                                          */
/* USERIN0    24                                             */
/* USERIN1    25                                             */
/* USERIN2    26                                             */
/* USERIN3    27                                             */
/*************************************************************/

#define WaitEvent(eventLevel,eventNo)	                  wait(eventLevel,eventNo)
/*==========================================����ģ��⺯������====================================*/

/**********************************************************/
/*�������������ذ�������Ϊ 1�� ʱ�����ڵ�Tirgger����*/ 

/**********************************************************/
void GenerateTrigger()
{
      static double flag = 0;
       if(flag==0){
       	flag = 1;
       	Delay(10.0,MS);
       	}

	  //�ȴ���λ�����͸��±�������
	  wait(0,0);
	  //������������trigger
    trigger(4.0);
    //������3usʱ����±���	
    Delay(3.0,US);
    update;
    wait(1,2);
    //����ʱ�����trigger
    trigger(4.0);
}

/**********************************************************/
/*�������������ذ����Trigger�ź�                         */ 
/*��ڲ�����noAverages��ƽ������                          */
/*          noScans, TR����                               */
/*          TR,ɨ����,��λMS   */
/**********************************************************/
double MainctrlTrigger_scan_cnt = 0.0;
double MainctrlTrigger_Ave_cnt = 0.0;
void MainctrlTrigger(double noAverages,double noScans,double TR)
{	
    main_ctrl_start:
    MainctrlTrigger_Ave_cnt = 0.0;
    noAverages_loop: 
    GenerateTrigger(); 
    TimerCmp(TR,MS); 
	  MainctrlTrigger_Ave_cnt = MainctrlTrigger_Ave_cnt + 1.0;    
    if(MainctrlTrigger_Ave_cnt < noAverages)
    goto noAverages_loop;
    
    MainctrlTrigger_scan_cnt = MainctrlTrigger_scan_cnt + 1.0;    
    if(MainctrlTrigger_scan_cnt < noScans)
    goto main_ctrl_start;
    Lend:
    end;
}

#endif 	