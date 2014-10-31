#include "cocos2d.h"
#include "TestJni.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
//#include "jnier.h"
#define CLASS_NAME "org/cocos2dx/cpp/MainActivity"
#include "string"
using namespace cocos2d;
#ifdef __cplusplus
extern "C" {
#endif
void Java_org_cocos2dx_cpp_MainActivity_initMode(JNIEnv* env,
        jobject thiz) {
        CCLog("µÇÂ¼Ê§°Ü");
        CCLog("java from c");
}
#ifdef __cplusplus
}
#endif
#endif

