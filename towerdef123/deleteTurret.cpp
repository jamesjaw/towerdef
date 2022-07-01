#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "frieBullet.hpp"
#include "Group.hpp"
#include "deleteTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int deleteTurret::Price = -50;
deleteTurret::deleteTurret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/bomb.png", x, y,10, Price, 0.5,0,1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
    //Enabled = false;
}






void deleteTurret::CreateBullet() {

}
