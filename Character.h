#pragma once
#include "GameEntity.h"
#include <string>
#include "Animation.h"
#include "allegro5/allegro_primitives.h"

class Character :
	public GameEntity
{
private:
	int maxHP;
	int HP;
	int damage;
	bool on_ground;
	bool left;
	bool right;
	bool up;
	bool down;
	bool sprint;
	bool damaged;
	int last_direction;
	int gravitytimer;
	std::string type;
	Animation* animation;
public:
	Character(int cx, int cy, int cbound_x, int cbound_y, bool cactive, int cmaxHP);
	virtual ~Character();
	void set_maxHP(const int cmaxHP);
	const int get_maxHP() const;
	void set_HP(const int cHP);
	const int get_HP() const;
	void set_on_ground();
	void set_off_ground();
	const bool get_on_ground() const;
	void set_left_on();
	void set_left_off();
	bool get_left();
	void set_right_on();
	void set_right_off();
	bool get_right();
	void set_up_on();
	void set_up_off();
	bool get_up();
	void set_down_on();
	void set_down_off();
	bool get_down();
	void set_sprint_on();
	void set_sprint_off();
	bool get_sprint();
	void set_damaged_on();
	void set_damaged_off();
	bool get_damaged();
	int get_last_direction();
	void set_last_direction(int direction);
	virtual void update() = 0;
	virtual void draw(Camera camera) = 0;
	virtual void move() = 0;
	virtual void set_type(std::string ctype);
	virtual std::string get_type();
	void set_animation(const char* bitmap, const int max_frames, const int frame_width, const int frame_height);
	Animation* get_animation();
	void set_gravity_timer(int cgravitytimer);
	int get_gravity_timer();
};

