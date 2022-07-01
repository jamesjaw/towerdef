#ifndef ROCKTURRET_HPP
#define ROCKTURRET_HPP
#include "Turret.hpp"

class rockTurret: public Turret {
public:
	static const int Price;
    rockTurret(float x, float y);
	void CreateBullet() override;
};
#endif // ROCKTURRET_HPP
