#ifndef KILLERBULLET_HPP
#define KILLERBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class killerBullet : public Bullet {
public:
	explicit killerBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
	void Update(float deltaTime) override;
};
#endif // KILLERBULLET_HPP
