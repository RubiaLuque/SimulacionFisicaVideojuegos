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
	SpringForceGenerator(int K, int x0, T other);
	virtual ~SpringForceGenerator();
	void updateForce(T p, double t);
	void removeForce(T p) {};
	inline void increaseK() noexcept { K += increment; }
	inline void decreaseK() noexcept { if(K>abs(decrement)) K += decrement; }
};

