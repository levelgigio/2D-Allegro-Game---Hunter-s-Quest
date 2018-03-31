#include "Menu.h"

enum {
	main_menu_image, level_select_menu_image, pause_menu_image, game_over_menu_image, victory_menu_image, menu_selection_arrow
};

Menu::Menu(Game* cgame) : game(cgame)
{
	menu.push_back(al_load_bitmap("main_menu.png"));
	menu.push_back(al_load_bitmap("level_select_menu.png"));
	menu.push_back(al_load_bitmap("pause_menu.png"));
	menu.push_back(al_load_bitmap("game_over_menu.png"));
	menu.push_back(al_load_bitmap("victory_menu.png"));
	menu.push_back(al_load_bitmap("menu_selection_arrow.png"));
	font1 = al_load_font("OldEnglishFive.ttf", 64, 0);
	font2 = al_load_font("OldEnglishFive.ttf", 32, 0);
}

Menu::~Menu()
{
}

void Menu::main_menu()
{

	bool done = false;
	int option = 1;

	while (!done) {
		ALLEGRO_EVENT ev;
		al_draw_scaled_bitmap(menu.at(main_menu_image), 0, 0, 1280, 720, 0, 0, game->get_display_width(), game->get_display_height(), 0);
		switch (option) {
		case 1:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 3 / 9, 0);
			break;
		case 2:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 5 / 9, 0);
			break;
		case 3:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 7 / 9, 0);
			break;
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_wait_for_event(game->get_event_queue(), &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				if (option < MENU1OPTIONS)
					option++;
				break;
			case ALLEGRO_KEY_UP:
				if (option > 1)
					option--;
				break;
			case ALLEGRO_KEY_ENTER:
				if (option == 1) {
					int sucess = select_level();
					if (sucess == -1) {
						done = true;
						game->set_run_off();
						return;
					}
					else if (sucess)
						return;
					else
						break;
				}
				else if (option == 2) {
					if (game->get_map()->load_map())
						return;
				}
				else if (option == 3) {
					done = true;
					game->set_run_off();
				}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
			game->set_run_off();
		}
	}
}

int Menu::select_level() {

	bool done = false;

	int option = 1;

	while (!done) {
		ALLEGRO_EVENT ev;
		al_draw_scaled_bitmap(menu.at(level_select_menu_image), 0, 0, 1280, 720, 0, 0, game->get_display_width(), game->get_display_height(), 0);
		switch (option) {
		case 1:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 3 / 9, 0);
			break;
		case 2:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 5 / 9, 0);
			break;
		case 3:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 7 / 9, 0);
			break;
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_wait_for_event(game->get_event_queue(), &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				if (option < MENU2OPTIONS)
					option++;
				break;
			case ALLEGRO_KEY_UP:
				if (option > 1)
					option--;
				break;
			case ALLEGRO_KEY_ENTER:
				game->set_stage(option);
				game->get_map()->MapInit("map_" + to_string(option) + ".txt", false);
				return 1;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return -1;
		}
	}
	return 0;
}

void Menu::pause_menu() {
	bool done = false;
	int option = 1;

	while (!done) {
		ALLEGRO_EVENT ev;
		al_draw_scaled_bitmap(menu.at(pause_menu_image), 0, 0, 1280, 720, 0, 0, game->get_display_width(), game->get_display_height(), 0);
		switch (option) {
		case 1:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 1 / 9, 0);
			break;
		case 2:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 3 / 9, 0);
			break;
		case 3:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 5 / 9, 0);
			break;
		case 4:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 7 / 9, 0);
			break;
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_wait_for_event(game->get_event_queue(), &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				if (option < MENU3OPTIONS)
					option++;
				break;
			case ALLEGRO_KEY_UP:
				if (option > 1)
					option--;
				break;
			case ALLEGRO_KEY_ENTER:
				if (option == 1)
					done = true;
				else if (option == 2) {
					game->get_map()->save_map();
					return;
				}
				else if (option == 3) {
					main_menu();
					return;
				}
				else if (option == 4) {
					game->get_map()->save_map();
					done = true;
					game->set_run_off();
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			game->set_run_off();
			return;
		}
	}
}

