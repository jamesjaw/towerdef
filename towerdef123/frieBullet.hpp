#ifndef FRIEBULLET_HPP
#define FRIEBULLET_HPP
#include "Bullet.hpp"
#include "Sprite.hpp"
class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class frieBullet : public Bullet {
public:
	explicit frieBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
	//void Update(float deltaTime) override;
};
#endif // FRIEBULLET_HPP
