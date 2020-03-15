#include "Map.h"
#include <time.h>
#include <random>

#define PLAYERHEALTH 100
#define PLAYERSTAMINA 100
#define JUMPERHEALTH 30
#define SHOOTERHEALTH 20
#define WALKERHEALTH 10
#define BOSSHEALTH 100

Map::Map(Game* cgame) : game(cgame), initialized(false)
{
	spriteload = new TileBitmapLoad;
	spriteload->init();
	srand(time(NULL));
}

Map::~Map() {
	Map_destroy();
	delete spriteload;
}

void Map::MapInit(const string map, bool load) {
	game->set_score(1000);
	ifstream file;
	if (initialized)
		Map_destroy();

	game->set_second_player_is_dead(false);
	game->set_twoplayers_off();

	game->set_player(new Player(0, 0, 11, 14, true, PLAYERHEALTH, PLAYERSTAMINA, new MainPlayer));
	//identifica o tamanho do Map
	int map_width = 0;
	int map_height = 0;
	file.open(map);
	if (!file.fail()) {
		char i;
		file >> i;
		while (i != '*') {
			map_width++;
			file >> i;
		}

		file >> i;
		while (i != '*') {
			map_height++;
			file >> i;
		}
		map_height = (map_height + map_width) / map_width;
	}
	file.close();

	background = al_load_bitmap("background.png");
	game->set_map_width(map_width);
	game->set_map_height(map_height);
	game->get_player()->set_active();
	initialized = true;

	int max_enemys = 0;
	int max_jumper_quantity = 0;
	int max_shooter_quantity = 0;
	int max_walker_quantity = 0;

	//carrega o Map
	file.open(map);
	if (!file.fail()) {
		map_array = new char*[map_height];
		for (int i = 0; i < map_height; i++) {
			map_array[i] = new char[map_width];
			for (int j = 0; j < map_width; j++)
			{
				file >> map_array[i][j];
				if (map_array[i][j] == '*') {
					j--;
					continue;
				}
				if (map_array[i][j] == 'P') {
					game->get_player()->set_x(DEFAULTTILESIZE / 2 + DEFAULTTILESIZE * j);
					game->get_player()->set_y(DEFAULTTILESIZE / 2 + DEFAULTTILESIZE * i);
				}
				if (map_array[i][j] == 'E') {
					enemy_points_vector.push_back(new Points((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE));
					max_enemys++;
				}
				if (map_array[i][j] == '.')
					random_points_vector.push_back(new Points((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE));
				if (map_array[i][j] == 'B')
					game->get_enemy_list()->push_back(new Enemy((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, 9, 13, true, BOSSHEALTH, new Boss(&random_points_vector), game->get_player()));
				if (map_array[i][j] == '@')
					game->get_tile_list()->push_back(new Tile((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, true, new Ground(spriteload->get_sprite(1))));
				if (map_array[i][j] == '#')
					game->get_tile_list()->push_back(new Tile((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, true, new Ground(spriteload->get_sprite(2))));
				if (map_array[i][j] == '_')
					game->get_tile_list()->push_back(new Tile((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, true, new DestroyablePlatform(spriteload->get_sprite(3), spriteload->get_sprite(4))));
				if (map_array[i][j] == '^')
					game->get_tile_list()->push_back(new Tile((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, true, new Spikes(spriteload->get_sprite(6))));
				if (map_array[i][j] == '~')
					game->get_tile_list()->push_back(new Tile((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, true, new Lava(spriteload->get_sprite(5))));
				if (map_array[i][j] == '|')
					game->get_tile_list()->push_back(new Tile((j + 0.5)*DEFAULTTILESIZE, (i + 0.5)*DEFAULTTILESIZE, true, new Ground(spriteload->get_sprite(7))));
			}
		}
	}
	if (!load) {
		//gera quantidade aleatoria de inimigos
		if (max_enemys > 1)
			max_enemys -= (rand() % (max_enemys - 1));
		if (max_enemys) {
			max_jumper_quantity = rand() % max_enemys;
			max_enemys -= max_jumper_quantity;
		}
		if (max_enemys) {
			max_shooter_quantity = rand() % max_enemys;
			max_enemys -= max_shooter_quantity;
		}
		max_walker_quantity = max_enemys;

		for (int i = 0; i < max_jumper_quantity; i++)
		{
			pointsitr = enemy_points_vector.begin();
			pointsitr += rand() % enemy_points_vector.size();
			game->get_enemy_list()->push_back(new Enemy((*pointsitr)->x, (*pointsitr)->y, 10, 14, true, JUMPERHEALTH, new Jumper, game->get_player()));
			enemy_points_vector.erase(pointsitr);
		}
		for (int i = 0; i < max_shooter_quantity; i++)
		{
			pointsitr = enemy_points_vector.begin();
			pointsitr += rand() % enemy_points_vector.size();
			game->get_enemy_list()->push_back(new Enemy((*pointsitr)->x, (*pointsitr)->y, 11, 14, true, SHOOTERHEALTH, new Shooter, game->get_player()));
			enemy_points_vector.erase(pointsitr);
		}
		for (int i = 0; i < max_walker_quantity; i++)
		{
			pointsitr = enemy_points_vector.begin();
			pointsitr += rand() % enemy_points_vector.size();
			game->get_enemy_list()->push_back(new Enemy((*pointsitr)->x, (*pointsitr)->y, 9, 14, true, WALKERHEALTH, new Walker, game->get_player()));
			enemy_points_vector.erase(pointsitr);
		}
	}
	file.close();
}

void Map::Map_destroy() {
	while (game->get_enemy_list()->size() > 0) {
		game->get_enemy_list()->back()->destroy_strategy();
		delete game->get_enemy_list()->back();
		game->get_enemy_list()->pop_back();
	}
	while (game->get_tile_list()->size() > 0) {
		game->get_tile_list()->back()->destroy_strategy();
		delete game->get_tile_list()->back();
		game->get_tile_list()->pop_back();
	}
	while (game->get_projectile_list()->size() > 0) {
		delete game->get_projectile_list()->back();
		game->get_projectile_list()->pop_back();
	}
	while (enemy_points_vector.size() > 0) {
		delete enemy_points_vector.back();
		enemy_points_vector.pop_back();
	}
	while (random_points_vector.size() > 0) {
		delete random_points_vector.back();
		random_points_vector.pop_back();
	}
	game->set_map_width(0);
	game->set_map_height(0);
	if(game->get_player())
        delete game->get_player();
	if (game->get_two_players())
		delete game->get_player2();
}

void Map::draw(Camera camera, std::vector<Tile*>& Tile_list)
{
	al_draw_scaled_bitmap(background, 0, 0, 1920, 1200, 0, 0, 1280, 720, 0);

	for (Tile* ground : Tile_list)
		ground->draw(camera);
}


void Map::save_map()
{
	ofstream save_file;
	save_file.open("save.bin", ios::out | ios::trunc);
	if (save_file.is_open())
	{
		save_file << game->get_stage() << endl;
		save_file << game->get_score() << endl;
		save_file << game->get_two_players() << endl;
	    if(game->get_two_players())
        {
            save_file << game->get_player2()->get_maxHP() << endl;
			save_file << game->get_player2()->get_HP() << endl;
			save_file << game->get_player2()->get_maxSP() << endl;
			save_file << game->get_player2()->get_SP() << endl;
            save_file << game->get_player2()->get_x() << endl;
            save_file << game->get_player2()->get_y() << endl;
            save_file << game->get_player2()->get_last_direction() << endl;
            save_file << game->get_player2()->get_bound_x() << endl;
            save_file << game->get_player2()->get_bound_y() << endl;
        }
		save_file << game->get_player()->get_HP() << endl;
		save_file << game->get_player()->get_SP() << endl;
		save_file << game->get_player()->get_x() << endl;
		save_file << game->get_player()->get_y() << endl;
		save_file << game->get_player()->get_last_direction() << endl;
		save_file << game->get_player()->get_bound_x() << endl;
		save_file << game->get_player()->get_bound_y() << endl;
		for (Enemy* enemy : (*game->get_enemy_list()))
		{
			save_file << enemy->get_maxHP() << endl;
			save_file << enemy->get_HP() << endl;
			save_file << enemy->get_x() << endl;
			save_file << enemy->get_y() << endl;
			save_file << enemy->get_last_direction() << endl;
			save_file << enemy->get_bound_x() << endl;
			save_file << enemy->get_bound_y() << endl;
			save_file << enemy->get_type() << endl;
		}
		save_file << "-----" << endl;
		for (Projectile* projectile : (*game->get_projectile_list()))
		{
			save_file << projectile->get_x() << endl;
			save_file << projectile->get_y() << endl;
			save_file << projectile->get_angle() << endl;
			save_file << projectile->get_damage() << endl;
		}
		save_file << "-----" << endl;
	}
	save_file.close();
}

bool Map::load_map()
{
	ifstream save_file;
	string line;
	int  mhp, hp, msp, sp, x, y, ld, bx, by, pdmg;
	float angle;
	save_file.open("save.bin", ios::in);
	if (save_file.is_open())
	{
		//Stage Attibutes
		getline(save_file, line);
		game->get_map()->MapInit("map_" + line + ".txt", true);
		getline(save_file, line);
		game->set_score(atoi(line.c_str()));

		while (game->get_enemy_list()->size() > 0) {
			game->get_enemy_list()->back()->destroy_strategy();
			delete game->get_enemy_list()->back();
			game->get_enemy_list()->pop_back();
		}
		while (game->get_projectile_list()->size() > 0) {
			delete game->get_projectile_list()->back();
			game->get_projectile_list()->pop_back();
		}
		//SecondPlayer attributes
		getline(save_file, line);
		if(atoi(line.c_str()) == 1)
        {
            game->set_twoplayers_on();
            getline(save_file, line);
            mhp = atoi(line.c_str());
            getline(save_file, line);
            hp = atoi(line.c_str());
            getline(save_file, line);
            msp = atoi(line.c_str());
            getline(save_file, line);
            sp = atoi(line.c_str());
            getline(save_file, line);
            x = atoi(line.c_str());
            getline(save_file, line);
            y = atoi(line.c_str());
            getline(save_file, line);
            ld = atoi(line.c_str());
            getline(save_file, line);
            bx = atoi(line.c_str());
            getline(save_file, line);
            by = atoi(line.c_str());
            game->set_player2(new Player(x, y, bx, by, true, mhp, msp, new secondPlayer(game->get_player())));
            game->get_player2()->set_HP(hp);
            game->get_player2()->set_SP(sp);
        }
        else
        {
            game->set_twoplayers_off();
        }
		//Player Attributes

		getline(save_file, line);
		game->get_player()->set_HP(atoi(line.c_str()));
		getline(save_file, line);
		game->get_player()->set_SP(atoi(line.c_str()));
		getline(save_file, line);
		game->get_player()->set_x(atoi(line.c_str()));
		getline(save_file, line);
		game->get_player()->set_y(atoi(line.c_str()));
		getline(save_file, line);
		game->get_player()->set_last_direction(atoi(line.c_str()));
		getline(save_file, line);
		game->get_player()->set_bound_x(atoi(line.c_str()));
		getline(save_file, line);
		game->get_player()->set_bound_y(atoi(line.c_str()));
		//Projectile Attributes
		getline(save_file, line);
		while (!(line == "-----"))
		{
			mhp = atoi(line.c_str());
			getline(save_file, line);
			hp = atoi(line.c_str());
			getline(save_file, line);
			x = atoi(line.c_str());
			getline(save_file, line);
			y = atoi(line.c_str());
			getline(save_file, line);
			ld = atoi(line.c_str());
			getline(save_file, line);
			bx = atoi(line.c_str());
			getline(save_file, line);
			by = atoi(line.c_str());
			getline(save_file, line);
			if (line == "Jumper")
				game->get_enemy_list()->push_back(new Enemy(x, y, bx, by, true, mhp, new Jumper, game->get_player()));
			else if (line == "Shooter")
				game->get_enemy_list()->push_back(new Enemy(x, y, bx, by, true, mhp, new Shooter, game->get_player()));
			else if (line == "Walker")
				game->get_enemy_list()->push_back(new Enemy(x, y, bx, by, true, mhp, new Walker, game->get_player()));
			else if (line == "Boss")
				game->get_enemy_list()->push_back(new Enemy(x, y, bx, by, true, mhp, new Boss(&random_points_vector), game->get_player()));
			game->get_enemy_list()->back()->set_last_direction(ld);
			getline(save_file, line);
		}
		//Projectile Attributes
		getline(save_file, line);
		while (!(line == "-----"))
		{
			x = atoi(line.c_str());
			getline(save_file, line);
			y = atoi(line.c_str());
			getline(save_file, line);
			angle = atof(line.c_str());
			getline(save_file, line);
			pdmg = atoi(line.c_str());
			game->get_projectile_list()->push_back(new Projectile(x, y, angle, pdmg));
			getline(save_file, line);
		}
		save_file.close();
		return true;
	}
	else
		return false;
}
