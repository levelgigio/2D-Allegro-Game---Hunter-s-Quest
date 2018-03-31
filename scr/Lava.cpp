#include "Lava.h"

Lava::Lava(ALLEGRO_BITMAP* csprite)
{
	sprite = csprite;
}


Lava::~Lava()
{
}


void Lava::draw(Camera camera)
{
	al_draw_scaled_bitmap(sprite, 0, 0, DEFAULTSPRITESIZE, DEFAULTSPRITESIZE,
		tile->get_x() - tile->get_bound_x() - camera.x, tile->get_y() - tile->get_bound_y() - camera.y,
		2 * tile->get_bound_x(), 2 * tile->get_bound_y(), 0);
}

void Lava::set_strategy(Tile* ctile)
{
	tile = ctile;
	tile->set_damage(1);
}

void Lava::character_collision(Character* character, Tile* tile) {
	damageCollision(character, tile);
}
void Lava::projectile_collision(Projectile* projectile, Tile* tile) {
	if (checkCollision(projectile, tile))
		projectile->set_unactive();
}
