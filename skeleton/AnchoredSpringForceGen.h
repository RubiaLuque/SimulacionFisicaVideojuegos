#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringForceGen : public SpringForceGenerator
{
private:

public:
	AnchoredSpringForceGen(int K, double x0, const Vector3& anchor_pos);
	virtual ~AnchoredSpringForceGen();

	void updateForce(Particle* p, double t);

};

