#ifndef __ABOUTCODER_LAYER_H__
#define __ABOUTCODER_LAYER_H__
#include "BaseLayer.h"
class AboutCoderLayer:public BaseLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(AboutCoderLayer);
	void menuReturnCallBack(cocos2d::CCObject* pSend);
private:
	bool setUpdateView();
};
#endif