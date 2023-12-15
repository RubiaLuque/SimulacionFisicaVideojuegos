#pragma once
#include "ForceGenerator.h"
#include <map>
template <typename T>
class ForceRegistry : public std::multimap<ForceGenerator<T>*, T*>
{
private:

public:
	ForceRegistry(){ }
	virtual ~ForceRegistry() {
		this->clear();
	}

	void updateForces(double t) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->second != nullptr)
				it->first->updateForce(it->second, t);
		}
	}

	void addRegistry(ForceGenerator<T>* f, T* p) {
		this->insert({ f, p });
	}

	void deleteParticleRegistry(T* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else ++it;
		}
	}

};

