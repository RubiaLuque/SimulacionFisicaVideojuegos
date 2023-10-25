#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include "Data.h"

using namespace physx;

class Particle
{
private:	
	Vector3 vel;
	Vector3 acc;
	Vector3 pos;
	PxTransform transform;
	RenderItem* renderItem = nullptr;
	double dumping; //limita la velocidad para que no se dispare por errores numericos

public:
	bool alive = true;
	double limit_time = 0; //tiempo que lleva en pantalla
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius, double dumping, Data::PROJECTILE_TYPE type);
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double dumping, Data::GENERATORS type);
	virtual ~Particle();

	void update(double t);

};

