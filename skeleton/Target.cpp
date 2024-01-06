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
	mass = 1.0;

	target = gPhysics->createRigidDynamic(PxTransform(pos));

	target->setLinearVelocity(this->lVel);
	target->setAngularVelocity(this->aVel);
	PxShape* shape = CreateShape(PxSphereGeometry(radius));
	target->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*target, (mass));
	gScene->addActor(*target);

	//Elimina el efecto de la gravedad en las dianas
	target->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

	if (mode == Data::ORANGE) {
		renderItem = new RenderItem(shape, target, { 1.0, 0.2, 0.0, 1.0 });
	}
	else if (mode == Data::BLUE) {
		renderItem = new RenderItem(shape, target, { 0, 0.49, 1, 1 });
	}
	else if (mode == Data::BLACK) {
		renderItem = new RenderItem(shape, target, { 0.2, 0.2, 0.2, 1 });

	}
	else if (mode == Data::RED) {
		renderItem = new RenderItem(shape, target, { 0.8, 0.0, 0.0, 1 });

	}
	else if (mode == Data::WHITE) {
		renderItem = new RenderItem(shape, target, { 0.9, 0.9, 0.9, 1 });
	}
}

Target::~Target()
{
	target->release();
}

void Target::update(double t) {

	
}

