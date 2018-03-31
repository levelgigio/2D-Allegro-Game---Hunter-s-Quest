#include "Character.h"

Character::Character(int cx = 0, int cy = 0, int cbound_x = 0, int cbound_y = 0, bool cactive = false, int cmaxHP = 0)
	: GameEntity(cx, cy, 0, 0, cbound_x, cbound_y, cactive), maxHP(cmaxHP), HP(cmaxHP), last_direction(-1),
	on_ground(false), left(false), right(false), up(false), down(false), sprint(false), damaged(false), gravitytimer(0)
{
}


Character::~Character()
{
}

void Character::set_maxHP(const int cmaxHP) { maxHP = cmaxHP; }
const int Character::get_maxHP() const { return maxHP; }
void Character::set_HP(const int cHP) { HP = cHP; }
const int Character::get_HP() const { return HP; }
void Character::set_on_ground() { on_ground = true; }
void Character::set_off_ground() { on_ground = false; }
const bool Character::get_on_ground() const { return on_ground; }
void Character::set_left_on() { left = true; }
void Character::set_left_off() { left = false; }
bool Character::get_left() { return left; }
void Character::set_right_on() { right = true; }
void Character::set_right_off() { right = false; }
bool Character::get_right() { return right; }
void Character::set_up_on() { up = true; }
void Character::set_up_off() { up = false; }
bool Character::get_up() { return up; }
void Character::set_down_on() { down = true; }
void Character::set_down_off() { down = false; }
bool Character::get_down() { return down; }
void Character::set_sprint_on() { sprint = true; }
void Character::set_sprint_off() { sprint = false; }
bool Character::get_sprint() { return sprint; }
void Character::set_damaged_on() { damaged = true; }
void Character::set_damaged_off() { damaged = false; }
bool Character::get_damaged() { return damaged; }
int Character::get_last_direction() { return last_direction; }
void Character::set_last_direction(int direction) { last_direction = direction; }
void Character::set_type(std::string ctype) { type = ctype; }
std::string Character::get_type() { return type; }
void Character::set_gravity_timer(int cgravitytimer) { gravitytimer = cgravitytimer; }
int Character::get_gravity_timer() { return gravitytimer; }
void Character::set_animation(const char* bitmap, const int max_frames, const int frame_width, const int frame_height)
{
    animation = new Animation(this, bitmap, max_frames, frame_width, frame_height);
}
Animation* Character::get_animation() { return animation; }
