#include "AnchoredSpringForceGen.h"
template <typename T>
AnchoredSpringForceGen<T>::AnchoredSpringForceGen(int K, double x0, const Vector3& anchor_pos): 
	SpringForceGenerator(K, x0, nullptr)
{
	other = new Particle(anchor_pos, { 0,0,0 }, { 0,0,0 }, 1e16, 5.0, 0.0);

}
template <typename T>
AnchoredSpringForceGen<T>::~AnchoredSpringForceGen()
{
	delete other;
}
template <typename T>
void AnchoredSpringForceGen<T>::updateForce(T p, double t)
{
	SpringForceGenerator<T>::updateForce(p, t);
}
