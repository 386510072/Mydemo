package com.lee.edu.mydemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.text.DecimalFormat;
import android.Manifest;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class MainActivity extends AppCompatActivity {


    private double []Freqarrary = {15050,15400,15750,16100,16450,16800,17150,17500,17850,18200,18550,18900,19250,19600,19950,20300};
    private int numfre = 16;
//    private double []Freqarrary = {17500,17850,18200,18550,18900,19250,19600,19950,20300,20650};		//设置播放频率
//    private int numfre = 8;



    private Button btnPlayRecord;		//开始按钮

    private Button btnStopRecord;		//结束按钮

    private EditText editText;			//显示距离

    private TextView tvDist;			//显示距离
    private TextView tvDist2;			//显示距离


    private boolean flag = true;		//播放标志

    private AudioRecord audioRecord;	//录音对象

    private int recBufSize = 4800*2;			//定义录音片长度




    /**
     * 采样率（默认44100，每秒44100个点）
     */
    private int sampleRateInHz = 48000;

    private int Deci = 16;

    /**
     * 编码率（默认ENCODING_PCM_16BIT）
     */
    private int encodingBitrate = AudioFormat.ENCODING_PCM_16BIT;

    /**
     * 声道（默认单声道）
     */
    private int channelConfig = AudioFormat.CHANNEL_IN_STEREO;		//立体道



    /**
     * 1s内17500hz的波值
     */

//    private int [] BIGbufferL=new int[10240*(300)];
//    private int [] BIGbufferR=new int[10240*(300)];



    private Handler mHandler = new Handler() {
        //设置圆环角度
        @Override
        public void handleMessage(Message msg) {

            switch (msg.what) {
                case 0:

                    break;

                case 1:
                    tvDist.setText(msg.obj.toString());
                    break;
                case 2:
                    tvDist2.setText(msg.obj.toString());
                    break;
            }


        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String[] permissions = {Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE};

            requestPermissions(permissions, 1);
        btnPlayRecord = (Button)findViewById(R.id.btnplayrecord);
        btnStopRecord = (Button)findViewById(R.id.btnstoprecord);
        tvDist = (TextView)findViewById(R.id.textView1);
        tvDist.setText(String.valueOf(0));
        tvDist2 = (TextView)findViewById(R.id.textView2);
        tvDist2.setText(String.valueOf(0));
        editText = (EditText)findViewById(R.id.editText);
        editText.setText("");

        btnStopRecord.setEnabled(false);	//


        int minBufSize = AudioRecord.getMinBufferSize(
                sampleRateInHz, channelConfig,
                encodingBitrate);
//        Log.w("recBufSize",String.valueOf(minBufSize));         //7104


        minBufSize = recBufSize;      //0.1s

        audioRecord = new AudioRecord(
                MediaRecorder.AudioSource.MIC, sampleRateInHz,
                channelConfig,
                encodingBitrate, minBufSize);
//        Log.w("","s");
        //17500Hz的波形
        /**
         * 这部分取最大波形恐怕有问题，录取声音不一定为小于1的正弦波
         *
         */


        //播放按钮
        btnPlayRecord.setOnClickListener(new OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                btnPlayRecord.setEnabled(false);
                btnStopRecord.setEnabled(true);
                flag=true;
//	            Log.w("",1);
                new ThreadInstantPlay().start();		//播放
                try {
                    Thread.currentThread().sleep(10);	//等待开始播放再录音
                } catch (InterruptedException e) {
                    // TODO 自动生成的 catch 块
                    e.printStackTrace();
                }
                new ThreadInstantRecord().start();		//录音

                //录音播放线程
            }
        });
        //停止按钮
        btnStopRecord.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO 自动生成的方法存根
                btnPlayRecord.setEnabled(true);
                btnStopRecord.setEnabled(false);
//                CkBox.setChecked(false);
                flag=false;

            }
        });

    }
    /**
     * 即时播放线程
     * @author lisi
     *
     */
    class ThreadInstantPlay extends Thread
    {
        @Override
        public void run()
        {
            FrequencyPlayer FPlay = new FrequencyPlayer(numfre,Freqarrary);
            FPlay.palyWaveZ();
            while(flag){
                if(!flag)
                    FPlay.colseWaveZ();
            }
            FPlay.colseWaveZ();
            Log.w("tip","pstop");
        }
    }

    /**
     *
     * 即时录音线程
     *
     */
    class ThreadInstantRecord extends Thread
    {
        @Override
        public void run()
        {
            int cutlength = sampleRateInHz/Deci/10;//300

            short [] bsRecord = new short[recBufSize];
            short [] bsRecordL = new short[recBufSize/2];
            short [] bsRecordR = new short[recBufSize/2];
            short [] BIGDATA = new short[48000*30];
            short [] BIGDATA2 = new short[48000*30];
            int n=0;
            double lastDistL = 0;
            double lastDistR = 0;
            //---------------------------

            //--------------jni------------------------
            DemoNew(numfre);
            //=========================================

            while (flag==false){}
            try {
                audioRecord.startRecording();
            } catch (IllegalStateException e) {
                // 录音开始失败
                e.printStackTrace();
                return;
            }
            Log.w("tip","start");

            int Len;
            while(flag)//大循环
            {
                Len = audioRecord.read(bsRecord, 0, recBufSize);//读取录音

                for(int i=0;i<Len;i++){
                    BIGDATA[n] = bsRecord[i];
                        bsRecordL[i/2] = bsRecord[i++];
                    BIGDATA2[n++] = bsRecord[i];
                        bsRecordR[i/2] = bsRecord[i];
                    }


                if(numfre==8) {
                    double []di = new double[cutlength] ;

                    double[] tempIIL = new double[numfre*cutlength];
                    double[] tempQQL = new double[numfre*cutlength];
                    DemoL(bsRecordL, di, tempIIL, tempQQL);
                    lastDistL = di[cutlength - 1];

                    double[] tempIIR = new double[numfre*cutlength];
                    double[] tempQQR = new double[numfre*cutlength];

                    DemoR(bsRecordR, di, tempIIR, tempQQR);
                    lastDistR = di[cutlength - 1];


                }
                else if(numfre==16) {
                    double[] di = new double[cutlength];//300

                    double[] tempIIL = new double[numfre*cutlength];
                    double[] tempQQL = new double[numfre*cutlength];
                    long s1 = System.currentTimeMillis();
                    Log.w("t-s", String.valueOf(s1));
                    DemoL16(bsRecordL, di, tempIIL, tempQQL,numfre);
                    lastDistL = di[cutlength - 1];
                    Log.w("t-d", String.valueOf(lastDistL));

                    double[] tempIIR = new double[numfre*cutlength];
                    double[] tempQQR = new double[numfre*cutlength];

                    DemoR16(bsRecordR, di, tempIIR, tempQQR,numfre);
                    lastDistR = di[cutlength - 1];
                }

                long s2=System.currentTimeMillis();
                Log.w("t-e",String.valueOf(s2));

                Message msg1 = new Message();
                msg1.what = 1;
                DecimalFormat df = new DecimalFormat("#.00");

                msg1.obj = (df.format(lastDistL));
                mHandler.sendMessage(msg1);

                Message msg2 = new Message();
                msg2.what = 2;

                msg2.obj = (df.format(lastDistR));
                mHandler.sendMessage(msg2);


            }//while end

            audioRecord.stop();
            Log.w("tip","stop");
            String filename = "";
            filename = editText.getText().toString();

            if(filename.isEmpty())
            {
                long a =System.currentTimeMillis();
                filename = ""+numfre+"-"+a;
            }
            try {
                saveToSDCard("01"+filename+".txt",BIGDATA,n);
                saveToSDCard("02"+filename+".txt",BIGDATA2,n);
            } catch (Exception e) {
                e.printStackTrace();
            }
            Log.w("tip","end");

        }


        /**
         *
         * 存储方法
         * @param filename
         * @param content
         * @param length
         * @throws Exception
         */
        public void saveToSDCard(String filename, short[] content, int length) throws Exception
        {
            ///storage/emulated/0
            File file = new File(Environment.getExternalStorageDirectory()+"/TEST", filename);
            FileOutputStream outStream = new FileOutputStream(file);
            OutputStreamWriter writer = new OutputStreamWriter(outStream,"gb2312");
            for (int i = 0; i<length;i++)
            {
                writer.write(String.valueOf(content[i]));
                writer.write("\n");
            }
            writer.flush();
            writer.close();
            outStream.close();
        }
        public void saveToSDCard(String filename, double[] content,int length) throws Exception
        {
            File file = new File(Environment.getExternalStorageDirectory()+"/TEST", filename);
            FileOutputStream outStream = new FileOutputStream(file);
            OutputStreamWriter writer = new OutputStreamWriter(outStream,"gb2312");
            for (int i = 0; i<length;i++)
            {
                writer.write(String.valueOf(content[i]));
                writer.write("\n");
            }
            writer.flush();
            writer.close();
            outStream.close();
        }



    }


    //本地方法，由java调用

    public native String stringFromJNI(int[] I);
    public native void myADistFromJNI(double[] inC,double[] inS,double[] RE);
    public native void DemoNew(int n);
    public native int DemoL(short[] Record,double[] DIST,double[] tempII,double[] tempQQ);
    public native int DemoR(short[] Record,double[] DIST,double[] tempII,double[] tempQQ);
    public native int DemoL16(short[] Record,double[] DIST,double[] tempII,double[] tempQQ,int numfre);
    public native int DemoR16(short[] Record,double[] DIST,double[] tempII,double[] tempQQ,int numfre);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
