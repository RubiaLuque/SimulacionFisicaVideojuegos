#include "Target.h"

Target::Target(Vector3 pos, Vector3 lVel, Vector3 aVel, double radius, Data::TARGET_MODE mode)
{
	this->pos = pos;
	this->lVel = lVel;
	this->aVel = aVel;
	this->radius = radius;
}

Target::~Target()
{
	target->release();
}

void Target::update(double t) {

}
