#include <string>
#include "PlayScene.hpp"
#include "StrongEnemy.hpp"
#include "NormalEnemy.hpp"
#include "AudioHelper.hpp"
#include "badbadBullet.hpp"
StrongEnemy::StrongEnemy(int x, int y) : Enemy("play/enemy-3.png", x, y, 23, 20, 100, 50) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}

void StrongEnemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new badbadBullet(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}

