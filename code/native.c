/*
编译：gcc -I/usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -fPIC -shared -o libnative.so native.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <jni.h> //usr/lib/jvm/java-1.7.0-openjdk-amd64/include/jni.h

#if 0
typedef struct {
	char *name;			/* java里调用的函数名 */
	char *signature;	/* JNI字段描述符，用来表示Jave里调用的函数的参数和返回值类型 */
	void *fnPtr;		/* C语言实现的本地函数 */
}JNINativeMethod;
#endif


/*
注意：C函数比Java里的声明多2个参数: (JNIEnv *env, jclass cls)
*/
void c_hello(JNIEnv *env, jobject cls)
{
	printf("hello world!\n");
}

/*
	形参：int
	返回值：int
*/
jint c_myprintf(JNIEnv *env, jobject cls, jint m)
{
	printf("hello world! %d\n",m);
	return 100;
}

/*
	形参：String
	返回值：String
*/
jstring JNICALL c_display_string(JNIEnv *env, jobject cls, jstring str)
{
	//printf("this is c : %s\n",str);
	//return "return from C";

    const jbyte *cstr;
    cstr = (*env)->GetStringUTFChars(env, str, NULL);
    if (cstr == NULL) {
        return NULL; /* OutOfMemoryError already thrown */
    }
    printf("get string from java:%s\n", cstr);
	(*env)->ReleaseStringUTFChars(env, str, cstr);

	return (*env)->NewStringUTF(env, "return from c");

}

/*
	形参：传入数组
	返回值：int
*/
jint JNICALL c_display_data(JNIEnv *env, jobject cls, jintArray arr)
{
	jint *carr;
    jint i, sum = 0;

    carr = (*env)->GetIntArrayElements(env, arr, NULL);
    if (carr == NULL) {
        return 0; /* exception occurred */
    }
    for (i = 0; i < (*env)->GetArrayLength(env,arr); i++) {
        sum += carr[i];
    }
    (*env)->ReleaseIntArrayElements(env, arr, carr, 0);

    return sum;
}

/*
 * Class:     JNIDemo
 * Method:    display_array
 * Signature: ([I)[I
 *
 * 形参：传入数组
 * 返回值：输出数组
 */
jintArray JNICALL c_display_array(JNIEnv *env, jobject cls, jintArray arr)
{

	jint *carr;
	jint *oarr;
	jintArray rarr;
    jint i, n = 0;

    carr = (*env)->GetIntArrayElements(env, arr, NULL);
    if (carr == NULL) {
        return 0; /* exception occurred */
    }
	n = (*env)->GetArrayLength(env,arr);

	oarr = malloc(sizeof(jint)*n);
	if(oarr == NULL) {
		(*env)->ReleaseIntArrayElements(env, arr, carr, 0);
		return 0;
		
	}
	for(i = 0; i < n; i++) {
		oarr[i] = carr[n-1-i];
	}

	/*Creates an jint array with thegiven length.*/
	rarr = (*env)->NewIntArray(env,n);
	if(rarr == NULL) {
		(*env)->ReleaseIntArrayElements(env, arr, carr, 0);
		return 0;
	}
	/*Copies the contents of primitive arrays to or from a preallocated C buffer.	
	void (JNICALL *SetIntArrayRegion)
		  (JNIEnv *env, jintArray array, jsize start, jsize len, const jint *buf);
	*/
	(*env)->SetIntArrayRegion(env,rarr,0,n,oarr);

    (*env)->ReleaseIntArrayElements(env, arr, carr, 0);
	free(oarr);
/*---------------------- C callback Java ------------------------*/
	char cbuf[] = "hello callback in c";
	jbyteArray jbuf;
	jint len = sizeof(cbuf);
	jbuf = (*env)->NewByteArray(env,len);
	(*env)->SetByteArrayRegion(env,jbuf,0,len,(jbyte*)cbuf);
	jclass cls2 = (*env)->GetObjectClass(env,cls);
	jmethodID mid = (*env)->GetMethodID(env,cls2,"myCallBack","([B)V");
	if(mid == NULL)
		return ;/* method not found */
	printf("In C\n");
	(*env)->CallVoidMethod(env,cls,mid,jbuf);
	
    return rarr;
}

/* 
定义一个映射数组JNINativeMethod[]
可以注册多个本地函数
*/
static const JNINativeMethod methods[] = {
	{"hello","()V",(void *)c_hello},
	{"myprintf","(I)I",(void *)c_myprintf},
	{"display_string","(Ljava/lang/String;)Ljava/lang/String;",(void *)c_display_string},
	{"display_data","([I)I",(void *)c_display_data},
	{"display_array","([I)[I",(void *)c_display_array},
};


/* 只要java 加载库System.loadLibrary      就会执行该函数          */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    JNIEnv *env;
    jclass cls;

	/* 获得运行环境 */
    if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
        return JNI_ERR; /* JNI version not supported */
    }
    cls = (*env)->FindClass(env, "JNIDemo");
    if (cls == NULL) {
        return JNI_ERR;
    }

	/* 建立联系 java<--->c*/
	if((*env)->RegisterNatives(env,cls,methods,5) < 0)
		return JNI_ERR;
	
    return JNI_VERSION_1_4;
}


