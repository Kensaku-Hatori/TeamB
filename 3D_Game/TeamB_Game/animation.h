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
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO*Motion,int BlendFlame);	// モーション設定処理
void UpdateCurrentMotion(OBJECTINFO* Motion);
void UpdateBlendMotion(OBJECTINFO* Motion);
void CaceOneAction(OBJECTINFO *Motion);
void CaceTwoAction(OBJECTINFO *Motion);
void CaceThreeAction(OBJECTINFO* Motion);
void CheckActionFlame(OBJECTINFO* Motion);
#endif // !ANIMATION_H_