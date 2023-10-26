#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include <iostream>

Firework::Firework()
{
    unif = new UniformParticleGenerator({ 0,0,0 }, { 5,40,5 }, { 50, 0, 50 }, { 1,1,1 }, Data::FIREWORK);
    normal = new GaussianParticleGenerator({ 0,0,0 }, { 5,40,5 }, { 50, 0, 50 }, { 1,1,1 }, Data::FIREWORK);
    particles = vector<Particle*>{};
}

Firework::~Firework()
{
    delete unif;
    delete normal;
    for (auto it = particles.begin(); it != particles.end(); ++it) {
        if (*it != nullptr) {
            delete* it;
            *it = nullptr;
        }
    }

    particles.clear();
}

int Firework::update(double t)
{
    elapsedTime += t;
    while (elapsedTime <= Data::FIREWORK_DEATH) {
        if (elapsedTime <= Data::FIREWORK_INIT_DEATH) {
            return 0;
        }
        else {
            auto aux = explode(initP);
            particles.clear();
            for (auto it = aux.begin(); it != aux.end(); ++it) {
                particles.push_back(*it);
            }
        }

        for (int i = 0; i < particles.size(); ++i) {
            particles.at(i)->limit_time += t;
            if (particles.at(i)->limit_time > Data::FIREWORK_P_DEATH) {
                //se marca como no vivo
                setAlive(particles.at(i), false);
                auto aux = explode(particles.at(i));
                for (auto it = aux.begin(); it != aux.end(); ++it) {
                    particles.push_back(*it);
                }
                particles.erase(remove_if(particles.begin(), particles.end(),
                    [](Particle* p) noexcept {
                        if (p->alive) return false;
                        else { //si no esta vivo, se elimina
                            delete p;
                            return true;
                        }
                    }), particles.end()
                        );
            }
        }

        //se hace update de todas las demas
        for (int i = 0; i < particles.size(); ++i) {
            particles.at(i)->update(t);
        }

        return 0;
    }

}

void Firework::shootParticle()
{
    Vector3 auxPos, auxVel, color;
    auxPos.x = dis(gen) * iniPos.x;
    auxPos.y = dis(gen) * iniPos.y;
    auxPos.z = dis(gen) * iniPos.z;

    auxVel.x = dis(gen) * iniVel.x;
    auxVel.y = dis(gen) * iniVel.y;
    auxVel.z = dis(gen) * iniVel.z;
    
    color.x = dis(gen);
    color.y = dis(gen);
    color.z = dis(gen);

    initP = new Particle(auxPos, auxVel, {0, -9.8, 0}, { color, 1.0 }, 1, 0.998, Data::FIREWORK);
    particles.push_back(initP);
}

list<Particle*> Firework::explode(Particle* p)
{
    list<Particle*> aux;
    Vector3 pos = p->getPos();
    Vector3 vel = p->getVel();

    int n = numParticulas(gen);
    for (int i = 0; i <= n; ++i) {
        Vector3 auxPos, auxVel, color;
        auxPos.x = dis(gen) * pos.x;
        auxPos.y = dis(gen) * pos.y;
        auxPos.z = dis(gen) * pos.z;

        auxVel.x = dis(gen) * vel.x;
        auxVel.y = dis(gen) * vel.y;
        auxVel.z = dis(gen) * vel.z;

        color.x = dis(gen);
        color.y = dis(gen);
        color.z = dis(gen);
        
        auto p = new Particle(pos, vel, { 0, -9.8, 0 }, { color, 1.0 }, 1, 0.998, 
            Data::FIREWORK);
        aux.push_back(p);
    }

    return aux;
}
