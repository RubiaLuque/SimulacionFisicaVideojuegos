#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius, double dumping, PROJECTILE_TYPE type) {
	this->dumping = dumping;
	this->pos = pos;
	this->acc = acc;
	transform = PxTransform(pos.x, pos.y, pos.z);

	physx::PxShape* sphere = CreateShape(PxSphereGeometry(radius)); 
	if (type == FIREBALL)
		renderItem = new RenderItem(sphere, &transform, Vector4(255.0, 140.0, 0.0, 1.0));
	else if (type == LIGHTGUN)
		renderItem = new RenderItem(sphere, &transform, Vector4(0.0, 0.0, 255.0, 1.0));
	else if (type == GUN)
		renderItem = new RenderItem(sphere, &transform, Vector4(128, 128, 128, 1.0));
	else if (type == CANNON)
		renderItem = new RenderItem(sphere, &transform, Vector4(70, 130, 180, 1.0));
	else
		renderItem = new RenderItem(sphere, &transform, Vector4(139, 0, 225, 1.0));

	//se registra en la lista de elementos a renderizar
	RegisterRenderItem(renderItem);
	this->vel = vel;
}

Particle::~Particle() {
	//se eliminan de la lista de elementos a renderizar
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t) {
	vel += acc * t;
	vel *= powf(dumping, t);
	pos = pos + vel * t; 
	transform.p.x = pos.x; transform.p.y = pos.y; transform.p.z = pos.z;
}

Particle* Particle::clone() const
{

	return nullptr;
}
