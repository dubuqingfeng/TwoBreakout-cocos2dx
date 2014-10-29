#ifndef __GameLvlChoose__H__
#define __GameLvlChoose__H__

#include "cocos2d.h"
USING_NS_CC;

class GameLvlChoose : public Layer{
public:
	GameLvlChoose();
	~GameLvlChoose();
	virtual bool init();
	CREATE_FUNC(GameLvlChoose);

	static Scene* createScene();

private:
	//--1--��init������Ӳ˵��������ǻص�����
    void level_1(Ref* pSender);
    void level_2(Ref* pSender);
    void level_3(Ref* pSender);

	//--1--���ݲ�ͬ����createLabel���˵���ǩ
	Label* createLevelLab(const char* sLvl);

	int _level;
};/**/

#endif