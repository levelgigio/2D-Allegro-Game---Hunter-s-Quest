#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
private:
	Player* player;
	CharacterInterface* strategy;
public:
	Enemy(int cx, int cy, int cbound_x, int cbound_y, bool cactive, int cmaxHP, CharacterInterface* cstrategy, Player* cplayer);
	~Enemy();
	void move();
	void draw(Camera camera);
	void update();
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	Player* get_player();
	void setPlayer(Player* cplayer);
	void set_strategy(CharacterInterface* cstrategy);
	void destroy_strategy();
	int get_score_worth();
};

