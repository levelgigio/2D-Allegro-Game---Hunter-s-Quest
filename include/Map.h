#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "TileInterface.h"
#include "Ground.h"
#include "Player.h"
#include "MainPlayer.h"
#include "Game.h"
#include "Jumper.h"
#include "Walker.h"
#include "Shooter.h"
#include "Boss.h"
#include "Spikes.h"
#include "Lava.h"
#include "TileBitmapLoad.h"
#include "Points.h"
#include "DestroyablePlatform.h"

class Game;

class Map
{
private:
	Game* game;
	ALLEGRO_BITMAP* background;
	TileBitmapLoad* spriteload;
	char** map_array;
	int initialized;
	std::vector<Points*> enemy_points_vector;
	std::vector<Points*>::iterator pointsitr;
	std::vector<Points*> obstacle_points_vector;
	std::vector<Points*> random_points_vector;
public:
	Map(Game* cgame);
	~Map();
	void MapInit(const string map, bool load);
	void Map_destroy();
	void draw(Camera camera, std::vector<Tile*>& Tile_list);
	void save_map();
	bool load_map();
};
