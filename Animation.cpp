#pragma once
#include "Animation.h"
#include "Character.h"

Animation::Animation(Character* ccharacter, const char* bitmap, const int max_frames,
	const int frame_width, const int frame_height) :
	character(ccharacter), max_frames(max_frames), frame_width(frame_width), frame_height(frame_height),
	current_frame(0), frame_delay(5), frame_count(0)
{
	sprite = al_load_bitmap(bitmap);
	al_convert_mask_to_alpha(sprite, al_map_rgb(255, 0, 255));
}

void Animation::animate(Camera camera)
{
	frame_count++;
	if (frame_count == frame_delay)
	{
		current_frame++;
		current_frame %= max_frames;
		frame_count = 0;
	}

	bool t[] = { false, false, false, false };
	if (character->get_vel_x() < 0)
		t[0] = character->get_vel_x() / character->get_vel_x();
	else if (character->get_vel_x() > 0)
		t[1] = character->get_vel_x() / character->get_vel_x();
	if (character->get_vel_y() < 0)
		t[2] = character->get_vel_y() / character->get_vel_y();
	else if (character->get_vel_y() > 0)
		t[3] = character->get_vel_y() / character->get_vel_y();

	int i;
	for (i = 0; i < 4; i++)
		if (t[i])
		{
			al_draw_bitmap_region(sprite, current_frame*frame_width, i*frame_height, frame_height, frame_width,
				character->get_x() - camera.x - frame_width / 2, character->get_y() - camera.y - frame_height / 2, 0);
			last_direction = i;
			break;
		}
	if (i == 4)
		al_draw_bitmap_region(sprite, 0 * frame_width, last_direction*frame_height, frame_height, frame_width,
			character->get_x() - camera.x - frame_width / 2, character->get_y() - camera.y - frame_height / 2, 0);
}
