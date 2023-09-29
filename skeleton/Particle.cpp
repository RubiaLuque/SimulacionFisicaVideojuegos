#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius) {
	this->pos = pos;
	transform = PxTransform(pos.x, pos.y, pos.z);
	physx::PxShape* sphere = CreateShape(PxSphereGeometry(radius));
	renderItem = new RenderItem(sphere, &transform, Vector4(1.0, 1.0, 1.0, 1.0));
	RegisterRenderItem(renderItem);
	this->vel = vel;
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t) {
	pos = pos + vel * t;
	transform.p.x = pos.x; transform.p.y = pos.y; transform.p.z = pos.z;
	//renderItem->transform = &transform;
}
