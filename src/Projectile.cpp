#include "Projectile.h"

ProjectileBitmapLoad* Projectile::spriteload = new ProjectileBitmapLoad();

Projectile::Projectile(Character* source, Character* target, bool friendly, int cdamage) :
	GameEntity(source->get_x(), source->get_y(), 0, 0, 8, 8, true), is_friendly(friendly), angle(0)
{
	sprite = spriteload->get_sprite(1);
	angle = atan2(target->get_y() - source->get_y(), target->get_x() - source->get_x());
	set_vel_x(cos(angle)*PROJECTILEVELOCITY);
	set_vel_y(sin(angle)*PROJECTILEVELOCITY);
	set_damage(cdamage);
}

Projectile::Projectile(Character* source, bool friendly, int cdamage, float cangle) :
	GameEntity(source->get_x(), source->get_y(), 0, 0, 8, 8, true), is_friendly(friendly), angle(cangle)
{
	sprite = spriteload->get_sprite(1);
    set_vel_x(cos(angle)*PROJECTILEVELOCITY);
    set_vel_y(sin(angle)*PROJECTILEVELOCITY);
    set_damage(cdamage);
}

Projectile::Projectile(int cx, int cy, float cangle, int cdamage) : 
	GameEntity(0, 0, 0, 0, 8, 8, true)
{
	sprite = spriteload->get_sprite(1);
	set_x(cx);
	set_y(cy);
	set_angle(cangle);
	set_vel_x(cos(cangle)*PROJECTILEVELOCITY);
	set_vel_y(sin(cangle)*PROJECTILEVELOCITY);
    set_damage(cdamage);
}

Projectile::~Projectile()
{
}

void Projectile::set_angle(float cangle) { angle = cangle; }
float Projectile::get_angle() const { return angle; }
void Projectile::set_friendly(bool cis_friendly) { is_friendly = cis_friendly; }
bool Projectile::get_friendly() { return is_friendly; }

void Projectile::update()
{

}
void Projectile::draw(Camera camera)
{
	al_draw_scaled_rotated_bitmap(sprite, 200, 128, get_x() - camera.x, get_y() - camera.y, (float)DEFAULTTILESIZE / DEFAULTSPRITESIZE, (float)DEFAULTTILESIZE / DEFAULTSPRITESIZE, angle, 0);
}

void Projectile::move()
{
	set_x(get_x() + get_vel_x());
	set_y(get_y() + get_vel_y());
}
