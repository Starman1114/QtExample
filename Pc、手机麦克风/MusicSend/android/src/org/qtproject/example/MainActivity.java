package org.qtproject.example;
import android.os.Environment;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.media.MediaScannerConnection;
import android.util.Log;
import android.widget.EditText;

import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.text.SimpleDateFormat;
import java.util.Date;


public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity{
    private static final String storagePath = Environment.getExternalStorageDirectory().getAbsolutePath();
    private static final String appPath = storagePath+"/EnergyEvaluationApp";

    public MainActivity()
      {

      }


   public static int getmax(){
          int m=2;
          return m;
   }

  public static String path(){
      return storagePath;
   }

  public static void recordMusic(){
      int audioRecordBufSize = AudioRecord.getMinBufferSize(48000,
                                    AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);
      audioRecordBufSize = 9600;
      AudioRecord audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, 48000,
                        AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT, audioRecordBufSize*2);

      try {
          audioRecord.startRecording();
          byte[] recordBuffer = new byte[audioRecordBufSize];
        // while(true){
        //      String name = "输入文件名字"
        //      SimpleDateFormat df = new SimpleDateFormat("yyyyMMddHHmmss");
        //      File recordFile = new File(appPath+"/"+name+df.format(new Date())+".pcm");
        //      recordFile.mkdirs();
        //      recordFile.createNewFile();
        //      if(recordFile.exists())
        //          recordFile.delete();
        //
        //      DataOutputStream dos = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(recordFile)));
        //
        //      int bufferReadResult = audioRecord.read(recordBuffer, 0, recordBuffer.length);
        //      dos.write(recordBuffer ,0, bufferReadResult);
        //      MediaScannerConnection.scanFile(MainActivity.this, new String[] { recordFile.getAbsolutePath() }, null, null);
        //      dos.close();
        //  }

      } catch (Exception e) {
          // TODO Auto-generated catch block
          e.printStackTrace();
      }

  }
}
