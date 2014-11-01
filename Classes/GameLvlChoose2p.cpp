#include "GameLvlChoose.h"
#include "GameViewLayer.h"
#include "GameLvlChoose2p.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "WelComeGameLayer.h"
#include "AboutCoderLayer.h"

GameLvlChoose2p::GameLvlChoose2p() {
	_level = 1;
	levelchoose = false;
}
GameLvlChoose2p::~GameLvlChoose2p() {
}

Scene* GameLvlChoose2p::createScene() {
	Scene* scene = Scene::create();
	auto layer = GameLvlChoose2p::create();
	scene->addChild(layer);
	return scene;
}
void GameLvlChoose2p::Login2RegisterClicked(CCObject *pSender) {

	JniMethodInfo jnifo;
	bool isHave = JniHelper::getStaticMethodInfo(jnifo,
			"com/digdream/breakout/MainActivity", "initStatic",
			"()Ljava/lang/Object;");
	jobject jobj;
	if (isHave) {
		jobj = jnifo.env->CallStaticObjectMethod(jnifo.classID, jnifo.methodID);
	}
	CCLog("正确获取到了 jobj");
	//获取方法信息
	isHave = JniHelper::getMethodInfo(jnifo,
			"com/digdream/breakout/MainActivity", "isInviter",
			"([Ljava/lang/String;)V");
	if (isHave) {
		jclass str_cls = jnifo.env->FindClass("java/lang/String");
		jstring str1 = jnifo.env->NewStringUTF("a"); //标识数据无意义，供java判断传入数据类型
		jobjectArray arrs = jnifo.env->NewObjectArray(3, str_cls, 0);
		jnifo.env->SetObjectArrayElement(arrs, 0, str1);
		jnifo.env->CallVoidMethod(jobj, jnifo.methodID, arrs);
	}
	CCLog("jni执行完毕");
}
bool GameLvlChoose2p::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//**1**-------- 创建关卡选择菜单 ------------------------------
	const char* norImg = "Button/choose_btn_nor.png";
	const char* lightImg = "Button/choose_btn_light.png";
	CC_CALLBACK_1(GameLvlChoose2p::Login2RegisterClicked, this);
	JniMethodInfo jnifo;
	bool isHavetest = JniHelper::getStaticMethodInfo(jnifo,
			"com/digdream/breakout/MainActivity", "initStatic", "()V");
	jobject jobj;
	if (isHavetest) {
		jobj = jnifo.env->CallStaticObjectMethod(jnifo.classID, jnifo.methodID);
	}
	CCLog("正确获取到了 jobj");
	//Lv_1
	auto level_1_Item = MenuItemImage::create(norImg, lightImg,
			CC_CALLBACK_1(GameLvlChoose2p::level_1, this));
	level_1_Item->addChild(createLevelLab("1"));

	//Lv_2
	auto level_2_Item = MenuItemImage::create(norImg, lightImg,
			CC_CALLBACK_1(GameLvlChoose2p::level_2, this));
	level_2_Item->addChild(createLevelLab("2"));

	//Lv_3
	auto level_3_Item = MenuItemImage::create(norImg, lightImg,
			CC_CALLBACK_1(GameLvlChoose2p::level_3, this));
	level_3_Item->addChild(createLevelLab("3"));

	// 这里创建一个准备按钮
	// 点击以后改成已准备

	//**1**	关卡菜单
	auto menu = CCMenu::create(level_1_Item, level_2_Item, level_3_Item,
			nullptr);

	//**1**	按照一行放置
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu);
	// 添加声音菜单按钮
	CCTexture2D* textureon =
			CCTextureCache::sharedTextureCache()->textureForKey(
					"gmme/button_sound_on.png");
	CCTexture2D* textureoff =
			CCTextureCache::sharedTextureCache()->textureForKey(
					"gmme/button_sound_off.png");
	CCMenuItemSprite* pitemVon = CCMenuItemSprite::create(
			CCSprite::createWithTexture(textureon),
			CCSprite::createWithTexture(textureon));
	CCMenuItemSprite* pitemVoff = CCMenuItemSprite::create(
			CCSprite::createWithTexture(textureoff),
			CCSprite::createWithTexture(textureoff));
	CCMenuItemToggle* pVedioTo = NULL;
	//
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isprepare", false)) {
		pVedioTo = CCMenuItemToggle::createWithTarget(this,
				menu_selector(GameLvlChoose2p::menuPerpareCallback), pitemVoff,
				pitemVon, NULL);
		CCLOG("isprepare false");
	} else {
		pVedioTo = CCMenuItemToggle::createWithTarget(this,
				menu_selector(GameLvlChoose2p::menuPerpareCallback), pitemVon,
				pitemVoff, NULL);
	}
	pVedioTo->setPosition(
			converSpritRel(getWinSize().width * 0.50f,
					getWinSize().height * 0.35f));
	// 创建返回菜单
	CCTexture2D* texturestar_up =
			CCTextureCache::sharedTextureCache()->textureForKey(
					"gmme/return_up.png");
	CCTexture2D* texturestar_down =
			CCTextureCache::sharedTextureCache()->textureForKey(
					"gmme/return_down.png");
	CCMenuItemSprite* pStar = CCMenuItemSprite::create(
			CCSprite::createWithTexture(texturestar_up),
			CCSprite::createWithTexture(texturestar_down), this,
			menu_selector(GameLvlChoose2p::menuReturnCallBack));

	pStar->setPosition(converSpritRel(0, 10));
	CCMenu* pMenu = CCMenu::create(pStar, pVedioTo, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
	this->scheduleUpdate();
	return true;
}
//更新函数
void GameLvlChoose2p::update(float delta) {
	//这里监听
	//if(本地准备好&&收到对方message，并且message中选择关卡一致)
	//{发送message;跳转}
	//
}

