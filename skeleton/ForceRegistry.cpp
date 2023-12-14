#include "ForceRegistry.h"
template <typename T>
ForceRegistry<T>::~ForceRegistry()
{
	this->clear();
}
template <typename T>
void ForceRegistry<T>::updateForces(double t)
{
	for (auto it = begin(); it != end(); ++it) {
		if(it->second!= nullptr)
			it->first->updateForce(it->second, t);
	}
}
template <typename T>
void ForceRegistry<T>::addRegistry(ForceGenerator<T>* f, T p)
{
	this->insert({ f, p });
	//auto itForce = find(f);
	////La fuerza no estaba registrada
	//if (itForce == end()) {
	//}
	//else {
	//	itForce->second = p;
	//}
}
template <typename T>
void ForceRegistry<T>::deleteParticleRegistry(T p)
{
	for (auto it = begin(); it != end();) {
		if (it->second == p) it = erase(it);
		else ++it;
	}
}
