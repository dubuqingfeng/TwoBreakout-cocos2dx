#include "LoadingLayer.h"
#include "WelComeGameLayer.h"
#include "GameLvlChoose2p.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
USING_NS_CC;
LoadingLayer::LoadingLayer(){
	this->loadingNum=0;
	this->totalNum=16;
}
bool LoadingLayer::init(){
	bool isRet=false;
	do 
	{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!this->setUpdateView());

	CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/welcomebg.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));/*callfuncO_selector(LoadingLayer::loadCallBack))*/ 
	CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/coder.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); 
  
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/button_sound_on.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); 
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/button_sound_off.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));

	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/1p.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); 
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/1p_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/2p_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/about_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/option_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));

	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/2p.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/option.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/about.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/prepared.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/unprepared.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/return_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/return_up.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));

	isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingLayer::createScene(){
	CCScene* scene=CCScene::create();
	LoadingLayer* layer=LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingLayer::loadCallBack(CCObject* ped){
	loadingNum++;	 
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	float now=pt->getPercentage();
	pt->setPercentage(100/totalNum+now);
	if(loadingNum<totalNum){
		
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JniMethodInfo minfo;

bool isHave = JniHelper::getStaticMethodInfo(minfo,
		"com/digdream/breakout/MainActivity","initGameMode","()I");
jint _int;

if (!isHave) {
	CCLog("jni");
} else {
	CCLog("jni");
	_int = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);

	JniMethodInfo minfo_ty;
	bool isHave = JniHelper::getStaticMethodInfo(minfo_ty, "com/digdream/breakout/MainActivity", "initGameMode", "()I");
	if (isHave) {
		minfo_ty.env->CallStaticVoidMethod(minfo_ty.classID, minfo_ty.methodID,_int);
	}
	if(_int == 2)
	{to2pLayer();}
	else
	{
		goWelcomeLayer();
	}
}
CCLog("jni-");
#endif
		CCLOG("loading over");

	}
}
void LoadingLayer::to2pLayer() {
	CCLOG("to2player");
	CCScene* se = GameLvlChoose2p::createScene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInR::create(1, se));
}

void LoadingLayer::goWelcomeLayer(){
	CCScene* se=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1,se));
}

bool LoadingLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
	CCSprite* logoimg=CCSprite::create("gmbg/logo.png");
	CC_BREAK_IF(!logoimg);
	logoimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/2+getWinOrigin().y));
	this->addChild(logoimg,1);

    CCSprite* loadbackimg=CCSprite::create("gmbg/lodingbg.png");
	CC_BREAK_IF(!loadbackimg);	
	loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
	this->addChild(loadbackimg,1);
	
	CCSprite* loadimg=CCSprite::create("gmbg/longding.png");
	CC_BREAK_IF(!loadimg);	
	CCProgressTimer* pt = CCProgressTimer::create(loadimg);
	pt->setType(kCCProgressTimerTypeBar);
	pt->setMidpoint(ccp(0,0)); 
	pt->setBarChangeRate(ccp(1,0));
	float tex=getWinSize().width/2+getWinOrigin().x;
	float tey=getWinSize().height/5+getWinOrigin().y-5;
	pt->setPosition(ccp(tex,tey));
	pt->setPercentage(0);
	this->addChild(pt,2,1);

	isRet=true;
	} while (0);
	return isRet;
}
