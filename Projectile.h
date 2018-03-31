#pragma once
#include "Character.h"
#include "allegro5/allegro_image.h"
#include <ctgmath>
#include "ProjectileBitmapLoad.h"

#define PROJECTILEVELOCITY 10

class Character;
class GameInterface;

using namespace std;

class Projectile :
	public GameEntity
{
private:
	bool is_friendly;
	ALLEGRO_BITMAP* sprite;
	float angle;
	static ProjectileBitmapLoad* spriteload;
public:
	Projectile(Character* source, Character* target, bool friendly, int damage);
	Projectile(Character* source, bool friendly, int cdamage, float cangle);
	Projectile(int cx, int cy, float angle, int cdamage);
	~Projectile();
	bool get_friendly();
	void set_friendly(bool cis_friendly);
	void update();
	void move();
	void draw(Camera camera);
	void set_angle(float cangle);
	float get_angle() const;
};
