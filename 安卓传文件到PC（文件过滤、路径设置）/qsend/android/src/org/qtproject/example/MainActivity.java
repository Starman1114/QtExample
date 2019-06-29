package org.qtproject.example;


import android.os.Environment;

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
}

