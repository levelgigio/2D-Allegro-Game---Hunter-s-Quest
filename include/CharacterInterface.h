#pragma once
#include "Camera.h"
#include <vector>
#include "Projectile.h"

#define square(A) ((A)*(A))

#define GRAVITYTIMER 2 //o jogo espera essa quantidade de frames+1 antes de atualizar a gravidade

//walker
#define WALKERTURNCHANCE 100

//shooter
#define SHOOTTIMER 60 //seconds between shots
#define SHOOTATTACKRADIUS 600

//enemy
#define ENEMYSPEED 1
#define ENEMYJUMPCHANCE 50
#define ENEMYJUMP 6
#define CHASERADIUS 300

//player
#define PLAYERSPEED 5
#define PLAYERACCELERATION 1
#define PLAYERJUMP 10
#define PLAYERSPREGENTIMER 5
#define PLAYERMAXSP 100
#define PLAYERDAMAGE 10
//player 2
#define PLAYERTWOREACH 100

//boss
#define BOSSSPEED 3
#define ENEMYJUMPTIMER 60
#define BOSSJUMP 7
#define BOSSCHASEDISTANCEX 10000
#define BOSSCHASEDISTANCEY 10000
#define SHOOTDELAY 60
#define SHOOTTIMING 10
#define BOSSATTACKRADIUS 10000

class CharacterInterface
{
public:
	CharacterInterface() {}
	~CharacterInterface() {}
	virtual void set_strategy(Character* ccharacter) = 0;
	virtual void move() = 0;
	virtual void update() = 0;
	virtual void draw(Camera camera) = 0;
	virtual void attack(std::vector<Projectile*>* projectile_list, float cangle) = 0;
	virtual int get_score_worth() = 0;
};
