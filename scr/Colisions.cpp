#include "Colisions.h"

#define MAXGAMESPEED 5
#define KNOCKBACK 5

void secondPlayerDamageKnockbackCollision(Character* player, GameEntity* object) {

	//Minkowski sum collision method

	int w = player->get_bound_x() + object->get_bound_x();
	int h = player->get_bound_y() + object->get_bound_y();
	int dx = player->get_x() - object->get_x();
	int dy = player->get_y() - object->get_y();


	if (abs(dx) <= w && abs(dy) <= h) //collision
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx) {
			if (wy > -hx) {
				//bottom collision
				player->set_y(object->get_y() + object->get_bound_y() + player->get_bound_y());
				player->set_vel_y(2 * KNOCKBACK);
                player->set_HP(player->get_HP() - object->get_damage());
			}
			else {
				//left collision
				player->set_x(object->get_x() - object->get_bound_x() - player->get_bound_x());
				player->set_vel_x(-2*KNOCKBACK);
				player->set_vel_y(-2*KNOCKBACK);
                player->set_HP(player->get_HP() - object->get_damage());
			}
		}
		else {
			if (wy > -hx) {
				//right collision
				player->set_x(object->get_x() + object->get_bound_x() + player->get_bound_x());
				player->set_vel_x(2*KNOCKBACK);
				player->set_vel_y(-2*KNOCKBACK);
                player->set_HP(player->get_HP() - object->get_damage());
			}
			else {
				//top collision
				player->set_y(object->get_y() - object->get_bound_y() - player->get_bound_y());
				player->set_vel_y(-2 * KNOCKBACK);
                player->set_HP(player->get_HP() - object->get_damage());
			}
		}
	}
}

bool solidCollision(Character* character, GameEntity* object) {

	//Minkowski sum collision method
	character->set_y(character->get_y() + 1);

	int w = character->get_bound_x() + object->get_bound_x();
	int h = character->get_bound_y() + object->get_bound_y();
	int dx = character->get_x() - object->get_x();
	int dy = character->get_y() - object->get_y();


	if (abs(dx) <= w && abs(dy) <= h) //collision
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx) {
			if (wy > -hx) {
				//bottom collision
				character->set_y(object->get_y() + object->get_bound_y() + character->get_bound_y());
				character->set_vel_y(0);
			}
			else {
				//left collision
				character->set_x(object->get_x() - object->get_bound_x() - character->get_bound_x() - 1);
				if (!character->get_damaged())
					character->set_vel_x(0);
			}
		}
		else {
			if (wy > -hx) {
				//right collision
				character->set_x(object->get_x() + object->get_bound_x() + character->get_bound_x() + 1);
				if (!character->get_damaged())
					character->set_vel_x(0);
			}
			else {
				//top collision
				character->set_y(object->get_y() - object->get_bound_y() - character->get_bound_y());
				character->set_vel_y(0);
				character->set_on_ground();
				character->set_up_off();

			}
		}
		character->set_y(character->get_y() - 1);
		return true;
	}
	else {
		character->set_y(character->get_y() - 1);
		character->set_off_ground();
		return false;
	}
}

