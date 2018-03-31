#include "MainPlayer.h"

MainPlayer::MainPlayer() : player(nullptr)
{
}


MainPlayer::~MainPlayer()
{
}

void MainPlayer::set_strategy(Character* ccharacter) {
	player = static_cast<Player*>(ccharacter);
	player->set_animation("mainplayer.png", 3, DEFAULTTILESIZE, DEFAULTTILESIZE);
	string type = "MainPlayer";
	player->set_type(type);
	player->set_damage(10);
}

void MainPlayer::move()
{
	//gravidade
	if (player->get_on_ground())
		player->set_gravity_timer(0);
	if (!player->get_on_ground() && !player->get_gravity_timer()) {
		player->set_vel_y(player->get_vel_y() + 1);
	}
	player->set_gravity_timer(player->get_gravity_timer()+1);
	if (player->get_gravity_timer() > GRAVITYTIMER)
		player->set_gravity_timer(0);

	//velocidade terminal

	if (player->get_vel_y() > 16)
		player->set_vel_y(16);

	//movimento com o input do usuario
	int dash;

	if (!player->get_damaged()) {
		if (player->get_sprint())
			dash = 2;
		else
			dash = 1;

		if ((player->get_left() && !player->get_right() && player->get_vel_x() > -dash * PLAYERSPEED) || player->get_vel_x() > dash*PLAYERSPEED)
			player->set_vel_x(player->get_vel_x() - PLAYERACCELERATION);
		else if ((!player->get_left() && player->get_right() && player->get_vel_x() < dash * PLAYERSPEED) || player->get_vel_x() < -dash*PLAYERSPEED)
			player->set_vel_x(player->get_vel_x() + PLAYERACCELERATION);

		if ((player->get_left() && player->get_right()) || (!player->get_left() && !player->get_right())) {
			if (player->get_vel_x() > 0)
				player->set_vel_x(player->get_vel_x() - PLAYERACCELERATION);
			else if (player->get_vel_x() < 0)
				player->set_vel_x(player->get_vel_x() + PLAYERACCELERATION);
		}

		if (player->get_up() && player->get_on_ground())
			player->set_vel_y(-PLAYERJUMP);
	}

	player->set_x(player->get_x() + player->get_vel_x());
	player->set_y(player->get_y() + player->get_vel_y());
}

void MainPlayer::update()
{
	if (player->get_HP() > 0)
		al_draw_line(20, 20, player->get_HP() * 2 + 20, 20, al_map_rgb(255, 0, 0), 10);

	static int regentimer = PLAYERSPREGENTIMER;
	if (player->get_SP() > 0) {
		al_draw_line(20, 30, player->get_SP() * 2 + 20, 30, al_map_rgb(0, 255, 0), 10);
	}
	else {
		player->set_sprint_off();
	}

	if ((!player->get_sprint() || !player->get_vel_x()) && (player->get_SP() < player->get_maxSP())) {
		if (!regentimer) {
			player->set_SP(player->get_SP() + 1);
			regentimer = PLAYERSPREGENTIMER;
		}
		else {
			regentimer--;
		}
	}

	if (player->get_sprint() && !player->get_damaged() && (player->get_left() || player->get_right()))
		player->set_SP(player->get_SP() - 1);

    if (player->get_vel_x() > 0)
		player->set_last_direction(1);
	if (player->get_vel_x() < 0)
		player->set_last_direction(-1);
}


void MainPlayer::draw(Camera camera)
{
	player->get_animation()->animate(camera);
}

void MainPlayer::attack(std::vector<Projectile*>* projectile_list, float cangle) {
    projectile_list->push_back(new Projectile(player, true, PLAYERDAMAGE, cangle));
}
