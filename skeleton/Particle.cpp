#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double radius, double dumping, Data::PROJECTILE_TYPE type) {
	this->dumping = dumping;
	this->pos = pos;
	this->acc = acc;
	transform = PxTransform(pos.x, pos.y, pos.z);

	physx::PxShape* sphere = CreateShape(PxSphereGeometry(radius)); 
	physx::PxShape* sphere1 = CreateShape(PxSphereGeometry(0.3));

	if (type == Data::FIREBALL)
		renderItem = new RenderItem(sphere, &transform, Vector4(255.0, 140.0, 0.0, 1.0));
	else if (type == Data::LIGHTGUN)
		renderItem = new RenderItem(sphere, &transform, Vector4(0.0, 0.0, 255.0, 1.0));
	else if (type == Data::GUN)
		renderItem = new RenderItem(sphere, &transform, Vector4(128, 128, 128, 1.0));
	else if (type == Data::CANNON)
		renderItem = new RenderItem(sphere, &transform, Vector4(70, 130, 180, 1.0));
	else
		renderItem = new RenderItem(sphere1, &transform, Vector4(139, 0, 225, 0.8));
	
	this->vel = vel;

	//se registra en la lista de elementos a renderizar
	RegisterRenderItem(renderItem);
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, double dumping, Data::GENERATORS type) {
	this->dumping = dumping;
	this->pos = pos;
	this->acc = acc;
	transform = PxTransform(pos.x, pos.y, pos.z);

	physx::PxShape* sphereFuente = CreateShape(PxSphereGeometry(2));
	physx::PxShape* shapeLluvia = CreateShape(PxCapsuleGeometry(0.3, 1));
	physx::PxShape* sphereNieve = CreateShape(PxSphereGeometry(1));
	physx::PxShape* sphereNiebla = CreateShape(PxSphereGeometry(0.5));

	if (type == Data::FUENTE)
		renderItem = new RenderItem(sphereFuente, &transform, Vector4(0.0, 191.0, 255.0, 0.9));
	else if (type == Data::LLUVIA)
		renderItem = new RenderItem(shapeLluvia, &transform, Vector4(65.0, 105.0, 225.0, 0.9));
	else if (type == Data::NIEVE)
		renderItem = new RenderItem(sphereNieve, &transform, Vector4(211, 211, 211, 0.9));
	else //NIEBLA
		renderItem = new RenderItem(sphereNiebla, &transform, Vector4(128, 128, 128, 0.9));
	

	this->vel = vel;
	//se registra en la lista de elementos a renderizar
	RegisterRenderItem(renderItem);
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
