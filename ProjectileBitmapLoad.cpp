#include "ProjectileBitmapLoad.h"

ProjectileBitmapLoad::ProjectileBitmapLoad() : initialized(false)
{
}


ProjectileBitmapLoad::~ProjectileBitmapLoad()
{
}

ALLEGRO_BITMAP* ProjectileBitmapLoad::get_sprite(int i) {
	if (!initialized) {
		init();
		initialized = true;
	}
	return sprite.at(i - 1);
}

void ProjectileBitmapLoad::init() {
	sprite.push_back(al_load_bitmap("arrow.png"));
}