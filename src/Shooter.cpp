#pragma once
#include "Shooter.h"

Shooter::Shooter() : fixed_y(-1), shoottimer(SHOOTTIMER)
{
}

Shooter::~Shooter()
{
}

void Shooter::move()
{
	//gravidade
	if (enemy->get_on_ground())
		enemy->set_gravity_timer(0);
	if (!enemy->get_on_ground() && !enemy->get_gravity_timer()) {
		enemy->set_vel_y(enemy->get_vel_y() + 1);
	}
	enemy->set_gravity_timer(enemy->get_gravity_timer() + 1);
	if (enemy->get_gravity_timer() > GRAVITYTIMER)
		enemy->set_gravity_timer(0);

	if (!enemy->get_on_ground() && !enemy->get_vel_y())
	{
		enemy->set_x(enemy->get_x() - enemy->get_last_direction() * 5);
		enemy->set_last_direction(enemy->get_last_direction()*-1);
	}
	else if (!enemy->get_vel_x())
		enemy->set_last_direction(enemy->get_last_direction()*-1);

	//velocidade terminal

	if (enemy->get_vel_y() > 16)
		enemy->set_vel_y(16);

	enemy->set_vel_x(ENEMYSPEED*enemy->get_last_direction());

	if (!(rand() % WALKERTURNCHANCE))
		enemy->set_vel_x(-enemy->get_vel_x());

	enemy->set_x(enemy->get_x() + enemy->get_vel_x());
	enemy->set_y(enemy->get_y() + enemy->get_vel_y());
}

void Shooter::attack(std::vector<Projectile*>* projectile_list, float cangle)
{
	if (square(enemy->get_x() - enemy->get_player()->get_x()) + square(enemy->get_y() - enemy->get_player()->get_y()) < square(SHOOTATTACKRADIUS)) {
		if ((enemy->get_player()->get_x() - enemy->get_x())*enemy->get_last_direction() > 0)
			if (!(shoottimer)) {
				projectile_list->push_back(new Projectile(enemy, enemy->get_player(), false, 10));
				shoottimer = SHOOTTIMER;
			}
			else {
				shoottimer--;
			}
			if (enemy->get_x() >= enemy->get_player()->get_x())
				enemy->set_last_direction(-1);
			else
				enemy->set_last_direction(1);
	}
}

void Shooter::draw(Camera camera)
{
	enemy->get_animation()->animate(camera);
	al_draw_line(enemy->get_x() - enemy->get_bound_x() - camera.x, enemy->get_y() - enemy->get_bound_y() - camera.y - 5,
		enemy->get_x() - enemy->get_bound_x() + 2 * enemy->get_bound_x()*(enemy->get_HP() / (float)enemy->get_maxHP()) - camera.x,
		enemy->get_y() - enemy->get_bound_y() - camera.y - 5, al_map_rgb(255, 0, 0), 2);
}

void Shooter::update()
{
	if (enemy->get_vel_x() > 0)
		enemy->set_last_direction(1);
	if (enemy->get_vel_x() < 0)
		enemy->set_last_direction(-1);
}

void Shooter::set_strategy(Character* ccharacter)
{
	enemy = static_cast<Enemy*>(ccharacter);
	enemy->set_animation("shooter.png", 3, DEFAULTTILESIZE, DEFAULTTILESIZE);
	enemy->set_damage(15);
	string type = "Shooter";
	enemy->set_type(type);
	enemy->set_last_direction(1);

}

int Shooter::get_score_worth() { return 200; }
