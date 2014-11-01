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

private:
	//--1--在init里面添加菜单，这里是回调函数
    void level_1(Ref* pSender);
    void level_2(Ref* pSender);
    void level_3(Ref* pSender);
    void menuReturnCallBack(cocos2d::CCObject* pSend);
	//--1--根据不同级别createLabel，菜单标签
	Label* createLevelLab(const char* sLvl);
	void goWelcomeLayer();
	int _level;
};/**/

#endif
