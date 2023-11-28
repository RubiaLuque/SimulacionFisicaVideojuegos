#include "AnchoredSpringForceGen.h"

AnchoredSpringForceGen::AnchoredSpringForceGen(int K, double x0, const Vector3& anchor_pos): 
	SpringForceGenerator(K, x0, nullptr)
{
	other = new Particle(anchor_pos, { 0,0,0 }, { 0,0,0 }, 1e16, 5.0, 0.0);

}

AnchoredSpringForceGen::~AnchoredSpringForceGen()
{
	delete other;
}

void AnchoredSpringForceGen::updateForce(Particle* p, double t)
{
	SpringForceGenerator::updateForce(p, t);
}
