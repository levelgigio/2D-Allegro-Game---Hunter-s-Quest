#include "DestroyablePlatform.h"

DestroyablePlatform::DestroyablePlatform(ALLEGRO_BITMAP* csprite_unhit, ALLEGRO_BITMAP* csprite_hit) : hit(false)
{
	sprite_unhit = csprite_unhit;
	sprite_hit = csprite_hit;
}


DestroyablePlatform::~DestroyablePlatform()
{
}


void DestroyablePlatform::draw(Camera camera)
{
	if (!hit)
		al_draw_scaled_bitmap(sprite_unhit, 0, 0, DEFAULTSPRITESIZE, DEFAULTSPRITESIZE,
			tile->get_x() - tile->get_bound_x() - camera.x, tile->get_y() - tile->get_bound_y() - camera.y,
			2 * tile->get_bound_x(), 2 * tile->get_bound_y(), 0);
	else
		al_draw_scaled_bitmap(sprite_hit, 0, 0, DEFAULTSPRITESIZE, DEFAULTSPRITESIZE,
			tile->get_x() - tile->get_bound_x() - camera.x, tile->get_y() - tile->get_bound_y() - camera.y,
			2 * tile->get_bound_x(), 2 * tile->get_bound_y(), 0);

}

void DestroyablePlatform::set_strategy(Tile* ctile)
{
	tile = ctile;
}

void DestroyablePlatform::character_collision(Character* character, Tile* tile) {
	solidCollision(character, tile);
}

void DestroyablePlatform::projectile_collision(Projectile* projectile, Tile* tile) {
	if (checkCollision(projectile, tile)) {
		projectile->set_unactive();
		if (!hit)
			hit = true;
		else
			tile->set_unactive();
	}
}
