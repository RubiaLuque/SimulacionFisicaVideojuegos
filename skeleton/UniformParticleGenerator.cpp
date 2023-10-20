#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator()
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<> dis(1.0, 2.0);
	
}

UniformParticleGenerator::~UniformParticleGenerator()
{
}

list<Particle*> UniformParticleGenerator::generateParticle()
{


	return list<Particle*>();
}
