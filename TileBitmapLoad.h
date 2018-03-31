#pragma once
#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include <vector>

class TileBitmapLoad
{
private:
	std::vector<ALLEGRO_BITMAP*> sprite;
public:
	TileBitmapLoad();
	~TileBitmapLoad();
	void init();
	ALLEGRO_BITMAP* get_sprite(int i);
};

