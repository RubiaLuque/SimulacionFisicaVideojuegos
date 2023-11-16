#include "Particle.h"


Particle::Particle(Vector3 pos, Vector3 vel, double mass, double radius, double dumping, Data::PROJECTILE_TYPE type) {
	this->dumping = dumping;
	this->pos = pos;
	transform = PxTransform(pos.x, pos.y, pos.z);
	this->vel = vel;
	this->radius = radius;
	this->mass = mass;

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
	

}

Particle::Particle(Vector3 pos, Vector3 vel, double mass, double dumping, Data::GENERATORS type) {
	this->dumping = dumping;
	this->pos = pos;
	this->mass = mass;
	transform = PxTransform(pos.x, pos.y, pos.z);

	physx::PxShape* sphereFuente = CreateShape(PxSphereGeometry(0.5));
	physx::PxShape* shapeLluvia = CreateShape(PxCapsuleGeometry(0.1, 0.3));
	physx::PxShape* sphereNieve = CreateShape(PxSphereGeometry(1));
	physx::PxShape* sphereNiebla = CreateShape(PxSphereGeometry(0.3));
	this->vel = vel;

	if (type == Data::FUENTE)
		renderItem = new RenderItem(sphereFuente, &transform, Vector4(0.0, 191.0, 255.0, 1.0));
	else if (type == Data::LLUVIA)
		renderItem = new RenderItem(shapeLluvia, &transform, Vector4(0.2, 0.3, 1.0, 1.0));
	else if (type == Data::NIEVE)
		renderItem = new RenderItem(sphereNieve, &transform, Vector4(0.9, 0.9, 0.9, 1.0));
	else if (type == Data::NIEBLA)
		renderItem = new RenderItem(sphereNiebla, &transform, Vector4(0.5, 0.5, 0.5, 1.0));
	else if (type == Data::IDLE)
		renderItem = new RenderItem(sphereNiebla, &transform, Vector4(1, 0, 0, 1.0));

}

Particle::Particle(Vector3 pos, Vector3 vel, double mass, Vector4 color, float radius,
	double dumping, Data::GENERATORS type = Data::FIREWORK)
{
	this->dumping = dumping;
	this->pos = pos;
	transform = PxTransform(pos.x, pos.y, pos.z);
	this->vel = vel;
	this->radius = radius;
	this->mass = mass;

	physx::PxShape* firework = CreateShape(PxSphereGeometry(radius));
	if (Data::FIREWORK)
		renderItem = new RenderItem(firework, &transform, color);
}

Particle::~Particle() {
	//se eliminan de la lista de elementos a renderizar
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t) {

	Vector3 resulting_accel = forceAccum * (double)(1/mass);
	
	vel += resulting_accel * t;
	vel *= powf(dumping, t);
	pos = pos + vel * t; 
	transform.p.x = pos.x; transform.p.y = pos.y; transform.p.z = pos.z;

	clearForces();
}
