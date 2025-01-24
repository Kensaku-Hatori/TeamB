#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "main.h"
#include "key.h"
#include "Player.h"
#include "enemy.h"

void UpdateMotion(OBJECTINFO*Motion);
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO*Motion);
#endif // !ANIMATION_H_