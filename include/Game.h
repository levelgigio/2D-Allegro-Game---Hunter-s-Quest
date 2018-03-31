#pragma once
#include "Player.h"
#include "Enemy.h"
#include "secondPlayer.h"
#include "Colisions.h"
#include "Camera.h"
#include "Map.h"
#include "Menu.h"
#include "Projectile.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_font.h"
#include <vector>
#include "Points.h"

#define FPS 60
#define PLAYERINVTIME 20

#define SCOREDELAY 30

class Map;
class Menu;

class Game
{
private:
	Player*	player;
	Player* player2;
	std::vector<Tile*> tile_list;
	std::vector<Enemy*> enemy_list;
	std::vector<Projectile*> projectile_list;
	std::vector<Tile*>::iterator tileitr;
	std::vector<Enemy*>::iterator enemyitr;
	std::vector<Projectile*>::iterator projectileitr;
	Camera camera;
	Map* map;
	Menu* menu;
	ALLEGRO_FONT *font24;
	int display_width;
	int display_height;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_MOUSE_STATE state;
	ALLEGRO_TIMER *timer;
	int map_width;
	int map_height;
	bool run;
	int stage;
	bool twoplayers;
	int score;
	float playershotangle;
	int score_delay;
	bool second_player_is_dead;
public:
	Game(int cdisplay_width, int cdisplay_height);
	~Game();
	int execute();
	void move();
	void collisions();
	void draw();
	void update();
	void attack();
	void update_camera();
	void check_actives();
	ALLEGRO_DISPLAY* get_display() const;
	int get_display_width() const;
	int get_display_height() const;
	ALLEGRO_EVENT_QUEUE* get_event_queue() const;
	void set_player(Player* cplayer);
	void set_player2(Player* cplayer);
	Player* get_player() const;
	Player* get_player2() const;
	void set_twoplayers_off();
    void set_twoplayers_on();
	std::vector<Tile*>* get_tile_list();
	std::vector<Enemy*>* get_enemy_list();
	std::vector<Projectile*>* get_projectile_list();
	Map* get_map() const;
	void set_map_width(const int cmap_width);
	const int get_map_width() const;
	void set_map_height(const int cmap_height);
	const int get_map_height() const;
	void set_run_on();
	void set_run_off();
	const int get_stage();
	void set_stage(const int cstage);
	void set_score(const int cscore);
	int get_score();
	const bool get_two_players();
	void set_second_player_is_dead(const bool cdead);
};
