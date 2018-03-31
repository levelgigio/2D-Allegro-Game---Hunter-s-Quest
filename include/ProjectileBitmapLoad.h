#pragma once
#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include <vector>

class ProjectileBitmapLoad
{
private:
	std::vector<ALLEGRO_BITMAP*> sprite;
	bool initialized;
public:
	ProjectileBitmapLoad();
	~ProjectileBitmapLoad();
	void init();
	ALLEGRO_BITMAP* get_sprite(int i);
};

