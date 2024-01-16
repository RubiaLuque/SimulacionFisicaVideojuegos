#pragma once
#include "ForceGenerator.h"
template <typename T>
class SpringForceGenerator : public ForceGenerator<T>
{
protected:
	int K;
	int x0; //Longitud del muelle en reposo
	T* other;
	int increment = 10;
	int decrement = -10;

public:
	SpringForceGenerator(int K, int x0, T* other) {
		this->K = K;
		this->other = other;
		this->x0 = x0;
	}

	virtual ~SpringForceGenerator() {

	}

	void updateForce(T* p, double t) {
		if (p != nullptr) {
			Vector3 aux = other->getPos() - p->getPos();
			Vector3 force;
			int aux_length = aux.magnitude();

			const float length = aux.normalize();
			const float delta_x = length - x0;

			force = aux * delta_x * K;

			p->addForce(force);
		}
	}

	void removeForce(T* p) {}
	inline void increaseK() noexcept { K += increment; }
	inline void decreaseK() noexcept { if(K>abs(decrement)) K += decrement; }
};

