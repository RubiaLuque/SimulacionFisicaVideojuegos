#pragma once

namespace Data {
	static const float LIMIT_ON_SCREEN= 10.0;
	static const int TAM_LIST = 5;
	static const float FIREWORK_DEATH = 5.0; //tiempo de muerte de todo el firework
	static const float FIREWORK_INIT_DEATH = 1.5; //tiempo que tarda en morir la particula inicial
	static const float FIREWORK_P_DEATH = 0.5; //tiempo de muerte de cada particula del firework

	static enum GENERATORS {
		FUENTE, LLUVIA, NIEVE, NIEBLA, FIREWORKS
	};

	static enum PROJECTILE_TYPE {
		FIREBALL, LIGHTGUN, GUN, CANNON,
	};

}

