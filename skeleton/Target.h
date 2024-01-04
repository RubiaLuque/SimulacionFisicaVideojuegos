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

	PxRigidDynamic* target;

public:
	Target(Vector3 pos, Vector3 lVel, Vector3 aVel, double radius, Data::TARGET_MODE mode);
	virtual ~Target();

	void update(double t);
};

