#pragma once
#include "Projectile.h"
#include "Enemy.h"
#include "CharacterInterface.h"

using namespace std;

class Walker : public CharacterInterface
{
private:
	Enemy* enemy;
	int gravitytimer;
	int fixed_y;
public:
	Walker();
	~Walker();

	void move();
	void update();
	void draw(Camera camera);
	void set_strategy(Character* ccharacter);
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	int get_score_worth();
};

