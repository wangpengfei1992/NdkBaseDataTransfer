#include <jni.h>
#include <string>
#include<android/log.h>
#include "test.h"


#define LOG_TAG  "wpf"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
extern "C" {
using namespace std;
JNIEXPORT jstring JNICALL Java_com_wpf_ctest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());

}

JNIEXPORT jint JNICALL
Java_com_wpf_ctest_MainActivity_intFromJni(JNIEnv *env, jobject instance, jint x, jint y) {
    test t;
    int result = t.getAdd(x,y);
    return result;
//    return x+y;
}

JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setInt(JNIEnv *env, jobject instance, jint x) {
    LOGE("setInt ===%d", x);
}

JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setLong(JNIEnv *env, jobject instance, jlong x) {
    LOGE("setLong === %ld", x);
}
JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setFloat(JNIEnv *env, jobject instance, jfloat x) {
    LOGE("setFloat === %f", x);
}
JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setDouble(JNIEnv *env, jobject instance, jdouble x) {
    LOGE("setDouble === %lf", x);
}
JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setString(JNIEnv *env, jobject instance, jstring jdata) {
    LOGE("setString ===%s", jdata);
    const char* cdata = env->GetStringUTFChars(jdata, 0);

    LOGE("setString ===%s", cdata);

    env->ReleaseStringUTFChars(jdata, cdata);
    env->DeleteLocalRef(jdata);
}
//传入list
JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setList(JNIEnv *env, jobject instance, jobject list, jint listLength) {

    //传入一个JAVA 的ArrayList对象，存放的范型为Integer，下面我们尝试拿到ArrayList的第一个元素

    //获取传入对象的java类型，也就是ArrayList
    jclass datalistcls = env->GetObjectClass(list);

    //执行 javap -s java.util.ArrayList 查看ArrayList的函数签名

    /* public E get(int);
       descriptor: (I)Ljava/lang/Object;
     */
    //从ArrayList对象中拿到其get方法的方法ID
    jmethodID getMethodID = env->GetMethodID(datalistcls, "get", "(I)Ljava/lang/Object;");
    //调用get方法，拿到list中存储的第一个Integer 对象
    jobject data0 = env->CallObjectMethod(list, getMethodID, 0);

    //javap -s java/lang/Integer
    jclass datacls = env->GetObjectClass(data0);
    /*
     * public int intValue();
       descriptor: ()I
     */
    jmethodID intValueMethodID = env->GetMethodID(datacls, "intValue", "()I");
    //将Integer 对象的int值取出
    int data0_int = env->CallIntMethod(data0, intValueMethodID);

    LOGE("%d", data0_int);

}

//传入对象如：JNIWrapper
JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setClass(JNIEnv *env, jobject instance, jobject data) {

    jclass cdata = env->GetObjectClass(data);

    //boolean 比较特殊
    jfieldID booleanDataID = env->GetFieldID(cdata, "booleanData", "Z");
    jboolean cbooleanData = env->GetBooleanField(data, booleanDataID);

    jfieldID byteDataID = env->GetFieldID(cdata, "byteData", "B");
    jboolean cbyteData = env->GetByteField(data, byteDataID);

    //注意JAVA 对象的私有属性此处也可以获取到
    jfieldID intDataID = env->GetFieldID(cdata, "intData", "I");
    jint cintData = env->GetIntField(data, intDataID);

    //long比较特殊
    jfieldID longDataID = env->GetFieldID(cdata, "longData", "J");
    jlong clongData = env->GetLongField(data, longDataID);

    jfieldID floatDataID = env->GetFieldID(cdata, "floatData", "F");
    jfloat cfloatData = env->GetFloatField(data, floatDataID);
//
    jfieldID doubleDataID = env->GetFieldID(cdata, "doubleData", "D");
    jdouble cdoubleData = env->GetDoubleField(data, doubleDataID);

    jfieldID stringDataID = env->GetFieldID(cdata, "stringData", "Ljava/lang/String;");
    jstring cstringData = (jstring)env->GetObjectField(data, stringDataID);
    const char *ccharData = env->GetStringUTFChars(cstringData, JNI_FALSE);
//
    LOGE("setClass bool %d", cbooleanData);
    LOGE("setClass byte %d", cbyteData);
    LOGE("setClass int %d", cintData);
    LOGE("setClass long %ld", clongData);
    LOGE("setClass float %f", cfloatData);
    LOGE("setClass double %lf", cdoubleData);
    LOGE("setClass String %s", ccharData);

    env->ReleaseStringUTFChars(cstringData, ccharData);
    env->DeleteLocalRef(cstringData);
}

//传入数组
JNIEXPORT void JNICALL Java_com_wpf_ctest_MainActivity_setBuf(JNIEnv *env, jobject instance, jbyteArray jbuf,jint len) {

    jbyte *cbuf = env->GetByteArrayElements(jbuf, JNI_FALSE);

    for(int i=0; i<len; i++){
        LOGE("setBuf buf[%d] %c", i, cbuf[i]);
    }

    env->ReleaseByteArrayElements(jbuf, cbuf, 0);
    env->DeleteLocalRef(jbuf);
}










/**
 * native向java 传递值
 */
//返回字符串
JNIEXPORT jstring JNICALL Java_com_wpf_ctest_MainActivity_getString(JNIEnv *env, jobject instance) {
    const char buf[] = "getString : I am from jni";
    return env->NewStringUTF(buf);
}
//返回数组
JNIEXPORT jbyteArray JNICALL Java_com_wpf_ctest_MainActivity_getBuf(JNIEnv *env, jobject instance) {

    //char *buf = "I am from jni";
    char buf[] = "getBuf : I am from jni";

    int len = sizeof(buf);
    LOGE("sizeof %d", len);    // 注意sizeof对于数组和指针是区别对待的
    jbyteArray ret = env->NewByteArray(len);
    env->SetByteArrayRegion(ret, 0, len, (jbyte *) buf);

    return ret;
}
//返回对象
JNIEXPORT jobject JNICALL Java_com_wpf_ctest_MainActivity_getPackage(JNIEnv *env, jobject instance) {
    //获取类对象 这个class文件存在于dex中，我们可以通过分析apk工具查看
//    jclass packagecls = env->FindClass("com/vonchenchen/myapplication/JNIWrapper$Package");
    jclass packagecls = env->FindClass("com/wpf/ctest/JNIWrapper");

    //获取这个类的构造方法的方法id 以及这个方法的函数签名
    jmethodID construcMethodID = env->GetMethodID(packagecls, "<init>", "()V");
    //创建这个java对象
    jobject packageobj = env->NewObject(packagecls, construcMethodID);

    //操作对象的属性
    jfieldID intDataID = env->GetFieldID(packagecls, "intData", "I");
    env->SetIntField(packageobj, intDataID, 88888);

    return packageobj;
}
}