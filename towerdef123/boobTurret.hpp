#ifndef BOOBTURRET_HPP
#define BOOBTURRET_HPP
#include "Turret.hpp"

class boobTurret: public Turret {
public:
	static const int Price;
    boobTurret(float x, float y);
	void CreateBullet() override;
	void Update(float deltaTime) override;
};
#endif // BOOBTURRET_HPP
