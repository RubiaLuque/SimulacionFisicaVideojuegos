#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include <iostream>

Firework::Firework()
{
    particles = vector<Particle*>();
    elapsedTime = 0;
}

Firework::Firework(Vector3 pos, Vector4 color) {
    particles = vector<Particle*>();
    elapsedTime = 0;

    Vector3 vel = { 50, 100, 50 };

    auto p = new Particle(pos, vel, 1.0, color, 2.0, 0.98, Data::FIREWORK);
    DeregisterRenderItem(p->getRenderItem());
    colors = true;

    auto aux = explodeWithColor(p, color);
    for (int j = 0; j < aux.size(); ++j) {
        particles.push_back(aux.at(j));
    }
}

Firework::~Firework()
{

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
    if (elapsedTime <= Data::FIREWORK_DEATH && !colors) {
        elapsedTime += t;

        //las particulas creadas explotan si han superado su tiempo
        for (int i = 0; i < particles.size(); ++i) {
            particles.at(i)->limit_time += t;
            gr->updateForce(initP, t);
            particles.at(i)->update(t);
            if (particles.at(i)->limit_time >= _life_time) {
                cout << particles.at(i)->limit_time << ' ';
                setAlive(particles.at(i), false);
                auto aux = explode(particles.at(i));
                for (int j = 0; j < aux.size(); ++j) {
                    particles.push_back(aux.at(j));
                }
            }
        }

        //Se eliminan las particulas que han explotado
        particles.erase(remove_if(particles.begin(), particles.end(),
            [](Particle* p) noexcept {
                if (p->alive) return false;
                else { //si no esta vivo, se elimina
                    delete p;
                    return true;
                }
            }), particles.end());
    }


    else if (elapsedTime <= Data::FIREWORK_DEATH && colors) {
        elapsedTime += t;

        for (int i = 0; i < particles.size(); ++i) {
            gr->updateForce(particles.at(i), t);
            particles.at(i)->update(t);
        }
    }


    //mientras dure el tiempo de vida del firework
    else {
        //se hace update de las particulas que queden tras finalizar el tiempo del firework
        for (int i = 0; i < particles.size(); ++i) {
            gr->updateForce(particles.at(i), t);
            particles.at(i)->update(t);
        }

        //Se van eliminando el resto
        for (auto it = particles.begin(); it != particles.end(); it++) {
            (*it)->limit_time += t;
            if ((*it)->limit_time >= Data::FIREWORK_P_DEATH) {
                setAlive(*it, false);
            }
        }

        // Se eliminan las particulas que han explotado
        particles.erase(remove_if(particles.begin(), particles.end(),
            [](Particle* p) noexcept {
                if (p->alive) return false;
                else { //si no esta vivo, se elimina
                    delete p;
                    return true;
                }
            }), particles.end());
    }


    return 0;
}

void Firework::shootParticle()
{
    Vector3 auxPos, auxVel, color;
    auxPos.x = dis(gen) * iniPos.x;
    auxPos.y = dis(gen) * iniPos.y;
    auxPos.z = dis(gen) * iniPos.z;

    auxVel.x = iniVel.x;
    auxVel.y = iniVel.y;
    auxVel.z = iniVel.z;
    
    color.x = dis(gen);
    color.y = dis(gen);
    color.z = dis(gen);

    initP = new Particle(auxPos, auxVel, 1.0, { color, 1.0 }, 1, 0.998, Data::FIREWORK);
    
    particles.push_back(initP);
}

vector<Particle*> Firework::explode(Particle* p)
{
    vector<Particle*> aux;
    Vector3 pos = p->getPos();
    double radius = p->getRadius();

    int n = numParticulas(gen);

    for (int i = 0; i < n; ++i) {
        Vector3 auxVel, color;

        auxVel.x = (velD(gen2)) * 5;
        auxVel.y = (velD(gen2)*5) + 10;
        auxVel.z = (velD(gen2)) * 5;

        color.x = dis(gen);
        color.y = dis(gen);
        color.z = dis(gen);
        
        auto p = new Particle(pos, auxVel, 1.0, { color, 1.0 }, radius/2.0, 0.998, 
            Data::FIREWORK);
        
        aux.push_back(p);
    }
    return aux;
}

vector<Particle*> Firework::explodeWithColor(Particle* p, Vector4 color)
{
    vector<Particle*> aux;
    Vector3 pos = p->getPos();
    double radius = p->getRadius();

    int n = numParticulas(gen);

    for (int i = 0; i < n; ++i) {
        Vector3 auxVel;

        auxVel.x = (velD(gen2)) * 5;
        auxVel.y = (velD(gen2) * 5) + 10;
        auxVel.z = (velD(gen2)) * 5;

        auto p = new Particle(pos, auxVel, 1.0, { color }, radius, 0.998,
            Data::FIREWORK);

        aux.push_back(p);
    }
    return aux;
}
