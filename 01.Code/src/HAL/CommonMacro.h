#ifndef __COMMONMACRO_H
#define __COMMONMACRO_H

/*********************************/
/*          ͨ�ú궨���         */
/*  ��������ľ���̶��Լ��ɶ��� */
/*    Designed by _VIFEXTech     */
/*********************************/

//Finish  2019-03-21 v1.0 ����ע��
//Upgrade 2019-03-21 v1.1 ����__ValueCloseTo
//Upgrade 2019-05-16 v1.2 ����__ExecuteFuncWithTimeout
//Upgrade 2019-05-16 v1.3 ����__ValueStep
//Upgrade 2019-09-25 v1.4 ����__ExecuteOnce
//Upgrade 2020-01-27 v1.5 ����__SemaphoreTake
//Upgrade 2020-03-10 v1.6 ����__ValuePlus

/**
  * @brief  �������������������ı�ʱ����һ���¼�
  * @param  now:����صı���(����)
  * @param  func:�¼������ص�����(�����Ǹ�ֵ���������)
  * @retval ��
  */
#define __ValueMonitor(now, func) \
do{\
    static int last=(now);\
    if(last!=(now))func,last=(now);\
}while(0)
#define __EventMonitor(now, func) __ValueMonitor((now),func)//���ݾɴ���

/**
  * @brief  ��һ����������ƵĲ����ӽ�ָ��ֵ
  * @param  src:���ر���
  * @param  dest:���ӽ���ֵ
  * @param  step:����
  * @retval ��
  */
#define __ValueCloseTo(src, dest, step) \
do{\
    if((src)<(dest))(src)+=(step);\
    else if((src)>(dest))(src)-=(step);\
}while(0)

/**
  * @brief  ��һ���������ӻ��߼�ȥһ��ֵ���ڴ��ڵ������ֵ���0��ʼ������0������ֵ��ʼ
  * @param  src:���ر���
  * @param  step:���ӻ��߼��ٵ�ֵ
  * @param  max:���ֵ
  * @retval ��
  */
#define __ValueStep(src, step, max) ((src)=(((step)>=0)?(((src)+(step))%(max)):(((src)+(max)+(step))%(max))))

/**
  * @brief  ��һ���������ӻ��߼�ȥһ��ֵ���ڴ������ֵ�����Сֵ��ʼ��С����Сֵ������ֵ��ʼ
  * @param  src:���ر���
  * @param  plus:���ӵ�ֵ
  * @param  min:��Сֵ
  * @param  max:���ֵ
  * @retval ��
  */
#define __ValuePlus(src, plus, min, max)\
do{\
    int __value_temp = (src);\
    __value_temp += (plus);\
    if(__value_temp<(min))__value_temp=(max);\
    else if(__value_temp>(max))__value_temp=(min);\
    (src) = __value_temp;\
}while(0)

/**
  * @brief  ������ʽ���ָ��ʱ��ִ��һ������
  * @param  func:��ִ�к���(�����Ǹ�ֵ���������)
  * @param  time:�趨���ʱ��(ms)
  * @retval ��
  */
#define __IntervalExecute(func, time) \
do{\
    static unsigned long lasttime=0;\
    if(millis()-lasttime>=(time))func,lasttime=millis();\
}while(0)

/**
  * @brief  ��һ�������ظ�����ָ������
  * @param  func:�����ú���(�����Ǹ�ֵ���������)
  * @param  n:�ظ����ô���
  * @retval ��
  */
#define __LoopExecute(func, n) for(unsigned long i=0;i<(n);i++)func

#ifndef constrain
#   define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

/**
  * @brief  ��һ��ֵ������һ����Χ��
  * @param  x:�����Ƶ�ֵ(��������)
  * @param  min:��Сֵ(��������)
  * @param  max:���ֵ(��������)
  * @retval ��
  */
#define __LimitValue(x, min, max) ((x)=constrain((x),(min),(max)))

/**
  * @brief  ��һ��ֵ�ı仯��������ӳ�䵽��һ������
  * @param  x:��ӳ���ֵ(��������)
  * @param  in_min:��ӳ���ֵ����Сֵ
  * @param  in_max:��ӳ���ֵ�����ֵ
  * @param  out_min:��ӳ���ֵ����Сֵ
  * @param  out_max:��ӳ���ֵ�����ֵ
  * @retval ӳ��ֵ���
  */
#define __Map(x, in_min, in_max, out_min, out_max) \
    (((x)-(in_min))*((out_max)-(out_min))/((in_max)-(in_min))+(out_min))

/**
  * @brief  ��ȡһ�������Ԫ�ظ���
  * @param  arr:������(��������)
  * @retval ��������Ԫ�ظ���
  */
#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))

/**
  * @brief  ��һ��ֵǿ�ư�ָ�����ͽ��ͣ������ڽṹ�忽��
  * @param  type:������(��������)
  * @param  data:�����͵�����(��������)
  * @retval �������
  */
#define __TypeExplain(type, data) (*((type*)(&(data))))

/**
  * @brief  ִ��һ�������ڲ���ʱ�������ֱ�������ķ���ֵΪָ��ֵ
  * @param  func:�����ú���
  * @param  n:ϣ�������ķ���ֵ
  * @param  timeout:��ʱʱ��
  * @param  flag:�ⲿ�ṩ���������ڼ���Ƿ�ʱ
  * @retval ��
  */
#define __ExecuteFuncWithTimeout(func, n, timeout, flag)\
do{\
    volatile unsigned long start=millis();\
    (flag)=false;\
    while(millis()-start<(timeout)){\
        if(func==(n)){(flag)=true;break;}\
    }\
}while(0)

/**
  * @brief  ����ִֻ��һ�Σ������ڳ�ʼ��
  * @param  func:�����ú���(Ҳ�����Ǹ�ֵ���������)
  * @retval ��
  */
#define __ExecuteOnce(func)\
do{\
    static bool isInit = false;\
    if(!isInit){func,isInit=true;}\
}while(0)

/**
  * @brief  ��ȡ�ź�������semΪtrueʱִ��һ��func
  * @param  sem:�ź���(bool����)
  * @param  func:�����ú���(Ҳ�����Ǹ�ֵ���������)
  * @retval ��
  */
#define __SemaphoreTake(sem, func)\
do{\
    if((sem)){func,(sem)=false;}\
}while(0)

#endif
