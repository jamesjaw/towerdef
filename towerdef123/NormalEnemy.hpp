#ifndef NORMALENEMY_HPP
#define NORMALENEMY_HPP
#include "Enemy.hpp"
#include "badbadBullet.hpp"
class NormalEnemy : public Enemy {
public:
	NormalEnemy(int x, int y);
	void CreateBullet() override;
};
#endif // NORMALENEMY_HPP
