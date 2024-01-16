#include "Target.h"

Target::Target(Vector3 pos, Vector3 lVel, Vector3 aVel, double radius, Data::TARGET_MODE mode, PxPhysics* gPhysics, PxScene* gScene)
{
	this->gScene = gScene;
	this->gPhysics = gPhysics;
	this->pos = pos;
	this->lVel = lVel;
	this->aVel = aVel;
	this->radius = radius;
	this->type = mode;

	target = gPhysics->createRigidDynamic(PxTransform(pos));

	target->setLinearVelocity(this->lVel);
	target->setAngularVelocity(this->aVel);
	PxShape* shape = CreateShape(PxBoxGeometry(0.1, radius, radius));
	target->attachShape(*shape);

	
	gScene->addActor(*target);

	//Elimina el efecto de la gravedad en las dianas
	target->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

	if (mode == Data::ORANGE) {
		mass = 1.0;
		PxRigidBodyExt::updateMassAndInertia(*target, (mass));
		color = { 1.0, 0.1, 0.0, 1.0 };
		renderItem = new RenderItem(shape, target, color);
	}
	else if (mode == Data::BLUE) {
		mass = 20.0;
		PxRigidBodyExt::updateMassAndInertia(*target, (mass));
		color = { 0, 0.49, 1, 1 };
		renderItem = new RenderItem(shape, target, color);
	}
	else if (mode == Data::BLACK) {
		mass = 50.0;
		PxRigidBodyExt::updateMassAndInertia(*target, (mass));
		color = { 0.01, 0.01, 0.01, 1 };
		renderItem = new RenderItem(shape, target, color);

	}
	else if (mode == Data::RED) {
		mass = 0.1;
		PxRigidBodyExt::updateMassAndInertia(*target, (mass));
		color = { 0.8, 0.0, 0.0, 1 };
		renderItem = new RenderItem(shape, target, color);

	}
	else if (mode == Data::WHITE) {
		mass = 2.0;
		PxRigidBodyExt::updateMassAndInertia(*target, (mass));
		color = { 0.9, 0.9, 0.9, 1 };
		renderItem = new RenderItem(shape, target, color);
	}
}

Target::~Target()
{
	DeregisterRenderItem(renderItem);
	target->release();
}

void Target::addForce(Vector3 force)
{
	target->addForce(force);
}

void Target::update(double t) {

	
}

