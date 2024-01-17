#pragma once
#include "ForceGenerator.h"
template <typename T>
class WindForceGenerator : public ForceGenerator<T>
{
protected:
	Vector3 windVel;
	float k1 = 10, k2 = 0.5;
	Particle* windSphere;
public:
	WindForceGenerator(Vector3 windVel, Vector3 pos) : ForceGenerator<T>() {
		this->windVel = windVel; 
		this->forcePos = pos;
		windSphere = new Particle(forcePos, { 0,0,0 }, { 0,0,0 }, { 0.5, 0.5, 0.5, 0.1 }, 1, Data::windSphereRadius, 0.1);
	}

	virtual void setForcePos(Vector3 pos) override { forcePos = pos; windSphere->setPos(forcePos); }

	virtual ~WindForceGenerator(){}

	void updateForce(T* p, double t) {
		if (p != nullptr && (p->getPos() - forcePos).magnitude() <= Data::windSphereRadius) {

			Vector3 vel = windVel - p->getVel();

			p->addForce(k1 * (vel) + k2 * (vel).magnitude() * (vel));
		}
	}

	void removeForce(T* p){ }
};

