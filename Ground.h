#pragma once
#include "Tile.h"
#include "TileInterface.h"
#include "Colisions.h"

class Map;

class Ground :
	public TileInterface
{
private:
	ALLEGRO_BITMAP* sprite;
public:
	Ground(ALLEGRO_BITMAP* csprite);
	~Ground();
	void draw(Camera camera);
	void set_strategy(Tile* tile);
	void character_collision(Character* character, Tile* tile);
	void projectile_collision(Projectile* projectile, Tile* tile);
};

