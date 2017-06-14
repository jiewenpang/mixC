#ifndef _TESTJNI_
#define _TESTJNI_

#include <jni.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
using namespace std;

#define ARRAY_LEN  20

class TestJNI
{
	public:
		TestJNI();
		jstring NewJString(const char *str);
		string jstringTostring(jstring jstr);
		void StringSay(string name);
		void VectorSay(string name);
		void ArrayListSay(string name);
	private:
		JavaVMOption options[3];
		JNIEnv *env;
		JavaVM *jvm;
		JavaVMInitArgs vm_args;
		long status;
};
#endif


TestJNI::TestJNI()
{
	options[0].optionString = const_cast<char*>("-Djava.class.path=/home/pjw/greatProj/sample/Demo:");
	options[1].optionString = const_cast<char*>("-Xms100M");
	options[2].optionString = const_cast<char*>("-Xmx1000M");
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 3;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = JNI_TRUE;
	status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
}

jstring TestJNI::NewJString(const char *str)
{
	if(status == JNI_ERR || str == NULL)
		return 0;
	jclass strClass = env->FindClass("Ljava/lang/String;");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(str));
	env->SetByteArrayRegion(bytes, 0, strlen(str), (jbyte*)str);
	jstring encoding = env->NewStringUTF("GB2312");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

std::string TestJNI::jstringTostring(jstring jstr){
	char*   rtn   =   NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("GB18030");
	jmethodID mid = env->GetMethodID(clsstring,"getBytes","(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr,JNI_FALSE);
	if(alen > 0)  {
		rtn = (char*)malloc(alen+1);         
		memcpy(rtn,ba,alen);
		rtn[alen]=0;
	}

	env->ReleaseByteArrayElements(barr,ba,0);  
	std::string stemp(rtn);

	free(rtn);
	env->DeleteLocalRef(barr);
	env->DeleteLocalRef(strencode);
	env->DeleteLocalRef(clsstring);
	return   stemp;
}

void TestJNI::StringSay(string name)
{
	if(status != JNI_ERR){
		struct timeval t1, t2;
		struct timezone tz;
		jclass cls = env->FindClass("Demo");
		jobject obj = env->AllocObject(cls);

		jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
		jstring arg = NewJString(name.c_str());
		env->CallObjectMethod(obj, mid, arg);	

		mid = env->GetMethodID(cls, "StringCall", "()Ljava/lang/String;");
		gettimeofday (&t1, &tz);
		jstring jstr = (jstring)env->CallObjectMethod(obj, mid);
		gettimeofday (&t2, &tz);
		char* cstr = (char*)env->GetStringUTFChars(jstr, 0);

		printf ("t2 - t1 = %.3f\n", (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0);
		printf ("cstr = %s\n", cstr);

		delete cstr;
		env->DeleteLocalRef(obj);
	}
}

void TestJNI::VectorSay(string name)
{
	if(status != JNI_ERR){

		struct timeval t1, t2;
		struct timezone tz;
		jclass cls = env->FindClass("Demo");
		printf ("********* cls = %d\n", cls);
		jobject obj = env->AllocObject(cls);	

		jobjectArray objarr;
		jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
		printf ("********* mid = %d\n", mid);
		// jstring arg = NewJString(name.c_str());
		env->CallObjectMethod(obj, mid, NewJString(name.c_str()));	

		gettimeofday (&t1, &tz);
		mid = env->GetMethodID(cls, "VectorCall", "()[Ljava/lang/String;");
		objarr = (jobjectArray)env->CallObjectMethod(obj, mid);

		jstring jstr;
		jint len = env->GetArrayLength(objarr);
		printf ("len = %d @ %d\n", len, __LINE__);
		char* cstr = new char(len * 1042);
		char* tmp;
		int pos = 0;
		for (int i = 0; i < len; i++) {
			jstr = (jstring)env->GetObjectArrayElement(objarr, i);
			tmp = (char*)env->GetStringUTFChars(jstr, 0);
			memcpy (cstr + pos, tmp, strlen(tmp) + 1);
			pos += strlen(tmp) + 1;
			// printf ("@ %d\n", __LINE__);
		}
		gettimeofday (&t2, &tz);
		printf ("不好：  xxxxx   %s\n",cstr);
		printf ("t2 - t1 = %.3f\n", (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1000000.0);
		// delete cstr;
		env->DeleteLocalRef(obj);
	}
}

void TestJNI::ArrayListSay(string name)
{
	if(status != JNI_ERR){

		jclass cls = env->FindClass("Demo");
		jobject obj = env->AllocObject(cls);	

		jobjectArray objarr;
		jmethodID mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
		jstring arg = NewJString(name.c_str());
		env->CallObjectMethod(obj, mid, arg);

		mid = env->GetMethodID(cls, "ArrayListCall", "()Ljava/util/ArrayList;");
		objarr = (jobjectArray)env->CallObjectMethod(obj, mid);

		jstring jstr;
		char* cstr;
		for (int i = 0;i < env->GetArrayLength(objarr); i++) {
			jstr = (jstring)env->GetObjectArrayElement(objarr, i);
			cstr = (char*)env->GetStringUTFChars(jstr, 0);
			printf ("%s\n", cstr);
		}
		env->DeleteLocalRef(obj);
	}
}

int main()
{
	TestJNI test;
	// test.StringSay("C#");
	// test.ArrayListSay("Perl");
	test.VectorSay("Phylon");
}
