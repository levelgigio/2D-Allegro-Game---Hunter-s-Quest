#pragma once
#include "Camera.h"

#define DEFAULTTILESIZE 32
#define DEFAULTSPRITESIZE 256

class GameEntity
{
protected:
	int x, y, vel_x, vel_y, bound_x, bound_y;
	bool active;
	int damage;
public:
	GameEntity(int cx, int cy, int cvel_x, int cvel_y, int cbound_x, int cbound_y, bool cactive);
	~GameEntity();
	void set_x(const int cx);
	const int get_x() const;
	void set_y(const int cy);
	const int get_y() const;
	void set_vel_x(const int cvel_x);
	const int get_vel_x() const;
	void set_vel_y(const int cvel_y);
	const int get_vel_y() const;
	void set_bound_x(const int cbound_x);
	const int get_bound_x() const;
	void set_bound_y(const int cbound_y);
	const int get_bound_y() const;
	void set_active();
	void set_unactive();
	void set_damage(const int cdamage);
	const int get_damage() const;
	const bool get_active() const;
	virtual void draw(Camera camera) = 0;
};