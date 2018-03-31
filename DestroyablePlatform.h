#pragma once
#include "Tile.h"
#include "TileInterface.h"
#include "Colisions.h"

class Map;

class DestroyablePlatform :
	public TileInterface
{
private:
	ALLEGRO_BITMAP* sprite_unhit;
	ALLEGRO_BITMAP*	sprite_hit;
	bool hit;
public:
	DestroyablePlatform(ALLEGRO_BITMAP* csprite_unhit, ALLEGRO_BITMAP* csprite_hit);
	~DestroyablePlatform();
	void draw(Camera camera);
	void set_strategy(Tile* tile);
	void character_collision(Character* character, Tile* tile);
	void projectile_collision(Projectile* projectile, Tile* tile);
};

