#ifndef SHOOTINGEFFECT_HPP
#define SHOOTINGEFFECT_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Sprite.hpp"

class PlayScene;

class shootingEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	shootingEffect(float x, float y);
	void Update(float deltaTime) override;
};
#endif // SHOOTINGEFFECT_HPP
