#pragma once
#include "SpringForceGenerator.h"
template <typename T>
class BungeeForceGenerator : public SpringForceGenerator<T>
{
private:
public:
	BungeeForceGenerator(int K, int x0, T* other) : SpringForceGenerator<T>(K, x0, other) {};
	virtual ~BungeeForceGenerator(){}

	void updateForce(T* p, double t) {
		Vector3 relPos = other->getPos() - p->getPos();
		if (relPos.magnitude() > x0) {
			SpringForceGenerator<T>::updateForce(p, t);
		}
	}
};

