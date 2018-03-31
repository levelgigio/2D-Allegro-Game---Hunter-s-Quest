#pragma once
#include "Character.h"
#include "CharacterInterface.h"

class Player :
	public Character
{
private:
	CharacterInterface* strategy;
	int SP;
	int maxSP;
public:
	Player(int cx, int cy, int cbound_x, int cbound_y, bool cactive, int cmaxHP, int cmaxSP, CharacterInterface* cstrategy);
	~Player();
	void set_SP(const int cSP);
	const int get_SP() const;
	void set_maxSP(const int cmaxSP);
	const int get_maxSP() const;
	void attack(std::vector<Projectile*>* projectile_list, float cangle);
	void update();
	void draw(Camera camera);
	void move();
	void set_strategy(CharacterInterface* cstrategy);
	void destroy_strategy();
};
