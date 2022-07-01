#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Collider.hpp"
#include "AudioHelper.hpp"
#include "frieBullet.hpp"
#include "Group.hpp"
#include "boobTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int boobTurret::Price = 70;
boobTurret::boobTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/turret-6.png", x, y,20, Price, 0.5,200,1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();

}
void boobTurret::CreateBullet() {

}

void boobTurret::Update(float deltaTime){
    Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
	if (Target) {



		if (Target->Position.x < Position.x&& Target->Position.y >= Position.y  && Target->Position.y < Position.y+scene->BlockSize) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Turret*>::iterator();
		}
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			CreateBullet();
		}
		/*

        */
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
            if (it->Position.x > Position.x && it->Position.y >= Position.y  && it->Position.y < Position.y+scene->BlockSize) {
				Target = dynamic_cast<Enemy*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}
    //!!!

	for (auto& it : scene->EnemyGroup->GetObjects()) {
            if (it->Position.x >= Position.x
                && it->Position.x < Position.x+scene->BlockSize -50
                && it->Position.y >= Position.y
                && it->Position.y < Position.y+scene->BlockSize) {
                Target = dynamic_cast<Enemy*>(it);
                Target->speed_eff(0);
			}

    }
    if(hp<=0){
        for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
			Enemy* enemy = dynamic_cast<Enemy*>(it);
			if (Engine::Collider::IsCircleOverlap(Position, 600, enemy->Position, enemy->CollisionRadius))
				enemy->Hit(INFINITY);
		}
    }
}
