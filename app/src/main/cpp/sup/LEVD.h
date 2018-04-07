//
// Created by lisi on 2017/9/22.
//

#ifndef MYDEMO_LEVD_H
#define MYDEMO_LEVD_H

#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "Peak.h"

#define TAG    "myjni-test" // 这个是自定义的LOG的标识
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型

int  Freqarrary[] = {17500,17850,18200,18600,18900,19250,19600,19950,20300,20650}	;	//设置播放频率
int  Freqarrary_16[] = {15050,15400,15750,16100,16450,16800,17150,17500,17850,18200,18600,18900,19250,19600,19950,20300}	;	//设置播放频率

class LEVD {
    public: bool flag ;       //是否找到第一个极值对
    double Thr;
    bool first;
    double *last;
    double last_SI;
    double *levd_SI;
    double last_Pks;
    bool last_type;
    double *levd_out;
    LEVD();
    bool levd(double *in,int length);
};


#endif //MYDEMO_7_11_LEVD_H
