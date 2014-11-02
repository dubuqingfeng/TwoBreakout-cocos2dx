LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/AboutCoderLayer.cpp \
				   ../../Classes/BaseLayer.cpp \
				   ../../Classes/LoadingLayer.cpp \
				   ../../Classes/WelComeGameLayer.cpp \
				   ../../Classes/GameViewLayer.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/MyContactListener.cpp \
				   ../../Classes/GameLvlChoose.cpp \
				   ../../Classes/GameLvlChoose2p.cpp \
				   ../../Classes/TestJni.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)
LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic

$(call import-module,.)
