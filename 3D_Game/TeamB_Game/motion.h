//==============================
//
//  èàóù[edit.h]
//  Author:kaiti
//
//==============================
#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"
#include "model.h"

typedef enum
{
	MOTION_USER_PLAYER = 0,
	MOTION_USER_ENEMY,
	MOTION_USER_MAX
}MOTION_USER;


void LoadPlayer1(void);
void SetMotion(MOTION_USER motion_user);

#endif 