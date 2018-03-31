#pragma once
#include "Tile.h"
#include "TileInterface.h"
#include "Colisions.h"

class Map;

class Spikes :
	public TileInterface
{
private:
	ALLEGRO_BITMAP* sprite;
public:
	Spikes(ALLEGRO_BITMAP* csprite);
	~Spikes();
	void draw(Camera camera);
	void set_strategy(Tile* tile);
	void character_collision(Character* character, Tile* tile);
	void projectile_collision(Projectile* projectile, Tile* tile);
};

