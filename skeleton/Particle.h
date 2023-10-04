#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

using namespace physx;

static enum PROJECTILE_TYPE {
	FIREBALL, LIGHTGUN, GUN, CANNON
};

class Particle
{
private:	
	Vector3 vel;
	Vector3 acc;
	Vector3 pos;
	PxTransform transform;
	RenderItem* renderItem;
	double dumping; //limita la velocidad para que no se dispare por errores numericos

public:
	bool alive = true;
	double limit_time = 0; //tiempo que lleva en pantalla
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius, double dumping, PROJECTILE_TYPE type);
	~Particle();

	void update(double t);

};

