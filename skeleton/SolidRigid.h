#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include "Data.h"

using namespace physx;


class SolidRigid
{
private:
	Vector3 pos;
	Vector3 lVel; //Velocidad lineal
	Vector3 aVel; //velocidad angular
	RenderItem* renderItem = nullptr;
	double radius;
	double mass;
	PxRigidStatic* suelo;
	PxRigidStatic* staticR;
	PxRigidDynamic* dynamicR;

	Data::RIGIDS r;
	Data::PROJECTILE_TYPE type;

	PxPhysics* gPhysics;
	PxScene* gScene;
	Camera* cam;

public:
	bool alive = true;

	SolidRigid(Vector3 pos, Vector3 lVel, Vector3 aVel, Vector4 color, double radius, double mass, Data::RIGIDS r, PxPhysics* gPhysics, PxScene* gScene);
	SolidRigid(Vector3 pos, Vector3 lVel, Vector3 aVel, Data::PROJECTILE_TYPE type, PxPhysics* gPhysics, PxScene* gScene);

	virtual ~SolidRigid();

	inline PxActor* getActor() { return dynamicR; }
	inline PxRigidActor* getRigidActor() { return staticR; }
	inline PxTransform getTransform() { return staticR->getGlobalPose(); }
	inline Data::PROJECTILE_TYPE getType() { return type; }
	inline void setVisible(bool v) { staticR->setActorFlag(PxActorFlag::eVISUALIZATION, v); }

	//Getters
	Vector3 getVel() { return lVel; }
	Vector3 getPos() { return pos; }
	double getRadius() noexcept { return radius; }
	double getMass() noexcept { return mass; }

	void update(double t);

	void addForce(Vector3 f);

	double limit_time = 0; //tiempo que lleva en pantalla
};

