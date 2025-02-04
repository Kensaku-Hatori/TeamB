//***************************************
//
/// モーションを再生する処理[animation.h]
// Hatori Kensaku
//
//***************************************
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "main.h"
#include "key.h"

void UpdateMotion(OBJECTINFO *Motion);						// モーション再生処理
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO*Motion);	// モーション設定処理
void MotionBlend(OBJECTINFO* Motion);

#endif // !ANIMATION_H_