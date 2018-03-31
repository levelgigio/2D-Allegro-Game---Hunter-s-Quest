#pragma once
#include "Game.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_font.h"

#define MENU1OPTIONS 3 //menu principal
#define MENU2OPTIONS 3 //menu de selecao de nivel
#define MENU3OPTIONS 4 //menu de pause
#define MENU4OPTIONS 2 //menu de game over
#define MENU5OPTIONS 2 //menu de vitoria

class Game;

class Menu
{
private:
	std::vector<ALLEGRO_BITMAP*> menu;
	Game* game;
	ALLEGRO_FONT *font1;
	ALLEGRO_FONT *font2;
public:
	Menu(Game* cgame);
	~Menu();
	void main_menu();
	int select_level();
	void pause_menu();
	void game_over_menu();
	void victory_menu();
	void save_score();
};