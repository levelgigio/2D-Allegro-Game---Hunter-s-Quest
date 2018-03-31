#include "Game.h"

Game::Game(int cdisplay_width, int cdisplay_height) : display_width(cdisplay_width), display_height(cdisplay_height), display(nullptr),
timer(nullptr), event_queue(nullptr), run(true), map(nullptr), menu(nullptr), map_width(0), map_height(0), twoplayers(false) ,
score_delay(0) , second_player_is_dead(false) , player(nullptr) , player2(nullptr)
{
	camera.x = 0;
	camera.y = 0;
}

Game::~Game()
{
}

ALLEGRO_DISPLAY* Game::get_display() const { return display; }
int Game::get_display_width() const { return display_width; }
int Game::get_display_height() const { return display_height; }
Map* Game::get_map() const { return map; }
Player* Game::get_player() const { return player; }
Player* Game::get_player2() const { return player2; }
void Game::set_twoplayers_off() { twoplayers = false; }
void Game::set_twoplayers_on() { twoplayers = true; }
ALLEGRO_EVENT_QUEUE* Game::get_event_queue() const { return event_queue; }
std::vector<Tile*>* Game::get_tile_list() { return &tile_list; }
std::vector<Enemy*>* Game::get_enemy_list() { return &enemy_list; };
std::vector<Projectile*>* Game::get_projectile_list() { return &projectile_list; }
void Game::set_player(Player* cplayer) { player = cplayer; }
void Game::set_player2(Player* cplayer) { player2 = cplayer; }
void Game::set_map_width(const int cmap_width) { map_width = cmap_width; }
const int Game::get_map_width() const { return map_width; }
void Game::set_map_height(const int cmap_height) { map_height = cmap_height; }
const int Game::get_map_height() const { return map_height; }
void Game::set_run_on() { run = true; }
void Game::set_run_off() { run = false; }
const int Game::get_stage() { return stage; }
void Game::set_stage(const int cstage) { stage = cstage; }
const bool Game::get_two_players() { return twoplayers; }
void Game::set_second_player_is_dead(const bool cdead) { second_player_is_dead = cdead; }

void Game::update_camera() {
	camera.x = player->get_x() - display_width / 2;
	camera.y = player->get_y() - display_height * 2 / 3;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > map_width * DEFAULTTILESIZE - display_width)
		camera.x = map_width * DEFAULTTILESIZE - display_width;
	if (camera.y > map_height * DEFAULTTILESIZE - display_height)
		camera.y = map_height * DEFAULTTILESIZE - display_height;
}

