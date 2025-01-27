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
	int nHP;
	float fPower;
	int nMP;
	float fSpeed;
}PlayerStatus;

typedef struct
{
	int nHP;
	float fPower;
	float fSpeed;
}EnemyStatus;
#endif // !STATUS_H_