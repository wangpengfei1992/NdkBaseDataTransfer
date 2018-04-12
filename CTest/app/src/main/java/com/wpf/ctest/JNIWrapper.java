package com.wpf.ctest;

import java.util.List;

/**
 * Created by wangpengfei on 2018/3/23.
 */

public class JNIWrapper {
    public boolean booleanData;
    public byte byteData;
    private int intData;
    public long longData;
    public float floatData;
    public double doubleData;
    public String stringData;

    public byte[] byteArray;

    public List<String> list;

    public void setIntData(int data){
        intData = data;
    }

    public int getIntData(){
        return intData;
    }
}
