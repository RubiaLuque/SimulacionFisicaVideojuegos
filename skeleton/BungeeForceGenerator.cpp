#include "BungeeForceGenerator.h"
template <typename T>
void BungeeForceGenerator<T>::updateForce(T p, double t)
{
	Vector3 relPos = other->getPos() - p->getPos();
	if (relPos.magnitude() > x0) {
		SpringForceGenerator<T>::updateForce(p, t);
	}
}
