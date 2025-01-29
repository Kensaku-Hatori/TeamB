#ifndef STATUS_H_
#define STATUS_H_

//=====================================
//
// ステータス[status.h]
// Author:kaiti
//
//=====================================

typedef struct
{
	float fHP;
	float fPower;
	int nMP;
	float fSpeed;
}PlayerStatus;

typedef struct
{
	float fHP;
	float fPower;
	float fSpeed;
}EnemyStatus;
#endif // !STATUS_H_