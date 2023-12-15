#pragma once
#include "ForceGenerator.h"
#include <map>
template <typename T>
class ForceRegistry : public std::multimap<ForceGenerator<T>*, T>
{
private:

public:
	ForceRegistry();
	virtual ~ForceRegistry();

	void updateForces(double t);
	void addRegistry(ForceGenerator<T>* f, T p);
	void deleteParticleRegistry(T p);

};

