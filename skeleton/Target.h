#pragma once
#include "Particle.h"
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

public:
	Target(Vector3 pos, Vector3 lVel, Vector3 aVel, Data::TARGET_MODE);
	virtual ~Target();

	void update(double t);
};

