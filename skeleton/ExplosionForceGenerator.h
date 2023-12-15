#pragma once
#include "ForceGenerator.h"
#include <cmath>
#include <numbers>

template <typename T>
class ExplosionForceGenerator : public ForceGenerator<T>
{
private:
	int K;
	float tau = 10000;
	Vector3 explosionPos;
	Vector3 expanseVel = { 340000,340000,340000 };
	double elapsedTime = 0;
	bool explosion = false;
	int R = Data::EXPLOSION_SPHERE_RADIUS;

public:
	ExplosionForceGenerator(Vector3 explosionPos) {
		this->explosionPos = explosionPos;
		K = 10000000000;
	}

	virtual ~ExplosionForceGenerator() {

	}

	void applyForce(T* p) {};
	void updateForce(T* p, double t) {
		if (p != nullptr && ((p)->getPos()).magnitude() <= R) {
			elapsedTime += t;
			double r = (pow(p->getPos().x - explosionPos.x, 2) + pow(p->getPos().y - explosionPos.y, 2)
				+ pow(p->getPos().z - explosionPos.z, 2));

			p->addForce(K / r * Vector3(p->getPos().x - explosionPos.x, p->getPos().y - explosionPos.y,
				p->getPos().z - explosionPos.z) * exp(-elapsedTime / tau));

			R += expandForce(t);

			//std::cout << K / r * (p->getPos().y - explosionPos.y) * exp(-elapsedTime / tau) << " ";

		}
	}


	double expandForce(double t) {
		return expanseVel.magnitude() * elapsedTime;
	}

	void enableExplosion() {
		elapsedTime = 0;
	}

	void removeForce(T* p) {}
};

