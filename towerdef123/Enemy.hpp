#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed;
    float hp;
    float y_pos;
    //
    float coolDown = 0.8;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;

    //
	int money;
	PlayScene* getPlayScene();
	virtual void OnExplode();
	//
	virtual void CreateBullet() = 0;
	//void CreateBullet();
    //
public:

	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money );
 	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	//
    void speed_eff(float eff_data);
    void freezn(bool fizz);

    //float can_i_shoot = 1;
    int speed_up;
    int speed_down;
    int speed_rec = 25;

};
#endif // ENEMY_HPP