void Menu::game_over_menu() {
	bool done = false;
	int option = 1;

	while (!done) {
		ALLEGRO_EVENT ev;
		al_draw_scaled_bitmap(menu.at(game_over_menu_image), 0, 0, 1280, 720, 0, 0, game->get_display_width(), game->get_display_height(), 0);
		switch (option) {
		case 1:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 3 / 9, 0);
			break;
		case 2:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() * 2 / 3, game->get_display_height() * 5 / 9, 0);
			break;
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_wait_for_event(game->get_event_queue(), &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				if (option < MENU4OPTIONS)
					option++;
				break;
			case ALLEGRO_KEY_UP:
				if (option > 1)
					option--;
				break;
			case ALLEGRO_KEY_ENTER:
				if (option == 1) {
					main_menu();
					return;
				}
				else if (option == 2) {
					done = true;
					game->set_run_off();
				}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			game->set_run_off();
			return;
		}
	}
}

void Menu::victory_menu() {
	bool done = false;
	int option = 1;

	ifstream infile;
	string line;
	int scores[6];

	infile.open(("ranking_" + to_string(game->get_stage()) + ".txt"), ios::in);
	if (infile.is_open()) {
		for (int i = 0; i < 6; i++) {
			getline(infile, line);
			scores[i] = atoi(line.c_str());
		}
		infile.close();
	}


	while (!done) {
		ALLEGRO_EVENT ev;
		al_draw_scaled_bitmap(menu.at(victory_menu_image), 0, 0, 1280, 720, 0, 0, game->get_display_width(), game->get_display_height(), 0);
		al_draw_textf(font1, al_map_rgb(255, 0, 0), game->get_display_width() * 1 / 4, 170, ALLEGRO_ALIGN_CENTER, "Score: %i", game->get_score());
		al_draw_textf(font1, al_map_rgb(255, 0, 0), game->get_display_width() * 3 / 4, 170, ALLEGRO_ALIGN_CENTER, "Record: %i", scores[0]);
		al_draw_text(font2, al_map_rgb(255, 0, 0), game->get_display_width() * 3 / 4, 300, ALLEGRO_ALIGN_CENTER, "ranking:");
		for (int i = 1; i < 5; i++)
			al_draw_textf(font2, al_map_rgb(255, 0, 0), game->get_display_width() * 3 / 4, 300 + 64 * i, ALLEGRO_ALIGN_CENTER, "%i", scores[i]);
		switch (option) {
		case 1:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() / 2 - 100, game->get_display_height() * 4 / 9 + 50, 0);
			break;
		case 2:
			al_draw_bitmap(menu.at(menu_selection_arrow), game->get_display_width() / 2 - 100, game->get_display_height() * 7 / 9, 0);
			break;
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_wait_for_event(game->get_event_queue(), &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				if (option < MENU5OPTIONS)
					option++;
				break;
			case ALLEGRO_KEY_UP:
				if (option > 1)
					option--;
				break;
			case ALLEGRO_KEY_ENTER:
				if (option == 1) {
					main_menu();
					return;
				}
				else if (option == 2) {
					done = true;
					game->set_run_off();
				}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			game->set_run_off();
			return;
		}
	}
}



void Menu::save_score()
{
	ifstream infile;
	ofstream outfile;
	string line;
	int score = game->get_score();
	int recentscore[6] = { 0,0,0,0,0,score };
	//se houver um arquivo com pontuacoes anteriores, salva seu valores
	infile.open(("ranking_" + to_string(game->get_stage()) + ".txt"), ios::in);
	if (infile.is_open()) {
		for (int i = 0; i < 5; i++) {
			getline(infile, line);
			recentscore[i] = atoi(line.c_str());
		}
		infile.close();
	}
	//ordena os scores
	int max = 0;
	int maxpos = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = i; j < 6; j++) {
			if (recentscore[j] > max) {
				max = recentscore[j];
				maxpos = j;
			}
		}
		swap(recentscore[i], recentscore[maxpos]);
		max = 0;
		maxpos = i+1;
	}

	//sobrescreve o arquivo com as pontuacoes, ou cria um se nao houver
	outfile.open(("ranking_" + to_string(game->get_stage()) + ".txt"), ios::out | ios::trunc);
	if (outfile.is_open()) {
		for (int i = 0; i < 5; i++)
			outfile << recentscore[i] << endl;
		outfile.close();
	}
}
