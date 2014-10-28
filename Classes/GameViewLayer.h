#ifndef __GAMEVIEW_LAYER_H__
#define __GAMEVIEW_LAYER_H__
#include "BaseLayer.h"
#include "../cocos2d/external/Box2D/Box2D.h"
#include "MyContactListener.h"
//  这个界面是  游戏界面
class GameViewLayer:public BaseLayer{
	int _score;
	b2World* _world;//描述重力加速度的世界。。
	b2Body* ball;
	b2Body* _paddle;
	b2MouseJoint* _mouseJoint;
	MyContactListener* listener;
	b2Fixture* _bottom;
	cocos2d::CCSprite* ballSp;
	cocos2d::CCSprite* paddleSp;
public:
	virtual bool init();
	//bool onTouchBegan(Touch* pTouch, Event* event);
	void update(float delta);
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameViewLayer);
	int _getTagForBody(b2Body* body);
	void menuReturnCallBack(cocos2d::CCObject* pSend); // 点击返回按钮 触发的事件
private:
	bool setUpdateView();
};
#endif
