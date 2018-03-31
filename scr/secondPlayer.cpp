#include "secondPlayer.h"
#include <iostream>

secondPlayer::secondPlayer(Player* cplayer) : player2(nullptr)
{
	player = cplayer;
}


secondPlayer::~secondPlayer()
{
}

void secondPlayer::set_strategy(Character* ccharacter) {
	player2 = static_cast<Player*>(ccharacter);
	player2->set_animation("player2.png", 1, DEFAULTTILESIZE, DEFAULTTILESIZE);
	string type = "SecondPlayer";
	player2->set_type(type);
}

void secondPlayer::move()
{
	//movimento com o input do usuario

		if ((player2->get_left() && !player2->get_right() && player2->get_vel_x() > -PLAYERSPEED) || player2->get_vel_x() > PLAYERSPEED)
			player2->set_vel_x(player2->get_vel_x() - PLAYERACCELERATION);
		else if ((!player2->get_left() && player2->get_right() && player2->get_vel_x() < PLAYERSPEED) || player2->get_vel_x() < -PLAYERSPEED)
			player2->set_vel_x(player2->get_vel_x() + PLAYERACCELERATION);

		if ((player2->get_left() && player2->get_right()) || (!player2->get_left() && !player2->get_right())) {
			if (player2->get_vel_x() > 0)
				player2->set_vel_x(player2->get_vel_x() - PLAYERACCELERATION);
			else if (player2->get_vel_x() < 0)
				player2->set_vel_x(player2->get_vel_x() + PLAYERACCELERATION);
		}

	if ((player2->get_up() && !player2->get_down() && player2->get_vel_y() > -PLAYERSPEED))
		player2->set_vel_y(player2->get_vel_y() - PLAYERACCELERATION);
	else if ((!player2->get_up() && player2->get_down() && player2->get_vel_y() < PLAYERSPEED))
		player2->set_vel_y(player2->get_vel_y() + PLAYERACCELERATION);

	if ((player2->get_up() && player2->get_down()) || (!player2->get_up() && !player2->get_down())) {
		if (player2->get_vel_y() > 0)
			player2->set_vel_y(player2->get_vel_y() - PLAYERACCELERATION);
		else if (player2->get_vel_y() < 0)
			player2->set_vel_y(player2->get_vel_y() + PLAYERACCELERATION);
	}

	player2->set_x(player2->get_x() + player2->get_vel_x());
	player2->set_y(player2->get_y() + player2->get_vel_y());

	if (square(player2->get_x() - player->get_x()) + square(player2->get_y() - player->get_y()) > square(PLAYERTWOREACH)) {
		float angle = atan2(player2->get_y() - player->get_y(), player2->get_x() - player->get_x());
		player2->set_x(player->get_x()+cos(angle)*PLAYERTWOREACH);
		player2->set_y(player->get_y()+sin(angle)*PLAYERTWOREACH);

	}


}

void secondPlayer::update()
{
    if (player2->get_HP() > 0)
		al_draw_line(1000, 20, player2->get_HP() * 2 + 1000, 20, al_map_rgb(255, 0, 0), 10);
	static int regentimer = PLAYERSPREGENTIMER;
	if (player2->get_SP() > 0) {
		al_draw_line(1000, 30, player2->get_SP() * 2 + 1000, 30, al_map_rgb(0, 255, 0), 10);
	}
	else {
		player2->set_sprint_off();
	}

	if ((!player2->get_sprint() || !player2->get_vel_x()) && (player2->get_SP() < player2->get_maxSP())) {
		if (!regentimer) {
			player2->set_SP(player2->get_SP() + 1);
			regentimer = PLAYERSPREGENTIMER;
		}
		else {
			regentimer--;
		}
	}
	if (player2->get_sprint() && (player2->get_left() || player2->get_right()))
		player2->set_SP(player2->get_SP() - 1);

    if (player2->get_vel_x() > 0)
		player2->set_last_direction(1);
	if (player2->get_vel_x() < 0)
		player2->set_last_direction(-1);
    if (player2->get_vel_y() > 0)
		player2->set_last_direction(-2);
    if (player2->get_vel_y() < 0)
		player2->set_last_direction(2);
}


void secondPlayer::draw(Camera camera)
{
	player2->get_animation()->animate(camera);
}

void secondPlayer::attack(std::vector<Projectile*>* projectile_list, float cangle) {
    if(player2->get_last_direction() == -1 )
        projectile_list->push_back(new Projectile(player2, true, PLAYERDAMAGE, 3.1415));
    else if(player2->get_last_direction() == 1)
        projectile_list->push_back(new Projectile(player2, true, PLAYERDAMAGE, 0));
    else if(player2->get_last_direction() == 2)
        projectile_list->push_back(new Projectile(player2, true, PLAYERDAMAGE, -3.1415/2.0));
    else if(player2->get_last_direction() == -2)
        projectile_list->push_back(new Projectile(player2, true, PLAYERDAMAGE, +3.1415/2.0));
}
