#include "Player.h"

Player::Player(int cx = 0, int cy = 0, int cbound_x = 0, int cbound_y = 0,
	bool cactive = 0, int cmaxHP = 0, int cmaxSP = 0, CharacterInterface* cstrategy = nullptr) :
	Character(cx, cy, cbound_x, cbound_y, cactive, cmaxHP), strategy(cstrategy), maxSP(cmaxSP), SP(cmaxSP)
{
	if (strategy != nullptr)
		strategy->set_strategy(this);
}


Player::~Player()
{
}

void Player::set_SP(const int cSP) { SP = cSP; }
const int Player::get_SP() const { return SP; }
void Player::set_maxSP(const int cmaxSP) { maxSP = cmaxSP; }
const int Player::get_maxSP() const { return maxSP; }

void Player::move() {
	strategy->move();
}

void Player::update() {
	strategy->update();
}

void Player::draw(Camera camera) {
	strategy->draw(camera);
}

void Player::set_strategy(CharacterInterface* cstrategy) {
	if (strategy != nullptr)
		delete strategy;
	strategy = cstrategy;
	strategy->set_strategy(this);
}

void Player::destroy_strategy() {
	delete strategy;
	return;
}

void Player::attack(std::vector<Projectile*>* projectile_list, float cangle)
{
	strategy->attack(projectile_list, cangle);
}
