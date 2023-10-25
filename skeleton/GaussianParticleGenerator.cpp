#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, 
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

GaussianParticleGenerator::~GaussianParticleGenerator()
{
	delete model;
}

list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> list{};
	for (int i = 0; i < Data::TAM_LIST; ++i) {
		Vector3 auxPos = meanPos;
		auxPos.x += d(gen) * stdDevPos.x;
		auxPos.y += d(gen) * stdDevPos.y;
		auxPos.z += d(gen) * stdDevPos.z;

		Vector3 auxVel = meanVel;
		auxVel.x += d(gen) * stdDevVel.x;
		auxVel.y += d(gen) * stdDevVel.y;
		auxVel.z += d(gen) * stdDevVel.z;


		if (g == Data::NIEBLA)
			model = new Particle(auxPos, auxVel, { 0, -2.6, 0 }, 0.988, g);
		else
			model = new Particle(auxPos, auxVel, { 0, -9.8, 0 }, 0.988, g);

		list.push_back(model);
	}


	return list;
}