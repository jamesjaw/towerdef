#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <random>
#include <vector>

#include "Collider.hpp"
#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"

#include "ExplosionEffect.hpp"
#include "AudioHelper.hpp"
#include "DirtyEffect.hpp"

PlayScene* Turret::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
//
void Turret::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}

Turret::Turret(std::string imgTurret, float x, float y, float radius, int price, float coolDown,float attack_range,float hp) :
	Sprite(imgTurret, x, y), price(price), coolDown(coolDown),hp(hp) {
	CollisionRadius = radius;
	attack_rangez = attack_range;
}
void Turret::Update(float deltaTime) {
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
                //Target->freezn(true);
                Target->speed_eff(0);
			}

    }

}
void Turret::Draw() const {
	if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw target radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
    al_draw_circle(Position.x, Position.y, attack_rangez, al_map_rgb(255, 0, 0), 2);
}
int Turret::GetPrice() const {
	return price;
}

void Turret::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		//
		//bomb
		 for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
			Enemy* enemy = dynamic_cast<Enemy*>(it);
			if (Engine::Collider::IsCircleOverlap(Position, attack_rangez, enemy->Position, enemy->CollisionRadius))
				enemy->Hit(99);
		}

		//
		// Remove all turret's reference to target.
		/*
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
        */
		getPlayScene()->TowerGroup->RemoveObject(objectIterator);
        getPlayScene()->re_map(Position.y,Position.x);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
