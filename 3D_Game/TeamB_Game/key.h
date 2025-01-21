#ifndef KEY_H_
#define KEY_H_

#define MAX_MODEL (11)
#define MAX_KEY (10)

#include "main.h"

typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

typedef struct
{
	int nFrame;
	KEY aKey[MAX_MODEL];
}KEYINFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEYINFO aKeyInfo[MAX_KEY];
}MOTIONINFO;
#endif // !KEY_H_