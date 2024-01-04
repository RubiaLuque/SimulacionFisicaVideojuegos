#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "Render/Camera.h"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "GameManager.h"

//#include "Particle.h"

#include <iostream>

std::string display_text = "TEST";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
GameManager* manager;

float timeKey = 0;
bool keyPressed = false;



// Initialize physics engine
//Codigo de inicializacion
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425.0, 10.0);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	//metodo que crea la fisica del motor
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	//material con coeficientes de rozamiento estatico, dinamico y elasticidad
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	manager = new GameManager(gPhysics, gScene);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds

//Aqui se hacen las actualizaciones del mundo en el que se trabaja
//Llamadas a actualizacion de escenas
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	
	manager->update(t);
	if (keyPressed) {
		timeKey += t;
		if (timeKey > Data::MAX_TIME_KEY) {
			keyPressed = false;
			timeKey = 0;
		}
	}
}

// Function to clean data
// Add custom code to the begining of the function
//Se limpia la memoria usada
void cleanupPhysics(bool interactive)
{
	delete manager;

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{//la camara tambien se mueve con teclas que estan reservadas para ello

	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case ' ':	break;
	case '1': //MODE PARTICLE
	{
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->chooseMode(key);
			timeKey = 0;
		}
		break;
	}
	case '2': //MODE SOLID RIGID
	{
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->chooseMode(key);
			timeKey = 0;
		}
		break;
	}
	
	default:
		break;
	}
	keyPressed = true;
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}