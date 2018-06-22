#include "GameViewLayer.h"
#include "WelComeGameLayer.h"
#include "Box2dUtils.h"
#include "MyContactListener.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
#define PTM_RATIO 32.0f
CCScene* GameViewLayer::scene() {
CCScene* scene = CCScene::create();
GameViewLayer* layer = GameViewLayer::create();
scene->addChild(layer);
return scene;
}
bool GameViewLayer::init() {
	bool isRet = false;
	do {
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateView());
		isRet = true;
	} while (0);
	ballSp = CCSprite::create("ball.png");
	ballSp->setPosition(ccp(39, 300));
	this->addChild(ballSp);

	paddleSp = CCSprite::create("Paddle.png");
	paddleSp->setPosition(ccp(120, 30));
	this->addChild(paddleSp);
	_world = new b2World(b2Vec2(0, 0));
	b2BodyDef paddleBodyDef;
	paddleBodyDef.type = b2_dynamicBody;
	paddleBodyDef.position.Set(paddleSp->getPositionX() / PTM_RATIO,
			paddleSp->getPositionY() / PTM_RATIO);
	paddleBodyDef.userData = paddleSp;
	_paddle = _world->CreateBody(&paddleBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(paddleSp->getContentSize().width / 2.0f / PTM_RATIO,
			paddleSp->getContentSize().height / 2.0f / PTM_RATIO);
	b2FixtureDef paddleFixDef;
	paddleFixDef.shape = &boxShape;
	paddleFixDef.density = 10.0f;

	paddleFixDef.friction = 0.4f;
	paddleFixDef.restitution = 0.1f;
	_paddle->CreateFixture(&paddleFixDef);

	const int padding = 30;
	int offsetX = 150;
	for (int i = 0; i < 4; i++) {
		CCSprite* block = CCSprite::create("block.png");
		block->setPosition(ccp(offsetX, 400));
		block->setTag(3);
		this->addChild(block);

		b2Body* blockBody = Box2dUtils::createDynamicBody(150 / PTM_RATIO,
				offsetX  / PTM_RATIO, block, _world);
		b2PolygonShape blockBox;
		blockBox.SetAsBox(block->getContentSize().width / 2.0f / PTM_RATIO,
				block->getContentSize().height / 2.0f / PTM_RATIO);

		Box2dUtils::createFixture(&blockBox, 10.0f, 0.0f, 0.2f, blockBody);
		offsetX += (padding + block->getContentSize().width);

	}

	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(39 / PTM_RATIO, 300 / PTM_RATIO);
	ballBodyDef.userData = ballSp;
	ball = _world->CreateBody(&ballBodyDef);

	b2CircleShape circle;
	circle.m_radius = (ballSp->getContentSize().width / 2.0f) / PTM_RATIO;
	b2FixtureDef ballFixDef;
	ballFixDef.shape = &circle;
	ballFixDef.density = 3;

	ballFixDef.friction = 0.2;
	ballFixDef.restitution = 0.8;
	ball->CreateFixture(&ballFixDef);
	ball->ApplyLinearImpulse(ball->GetMass() * b2Vec2(11,22),
			ball->GetWorldCenter(), true);
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
//3.b2BodyDef -- >b2Body
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0, 0);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
//b2FixtureDef -->b2Fixture

	b2EdgeShape groundShape;
	groundShape.Set(b2Vec2(0, 0), b2Vec2(screenSize.width / PTM_RATIO, 0));
	b2FixtureDef groundFixDef;
	groundFixDef.shape = &groundShape;
	groundFixDef.friction = 0.9f;
	_bottom = groundBody->CreateFixture(&groundFixDef);

	b2EdgeShape leftWall;
	leftWall.Set(b2Vec2(0, 0), b2Vec2(0, screenSize.height / PTM_RATIO));
	groundFixDef.shape = &leftWall;
	groundBody->CreateFixture(&groundFixDef);
	b2EdgeShape rightWall;
	rightWall.Set(b2Vec2(screenSize.width / PTM_RATIO, 0),
			b2Vec2(screenSize.width / PTM_RATIO,
					screenSize.height / PTM_RATIO));
	groundFixDef.shape = &rightWall;
	groundBody->CreateFixture(&groundFixDef);

	b2EdgeShape topWall;
	topWall.Set(b2Vec2(0, screenSize.height / PTM_RATIO),
			b2Vec2(screenSize.width / PTM_RATIO,
					screenSize.height / PTM_RATIO));
	groundFixDef.shape = &topWall;
	groundBody->CreateFixture(&groundFixDef);

	this->scheduleUpdate();

	this->setTouchEnabled(true);

	EventDispatcher* eventDispatcher =
			Director::getInstance()->getEventDispatcher();
	_mouseJoint = NULL;
	b2PrismaticJointDef primaticJointDef;
	primaticJointDef.Initialize(_world->CreateBody(new b2BodyDef), _paddle,
			_paddle->GetWorldCenter(), b2Vec2(3.0, 0));
	_world->CreateJoint(&primaticJointDef);
	auto listen = EventListenerTouchOneByOne::create();
