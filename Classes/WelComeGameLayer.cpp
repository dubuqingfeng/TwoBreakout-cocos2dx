#include "WelComeGameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameViewLayer.h"
#include "GameLvlChoose.h"
#include "GameLvlChoose2p.h"
#include "AboutCoderLayer.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
USING_NS_CC;
bool WelComeGameLayer::init() {
	bool isRet = false;
	do {
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateView());
		isRet = true;
	} while (0);
	return isRet;
}
void WelComeGameLayer::onEnter() {
	BaseLayer::onEnter();
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
	} else {
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isplay", true)) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
					"music/dt.mp3", true);
			CCUserDefault::sharedUserDefault()->setBoolForKey("isplay", true);
		}
	}

}
CCScene* WelComeGameLayer::scene() {
	CCScene* scene = CCScene::create();
	WelComeGameLayer* layer = WelComeGameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool WelComeGameLayer::setUpdateView() {
	bool isRet = false;
	do {
		CCTexture2D* texturebg =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmbg/welcomebg.png");
		CCSprite* pSpriteBg = CCSprite::createWithTexture(texturebg);
		CC_BREAK_IF(!pSpriteBg);
		pSpriteBg->setPosition(getWinCenter());
		this->addChild(pSpriteBg, 1);

		CCTexture2D* textureon =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/button_sound_on.png");
		CCTexture2D* textureoff =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/button_sound_off.png");
		CCMenuItemSprite* pitemVon = CCMenuItemSprite::create(
				CCSprite::createWithTexture(textureon),
				CCSprite::createWithTexture(textureon));
		CC_BREAK_IF(!pitemVon);
		CCMenuItemSprite* pitemVoff = CCMenuItemSprite::create(
				CCSprite::createWithTexture(textureoff),
				CCSprite::createWithTexture(textureoff));
		CC_BREAK_IF(!pitemVoff);
		CCMenuItemToggle* pVedioTo = NULL;
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",
				false)) {
			pVedioTo = CCMenuItemToggle::createWithTarget(this,
					menu_selector(WelComeGameLayer::vedioOnAndOffCallBack),
					pitemVoff, pitemVon, NULL);
		} else {
			pVedioTo = CCMenuItemToggle::createWithTarget(this,
					menu_selector(WelComeGameLayer::vedioOnAndOffCallBack),
					pitemVon, pitemVoff, NULL);
		}

		CC_BREAK_IF(!pVedioTo);
		pVedioTo->setPosition(
				converSpritRel(getWinSize().width * 0.10f,
						getWinSize().height * 0.95f));

		CCTexture2D* texturecoder_up =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/about.png");
		CCTexture2D* texturecoder_down =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/about_down.png");
		CCMenuItemSprite* pcoder = CCMenuItemSprite::create(
				CCSprite::createWithTexture(texturecoder_up),
				CCSprite::createWithTexture(texturecoder_down), this,
				menu_selector(WelComeGameLayer::menuAboutCoderCallback));
		CC_BREAK_IF(!pcoder);
		pcoder->setPosition(
				converSpritRel(getWinSize().width * 0.73f,
						getWinSize().height * 0.16f));

		CCTexture2D* texture1p_up =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/1p.png");
		CCTexture2D* texture1p_down =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/1p_down.png");
		CCMenuItemSprite* p1p = CCMenuItemSprite::create(
				CCSprite::createWithTexture(texture1p_up),
				CCSprite::createWithTexture(texture1p_down), this,
				menu_selector(WelComeGameLayer::menu1pCallback));
		CC_BREAK_IF(!p1p);
		p1p->setPosition(
				converSpritRel(getWinSize().width * 0.73f,
						getWinSize().height * 0.40f));

		CCTexture2D* texture2p_up =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/2p.png");
		CCTexture2D* texture2p_down =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/2p_down.png");
		CCMenuItemSprite* p2p = CCMenuItemSprite::create(
				CCSprite::createWithTexture(texture2p_up),
				CCSprite::createWithTexture(texture2p_down), this,
				menu_selector(WelComeGameLayer::menu2pCallback));
		CC_BREAK_IF(!p2p);
		p2p->setPosition(
				converSpritRel(getWinSize().width * 0.73f,
						getWinSize().height * 0.32f));

		CCTexture2D* textureaboutcoder_up =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/option.png");
		CCTexture2D* textureaboutcoder_down =
				CCTextureCache::sharedTextureCache()->textureForKey(
						"gmme/option_down.png");
		CCMenuItemSprite* paboutcoder = CCMenuItemSprite::create(
				CCSprite::createWithTexture(textureaboutcoder_up),
				CCSprite::createWithTexture(textureaboutcoder_down), this,
				menu_selector(WelComeGameLayer::menu1pCallback));
		CC_BREAK_IF(!paboutcoder);
		paboutcoder->setPosition(
				converSpritRel(getWinSize().width * 0.73f,
						getWinSize().height * 0.24f));

		CCMenu* pMenu = CCMenu::create(pVedioTo, pcoder, paboutcoder, p2p, p1p,
		NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 2);

		isRet = true;
	} while (0);
	return isRet;
}
void WelComeGameLayer::vedioOnAndOffCallBack(CCObject* pSend) {
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isplay", false)) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCLOG("music is stop");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isplay", false);
	} else {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("isplay", true);
		CCLOG("music is play");
	}

}
void WelComeGameLayer::menu1pCallback(CCObject* pSend) {
	CCScene* se = GameLvlChoose::createScene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInR::create(1, se));
}
void WelComeGameLayer::menuAboutCoderCallback(CCObject* pSend) {
	CCScene* se = AboutCoderLayer::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInR::create(1, se));
}
void WelComeGameLayer::menu2pCallback(CCObject* pSend) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	JniMethodInfo minfo; 

	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"com/digdream/breakout/MainActivity","initGameMode","()I");
	jint _int;
	if (!isHave) {

	} else {
		_int = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
		JniMethodInfo minfo_ty;
		bool isHave = JniHelper::getStaticMethodInfo(minfo_ty, "com/digdream/breakout/MainActivity", "initGameMode", "()I");
		if (isHave) {
			minfo_ty.env->CallStaticVoidMethod(minfo_ty.classID, minfo_ty.methodID,_int);
		}
		/*if(_int == 2)
		{*/
			CCScene* se = GameLvlChoose2p::createScene();
			CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1, se));
		/*}
		else
		{
			const char* pStr = "jni";
			JniMethodInfo MethodInfo;
			bool BExist = JniHelper::getStaticMethodInfo(MethodInfo,"com/digdream/breakout/MainActivity","initToast","(Ljava/lang/String;)V");
			if (BExist)
			{
				jstring Str = MethodInfo.env->NewStringUTF(pStr);
				MethodInfo.env->CallStaticVoidMethod(MethodInfo.classID,MethodInfo.methodID,Str);
				MethodInfo.env->DeleteLocalRef(Str);
				MethodInfo.env->DeleteLocalRef(MethodInfo.classID);
			}

		}*/
	}
#endif

}
void WelComeGameLayer::to2pLayer() {
	CCLOG("to2player");
	CCScene* se = GameLvlChoose2p::createScene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInR::create(1, se));
}
