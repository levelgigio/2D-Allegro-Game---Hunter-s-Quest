#include "TileBitmapLoad.h"

TileBitmapLoad::TileBitmapLoad()
{
}


TileBitmapLoad::~TileBitmapLoad()
{
}

ALLEGRO_BITMAP* TileBitmapLoad::get_sprite(int i) {
	return sprite.at(i - 1);
}

void TileBitmapLoad::init() {
	sprite.push_back(al_load_bitmap("tile_1.png"));
	sprite.push_back(al_load_bitmap("tile_2.png"));
	sprite.push_back(al_load_bitmap("tile_3.png"));
	sprite.push_back(al_load_bitmap("tile_4.png"));
	sprite.push_back(al_load_bitmap("tile_5.png"));
	sprite.push_back(al_load_bitmap("tile_6.png"));
	sprite.push_back(al_load_bitmap("tile_7.png"));
}