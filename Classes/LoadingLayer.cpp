#include "LoadingLayer.h"
#include "WelComeGameLayer.h"
#include "GameLvlChoose2p.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
USING_NS_CC;
LoadingLayer::LoadingLayer(){
	this->loadingNum=0;
	this->totalNum=14;
}
bool LoadingLayer::init(){
	bool isRet=false;
	do 
	{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!this->setUpdateView());

	CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/welcomebg.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));/*callfuncO_selector(LoadingLayer::loadCallBack))*/ // 欢迎界面 背景图片
	CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/coder.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); // 添加关于开发者背景图片
  
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/button_sound_on.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); // 欢迎界面 声音开始
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/button_sound_off.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); // 欢迎界面 声音关闭

	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/1p.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); // 欢迎界面 开发者按钮
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/1p_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/2p_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/about_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/option_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));

	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/2p.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/option.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/about.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this));
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/return_down.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); // 返回菜单按钮
	CCTextureCache::sharedTextureCache()->addImageAsync("gmme/return_up.png",CC_CALLBACK_1(LoadingLayer::loadCallBack,this)); // 返回菜单按钮

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
JniMethodInfo minfo;//定义Jni函数信息结构体
//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数

bool isHave = JniHelper::getStaticMethodInfo(minfo,
		"com/digdream/breakout/MainActivity","initGameMode","()I");
jint _int;
if (!isHave) {
	CCLog("jni:n此函数不存在");
} else {
	CCLog("jni:c此函数存在");
	//调用此函数
	_int = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);

	//尝试jint是否能正常接收返回的int值
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
CCLog("jni-javajj函数执行完毕");
#endif
		// 加载完的时候跳转到响应的界面
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
		//画面中部添加团队logo
	CCSprite* logoimg=CCSprite::create("gmbg/logo.png");
	CC_BREAK_IF(!logoimg);
	logoimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/2+getWinOrigin().y));
	this->addChild(logoimg,1);

	// 设置进度条的背景图片 我们把他放到屏幕下方的1/5处	
    CCSprite* loadbackimg=CCSprite::create("gmbg/lodingbg.png");
	CC_BREAK_IF(!loadbackimg);	
	loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
	this->addChild(loadbackimg,1);
	
	// 添加进度条
	CCSprite* loadimg=CCSprite::create("gmbg/longding.png");
	CC_BREAK_IF(!loadimg);	
	CCProgressTimer* pt = CCProgressTimer::create(loadimg);
	pt->setType(kCCProgressTimerTypeBar);// 设置成横向的
	//可以看作是按矩形显示效果的进度条类型
	pt->setMidpoint(ccp(0,0)); 
	//  用来设定进度条横向前进的方向从左向右或是从右向左
	pt->setBarChangeRate(ccp(1,0));
	//重新设置锚点
	float tex=getWinSize().width/2+getWinOrigin().x;
	float tey=getWinSize().height/5+getWinOrigin().y-5;
	pt->setPosition(ccp(tex,tey));
	pt->setPercentage(0);
	this->addChild(pt,2,1);

	isRet=true;
	} while (0);
	return isRet;
}
