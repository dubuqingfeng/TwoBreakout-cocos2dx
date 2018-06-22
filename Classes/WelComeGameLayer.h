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
	bool setUpdateView();
	void vedioOnAndOffCallBack(cocos2d::CCObject* pSend);
	void menu1pCallback(cocos2d::CCObject* pSend);
	void menu2pCallback(cocos2d::CCObject* pSend);
	void menuAboutCoderCallback(cocos2d::CCObject* pSend);
	void to2pLayer();
};
#endif
