#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "main.h"
#include "key.h"

void UpdateMotion(OBJECTINFO *Motion);
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO*Motion);
void MotionBlend(void);

#endif // !ANIMATION_H_