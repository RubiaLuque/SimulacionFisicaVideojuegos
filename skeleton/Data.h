#pragma once

namespace Data {
	static const float MAX_TIME_KEY = 1.0;

	static const float LIMIT_ON_SCREEN= 10.0;
	static const int TAM_LIST = 5;
	static const float FIREWORK_DEATH = 5.0; //tiempo de muerte de todo el firework
	static const float FIREWORK_INIT_DEATH = 1.5; //tiempo que tarda en morir la particula inicial
	static const float FIREWORK_P_DEATH = 3.0; //tiempo de muerte de cada particula del firework

	static const double EXPLOSION_SPHERE_RADIUS = 40;
	static const double windSphereRadius = 50;
	static const double vortexSphereRadius = 100;

	static enum GENERATORS {
		FUENTE, LLUVIA, NIEVE, NIEBLA, FIREWORK, NONE
	};

	static enum PROJECTILE_TYPE {
		FIREBALL, LASER, BULLET, ARROW, IDLE
	};

	static enum FORCES {
		NULLF = 0, WIND, VORTEX, EXPLOSION, SPRING
	};

	static enum RIGIDS {
		SUELO, _STATIC, DYNAMIC
	};

	static enum GAME_MODE {
		EASY, MEDIUM, HARD
	};

	//Tipo de movimiento de las dianas
	static enum TARGET_MOV {
		STATIC, SPRING_1, SPRING_2, CIRCLE
	};

	//Colores de las dianas
	static enum TARGET_MODE {
		ORANGE, BLUE, BLACK, RED, WHITE
	};
}

