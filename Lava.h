#pragma once
#include "Tile.h"
#include "TileInterface.h"
#include "Colisions.h"

class Map;

class Lava :
	public TileInterface
{
private:
	ALLEGRO_BITMAP* sprite;
public:
	Lava(ALLEGRO_BITMAP* csprite);
	~Lava();
	void draw(Camera camera);
	void set_strategy(Tile* tile);
	void character_collision(Character* character, Tile* tile);
	void projectile_collision(Projectile* projectile, Tile* tile);
};
