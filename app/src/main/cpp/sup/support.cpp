//
// Created by lisi on 2017/9/22.
//


#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "LEVD.h"
#include "Last.h"
#include "../ADist/ADist.h"
#include "../MyCic_16/MyCic_16.h"

#define recBufSize 4800*2			//定义录音片长度

#define numfre 8
#define numfre_16 16
#define Deci 16
#define CutLength  4800           //切片长度
#define LastLength 960        //窗口长度
#define Short_Max_Value 32767

#define IQ_Length 300


class newdemo{
private:
public:
    Last *lastL;
    Last *lastR;
    int now;
    short *lastRecordL;
    short *lastRecordR;
    LEVD *levdIL;
    LEVD *levdQL;
    LEVD *levdIR;
    LEVD *levdQR;
    newdemo(int Numfre)
    {
        levdIL = new LEVD[Numfre];
        levdQL = new LEVD[Numfre];
        levdIR = new LEVD[Numfre];
        levdQR = new LEVD[Numfre];
        lastL = new Last[Numfre];
        lastR = new Last[Numfre];
        now = 0;
        lastRecordL = new short[LastLength];
        lastRecordR = new short[LastLength];
    }
    ~newdemo()
    {
        delete []levdIL;
        delete []levdQL;
        delete []levdIR;
        delete []levdQR;
        delete []lastRecordL;
        delete []lastRecordR;
    }
};



int* Ichange(short *in,int fre,int now,int length)
{
    int *out = new int[length];
    double x = fre*2.0* M_PI/48000.0;
    for(int i=1;i<=length;i++) {
        out[i-1] = (int)(in[i-1] *((cos((i+(2*now-1)*2200) * x))*Short_Max_Value));
    }
    return out;
}

int* Qchange(short *in,int fre,int now,int length)
{
    int *out = new int[length];
    double x = fre*2.0* M_PI/48000.0;
    for(int i=1;i<=length;i++) {
        out[i-1] = (int)(in[i-1] *((sin((i+(2*now-1)*2200) * x))*Short_Max_Value));
    }
    return out;
}

 double* getPhase(double* I,double* Q)
{
    double* out = new double[IQ_Length+1];
        out[0] = 0;
        for(int i = 1;i<=IQ_Length;i++) {
            out[i] = atan2(Q[i-1],I[i-1]);
//            Log.w("phase",String.valueOf(out[i]));
            out[0] +=out[i];
        }
        return out;
    }
 double countPhase(double last,double now)
{
    double dPhase;
    if ((now >= last && now - last < M_PI)||(now <last && last - now < M_PI))
        dPhase = now - last;
    else if (now -last >= M_PI)
        dPhase = now - last - 2 * M_PI;
    else if (last -now >= M_PI)
        dPhase = now - last + 2 * M_PI;
    else
        dPhase = 0;
    return dPhase;
}

 double* getDist(double lastDist,double lastPhase,double* Phase,int fre)
{
    double* temp = new double[IQ_Length];
        memcpy(temp,Phase+1,IQ_Length*sizeof(double));
        double v = 34300;
        double wl = v/fre;
        double* Dist = new double[IQ_Length];
        if(lastPhase<0)
            lastPhase = lastPhase +2*M_PI;
        for(int i = 0;i<IQ_Length;i++) {     //i=1
            if(temp[i]<0)
                temp[i]+=(M_PI*2);
            if (i >0)
                Dist[i] = Dist[i-1]+countPhase(temp[i-1],temp[i])/2/M_PI*wl/2;
            else
                Dist[0] = lastDist+countPhase(lastPhase,temp[0])/2/M_PI*wl/2;
        }
//        Log.w("dist",String.valueOf(Dist[Dist.length-1]));
        return Dist;
    }

double myADist(double *I,double *Q,double *Dist);
double demo(short *CoRecord,int now,Last *last,
            LEVD *levdI, LEVD *levdQ,double DIST[300],double *tempII,double *tempQQ)
{
    double totPhase = 0;
    double* Phase[numfre];
    double* Dist[numfre];
    bool flag = true;

//    LOGW("tdemo1");
    double I_A[300*16],Q_A[300*16];

    for(int w = 0; w < numfre ; w++ )
    {
        int *I;
        int *Q;
        I = Ichange(CoRecord,Freqarrary[w],now,6000);
        Q = Qchange(CoRecord,Freqarrary[w],now,6000);

        double II[375];
        MyCic_16(I,II);
        double QQ[375];
        MyCic_16(Q,QQ);
        memcpy(tempII+w*300,II+60,sizeof(double)*300);
        memcpy(tempQQ+w*300,QQ+60,sizeof(double)*300);

//        LOGW("help4");
        //----------------LEDV-----------------
        if(levdI[w].levd(tempII,IQ_Length)&&levdQ[w].levd(tempQQ,IQ_Length))
        {
            memcpy(I_A+w*300,levdI[w].levd_out,sizeof(double)*300);
            memcpy(Q_A+w*300,levdQ[w].levd_out,sizeof(double)*300);
            Phase[w] = getPhase(levdI[w].levd_out,levdQ[w].levd_out);
            totPhase +=Phase[w][0];
            Dist[w] = getDist(last[w].lastDist,last[w].lastPhase,Phase[w],Freqarrary[w]);
//            //LOGW("%lf",Dist[w][300-1]);
            if(fabs(Dist[w][IQ_Length-1]-last[w].lastDist)<0.2||fabs(Dist[w][IQ_Length-1]-last[w].lastDist)>10.0||fabs(Dist[w][IQ_Length-1])>100.0)
                flag = false;        //过滤

            last[w].setLastPhase(Phase[w][IQ_Length]);
        }
        else{
            flag = false;
        }
//        LOGW("help5");
    }

    if(flag) {

        for(int i =0;i<300;i++) {
            DIST[i] = 0;
            for(int j =0;j<numfre;j++)
                DIST[i]+=Dist[j][i];
            DIST[i]/=numfre;
        }
        double D_re = DIST[IQ_Length-1];
        double redist = myADist(I_A,Q_A,DIST);
        //LOGW("AD%f",redist);
        if(fabs(redist-D_re)<20.0&&redist>0)
        {
            D_re = redist;
        }
        if(D_re<0||(redist<0&&fabs(redist-D_re)<20.0))
            D_re=0;
        for (int w = 0; w < numfre; w++)
            last[w].setLastDist(D_re);
    }
    else
        DIST[300-1] = last[0].lastDist;
    totPhase=totPhase/numfre;


    return totPhase;
}

