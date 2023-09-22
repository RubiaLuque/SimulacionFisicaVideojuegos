#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius) {
	transform = PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(, &transform, Vector4(1.0,1.0,1.0,1.0))
	RegisterRenderItem(renderItem);
	this->vel = vel;
}

Particle::~Particle() {
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t) {
	pos = pos + vel * t;
}
