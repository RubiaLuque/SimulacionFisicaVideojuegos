#include "WindForceGenerator.h"
template <typename T>
void WindForceGenerator<T>::updateForce(T p, double t)
{
	if (p != nullptr && p->getPos().magnitude() <= Data::windSphereRadius) {

		p->addForce(k1*(windVel - p->getVel()) + 
			k2*(windVel - p->getVel()).magnitude()* (windVel - p->getVel()));
	}
}
template <typename T>
void WindForceGenerator<T>::removeForce(T p)
{
}
