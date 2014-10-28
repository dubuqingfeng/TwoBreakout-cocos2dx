#pragma  once //避免重复包含  


#include "../../../../external/Box2D/Box2D.h"

class Box2dUtils{
public:
	static b2Body* createDynamicBody(float posX, float posY, void* userData, b2World* _world){
		
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody; // 
		ballBodyDef.position.Set(posX, posY);
		ballBodyDef.userData = userData; // 把屏幕中的精灵作为 物理世界中物体的 userData
		b2Body* ball = _world ->CreateBody(&ballBodyDef);
		return ball;
	}

	static b2Fixture* createFixture(b2Shape* shape, float density, float friction, float restitution, b2Body* ball ){
		
		b2FixtureDef ballFixDef;
		ballFixDef.shape = shape;
		ballFixDef.density = density;
		ballFixDef.friction = friction;
		ballFixDef.restitution = restitution;
		return ball->CreateFixture(&ballFixDef);
	}
};