#pragma once
#include "SolidRigid.h"
#include "Data.h"
using namespace std;

class Target
{
private:
	Vector3 pos;
	Vector3 lVel; //Velocidad lineal
	Vector3 aVel; //velocidad angular
	RenderItem* renderItem = nullptr;
	double radius;
	double mass;

	PxRigidDynamic* target;
	PxPhysics* gPhysics; 
	PxScene* gScene;

public:
	Target(Vector3 pos, Vector3 lVel, Vector3 aVel, double radius, Data::TARGET_MODE mode, PxPhysics* gPhysics, PxScene* gScene);
	virtual ~Target();

	void update(double t);
};

