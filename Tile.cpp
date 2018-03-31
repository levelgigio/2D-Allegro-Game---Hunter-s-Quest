#include "Tile.h"

Tile::Tile(int cx = 0, int cy = 0, bool cactive = false, TileInterface* cstrategy = nullptr) :
	GameEntity(cx, cy, 0, 0, DEFAULTTILESIZE / 2, DEFAULTTILESIZE / 2, cactive), strategy(cstrategy)
{
	if (strategy != nullptr)
		strategy->set_strategy(this);
}


Tile::~Tile()
{
}

void Tile::draw(Camera camera)
{
	strategy->draw(camera);
}

void Tile::set_strategy(TileInterface* cstrategy)
{
	if (strategy != nullptr)
		delete strategy;
	strategy = cstrategy;
	strategy->set_strategy(this);
}

void Tile::destroy_strategy() {
	delete strategy;
	return;
}


void Tile::character_collision(Character* player, Tile* tile) {
	strategy->character_collision(player, tile);
}

void Tile::projectile_collision(Projectile* projectile, Tile* tile) {
	strategy->projectile_collision(projectile, tile);
}