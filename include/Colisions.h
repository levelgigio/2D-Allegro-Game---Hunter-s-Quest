#pragma once
#include "Character.h"

bool solidCollision(Character* character, GameEntity* object);

void secondPlayerDamageKnockbackCollision(Character* player, GameEntity* object);

bool damageKnockbackCollision(Character* character, GameEntity* object);

bool enemyKnockbackCollision(Character* player, GameEntity* object);

bool checkCollision(GameEntity* obj1, GameEntity* obj2);

bool damageCollision(Character* player, GameEntity* object);
