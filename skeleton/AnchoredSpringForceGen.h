#pragma once
#include "SpringForceGenerator.h"
template <typename T>
class AnchoredSpringForceGen : public SpringForceGenerator<T>
{
private:

public:
	AnchoredSpringForceGen(int K, double x0, const Vector3& anchor_pos);
	virtual ~AnchoredSpringForceGen();

	void updateForce(T p, double t);

};

