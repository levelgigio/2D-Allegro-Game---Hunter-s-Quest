#include "Spikes.h"

Spikes::Spikes(ALLEGRO_BITMAP* csprite)
{
	sprite = csprite;
}


Spikes::~Spikes()
{
}


void Spikes::draw(Camera camera)
{
	al_draw_scaled_bitmap(sprite, 0, 0, DEFAULTSPRITESIZE, DEFAULTSPRITESIZE,
		tile->get_x() - tile->get_bound_x() - camera.x, tile->get_y() - tile->get_bound_y() - camera.y,
		2 * tile->get_bound_x(), 2 * tile->get_bound_y(), 0);
}

void Spikes::set_strategy(Tile* ctile)
{
	tile = ctile;
	tile->set_damage(15);
}

void Spikes::character_collision(Character* character, Tile* tile) {
	damageKnockbackCollision(character, tile);
}
void Spikes::projectile_collision(Projectile* projectile, Tile* tile) {
	if (checkCollision(projectile, tile)) {
		projectile->set_unactive();
		tile->set_unactive();
	}
}
