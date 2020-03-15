#include "GameEntity.h"

GameEntity::GameEntity(int cx = 0, int cy = 0, int cvel_x = 0, int cvel_y = 0, int cbound_x = 0, int cbound_y = 0, bool cactive = false) :
	x(cx), y(cy), vel_x(cvel_x), vel_y(cvel_y), bound_x(cbound_x), bound_y(cbound_y), active(cactive), damage(0) {}
GameEntity::~GameEntity() {}

void GameEntity::set_x(const int cx) { x = cx; }
const int GameEntity::get_x() const { return x; }
void GameEntity::set_y(const int cy) { y = cy; }
const int GameEntity::get_y() const { return y; }
void GameEntity::set_vel_x(const int cvel_x) { vel_x = cvel_x; }
const int GameEntity::get_vel_x() const { return vel_x; }
void GameEntity::set_vel_y(const int cvel_y) { vel_y = cvel_y; }
const int GameEntity::get_vel_y() const { return vel_y; }
void GameEntity::set_bound_x(const int cbound_x) { bound_x = cbound_x; }
const int GameEntity::get_bound_x() const { return bound_x; }
void GameEntity::set_bound_y(const int cbound_y) { bound_y = cbound_y; }
const int GameEntity::get_bound_y() const { return bound_y; }
void GameEntity::set_active() { active = true; }
void GameEntity::set_unactive() { active = false; }
const bool GameEntity::get_active() const { return active; }
void GameEntity::set_damage(const int cdamage) { damage = cdamage; }
const int GameEntity::get_damage() const { return damage; }