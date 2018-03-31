#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "GameEntity.h"
#include <string>

class Character;


class Animation
{
private:
	ALLEGRO_BITMAP* sprite;
	int max_frames;
	int current_frame;
	int frame_width;
	int frame_height;
	short int frame_delay;
	short int frame_count;
	short int last_direction;
	Character* character;
public:
	void animate(Camera camera);
	Animation(Character* ccharacter, const char* bitmap, const int max_frames,
		const int frame_width, const int frame_height);
};

