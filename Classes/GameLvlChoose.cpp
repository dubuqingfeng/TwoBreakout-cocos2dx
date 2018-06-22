#include "GameLvlChoose.h"
#include "GameViewLayer.h"

GameLvlChoose::GameLvlChoose(){
	_level = 1;
}
GameLvlChoose::~GameLvlChoose(){
}

Scene* GameLvlChoose::createScene(){
	Scene* scene = Scene::create();

	auto layer = GameLvlChoose::create();

	scene->addChild(layer);

	return scene;
}

bool GameLvlChoose::init(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	const char* norImg = "Button/choose_btn_nor.png";
	const char* lightImg = "Button/choose_btn_light.png";
	
	//Lv_1
	auto level_1_Item = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(GameLvlChoose::level_1,this));
	level_1_Item->addChild(createLevelLab("1"));
	
	//Lv_2
	auto level_2_Item = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(GameLvlChoose::level_2,this));
	level_2_Item->addChild(createLevelLab("2"));
	
	//Lv_3
	auto level_3_Item = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(GameLvlChoose::level_3,this));
	level_3_Item->addChild(createLevelLab("3"));
	
	auto menu = CCMenu::create(level_1_Item, level_2_Item, level_3_Item, nullptr);
	menu->alignItemsHorizontallyWithPadding(20);
	menu->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	this->addChild(menu);

	return true;
}

Label* GameLvlChoose::createLevelLab(const char* sLvl) {
	auto level_lab = Label::create(sLvl, "Arial", 60);
	level_lab->setColor(Color3B::RED);
	level_lab->setPosition(ccp(60, 60));

	return level_lab;
}

void GameLvlChoose::level_1(CCObject* pSender) {
	CCLOG("111111");
	CCScene* se=GameViewLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,se));
	_level = 1;
}

void GameLvlChoose::level_2(CCObject* pSender) {
	CCLOG("222222");
	_level = 2;
}

void GameLvlChoose::level_3(CCObject* pSender) {
	CCLOG("333333");
	_level = 3;
}