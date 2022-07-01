#ifndef REDTURRET_HPP
#define REDTURRET_HPP
#include "Turret.hpp"

class redTurret: public Turret {
public:
	static const int Price;
    redTurret(float x, float y);
	void CreateBullet() override;
};
#endif // REDTURRET_HPP
