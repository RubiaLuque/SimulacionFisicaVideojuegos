#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include "Data.h"

using namespace physx;

class Particle
{
private:	
	Vector3 vel;
	Vector3 acc = { 0, -9.8, 0 };
	Vector3 pos;
	PxTransform transform;
	RenderItem* renderItem = nullptr;
	double dumping; //limita la velocidad para que no se dispare por errores numericos
	double radius;
	double mass = 1.0;

public:
	bool alive = true;
	double limit_time = 0; //tiempo que lleva en pantalla
	Particle(Vector3 pos, Vector3 vel, double mass, double radius, double dumping, Data::PROJECTILE_TYPE type);
	Particle(Vector3 pos, Vector3 vel, double mass, double dumping, Data::GENERATORS type);
	Particle(Vector3 pos, Vector3 vel, double mass, Vector4 color, float radius, double dumping, Data::GENERATORS type);
	virtual ~Particle();

	Vector3 getVel() { return vel; }
	Vector3 getPos() { return pos; }
	double getRadius() noexcept { return radius; }
	double getMass() noexcept { return mass; }

	void setAcc(Vector3 acc) { this->acc = acc; }

	void update(double t);

};

