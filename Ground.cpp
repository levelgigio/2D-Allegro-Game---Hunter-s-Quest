#include "Ground.h"

Ground::Ground(ALLEGRO_BITMAP* csprite)
{
	sprite = csprite;
}


Ground::~Ground()
{
}


void Ground::draw(Camera camera)
{
	al_draw_scaled_bitmap(sprite, 0, 0, DEFAULTSPRITESIZE, DEFAULTSPRITESIZE,
		tile->get_x() - tile->get_bound_x() - camera.x, tile->get_y() - tile->get_bound_y() - camera.y,
		2 * tile->get_bound_x(), 2 * tile->get_bound_y(), 0);
}

void Ground::set_strategy(Tile* ctile)
{
	tile = ctile;
}

void Ground::character_collision(Character* character, Tile* tile) {
	solidCollision(character, tile);
}
void Ground::projectile_collision(Projectile* projectile, Tile* tile) {
	if (checkCollision(projectile, tile))
		projectile->set_unactive();
}
