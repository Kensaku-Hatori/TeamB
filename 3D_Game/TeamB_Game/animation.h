//***************************************
//
/// ���[�V�������Đ����鏈��[animation.h]
// Hatori Kensaku
//
//***************************************
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "main.h"
#include "key.h"

void UpdateMotion(OBJECTINFO *Motion);						// ���[�V�����Đ�����
void SetMotion(MOTIONTYPE MotionType, OBJECTINFO*Motion);	// ���[�V�����ݒ菈��
void MotionBlend(OBJECTINFO* Motion);

#endif // !ANIMATION_H_