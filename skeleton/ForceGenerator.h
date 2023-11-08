#pragma once
class ForceGenerator
{
private:
	ForceGenerator() noexcept {};
public:
	virtual ~ForceGenerator() {};
	virtual void applyForce(Particle* p) = 0;

};

