#pragma once
#include "WindForceGenerator.h"
template <typename T>
class VortexForceGenerator : public WindForceGenerator<T>
{
private:
	int K;
	Vector3 vortexPos = { 0,0, 0 };
	Particle* vortexSphere;
public:
	VortexForceGenerator(Vector3 windVel, Vector3 vortexPos) : WindForceGenerator<T>(windVel)
	{
		this->vortexPos = vortexPos;
		K = 1;
		vortexSphere = new Particle(vortexPos, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.5, 1.0, 0.1 }, 1, Data::vortexSphereRadius, 0.1);
	}

	virtual ~VortexForceGenerator() {};
	void updateForce(T* p, double t) {
		if (p != nullptr && ((p)->getPos()).magnitude() <= Data::vortexSphereRadius) {

			this->windVel = K * Vector3(-(p->getPos().z - this->vortexPos.z),
				100 - (p->getPos().y - this->vortexPos.y), p->getPos().x - this->vortexPos.x);

			p->addForce(k1 * (windVel - p->getVel()) +
				k2 * (windVel - p->getVel()).magnitude() * (windVel - p->getVel()));

		}
	}

	void removeForce(T* p){ }
};

