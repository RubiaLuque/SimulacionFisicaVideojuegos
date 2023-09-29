#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

using namespace physx;

class Particle
{
private:	
	Vector3 vel;
	Vector3 pos;
	PxTransform transform;
	RenderItem* renderItem;

public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius);
	~Particle();

	void update(double t);

};

