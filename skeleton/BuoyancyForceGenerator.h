#pragma once
#include "ForceGenerator.h"
template <typename T>
class BuoyancyForceGenerator : public ForceGenerator<T>
{
private:
	float height;
	float volume;
	float density;
	float gravity = 9.8;

	Particle* liquid;

public:
	BuoyancyForceGenerator(float height, float volume, float density) {
		this->height = height;
		this->volume = volume;
		this->density = density;
		liquid = new Particle({ 0,10,0 }, { 0,0,0 }, { 0,0,0 }, { 0.2, 1.0, 1.0, 1.0 }, (double)density / volume, 100, 0.0);
	
	}

	virtual ~BuoyancyForceGenerator() {
		delete liquid;
	}

	void removeForce(T* p) {};

	void updateForce(T* p, double t) {
		if (p == nullptr) return;

		float h = p->getPos().y;
		float h0 = liquid->getPos().y;

		Vector3 f = { 0,0,0 };
		float immersed = 0.0;

		//No esta sumergido
		if (h - h0 > height * 0.5) {
			immersed = 0.0;
		}
		//Esta totalmente sumergido
		else if (h0 - h > height * 0.5) {
			immersed = 1.0;
		}
		//Parcialmente sumergido
		else {
			immersed = (float)(h0 - h) / height + 0.5;
		}

		f.y = density * volume * immersed * gravity;

		p->addForce(f);
	}

};