//listen->onTouchBegan = CC_CALLBACK_2(GameViewLayer::onTouchBegan,this);

	listen->setSwallowTouches(true);

	listen->onTouchBegan = [=](Touch* pTouch,Event* event)
	{

		Point touchPos = pTouch->getLocation();
		b2Vec2 touchPhysicsPos(touchPos.x / PTM_RATIO,touchPos.y / PTM_RATIO);

		b2Fixture* paddleFix = _paddle->GetFixtureList();

		//CCRect paddleRect;
		//paddleRect.containsPoint(touchPos);
			if(paddleFix->TestPoint(touchPhysicsPos)) {
				b2MouseJointDef mouseJointDef;
				mouseJointDef.bodyA = _world->CreateBody(new b2BodyDef);
				mouseJointDef.bodyB = _paddle;
				mouseJointDef.maxForce = 1000.0 * _paddle->GetMass();
				mouseJointDef.target = touchPhysicsPos;//

				_mouseJoint = (b2MouseJoint*)_world->CreateJoint(&mouseJointDef);

				return true;

			}
			return false;
			//b2Vec2 ballPhysicsPos = ball->GetPosition();
			//b2Vec2 impulse = touchPhysicsPos - ballPhysicsPos;
			//impulse *= ball->GetMass();

			//ball->ApplyLinearImpulse(impulse,ball->GetWorldCenter(),true);

		};
	listen->onTouchMoved =
			[=](Touch* pTouch,Event* event)
			{
				if(_mouseJoint)
				{
					Point touchPos = pTouch->getLocation();
					b2Vec2 touchPhysicsPos(touchPos.x / PTM_RATIO,touchPos.y / PTM_RATIO);
					_mouseJoint->SetTarget(touchPhysicsPos);
				}
			};
	listen->onTouchEnded = [=](Touch* pTouch,Event* event)
	{
		if(_mouseJoint) {
			_world->DestroyJoint(_mouseJoint);
			_mouseJoint = NULL;
		}
	};
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
	listener = new MyContactListener;
	_world->SetContactListener(listener);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/dt.mp3",true);
	_score = 0;
	return isRet;
}
int GameViewLayer::_getTagForBody(b2Body* body) {
	if (body->GetUserData()) {
		CCSprite* sp = (CCSprite*) body->GetUserData();
		return sp->getTag();
	}
	return -1;
}
void GameViewLayer::update(float delta) {
	_world->Step(delta, 6, 6);

	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData()) {
			b2Vec2 physicPos = b->GetPosition();
			CCSprite* sp = (CCSprite*) b->GetUserData();
			if (sp == ballSp) {
				b2Vec2 spped = b->GetLinearVelocity();
				if (spped.LengthSquared() > 200) {
					b->SetLinearDamping(0.9);
				} else if (spped.LengthSquared() <= 200) {
					b->SetLinearDamping(0.0);
					if (spped.LengthSquared() < 60) {
						b->ApplyLinearImpulse(b->GetMass() * 5.0 * spped,
								b->GetWorldCenter(), true);
					}
				}

			}
			sp->setPosition(
					ccp(physicPos.x * PTM_RATIO, physicPos.y * PTM_RATIO));
		}
	}
	b2Body* bodyToDestroy = NULL;
	vector<MyContactPeer>::iterator it;
	for (it = listener->_contacts.begin(); it != listener->_contacts.end();
			it++) {
		MyContactPeer curContact = *it;
		b2Body* bodyA = curContact.fixA->GetBody();
		b2Body* bodyB = curContact.fixB->GetBody();
		int tagA, tagB;

		tagA = _getTagForBody(bodyA);
		tagB = _getTagForBody(bodyB);
		//ball background
		if (bodyA == ball && curContact.fixB == _bottom) {
			CCDirector::sharedDirector()->replaceScene(
					GameOverScene::sceneWithWin(false));
		} else if (bodyB == ball && curContact.fixA == _bottom) {
			CCDirector::sharedDirector()->replaceScene(
					GameOverScene::sceneWithWin(false));
		} else if (bodyA == ball && 3 == tagB) {
			bodyToDestroy = bodyB;
		} else if (bodyB == ball && 3 == tagA) {
			bodyToDestroy = bodyA;
		}

	}
	if (bodyToDestroy) {
				((CCSprite*) bodyToDestroy->GetUserData())->removeFromParentAndCleanup(true);
				_world->DestroyBody(bodyToDestroy);

				_score++;
				//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("blip.WAV");
				if (_score >= 4) {
					CCDirector::sharedDirector()->replaceScene(
							GameOverScene::sceneWithWin(true));
				}
			}


}

bool GameViewLayer::setUpdateView() {
	bool isRet = false;
	do {
		/*CCTexture2D* texturestar_up =
		 CCTextureCache::sharedTextureCache()->textureForKey(
		 "gmme/return_up.png");
		 CCTexture2D* texturestar_down =
		 CCTextureCache::sharedTextureCache()->textureForKey(
		 "gmme/return_down.png");

		 CCMenuItemSprite* pStar = CCMenuItemSprite::create(
		 CCSprite::createWithTexture(texturestar_up),
		 CCSprite::createWithTexture(texturestar_down), this,
		 menu_selector(GameViewLayer::menuReturnCallBack));
		 CC_BREAK_IF(!pStar);
		 pStar->setAnchorPoint(ccp(1, 0));
		 pStar->setPosition(converSpritRel(getWinSize().width, 10));
		 CCMenu* pMenu = CCMenu::create(pStar, NULL);
		 CC_BREAK_IF(!pMenu);
		 pMenu->setPosition(CCPointZero);
		 this->addChild(pMenu, 2);*/
		isRet = true;
	} while (0);
	return isRet;
}
void GameViewLayer::menuReturnCallBack(CCObject* pSend) {
	CCScene* scene = WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionSlideInL::create(1, scene));
}
