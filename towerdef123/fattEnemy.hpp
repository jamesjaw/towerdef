#ifndef FATTENEMY_HPP
#define FATTENEMY_HPP
#include "Enemy.hpp"

class fattEnemy : public Enemy {
public:
	fattEnemy(int x, int y);
	void CreateBullet() override;
};



#endif // FATTENEMY_HPP
