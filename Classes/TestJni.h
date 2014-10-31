#ifndef  _TEST_JNI_H_
#define  _TEST_JNI_H_
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#ifdef __cplusplus
#define CLASS_NAME "org/cocos2dx/cpp/MainActivity"
using namespace cocos2d;
extern "C" {

#endif

void Java_org_cocos2dx_cpp_MainActivity_initMode(JNIEnv *, jobject);


#ifdef __cplusplus

}

#endif
#endif
#endif