Label* GameLvlChoose2p::createLevelLab(const char* sLvl) {
	auto level_lab = Label::create(sLvl, "Arial", 60);
	level_lab->setColor(Color3B::RED);
	level_lab->setPosition(ccp(60, 60));
	return level_lab;
}
void GameLvlChoose2p::menuPerpareCallback(CCObject* pSend) {
	//if已选择关卡，发送准备好的message，否则调用toast
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isprepare", false)) {
		//未准备
		CCLOG("weizhunbei");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isprepare", false);
		//调用java inittoast
		//这里弹出toast
		//提示请使用茄子快传工具进行双人对战
		const char* pStr = "please prepare!!!";
		JniMethodInfo MethodInfo;
		bool BExist = JniHelper::getStaticMethodInfo(MethodInfo,
				"com/digdream/breakout/MainActivity", "initToast",
				"(Ljava/lang/String;)V");
		if (BExist) {
			jstring Str = MethodInfo.env->NewStringUTF(pStr);
			MethodInfo.env->CallStaticVoidMethod(MethodInfo.classID,
					MethodInfo.methodID, Str);
			MethodInfo.env->DeleteLocalRef(Str);
			MethodInfo.env->DeleteLocalRef(MethodInfo.classID);
		}
	} else {
		CCLOG("yizhunbei");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isprepare", true);
		//准备好了，选择关卡
		if (levelchoose == true) {
			//选择关卡并准备好了，发送信息到message
		} else {
			//调用inittoast，提示请选择关卡
			const char* pchooseStr = "please prepare!!!";
			JniMethodInfo MethodInfo;
			bool BchooseExist = JniHelper::getStaticMethodInfo(MethodInfo,
					"com/digdream/breakout/MainActivity", "initToast",
					"(Ljava/lang/String;)V");
			if (BchooseExist) {
				jstring Str = MethodInfo.env->NewStringUTF(pchooseStr);
				MethodInfo.env->CallStaticVoidMethod(MethodInfo.classID,
						MethodInfo.methodID, Str);
				MethodInfo.env->DeleteLocalRef(Str);
				MethodInfo.env->DeleteLocalRef(MethodInfo.classID);
			}
		}

	}
}
void GameLvlChoose2p::level_1(CCObject* pSender) {
	CCLOG("1");
	//关卡选择按钮
	_level = 1;
	levelchoose = true;
	//if点击了准备按钮，则发送message，否则调用jni 非ui线程调用toast
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("isprepare", true))
	{
		//发送message

	}
	else
	{
		//调用inittoast，提示请选择关卡
		const char* pchooseStr = "please prepare!!!";
		JniMethodInfo MethodInfo;
		bool BchooseExist = JniHelper::getStaticMethodInfo(MethodInfo,
				"com/digdream/breakout/MainActivity", "initToast",
				"(Ljava/lang/String;)V");
		if (BchooseExist) {
			jstring Str = MethodInfo.env->NewStringUTF(pchooseStr);
			MethodInfo.env->CallStaticVoidMethod(MethodInfo.classID,
					MethodInfo.methodID, Str);
			MethodInfo.env->DeleteLocalRef(Str);
			MethodInfo.env->DeleteLocalRef(MethodInfo.classID);
		}
	}
	CCScene* se = GameViewLayer::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInR::create(1, se));

}

void GameLvlChoose2p::level_2(CCObject* pSender) {
	CCLOG("2");
	_level = 2;
	levelchoose = true;
}

void GameLvlChoose2p::level_3(CCObject* pSender) {
	CCLOG("3");
	_level = 3;
	levelchoose = true;
}
void GameLvlChoose2p::menuReturnCallBack(CCObject* pSend) {
	CCScene* scene = WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInL::create(1, scene));
}
void GameLvlChoose2p::goWelcomeLayer() {
	CCScene* se = WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionMoveInR::create(1, se));
}
