#ifndef __GameLvlChoose2p__H__
#define __GameLvlChoose2p__H__

#include "cocos2d.h"
USING_NS_CC;

class GameLvlChoose2p : public BaseLayer{
public:
	GameLvlChoose2p();
	~GameLvlChoose2p();
	virtual bool init();
	CREATE_FUNC(GameLvlChoose2p);
	void Login2RegisterClicked(cocos2d::CCObject* pSender);
	static Scene* createScene();
	//更新函数
	void update(float delta);
private:
	//--1--在init里面添加菜单，这里是回调函数
    void level_1(Ref* pSender);
    void level_2(Ref* pSender);
    void level_3(Ref* pSender);
	//返回按钮的回调函数
    void menuReturnCallBack(cocos2d::CCObject* pSend);
	//准备按钮的回调函数
	void menuPerpareCallback(cocos2d::CCObject* pSend);
	//--1--根据不同级别createLabel，菜单标签
	Label* createLevelLab(const char* sLvl);
	void goWelcomeLayer();
	int _level;
	bool levelchoose;
};/**/

#endif
