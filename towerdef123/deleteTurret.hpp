#ifndef DELETETURRET_HPP
#define DELETETURRET_HPP
#include "Turret.hpp"

class deleteTurret: public Turret {
public:
	static const int Price;
    deleteTurret(float x, float y);
	void CreateBullet() override;
};
#endif // DELETETURRET_HPP
