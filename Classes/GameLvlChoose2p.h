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
	void update(float delta);
private:
    void level_1(Ref* pSender);
    void level_2(Ref* pSender);
    void level_3(Ref* pSender);
    void menuReturnCallBack(cocos2d::CCObject* pSend);
	void menuPerpareCallback(cocos2d::CCObject* pSend);
	Label* createLevelLab(const char* sLvl);
	void goWelcomeLayer();
	int _level;
	bool levelchoose;
};/**/

#endif
