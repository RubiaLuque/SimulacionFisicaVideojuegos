#pragma once
#include "WindForceGenerator.h"
template <typename T>
class VortexForceGenerator : public WindForceGenerator<T>
{
private:
	int K;
	Vector3 forcePos = { 0,0, 0 };
	Particle* vortexSphere;
public:
	VortexForceGenerator(Vector3 windVel, Vector3 forcePos) : WindForceGenerator<T>(windVel, forcePos)
	{
		this->forcePos = forcePos;
		K = 1;
		vortexSphere = new Particle(forcePos, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.5, 1.0, 0.1 }, 1, Data::vortexSphereRadius, 0.1);
	}

	virtual void setForcePos(Vector3 pos) override { forcePos = pos; vortexSphere->setPos(pos); }

	virtual ~VortexForceGenerator() { delete vortexSphere; };

	void updateForce(T* p, double t) {
		if (p != nullptr && (forcePos - p->getPos()).magnitude() <= Data::vortexSphereRadius) {

			this->windVel = K * Vector3(-(p->getPos().z - this->forcePos.z),
				100 - (p->getPos().y - this->forcePos.y), p->getPos().x - this->forcePos.x);

			p->addForce(k1 * (windVel - p->getVel()) +
				k2 * (windVel - p->getVel()).magnitude() * (windVel - p->getVel()));

		}
	}

	void removeForce(T* p){ }
};

