#ifndef __MYCONTACT_LISTENER_H__
#define __MYCONTACT_LISTENER_H__
#pragma once
#include "../cocos2d/external/Box2D/Box2D.h"
#include <vector>
using namespace std;
struct MyContactPeer{
	b2Fixture* fixA;
	b2Fixture* fixB;
};
class MyContactListener : public b2ContactListener{
public:
	vector<MyContactPeer> _contacts;
	
	MyContactListener();
	~MyContactListener();

	void BeginContact(b2Contact* contact);
	
	void EndContact(b2Contact* contact);
	
	void PreSolve(b2Contact* contact,const b2Manifold* oldManifold);
	
	void PostSolve(b2Contact* contact,const b2ContactImpulse* impulse);
};
#endif