double demo_16(short *CoRecord,int now,Last *last,
            LEVD *levdI, LEVD *levdQ,double DIST[300],double *tempII,double *tempQQ,int Numfre)
{
    double totPhase = 0;

    LOGW("tip3");
    double* Phase[numfre_16];
    double* Dist[numfre_16];
    bool flag = true;

    double I_A[300*numfre_16],Q_A[300*numfre_16];

//    LOGW("tip4");
    for(int w = 0; w < numfre_16 ; w++ )
    {
        int *I;
        int *Q;
        I = Ichange(CoRecord,Freqarrary[w],now,6000);
        Q = Qchange(CoRecord,Freqarrary[w],now,6000);
        double II[375];
//        LOGW("cic1");
        MyCic_16(I,II);
//        LOGW("cic2");
        double QQ[375];
        MyCic_16(Q,QQ);
        memcpy(tempII+w*300,II+75,sizeof(double)*300);
        memcpy(tempQQ+w*300,QQ+75,sizeof(double)*300);

        LOGW("levd1");
        //----------------LEDV-----------------
        if(levdI[w].levd(II+75,300)&&levdQ[w].levd(QQ+75,300))
        {
//            LOGW("levd2");
            memcpy(I_A+w*300,levdI[w].levd_out,sizeof(double)*300);
            memcpy(Q_A+w*300,levdQ[w].levd_out,sizeof(double)*300);
//            LOGW("levd3");
            Phase[w] = getPhase(levdI[w].levd_out,levdQ[w].levd_out);
            totPhase +=Phase[w][0];
//            LOGW("levd4");
            Dist[w] = getDist(last[w].lastDist,last[w].lastPhase,Phase[w],Freqarrary[w]);
            LOGW("levd5");
            if(fabs(Dist[w][IQ_Length-1]-last[w].lastDist)<0.2||fabs(Dist[w][IQ_Length-1]-last[w].lastDist)>20.0||fabs(Dist[w][IQ_Length-1])>100.0){
                flag = false;        //过滤
                LOGW("tip55");
                }

            last[w].setLastPhase(Phase[w][IQ_Length]);
        }
        else{
            flag = false;
        }
    }

//    LOGW("tip5");
    if(flag) {
        for(int i =0;i<300;i++) {
            DIST[i] = 0;
            for(int j =0;j<numfre_16;j++)
                DIST[i]+=Dist[j][i];
            DIST[i]/=numfre_16;
        }
        double D_re = DIST[IQ_Length-1];
        double redist = myADist(I_A,Q_A,DIST);
        //LOGW("AD%f",redist);
        if(fabs(redist-D_re)<20.0&&redist>0)
        {
            D_re = redist;
        }
        if(D_re<0||(redist<0&&fabs(redist-D_re)<20.0))
            D_re=0;
        for (int w = 0; w < numfre_16; w++)
            last[w].setLastDist(D_re);
    }
    else
        DIST[IQ_Length-1] = last[0].lastDist;


    totPhase=totPhase/numfre_16;


    return totPhase;
}
int MaxLoc(double  in[],int length)
{
    int re=0;
    double max = in[0];
    for(int i = 1;i<length;i++)
    {
        if(in[i]>max)
        {
            max = in[i];
            re = i;
        }
    }
    return re;
}
double myADist(double *I,double *Q,double *Dist)
{
    double Thr = 2.5e13;
    double dist=Dist[300-1];
    double basedist = 34300.0/(350*64)/2.0;         //补充到64位

    double *RE;
    RE = new double[64*300];
    ADist(I,Q,RE);
    double re[64][300];
    int Loc[64];            //j 0-109
    double Value[64];
    for( int i =0;i<64;i++)
    {
        memcpy(re[i],RE+i*300,300*sizeof(double));
        Loc[i] = MaxLoc(re[i],300);     //j 0-109
        Value[i] = re[i][Loc[i]];
    }

        int LOC = MaxLoc(Value,64);        //i 0-63
        if(LOC<8&&re[LOC][Loc[LOC]]>Thr)
        {
            //LOGW("ADV%lf",re[LOC][Loc[LOC]]);

            dist = basedist * LOC + Dist[300-1]-Dist[Loc[LOC]];
            if(dist>80)
            {
                //LOGW("ADF1%lf",Dist[300-1]);
                //LOGW("ADF2%lf",Dist[Loc[LOC]]);
            }
            //LOGW("ADF%lf",dist);
        }
    return dist;
}