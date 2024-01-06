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
	else if (r == Data::_STATIC) {
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
		renderItem = new RenderItem(new_shape, dynamicR, color);
	}
}

SolidRigid::SolidRigid(Vector3 pos, Vector3 lVel, Vector3 aVel, Data::PROJECTILE_TYPE type, PxPhysics* gPhysics, PxScene* gScene)
{
	this->gScene = gScene;
	this->gPhysics = gPhysics;
	this->pos = pos;
	this->aVel = aVel;
	this->type = type;

	dynamicR = gPhysics->createRigidDynamic(PxTransform(pos));

	if (type == Data::FIREBALL) {
		this->lVel = lVel*50;
		this->aVel = aVel;

		dynamicR->setLinearVelocity(this->lVel);
		dynamicR->setAngularVelocity(this->aVel);
		radius = 4.0;
		PxShape* shape = CreateShape(PxSphereGeometry(radius));
		dynamicR->attachShape(*shape);
		mass = 0.3;
		PxRigidBodyExt::updateMassAndInertia(*dynamicR, (mass));
		gScene->addActor(*dynamicR);
		//Pintar el nuevo solido rigido dinamico
		renderItem = new RenderItem(shape, dynamicR, {1, 0.35, 0, 1});
	}
	else if (type == Data::LASER) {
		this->lVel = lVel * 200;
		this->aVel = aVel;

		dynamicR->setLinearVelocity(this->lVel);
		dynamicR->setAngularVelocity(this->aVel);
		radius = 1.0;
		PxShape* shape = CreateShape(PxSphereGeometry(radius));
		dynamicR->attachShape(*shape);
		mass = 0.1;
		PxRigidBodyExt::updateMassAndInertia(*dynamicR, (mass));
		gScene->addActor(*dynamicR);
		//Pintar el nuevo solido rigido dinamico
		renderItem = new RenderItem(shape, dynamicR, { 0, 0.49, 1, 1 });
	}
	else if (type == Data::BULLET) {
		this->lVel = lVel * 100;
		this->aVel = aVel;

		dynamicR->setLinearVelocity(this->lVel);
		dynamicR->setAngularVelocity(this->aVel);
		radius = 2.0;
		PxShape* shape = CreateShape(PxSphereGeometry(radius));
		dynamicR->attachShape(*shape);
		mass = 1.0;
		PxRigidBodyExt::updateMassAndInertia(*dynamicR, (mass));
		gScene->addActor(*dynamicR);
		//Pintar el nuevo solido rigido dinamico
		renderItem = new RenderItem(shape, dynamicR, { 0.1, 0.1, 0.1, 1 });
	}
	else if (type == Data::ARROW) {
		this->lVel = lVel * 80;
		this->aVel = aVel;

		dynamicR->setLinearVelocity(this->lVel);
		dynamicR->setAngularVelocity(this->aVel);
		radius = 0.5;
		double height = 4.0;
		PxShape* shape = CreateShape(PxCapsuleGeometry(radius, height));
		dynamicR->attachShape(*shape);
		mass = 1.0;
		PxRigidBodyExt::updateMassAndInertia(*dynamicR, (mass));
		gScene->addActor(*dynamicR);
		//Pintar el nuevo solido rigido dinamico
		renderItem = new RenderItem(shape, dynamicR, { 1, 0.0, 0.0, 1 });
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
