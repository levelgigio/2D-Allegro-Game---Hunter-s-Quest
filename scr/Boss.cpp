#pragma once
#include "Boss.h"
#include <random>
#include <time.h>

Boss::Boss(std::vector<Points*>* crandom_points) : enemy(nullptr), gravitytimer(0) , shoot_timer(0) , shoot_delay(0)
{
	random_points = crandom_points;
	srand(time(NULL));
}

Boss::~Boss()
{
}

void Boss::move()
{
	if (enemy->get_damaged()) {
		int point = rand() % random_points->size();
		enemy->set_x(random_points->at(point)->x);
		enemy->set_y(random_points->at(point)->y);
		enemy->set_damaged_off();
	}
	int direcao_x = 0;

	if (enemy->get_player()->get_x() > enemy->get_x())
		direcao_x = 1;
	else if (enemy->get_player()->get_x() < enemy->get_x())
		direcao_x = -1;
	else
		direcao_x = 0;

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

	if (enemy->get_on_ground() && !(jump_timer % ENEMYJUMPTIMER))
    {
		enemy->set_vel_y(-BOSSJUMP);
		jump_timer = 0;
    }
	if (abs(enemy->get_x() - enemy->get_player()->get_x()) < BOSSCHASEDISTANCEX &&
		abs(enemy->get_y() - enemy->get_player()->get_y()) < BOSSCHASEDISTANCEY)
		enemy->set_vel_x(BOSSSPEED*direcao_x);
	else
		enemy->set_vel_x(0);

    jump_timer++;
	enemy->set_x(enemy->get_x() + enemy->get_vel_x());
	enemy->set_y(enemy->get_y() + enemy->get_vel_y());
}

void Boss::draw(Camera camera)
{
	enemy->get_animation()->animate(camera);
	if (enemy->get_HP() > 0)
		al_draw_line(enemy->get_x() - 5*enemy->get_bound_x() - camera.x, enemy->get_y() - enemy->get_bound_y() - camera.y - 5,
			enemy->get_x() - 5*enemy->get_bound_x() + 10 * enemy->get_bound_x()*(enemy->get_HP() / (float)enemy->get_maxHP()) - camera.x,
			enemy->get_y() - enemy->get_bound_y() - camera.y - 5, al_map_rgb(255, 0, 0), 10);
}

void Boss::update()
{
	if (enemy->get_vel_x() > 0)
		enemy->set_last_direction(1);
	if (enemy->get_vel_x() < 0)
		enemy->set_last_direction(-1);
}

void Boss::set_strategy(Character* ccharacter)
{
	enemy = static_cast<Enemy*>(ccharacter);
	enemy->set_animation("boss.png", 3, DEFAULTTILESIZE, DEFAULTTILESIZE);
	enemy->set_damage(5);
	string type = "Boss";
	enemy->set_type(type);
}

void Boss::attack(std::vector<Projectile*>* projectile_list, float cangle)
{
	if (square(enemy->get_x() - enemy->get_player()->get_x()) + square(enemy->get_y() - enemy->get_player()->get_y()) < square(BOSSATTACKRADIUS) && shoot_timer < SHOOTTIMING)
	{
		if (enemy->get_last_direction()*(enemy->get_x() - enemy->get_player()->get_x()) < 0)
			projectile_list->push_back(new Projectile(enemy, enemy->get_player(), false, 2));
        shoot_timer++;

	}
	else
        {
            shoot_delay++;
            if(shoot_delay == SHOOTDELAY)
            {
                shoot_delay = 0;
                shoot_timer = 0;
            }
        }
}

int Boss::get_score_worth() { return 1000; }
