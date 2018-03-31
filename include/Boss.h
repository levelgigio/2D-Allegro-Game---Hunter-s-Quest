#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Colisions.h"
#include "Points.h"

class Boss : public CharacterInterface
{
private:
	Enemy* enemy;
	int gravitytimer;
	int jump_timer;
	int shoot_timer;
	int shoot_delay;
	int map_width;
	std::vector<Points*>* random_points;
public:
	Boss(std::vector<Points*>* crandom_points);
	~Boss();

	void move();
	void update();
	void draw(Camera camera);
	void set_strategy(Character* ccharacter);
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	int get_score_worth();
};



