#ifndef __LOADING_LAYER_H__
#define __LOADING_LAYER_H__
#include "BaseLayer.h"

class LoadingLayer:public BaseLayer{
public:
	virtual bool init();
	CREATE_FUNC(LoadingLayer);
	static cocos2d::Scene* createScene();
	void loadCallBack(cocos2d::CCObject* ped);
	LoadingLayer();
private:
	int loadingNum;
	int totalNum;
	bool setUpdateView();
	void goWelcomeLayer();
	void to2pLayer();
};
#endif
