#include <jni.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <android/log.h>
#include <pthread.h>

#define DEBUG_TAG "NDK_threadCreate"
#define THREAD_TAG "NDK"

int t = 0;

jlong Java_com_jklarfeld_threadtest_MainActivity_getNumCores(JNIEnv *env, jobject this)
{
	return (jlong)(unsigned long long)cpuCount();
}

int cpuCount()
{
	return android_getCpuCount();
}

void *countToAMillion(void *threadid)
{
	long threadID;
	threadID = (long)threadid;

	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Thread#[%ld] reporting for duty!", threadID);

	long stop = pow(10, 7);
	long i;
	long fake = 0;
	for(i=0; i<stop; i++)
	{
		//__android_log_print(ANDROID_LOG_DEBUG, THREAD_TAG, "%ld is %ld", threadID, i);
		fake++;
		fake = fake-3;
		fake = fake%2;
	}

	__android_log_print(ANDROID_LOG_DEBUG, THREAD_TAG, "Thread#%ld has reached a million and will close", threadID);

	pthread_exit(NULL);
	return 0;
}

jboolean Java_com_jklarfeld_threadtest_MainActivity_createThread(JNIEnv *env, jobject this)
{
	__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "createThread");

	int numThreads = cpuCount();

	pthread_t threads[cpuCount()];

	//attempt to create a pthread here

	int rc = 0;

	rc = pthread_create(&threads[t], NULL, countToAMillion, (void *)t);
	t++;
	if(t==4)
	{
		t = 0;
	}

	if (rc > 0)
	{
		__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "ERROR; return code from pthread_create() is %d\n", rc);
		return 0;
	}
	return 1;
}
