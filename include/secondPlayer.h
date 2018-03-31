#pragma once
#include "CharacterInterface.h"
#include "Player.h"
#include "Animation.h"
#include "Projectile.h"

class secondPlayer :
	public CharacterInterface
{
private:
	Player* player;
	Player* player2;
public:
	secondPlayer(Player* cplayer);
	~secondPlayer();
	void set_strategy(Character* ccharacter);
	void move();
	void update();
	void draw(Camera camera);
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	int get_score_worth() { return 0; }
};

