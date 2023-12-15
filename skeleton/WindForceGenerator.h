#pragma once
#include "ForceGenerator.h"
template <typename T>
class WindForceGenerator : public ForceGenerator<T>
{
protected:
	Vector3 windVel;
	float k1 = 0.1, k2 = 0.005;

public:
	WindForceGenerator(Vector3 windVel) : ForceGenerator<T>() {
		this->windVel = windVel; 
	}

	virtual ~WindForceGenerator(){}

	void updateForce(T* p, double t) {
		if (p != nullptr && p->getPos().magnitude() <= Data::windSphereRadius) {

			p->addForce(k1 * (windVel - p->getVel()) +
				k2 * (windVel - p->getVel()).magnitude() * (windVel - p->getVel()));
		}
	}

	void removeForce(T* p){ }
};

