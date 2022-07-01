#include <string>
#include "boss.hpp"
#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "Turret.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"
boss::boss(int x, int y) : Enemy("play/boss.png", x, y, 111, 20, 50, 500) {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
    xs = 35;
    ys = 0;
}

void boss::CreateBullet() {

}

void boss::Update(float deltaTime) {
    PlayScene* scene = getPlayScene();
	float remainSpeed = speed * deltaTime;
	Position.x -= xs * deltaTime;
	Position.y += ys * deltaTime;

	if(Position.y <= 120)
    ys =  100;
    else if(Position.y >= 650)
    ys =  -100;

	speed_eff(1);
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(hp);
		getPlayScene()->Hit();
		//
		reachEndTime = 0;
		return;
	}
	//

    for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
		if (!turret->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
			turret->Hit(999);
		}
	}

	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}


