#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "frieBullet.hpp"
#include "Group.hpp"
#include "redTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int redTurret::Price = 70;
redTurret::redTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/turret-3.png", x, y,20, Price, 0.5,0,6) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void redTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	//Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new frieBullet(Position , Engine::Point(1,0.5) , rotation*0.5, this));
	getPlayScene()->BulletGroup->AddNewObject(new frieBullet(Position , diff, rotation, this));
	getPlayScene()->BulletGroup->AddNewObject(new frieBullet(Position , Engine::Point(1,-0.5), rotation*0.5, this));
	AudioHelper::PlayAudio("gun.wav");
}
