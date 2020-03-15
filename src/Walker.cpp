#pragma once
#include "Walker.h"
#include <random>
#include <time.h>

Walker::Walker() : gravitytimer(0), fixed_y(-1)
{
	srand(time(NULL));
}

Walker::~Walker()
{
}

void Walker::move()
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

void Walker::attack(std::vector<Projectile*>* projectile_list, float cangle)
{
	return;
}

void Walker::draw(Camera camera)
{
	enemy->get_animation()->animate(camera);
	al_draw_line(enemy->get_x() - enemy->get_bound_x() - camera.x, enemy->get_y() - enemy->get_bound_y() - camera.y - 5,
		enemy->get_x() - enemy->get_bound_x() + 2 * enemy->get_bound_x()*(enemy->get_HP() / (float)enemy->get_maxHP()) - camera.x,
		enemy->get_y() - enemy->get_bound_y() - camera.y - 5, al_map_rgb(255, 0, 0), 2);
}

void Walker::update()
{
	if (enemy->get_vel_x() > 0)
		enemy->set_last_direction(1);
	if (enemy->get_vel_x() < 0)
		enemy->set_last_direction(-1);
}

void Walker::set_strategy(Character* ccharacter)
{
	enemy = static_cast<Enemy*>(ccharacter);
	enemy->set_animation("walker.png", 3, DEFAULTTILESIZE, DEFAULTTILESIZE);
	enemy->set_damage(15);
	string type = "Walker";
	enemy->set_type(type);
	enemy->set_last_direction(1);
}

int Walker::get_score_worth() { return 50; }
