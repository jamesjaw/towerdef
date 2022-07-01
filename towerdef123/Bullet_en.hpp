#ifndef BULLET_EN_HPP
#define BULLET_EN_HPP
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet_en : public Engine::Sprite {
protected:
	float speed;
	float damage;

	Enemy* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Turret* turret);
public:
	Turret* Target = nullptr;
	explicit Bullet_en(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void Update(float deltaTime) override;
	//
    float bullet_eff = 1;
	//

};
#endif // BULLET_EN_HPP
