#include "UniformParticleGenerator.h"
#include "GravityForceGenerator.h"

template <typename T>
UniformParticleGenerator<T>::UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, 
	Vector3 velWidth, Data::GENERATORS g) : ParticleGenerator()
{
	//de donde se parte
	this->meanPos = meanPos;
	this->meanVel = meanVel;

	//tipo de generador
	this->g = g;

	//distribucion
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	dis = std::uniform_real_distribution<float> (1.0, 2.0);

	this->posWidth = posWidth;
	this->velWidth = velWidth;
}

template <typename T>
UniformParticleGenerator<T>::~UniformParticleGenerator()
{
}

template <typename T>
list<T> UniformParticleGenerator<T>::generateParticles()
{
	
	GravityForceGenerator* gr = new GravityForceGenerator();

	list<T> list{};
	
	for (int i = 0; i < Data::TAM_LIST; ++i) {
		Vector3 auxPos = meanPos;
		auxPos.x += dis(gen) * posWidth.x;
		auxPos.y += dis(gen) * posWidth.y;
		auxPos.z += dis(gen) * posWidth.z;

		Vector3 auxVel = meanVel;
		auxVel.x += dis(gen) * velWidth.x;
		auxVel.y += dis(gen) * velWidth.y;
		auxVel.z += dis(gen) * velWidth.z;

		auto p = new Particle(auxPos, auxVel, 1.0, 0.988, g);
		list.push_back(p);

		auto s = new SolidRigid(auxPos, auxVel, { 0,0,0 }, { 0.5, 0.5, 0.5, 1 }, Data::DYNAMIC);
		list.push_back(s);
	}

	return list;
}
