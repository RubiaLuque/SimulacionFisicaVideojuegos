#include "GaussianParticleGenerator.h"
#include "GravityForceGenerator.h"

template <typename T>
GaussianParticleGenerator<T>::GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, 
	Vector3 stdDevPos, Vector3 stdDevVel, Data::GENERATORS g) : ParticleGenerator()
{
	std::random_device rd{};
	std::mt19937 gen{rd()};
	d = std::normal_distribution<float>(0, stdDev_t);
	this->meanPos = meanPos;
	this->meanVel = meanVel;

	this->stdDevPos = stdDevPos;
	this->stdDevVel = stdDevVel;

	this->g = g;

}

template <typename T>
GaussianParticleGenerator<T>::~GaussianParticleGenerator()
{
}

template <typename T>
list<T> GaussianParticleGenerator<T>::generateParticles()
{
	GravityForceGenerator* gr = new GravityForceGenerator();
	list<T> list{};
	for (int i = 0; i < Data::TAM_LIST; ++i) {
		Vector3 auxPos = meanPos;
		auxPos.x += d(gen) * stdDevPos.x;
		auxPos.y += d(gen) * stdDevPos.y;
		auxPos.z += d(gen) * stdDevPos.z;

		Vector3 auxVel = meanVel;
		auxVel.x += d(gen) * stdDevVel.x;
		auxVel.y += d(gen) * stdDevVel.y;
		auxVel.z += d(gen) * stdDevVel.z;

		if (Particle * p == dynamic_cast<T*>()) {
			if (g == Data::NIEBLA) {
				//auto p = new Particle(auxPos, auxVel, { 0, -2.6, 0 }, 0.988, g); -> P2
				p = new Particle(auxPos, auxVel, 0.26, 0.998, g);
				list.push_back(p);
			}
			else {
				//auto p = new Particle(auxPos, auxVel, { 0, -9.8, 0 }, 0.988, g); -> P2
				p = new Particle(auxPos, auxVel, 1.0, 0.998, g);
				list.push_back(p);
			}

		}
		else if(SolidRigid* s == dynamic_cast<T*>()){
			if (g == Data::NIEBLA) {
				s = new SolidRigid(auxPos, auxVel, { 0,0,0 }, {1,1,1,1}, 10, 0.15, Data::DYNAMIC);
				list.push_back(s);
			}
			else {
				s = new SolidRigid(auxPos, auxVel, { 0,0,0 }, { 1,1,1,1 }, 10, 0.15, Data::DYNAMIC);
				list.push_back(s);
			}
		}

	}


	return list;
}
