#ifndef BOSS_HPP
#define BOSS_HPP
#include "Enemy.hpp"

class boss : public Enemy {
public:
	boss(int x, int y);
	void CreateBullet() override;
	void Update(float deltaTime) override;
	float xs;
	float ys;
};
#endif // BOSS_HPP
