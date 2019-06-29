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

    public MainActivity(){

     }

    public static String path(){
        return storagePath;
     }


}
