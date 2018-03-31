#pragma once
#include "Projectile.h"
#include "Enemy.h"
#include <ctgmath>
#include "CharacterInterface.h"

using namespace std;

class Shooter : public CharacterInterface
{
private:
	Enemy* enemy;
	int fixed_y;
	int shoottimer;
	int score_worth;
public:
	Shooter();
	~Shooter();

	void move();
	void update();
	void draw(Camera camera);
	void set_strategy(Character* ccharacter);
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	int get_score_worth();
};


