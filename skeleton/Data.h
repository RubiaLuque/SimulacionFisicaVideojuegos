#pragma once

namespace Data {
	static const int TAM_LIST = 5;
	static const int FIREWORK_DEATH = 5; //tiempo de muerte de todo el firework
	static const int FIREWORK_P_DEATH = 1; //tiempo de muerte de cada particula del firework

	static enum GENERATORS {
		FUENTE, LLUVIA, NIEVE, NIEBLA, FIREWORKS
	};

	static enum PROJECTILE_TYPE {
		FIREBALL, LIGHTGUN, GUN, CANNON,
	};

}

