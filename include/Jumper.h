#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "Projectile.h"
#include "CharacterInterface.h"

class Jumper : public CharacterInterface
{
private:
	Enemy* enemy;
	int gravitytimer;
public:
	Jumper();
	~Jumper();

	void move();
	void update();
	void draw(Camera camera);
	void set_strategy(Character* ccharacter);
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	int get_score_worth();
};

