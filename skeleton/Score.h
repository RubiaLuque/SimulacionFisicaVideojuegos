#pragma once
#include "Data.h"
class Score
{
private:
	int score = 0;

public:
	Score(){ }
	virtual ~Score() { score = 0; }

	void addScore(Data::TARGET_MODE mode) {
		if (mode == Data::BLUE) {
			score += 200;
		}
		else if (mode == Data::BLACK) {
			score += 400;
		}
		else if (mode == Data::RED) {
			score += 600;
		}
		else if (mode == Data::WHITE) {
			score += 100;
		}
		else if (mode == Data::ORANGE) {
			score += 800;
		}
	}

	inline int getScore() { return this->score; }
};

