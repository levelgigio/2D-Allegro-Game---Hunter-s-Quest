#pragma once
#include "Character.h"
#include "Tile.h"
#include "Projectile.h"

class Tile;

class TileInterface
{
protected:
	Tile* tile;
public:
	TileInterface() : tile(nullptr) {}
	~TileInterface() {}
	virtual void set_strategy(Tile* tile) = 0;
	virtual void draw(Camera camera) = 0;
	virtual void character_collision(Character* player, Tile* tile) = 0;
	virtual void projectile_collision(Projectile* projectile, Tile* tile) = 0;
};
