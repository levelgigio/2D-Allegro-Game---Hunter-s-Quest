#pragma once
#include "GameEntity.h"
#include "TileInterface.h"
#include "Projectile.h"

class TileInterface;

class Tile :
	public GameEntity
{
private:
	TileInterface* strategy;
public:
	Tile(int cx, int cy, bool cactive, TileInterface* cstrategy);
	~Tile();
	void set_strategy(TileInterface* cstrategy);
	void destroy_strategy();
	void draw(Camera camera);
	void character_collision(Character* player, Tile* tile);
	void projectile_collision(Projectile* projectile, Tile* tile);
};

