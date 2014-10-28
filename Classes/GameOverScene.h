#ifndef __GAMEOVER_SCENC_H__
#define __GAMEOVER_SCENC_H__
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameOverScene:public cocos2d::CCLayer
{
	public:
	bool initWithWin(bool isWin);
	
	static cocos2d::CCScene* sceneWithWin(bool isWin);
	
};
#endif
