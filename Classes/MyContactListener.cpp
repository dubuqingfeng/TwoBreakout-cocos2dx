#include "MyContactListener.h"
	MyContactListener::MyContactListener():_contacts(){
	}
	MyContactListener::~MyContactListener(){
	}
	void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
	}
	
	void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	}
	void MyContactListener::BeginContact(b2Contact* contact){
	MyContactPeer peer = {contact->GetFixtureA(),contact->GetFixtureB()};
	_contacts.push_back(peer);
}
	
	void MyContactListener::EndContact(b2Contact* contact){
	MyContactPeer peer = {contact->GetFixtureA(),contact->GetFixtureB()};
	vector<MyContactPeer>::iterator pos ,posFound;
	for(pos = _contacts.begin(); pos != _contacts.end(); pos ++)
	{
		MyContactPeer onePeer = *pos;
		if(onePeer.fixA == peer.fixA && onePeer.fixB == peer.fixB){
			posFound = pos;
			_contacts.erase(posFound);
			return;
		}
	}
	
	}
