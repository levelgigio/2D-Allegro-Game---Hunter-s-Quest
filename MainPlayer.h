#pragma once
#include "CharacterInterface.h"
#include "Player.h"
#include "Projectile.h"


class MainPlayer :
	public CharacterInterface
{
private:
	Player* player;
public:
	MainPlayer();
	~MainPlayer();
	void set_strategy(Character* ccharacter);
	void destroy_strategy();
	void move();
	void update();
	void draw(Camera camera);
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	int get_score_worth() { return 0; }
};
