#ifndef BADBADBULLET_HPP
#define BADBADBULLET_HPP
#include "Bullet_en.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class badbadBullet : public Bullet_en {
public:
	explicit badbadBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	//


};
#endif // BADBADBULLET_HPP
