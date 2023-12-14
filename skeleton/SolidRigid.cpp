#include "SolidRigid.h"
//#include "main.cpp"

SolidRigid::SolidRigid(Vector3 pos, Vector3 lVel, Vector3 aVel, Vector4 color, double radius, double mass, Data::RIGIDS r)
{
	this->pos = pos;
	this->mass = mass;
	this->radius = radius;

	if (r == Data::SUELO) {
		PxRigidStatic* suelo = mainSpace::getPhysics()->createRigidStatic(PxTransform(pos));
		PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
		suelo->attachShape(*shape); //Se enlaza la caja con un solido rigido
		mainSpace::getScene()->addActor(*suelo); //Se añade el solido rigido a la escena
		//Pintar el suelo
		renderItem = new RenderItem(shape, suelo, color);
		this->lVel = { 0,0,0 };
		this->aVel = { 0,0,0 };
	}
	else if (r == Data::STATIC) {
		PxRigidStatic* staticR = mainSpace::getPhysics()->createRigidStatic(PxTransform(pos));
		PxShape* shape = CreateShape(PxBoxGeometry(radius, radius, radius));
		staticR->attachShape(*shape); //Se enlaza la caja con un solido rigido
		mainSpace::getScene()->addActor(*staticR); //Se añade el solido rigido a la escena
		//Pintar el suelo
		renderItem = new RenderItem(shape, staticR, color);
		this->lVel = { 0,0,0 };
		this->aVel = { 0,0,0 };
	}
	else if (r == Data::DYNAMIC) {
		PxRigidDynamic* new_solid;
		new_solid = mainSpace::getPhysics()->createRigidDynamic(PxTransform(pos));
		new_solid->setLinearVelocity(lVel);
		new_solid->setAngularVelocity(aVel);
		PxShape* new_shape = CreateShape(PxBoxGeometry(radius, radius, radius));
		new_solid->attachShape(*new_shape);
		PxRigidBodyExt::updateMassAndInertia(*new_solid,(mass));
		mainSpace::getScene()->addActor(*new_solid);
		//Pintar el nuevo solido rigido dinamico
		renderItem = new RenderItem(new_shape, new_solid, { 0.2, 0.2, 0.2, 1 });
	}
}

SolidRigid::~SolidRigid()
{
	DeregisterRenderItem(renderItem);
}

void SolidRigid::update(double t)
{

}
