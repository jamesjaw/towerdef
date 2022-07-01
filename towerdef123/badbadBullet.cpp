#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "badbadBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
//
#include "Collider.hpp"

class Turret;

badbadBullet::badbadBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
	Bullet_en("play/bullet-11.png", -350, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
	// TODO 2 (1/8): You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}


