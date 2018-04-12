package com.wpf.ctest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        TextView text_add = (TextView) findViewById(R.id.text_add);
        text_add.setText(intFromJni(1,2)+"");

        setInt(3);
        setLong(4l);
        setFloat(5.0f);
        setDouble(6.0d);
        setString("测试传入字符串");



        List<Integer> listInteger = new ArrayList<>();
        listInteger.add(1);
        listInteger.add(2);
        listInteger.add(3);
        setList(listInteger,3);

        JNIWrapper wrapper = new JNIWrapper();
        wrapper.booleanData = false;
        String str = "Hello";
        byte[] srtbyte = str.getBytes();
        wrapper.byteData = srtbyte[1];
        wrapper.byteArray = srtbyte;
        wrapper.doubleData = 0.022;
        wrapper.floatData = 1.23f;
        wrapper.longData = (long) 23.232;
        wrapper.stringData = "测试传入object";
        wrapper.setIntData(11111);
        List<String> listString = new ArrayList<>();
        listString.add("1s");
        listString.add("2s");
        listString.add("3s");
        wrapper.list = listString;
        setClass(wrapper);

        setBuf(srtbyte,5);

        Log.e("wpf","1========="+getString());

//        byte[] byteL = getBuf();
//        for (int t=0;t<byteL.length;t++){
//            Log.e("wpf","2========="+byteL[t]);
//        }
        JNIWrapper obj = getPackage();
        Log.e("wpf","3========="+obj.getIntData());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int intFromJni(int a,int b);

    // java向native传递常用基本数据类型 和字符串类型
    public native void setInt(int data);
    public native void setLong(long data);
    public native void setFloat(float data);
    public native void setDouble(double data);
    public native void setString(String data);
    //java向native传递任意java对象（以向native传递ArrayList为例)
    public native void setList(List list, int len);
    //java向native传递自定义java对象
    public native void setClass(JNIWrapper data);
    //java向native传递数组类型
    public native void setBuf(byte[] buf, int len);

    //native向java传递字符串类型
    public native String getString();
    //native向java传递数组类型
    public native byte[] getBuf();
    //native向java传递java对象
    public native JNIWrapper getPackage();
}
