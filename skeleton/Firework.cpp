#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include <iostream>

Firework::Firework()
{
    particles = vector<Particle*>();
    elapsedTime = 0;
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
    //mientras dure el tiempo de vida del firework
    while (elapsedTime <= Data::FIREWORK_DEATH) {
        elapsedTime += t;
        //tiempo de vida de la particula inicial
        if (elapsedTime <= Data::FIREWORK_INIT_DEATH) {
            initP->update(t);
            return 0;
        }
        //la particula inicial exlota cuando acaba su tiempo de vida
        else{
            auto aux = explode(initP);
            particles.clear();
            for (int i = 0; i < aux.size(); ++i) {
                particles.push_back(aux.at(i));
            }
        }

        //las particulas creadas explotan si han superado su tiempo
        for (int i = 0; i < particles.size(); ++i) {
            particles.at(i)->limit_time += t;
            if (particles.at(i)->limit_time >= Data::FIREWORK_P_DEATH) {
                //se marca como no vivo
                setAlive(particles.at(i), false);
                //Se hace explotar
                auto aux = explode(particles.at(i));
                //se añaden las nuevas particulas al vector de particulas de firework
                for (int j = 0; j < aux.size(); ++j) {
                    particles.push_back(aux.at(j));
                }
            }
        }

        //se borran las particulas mas antiguas
        for (int i = 0; i < particles.size(); ++i) {
            particles.at(i)->limit_time += t;
            if (particles.at(i)->limit_time >= Data::FIREWORK_P_DEATH) {
                //Se elimina la particula que ha explotado
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
    }

    //se hace update de las particulas que queden tras finalizar el tiempo del firework
    for (int i = 0; i < particles.size(); ++i) {
        particles.at(i)->update(t);
    }

    //Se van eliminando el resto
    for (int i = 0; i < particles.size(); ++i) {
        particles.at(i)->limit_time += t;
        if (particles.at(i)->limit_time >= Data::FIREWORK_P_DEATH) {
            //Se elimina la particula que ha explotado
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

    return 0;
}

void Firework::shootParticle()
{
    Vector3 auxPos, auxVel, color;
    auxPos.x = dis(gen) * iniPos.x;
    auxPos.y = dis(gen) * iniPos.y;
    auxPos.z = dis(gen) * iniPos.z;

    auxVel.x = velD(gen) * iniVel.x;
    auxVel.y = velD(gen) * iniVel.y;
    auxVel.z = velD(gen) * iniVel.z;
    
    color.x = dis(gen);
    color.y = dis(gen);
    color.z = dis(gen);

    initP = new Particle(auxPos, auxVel, {0, -9.8, 0}, { color, 1.0 }, 1, 0.998, Data::FIREWORK);
    particles.push_back(initP);
}

vector<Particle*> Firework::explode(Particle* p)
{
    vector<Particle*> aux;
    Vector3 pos = p->getPos();
    Vector3 vel = p->getVel();

    int n = numParticulas(gen);
    for (int i = 0; i <= n; ++i) {
        Vector3 auxVel, color;

        auxVel.x = velD(gen2) * vel.x;
        auxVel.y = velD(gen2) * vel.y;
        auxVel.z = velD(gen2) * vel.z;

        color.x = dis(gen);
        color.y = dis(gen);
        color.z = dis(gen);
        
        auto p = new Particle(pos, auxVel, { 0, -9.8, 0 }, { color, 1.0 }, 1, 0.998, 
            Data::FIREWORK);
        aux.push_back(p);
    }

    return aux;
}
