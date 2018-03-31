#include "Enemy.h"

Enemy::Enemy(int cx = 0, int cy = 0, int cbound_x = 0, int cbound_y = 0,
	bool cactive = false, int cmaxHP = 0, CharacterInterface* cstrategy = nullptr, Player* cplayer = nullptr) :
	Character(cx, cy, cbound_x, cbound_y, cactive, cmaxHP), strategy(cstrategy), player(cplayer)
{
	if (strategy != nullptr)
		strategy->set_strategy(this);
}


Enemy::~Enemy()
{
}

void Enemy::move()
{
	strategy->move();
}

void Enemy::draw(Camera camera)
{
	strategy->draw(camera);
}

void Enemy::attack(std::vector<Projectile*>* projectile_list, float cangle)
{
	strategy->attack(projectile_list, cangle);
}

void Enemy::update()
{
	strategy->update();
}

Player* Enemy::get_player()
{
	return player;
}

void Enemy::set_strategy(CharacterInterface* cstrategy)
{
	if (strategy != nullptr)
		delete strategy;
	strategy = cstrategy;
	strategy->set_strategy(this);
}

void Enemy::destroy_strategy() {
	delete strategy;
	return;
}

void Enemy::setPlayer(Player* cplayer)
{
	player = cplayer;
}

int Enemy::get_score_worth()
{
    return strategy->get_score_worth();
}
