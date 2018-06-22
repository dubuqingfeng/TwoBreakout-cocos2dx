#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__
#include "cocos2d.h"
class BaseLayer:public cocos2d::CCLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(BaseLayer);
	cocos2d::CCSize getWinSize();
	cocos2d::CCPoint getWinOrigin();
	cocos2d::CCPoint getWinCenter();
	cocos2d::CCPoint converSpritRel(float x, float y);
};
#endif