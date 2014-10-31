#include "GameLvlChoose.h"
#include "GameViewLayer.h"
#include "GameLvlChoose2p.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "WelComeGameLayer.h"

GameLvlChoose2p::GameLvlChoose2p() {
	_level = 1;
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
			"org/cocos2dx/cpp/MainActivity", "initStatic",
			"()Ljava/lang/Object;");
	jobject jobj;
	if (isHave) {
		jobj = jnifo.env->CallStaticObjectMethod(jnifo.classID, jnifo.methodID);
	}
	CCLog("正确获取到了 jobj");
	//获取方法信息
	isHave = JniHelper::getMethodInfo(jnifo, "org/cocos2dx/cpp/MainActivity",
			"isInviter", "([Ljava/lang/String;)V");
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

	//**1**-------- 创建关卡选则菜单 ------------------------------
	const char* norImg = "Button/choose_btn_nor.png";
	const char* lightImg = "Button/choose_btn_light.png";
	CC_CALLBACK_1(GameLvlChoose2p::Login2RegisterClicked, this);
	JniMethodInfo jnifo;
	bool isHave = JniHelper::getStaticMethodInfo(jnifo,
			"org/cocos2dx/cpp/MainActivity", "initStatic", "()V");
	jobject jobj;
	if (isHave) {
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

	//**1**菜单
	auto menu = CCMenu::create(level_1_Item, level_2_Item, level_3_Item,
			nullptr);
	//**1**按照一行放置
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	this->addChild(menu);
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
	CCMenu* pMenu = CCMenu::create(pStar, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
	return true;
}

Label* GameLvlChoose2p::createLevelLab(const char* sLvl) {
	auto level_lab = Label::create(sLvl, "Arial", 60);
	level_lab->setColor(Color3B::RED);
	level_lab->setPosition(ccp(60, 60));

	return level_lab;
}

void GameLvlChoose2p::level_1(CCObject* pSender) {
	CCLOG("111111");
	CCScene* se = GameViewLayer::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInR::create(1, se));
	_level = 1;
}

void GameLvlChoose2p::level_2(CCObject* pSender) {
	CCLOG("222222");
	_level = 2;
}

void GameLvlChoose2p::level_3(CCObject* pSender) {
	CCLOG("333333");
	_level = 3;
}
void GameLvlChoose2p::menuReturnCallBack(CCObject* pSend){
	CCScene* scene=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(1,scene));
}
