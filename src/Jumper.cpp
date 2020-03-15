#pragma once
#include "Jumper.h"
#include <random>
#include <time.h>

Jumper::Jumper() : enemy(nullptr), gravitytimer(0)
{
	srand(time(NULL));
}

Jumper::~Jumper()
{
}

void Jumper::move()
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

	//velocidade terminal

	if (enemy->get_vel_y() > 16)
		enemy->set_vel_y(16);

	if (enemy->get_player()->get_x() > enemy->get_x())
		enemy->set_last_direction(1);
	else if (enemy->get_player()->get_x() < enemy->get_x())
		enemy->set_last_direction(-1);
	else
		enemy->set_last_direction(0);;

	if (enemy->get_on_ground() && !(rand() % ENEMYJUMPCHANCE))
		enemy->set_vel_y(-ENEMYJUMP);
	if (square(enemy->get_x() - enemy->get_player()->get_x()) + square(enemy->get_y() - enemy->get_player()->get_y()) < square(CHASERADIUS))
		enemy->set_vel_x(ENEMYSPEED*enemy->get_last_direction());
	else
		enemy->set_vel_x(0);

	enemy->set_x(enemy->get_x() + enemy->get_vel_x());
	enemy->set_y(enemy->get_y() + enemy->get_vel_y());
}

void Jumper::draw(Camera camera)
{
	enemy->get_animation()->animate(camera);
	al_draw_line(enemy->get_x() - enemy->get_bound_x() - camera.x, enemy->get_y() - enemy->get_bound_y() - camera.y - 5,
		enemy->get_x() - enemy->get_bound_x() + 2 * enemy->get_bound_x()*(enemy->get_HP() / (float)enemy->get_maxHP()) - camera.x,
		enemy->get_y() - enemy->get_bound_y() - camera.y - 5, al_map_rgb(255, 0, 0), 2);
}

void Jumper::update()
{
	if (enemy->get_vel_x() > 0)
		enemy->set_last_direction(1);
	if (enemy->get_vel_x() < 0)
		enemy->set_last_direction(-1);
}

void Jumper::set_strategy(Character* ccharacter)
{
	enemy = static_cast<Enemy*>(ccharacter);
	enemy->set_animation("jumper.png", 3, DEFAULTTILESIZE, DEFAULTTILESIZE);
	enemy->set_damage(15);
	string type = "Jumper";
	enemy->set_type(type);
}

void Jumper::attack(std::vector<Projectile*>* projectile_list, float cangle)
{
	return;
}

int Jumper::get_score_worth() { return 100; }
