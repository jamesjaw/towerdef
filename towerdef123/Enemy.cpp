#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"


PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
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
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money) :
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money) {
	CollisionRadius = radius;
	reachEndTime = 0;
	//
	speed_up = 1;
    speed_down = speed;
    y_pos = y;

	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	hp -= damage;

	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}

void Enemy::speed_eff(float eff_data){
    //?l?u???G
    Velocity = Engine::Point(speed * eff_data , 0);
    //can_i_shoot = eff_data;

    if(speed_up!=1 && Velocity!= Engine::Point(speed * 0 , 0)){
           if(hp<=3){
            //???H???G = ???????v
            Velocity = Engine::Point(speed * speed_up , 0);
        }
    }
}

void Enemy::freezn(bool fizz){
    if(fizz == true){
        speed = 0;
    }
    else{
        speed = speed_rec;
    }
}

void Enemy::Update(float deltaTime) {
    PlayScene* scene = getPlayScene();
	float remainSpeed = speed * deltaTime;
	Position.x -= Velocity.x * deltaTime;
	Position.y += Velocity.y * deltaTime;
	if(Position.x -180 <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
        if(getPlayScene()->killer_number[(int)((y_pos - 64) /128)] == 0){
            getPlayScene()->killer_number[(int)((y_pos - 64) /128)] = 1;
            getPlayScene()->Creat_killer(y_pos);
		}
	}
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(hp);
		getPlayScene()->Hit();
		//

		//
		reachEndTime = 0;
		return;
	}
	//
    for (auto& it : scene->TowerGroup->GetObjects()) {
            if (!(it->Position.x <= Position.x
                  && it->Position.x+scene->BlockSize -50> Position.x
                  && it->Position.y <= Position.y
                  && it->Position.y+scene->BlockSize > Position.y)) {

                speed_eff(1);
                //freezn(false);
			}
			//if(it->empty()) speed_eff(1);

			else{
               speed_eff(0);
               //freezn(true);
               reload -= deltaTime;
            if (reload <= 0) {
                // shoot.
                reload = coolDown;
                //if(can_i_shoot == 0)
                CreateBullet();
            }
			}
    }
    //
   // if(Velocity == Engine::Point(speed * 0 , 0)){
        // shoot badbad
        //CreateBullet();
    //}
    //CreateBullet();




    //if (reload <= 0) {
			 //shoot.
			//reload = coolDown;
			//CreateBullet();
		//}
    //
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}

void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}