int Game::execute()
{
	//inicializa display
	if (!al_init())
		return -1;
	display = al_create_display(display_width, display_height);
	if (!display)
		return -1;

	//inicializacao de addons e perifericos
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	//inicializacao de menu, fontes e timer
	menu = new Menu(this);
	font24 = al_load_font("OldEnglishFive.ttf", 24, 0);
	timer = al_create_timer(1.0 / FPS);

	//registro de eventos
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	map = new Map(this);

	menu->main_menu();

	al_start_timer(timer);
	int score_delay = 0;

	while (run)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (player->get_SP() > 20) {
				al_get_mouse_state(&state);
				playershotangle = atan2(state.y - player->get_y() + camera.y, state.x - player->get_x() + camera.x);
				player->attack(&projectile_list, playershotangle);
				player->set_SP(player->get_SP() - 20);
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				player->set_up_on();
				break;
			case ALLEGRO_KEY_SPACE:
				if (twoplayers)
                {
                    if (player2->get_SP() > 25) {
                        player2->attack(&projectile_list, 0);
                        player2->set_SP(player2->get_SP() - 25);
                    }
                }
				break;
			case ALLEGRO_KEY_A:
				player->set_left_on();
				break;
			case ALLEGRO_KEY_D:
				player->set_right_on();
				break;
			case ALLEGRO_KEY_ESCAPE:
				player->set_left_off();
				player->set_right_off();
				al_stop_timer(timer);
				menu->pause_menu();
				al_start_timer(timer);
				break;
			case ALLEGRO_KEY_LSHIFT:
				player->set_sprint_on();
				break;
			case ALLEGRO_KEY_0:
				if (!twoplayers && !second_player_is_dead) {
					player->set_maxHP(player->get_maxHP() / 2);
					player->set_maxSP(player->get_maxSP() / 2);
					player->set_HP(player->get_HP() / 2);
					player->set_SP(player->get_SP() / 2);
					player2 = new Player(player->get_x(), player->get_y(), 7, 14, true, player->get_maxHP(), player->get_maxSP(), new secondPlayer(player));
					player2->set_HP(player->get_HP());
					player2->set_SP(player->get_SP());
					twoplayers = true;
				}
				break;
			case ALLEGRO_KEY_LEFT:
				if (twoplayers && !second_player_is_dead)
					player2->set_left_on();
				break;
			case ALLEGRO_KEY_RIGHT:
				if (twoplayers  && !second_player_is_dead)
					player2->set_right_on();
				break;
			case ALLEGRO_KEY_UP:
				if (twoplayers && !second_player_is_dead)
					player2->set_up_on();
				break;
			case ALLEGRO_KEY_DOWN:
				if (twoplayers && !second_player_is_dead)
					player2->set_down_on();
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				player->set_up_off();
				break;
			case ALLEGRO_KEY_A:
				player->set_left_off();
				break;
			case ALLEGRO_KEY_D:
				player->set_right_off();
				break;
			case ALLEGRO_KEY_LSHIFT:
				player->set_sprint_off();
				break;
			case ALLEGRO_KEY_LEFT:
				if (twoplayers && !second_player_is_dead)
					player2->set_left_off();
				break;
			case ALLEGRO_KEY_RIGHT:
				if (twoplayers && !second_player_is_dead)
					player2->set_right_off();
				break;
			case ALLEGRO_KEY_UP:
				if (twoplayers && !second_player_is_dead)
					player2->set_up_off();
				break;
			case ALLEGRO_KEY_DOWN:
				if (twoplayers && !second_player_is_dead)
					player2->set_down_off();
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			run = false;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)  //executa FPS vezes por segundo
		{
			static int invtimer = PLAYERINVTIME;
			if (player->get_damaged()) {
				invtimer--;
			}
			if (invtimer <= 0) {
				player->set_damaged_off();
				invtimer = PLAYERINVTIME;
			}

			check_actives();
			map->draw(camera, tile_list);
			move();
			attack();
			collisions();
			update();
			update_camera();
			draw();
			if (score_delay < SCOREDELAY)
				score_delay++;
			else
			{
				score--;
				score_delay = 0;
			}
			al_draw_textf(font24, al_map_rgb(255, 0, 0), display_width / 2, 200, 0, "Score: %i", score);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	delete map;
	delete menu;
	al_destroy_display(display);
	return 0;
}

void Game::move() {

	player->move();
	if (twoplayers && !second_player_is_dead)
		player2->move();
	for (Enemy* enemy : enemy_list)
		enemy->move();
	for (Projectile* projectile : projectile_list)
		projectile->move();
}

void Game::collisions()
{
	for (Tile* tile : tile_list)
	{
		tile->character_collision(player, tile);
		if (player->get_on_ground())
			break;
	}

	for (Enemy* enemy : enemy_list)
	{
		for (Tile* tile : tile_list)
		{
			tile->character_collision(enemy, tile);
			if (enemy->get_on_ground())
				break;
		}
	}

	for (Enemy* enemy : enemy_list)
    {
		enemyKnockbackCollision(player, enemy);
		if (twoplayers && !second_player_is_dead)
            secondPlayerDamageKnockbackCollision(player2, enemy);
    }

	for (Projectile* projectile : projectile_list)
	{
		for (Tile* tile : tile_list)
		{
			tile->projectile_collision(projectile, tile);
			if (projectile->get_x() < 0 || projectile->get_x() > map_width*DEFAULTTILESIZE || projectile->get_y() > map_height*DEFAULTTILESIZE)
				projectile->set_unactive();
			if (!projectile->get_active())
				break;
		}
		if (projectile->get_friendly())
		{
			for (Enemy* enemy : enemy_list)
			{
				if (checkCollision(enemy, projectile))
				{
					enemy->set_HP(enemy->get_HP() - projectile->get_damage());
					enemy->set_damaged_on();
					projectile->set_unactive();
				}
			}
		}
		else if (checkCollision(player, projectile))
		{
			player->set_HP(player->get_HP() - projectile->get_damage());
			projectile->set_unactive();
		}
		else if(twoplayers && !second_player_is_dead && checkCollision(player2, projectile))
        {
            player2->set_HP(player2->get_HP() - projectile->get_damage());
            projectile->set_unactive();
        }
	}
}

void Game::draw() {

	for (Enemy* enemy : enemy_list)
		enemy->draw(camera);

	player->draw(camera);
	if (twoplayers)
		player2->draw(camera);

	for (Projectile* projectile : projectile_list)
		projectile->draw(camera);

}

void Game::update()
{
    if(twoplayers && !second_player_is_dead)
        player2->update();
	player->update();
	for (Enemy* enemy : enemy_list)
		enemy->update();
	if (score_delay < SCOREDELAY)
		score_delay++;
	else
	{
		if(score > 0)
			score--;
		score_delay = 0;
	}
}

void Game::attack() {

	for (Enemy* enemy : enemy_list)
		enemy->attack(&projectile_list, 0);
}

void Game::check_actives() {
    if(twoplayers && !second_player_is_dead)
        if (player2->get_HP() <= 0)
        {
            twoplayers = false;
            second_player_is_dead = true;
        }

	if (player->get_HP() <= 0 || player->get_x() < 0 || player->get_x() > map_width*DEFAULTTILESIZE || player->get_y() > map_height*DEFAULTTILESIZE)
		player->set_unactive();
	if (!player->get_active()) {
		al_stop_timer(timer);
		menu->game_over_menu();
		al_start_timer(timer);
	}
	for (enemyitr = enemy_list.begin(); enemyitr != enemy_list.end();) {
		if ((*enemyitr)->get_HP() <= 0 || (*enemyitr)->get_x() < 0 || (*enemyitr)->get_x() > map_width*DEFAULTTILESIZE || (*enemyitr)->get_y() > map_height*DEFAULTTILESIZE)
			(*enemyitr)->set_unactive();
		if (!(*enemyitr)->get_active()) {
			score += (*enemyitr)->get_score_worth();
			delete (*enemyitr);
			enemyitr = enemy_list.erase(enemyitr);
		}
		else
			enemyitr++;
	}
	for (projectileitr = projectile_list.begin(); projectileitr != projectile_list.end();)
		if (!(*projectileitr)->get_active()) {
			delete (*projectileitr);
			projectileitr = projectile_list.erase(projectileitr);
		}
		else
			projectileitr++;

	for (tileitr = tile_list.begin(); tileitr != tile_list.end();)
		if (!(*tileitr)->get_active()) {
			delete (*tileitr);
			tileitr = tile_list.erase(tileitr);
		}
		else
			tileitr++;

	if (enemy_list.size() == 0)
	{
		al_stop_timer(timer);
		menu->save_score();
		menu->victory_menu();
		al_start_timer(timer);
	}
}

void Game::set_score(const int cscore) { score = cscore; }
int Game::get_score() { return score; }
