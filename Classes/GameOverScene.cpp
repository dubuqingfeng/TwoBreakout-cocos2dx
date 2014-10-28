#include <GameOverScene.h>
bool GameOverScene::initWithWin(bool isWin)
{
	if(!CCLayer::init()){
		return false;
	}
	char words[64];
	if(isWin){
		sprintf(words,"Man you rock!");
		
	}
	else{
		sprintf(words,"Man you suck!");
	}
	CCLabelTTF* label = CCLabelTTF::create(words,"Arial",30);
	label->setPosition(ccp(320,300));
	this->addChild(label);
	
}
	
	CCScene* GameOverScene::sceneWithWin(bool isWin)
	{
		CCScene* sc = CCScene::create();
		GameOverScene* layer = new GameOverScene();
		layer->initWithWin(isWin);
		sc->addChild(layer);
		return sc;
	}
