#include "SolidRigid.h"

SolidRigid::SolidRigid(Vector3 pos, Vector3 lVel, Vector3 aVel, Vector4 color, double radius, double mass, Data::RIGIDS r, PxPhysics* gPhysics, PxScene* gScene)
{
	this->gScene = gScene;
	this->gPhysics = gPhysics;
	this->pos = pos;
	this->mass = mass;
	this->radius = radius;
	this->r = r;

	if (r == Data::SUELO) {
		suelo = gPhysics->createRigidStatic(PxTransform(pos));
		PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
		suelo->attachShape(*shape); //Se enlaza la caja con un solido rigido
		gScene->addActor(*suelo); //Se añade el solido rigido a la escena
		//Pintar el suelo
		renderItem = new RenderItem(shape, suelo, color);
		this->lVel = { 0,0,0 };
		this->aVel = { 0,0,0 };
	}
	else if (r == Data::STATIC) {
		staticR = gPhysics->createRigidStatic(PxTransform(pos));
		PxShape* shape = CreateShape(PxBoxGeometry(radius, radius, radius));
		staticR->attachShape(*shape); //Se enlaza la caja con un solido rigido
		gScene->addActor(*staticR); //Se añade el solido rigido a la escena
		//Pintar el suelo
		renderItem = new RenderItem(shape, staticR, color);
		this->lVel = { 0,0,0 };
		this->aVel = { 0,0,0 };
	}
	else if (r == Data::DYNAMIC) {
		dynamicR = gPhysics->createRigidDynamic(PxTransform(pos));
		dynamicR->setLinearVelocity(lVel);
		dynamicR->setAngularVelocity(aVel);
		PxShape* new_shape = CreateShape(PxBoxGeometry(radius, radius, radius));
		dynamicR->attachShape(*new_shape);
		PxRigidBodyExt::updateMassAndInertia(*dynamicR,(mass));
		gScene->addActor(*dynamicR);
		//Pintar el nuevo solido rigido dinamico
		renderItem = new RenderItem(new_shape, dynamicR, { 0.2, 0.2, 0.2, 1 });
	}
}

SolidRigid::~SolidRigid()
{
	if (r == Data::SUELO) suelo->release();
	else if (r == Data::STATIC) staticR->release();
	else if (r == Data::DYNAMIC) dynamicR->release();

	
}

void SolidRigid::update(double t)
{

}

void SolidRigid::addForce(Vector3 f)
{
	if (r == Data::DYNAMIC) dynamicR->addForce(f);
}
