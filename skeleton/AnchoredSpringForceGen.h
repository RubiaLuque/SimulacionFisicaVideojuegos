#pragma once
#include "SpringForceGenerator.h"
template <typename T>
class AnchoredSpringForceGen : public SpringForceGenerator<T>
{
private:
	Particle* other;
public:
	AnchoredSpringForceGen(int K, double x0, const Vector3& anchor_pos): SpringForceGenerator<T>(K, x0, nullptr)
	{
		other = new Particle(anchor_pos, { 0,0,0 }, { 0,0,0 }, 1e16, 5.0, 0.0);

	}

	virtual ~AnchoredSpringForceGen() {
		delete other;
	}

	void updateForce(T* p, double t) {
		SpringForceGenerator<T>::updateForce(p, t);
	}

};

