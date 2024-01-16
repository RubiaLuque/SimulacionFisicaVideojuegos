#pragma once
#include "ForceGenerator.h"
template <typename T>
class WindForceGenerator : public ForceGenerator<T>
{
protected:
	Vector3 windVel;
	float k1 = 10, k2 = 0.5;
	Vector3 windPos = { 0,0,0 };
	Particle* windSphere;
public:
	WindForceGenerator(Vector3 windVel) : ForceGenerator<T>() {
		this->windVel = windVel; 
		windSphere = new Particle(windPos, { 0,0,0 }, { 0,0,0 }, { 0.5, 0.5, 0.5, 0.1 }, 1, Data::windSphereRadius, 0.1);
	}

	inline void setPos(Vector3 pos) { windPos = pos; windSphere->setPos(pos); }

	virtual ~WindForceGenerator(){}

	void updateForce(T* p, double t) {
		if (p != nullptr && p->getPos().x <= windPos.x + Data::windSphereRadius && 
			p->getPos().y <= windPos.y + Data::windSphereRadius && p->getPos().z <= windPos.z + Data::windSphereRadius) {

			p->addForce(k1 * (windVel - p->getVel()) +
				k2 * (windVel - p->getVel()).magnitude() * (windVel - p->getVel()));
		}
	}

	void removeForce(T* p){ }
};

