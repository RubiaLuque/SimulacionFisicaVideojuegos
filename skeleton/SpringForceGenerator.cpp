#include "SpringForceGenerator.h"
template <typename T>
SpringForceGenerator<T>::SpringForceGenerator(int K, int x0, T other)
{
	this->K = K;
	this->other = other;
	this->x0 = x0;
}
template <typename T>
SpringForceGenerator<T>::~SpringForceGenerator()
{
	//delete other;
}
template <typename T>
void SpringForceGenerator<T>::updateForce(T p, double t)
{
	if (p != nullptr) {
		Vector3 aux = other->getPos() - p->getPos();
		Vector3 force;

		const float length = aux.normalize();
		const float delta_x = length - x0;

		force = aux * delta_x * K;

		p->addForce(force);
	}
}
