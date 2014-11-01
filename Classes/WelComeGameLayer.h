#ifndef __WELCOMEGAME_LAYER_H__
#define __WELCOMEGAME_LAYER_H__
#include "BaseLayer.h"
class WelComeGameLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(WelComeGameLayer);
	virtual void onEnter();
private:
	// s设置界面
	bool setUpdateView();
	// 播放或者暂停音乐回调函数
	void vedioOnAndOffCallBack(cocos2d::CCObject* pSend);
	// 跳转的 关于单人游戏的回调函数
	void menu1pCallback(cocos2d::CCObject* pSend);
	//关于双人游戏的回调函数
	void menu2pCallback(cocos2d::CCObject* pSend);
	//关于关于开发者的回调函数
	void menuAboutCoderCallback(cocos2d::CCObject* pSend);
	void to2pLayer();
};
#endif
