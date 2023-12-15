#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include "Data.h"

using namespace physx;


class SolidRigid
{
private:
	Vector3 pos;
	Vector3 lVel; //Velocidad lineal
	Vector3 aVel; //velocidad angular
	RenderItem* renderItem = nullptr;
	double radius;
	double mass;
public:
	SolidRigid(Vector3 pos, Vector3 lVel, Vector3 aVel, Vector4 color, double radius, double mass, Data::RIGIDS);

	virtual ~SolidRigid();

	//Getters
	Vector3 getVel() { return lVel; }
	Vector3 getPos() { return pos; }
	double getRadius() noexcept { return radius; }
	double getMass() noexcept { return mass; }

	void update(double t);

	bool alive = true;
	double limit_time = 0; //tiempo que lleva en pantalla
};