bool damageKnockbackCollision(Character* player, GameEntity* object) {

	//Minkowski sum collision method

	int w = player->get_bound_x() + object->get_bound_x();
	int h = player->get_bound_y() + object->get_bound_y();
	int dx = player->get_x() - object->get_x();
	int dy = player->get_y() - object->get_y();


	if (abs(dx) <= w && abs(dy) <= h) //collision
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx) {
			if (wy > -hx) {
				//bottom collision
				player->set_y(object->get_y() + object->get_bound_y() + player->get_bound_y());
				player->set_vel_y(1.5 * KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
			else {
				//left collision
				player->set_x(object->get_x() - object->get_bound_x() - player->get_bound_x());
				player->set_vel_x(-KNOCKBACK);
				player->set_vel_y(-KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
		}
		else {
			if (wy > -hx) {
				//right collision
				player->set_x(object->get_x() + object->get_bound_x() + player->get_bound_x());
				player->set_vel_x(KNOCKBACK);
				player->set_vel_y(-KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
			else {
				//top collision
				player->set_y(object->get_y() - object->get_bound_y() - player->get_bound_y());
				player->set_vel_y(-1.5 * KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
		}
		player->set_damaged_on();
		return true;

	}
	else
		return false;
}

bool checkCollision(GameEntity* obj1, GameEntity* obj2) {
	//Minkowski sum collision method

	int w = obj1->get_bound_x() + obj2->get_bound_x();
	int h = obj1->get_bound_y() + obj2->get_bound_y();
	int dx = obj1->get_x() - obj2->get_x();
	int dy = obj1->get_y() - obj2->get_y();


	if (abs(obj1->get_x() - obj2->get_x()) <= obj1->get_bound_x() + obj2->get_bound_x() &&
		abs(obj1->get_y() - obj2->get_y()) <= obj1->get_bound_y() + obj2->get_bound_y()) //collision
		return true;
	else
		return false;

}


bool enemyKnockbackCollision(Character* player, GameEntity* object) {

	//Minkowski sum collision method

	int w = player->get_bound_x() + object->get_bound_x();
	int h = player->get_bound_y() + object->get_bound_y();
	int dx = player->get_x() - object->get_x();
	int dy = player->get_y() - object->get_y();


	if (abs(dx) <= w && abs(dy) <= h) //collision
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx) {
			if (wy > -hx) {
				//bottom collision
				player->set_x(object->get_x() + object->get_bound_x() + player->get_bound_x());
				player->set_vel_x(KNOCKBACK);
				player->set_vel_y(-KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
			else {
				//left collision
				player->set_x(object->get_x() - object->get_bound_x() - player->get_bound_x());
				player->set_vel_x(-KNOCKBACK);
				player->set_vel_y(-KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
		}
		else {
			if (wy > -hx) {
				//right collision
				player->set_x(object->get_x() + object->get_bound_x() + player->get_bound_x());
				player->set_vel_x(KNOCKBACK);
				player->set_vel_y(-KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
			else {
				//top collision
				player->set_y(object->get_y() - object->get_bound_y() - player->get_bound_y());
				player->set_vel_y(-1.5 * KNOCKBACK);
				if (!player->get_damaged())
					player->set_HP(player->get_HP() - object->get_damage());
			}
		}
		player->set_damaged_on();
		return true;

	}
	else
		return false;
}

bool damageCollision(Character* character, GameEntity* object) {


	character->set_y(character->get_y() + 1);

	int w = character->get_bound_x() + object->get_bound_x();
	int h = character->get_bound_y() + object->get_bound_y();
	int dx = character->get_x() - object->get_x();
	int dy = character->get_y() - object->get_y();


	if (abs(dx) <= w && abs(dy) <= h) //collision
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx) {
			if (wy > -hx) {
				//bottom collision
				character->set_y(object->get_y() + object->get_bound_y() + character->get_bound_y());
				character->set_vel_y(0);
				if (!character->get_damaged())
					character->set_HP(character->get_HP() - object->get_damage());
			}
			else {
				//left collision
				character->set_x(object->get_x() - object->get_bound_x() - character->get_bound_x() - 1);
				if (!character->get_damaged())
					character->set_vel_x(0);
				if (!character->get_damaged())
					character->set_HP(character->get_HP() - object->get_damage());
			}
		}
		else {
			if (wy > -hx) {
				//right collision
				character->set_x(object->get_x() + object->get_bound_x() + character->get_bound_x() + 1);
				if (!character->get_damaged())
					character->set_vel_x(0);
				if (!character->get_damaged())
					character->set_HP(character->get_HP() - object->get_damage());
			}
			else {
				//top collision
				character->set_y(object->get_y() - object->get_bound_y() - character->get_bound_y());
				character->set_vel_y(0);
				character->set_on_ground();
				character->set_up_off();
				if (!character->get_damaged())
					character->set_HP(character->get_HP() - object->get_damage());
			}
		}
		character->set_y(character->get_y() - 1);
		return true;
	}
	else {
		character->set_y(character->get_y() - 1);
		character->set_off_ground();
		return false;
	}
}
