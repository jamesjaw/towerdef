#include <string>
#include "PlayScene.hpp"
#include "NormalEnemy.hpp"
#include "AudioHelper.hpp"
#include "badbadBullet.hpp"
NormalEnemy::NormalEnemy(int x, int y) : Enemy("play/enemy-1.png", x, y, 15, 50, 5, 5) {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}

void NormalEnemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new badbadBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
