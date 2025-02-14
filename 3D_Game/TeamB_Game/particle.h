//*****************************************
//
// パーティクル[particle.h]
// Author Kensaku Hatori
//
//*****************************************
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "main.h"
#include "Object.h"
#include "effect.h"

#define MAX_PARTICLE (514)
#define NORMALSKILL_COL (D3DXCOLOR)(0.25f,0.45f,1.0f,1.0f)

typedef enum
{
	PARTICLE_NONE = 0,
	PARTICLE_MAX
}PARTICLETYPE;

typedef struct
{
	OBJECT Object;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 move;
	D3DXVECTOR3 dir;
	PARTICLETYPE ntype;
	EFFECTTYPE EffectnType;
	bool bUse;
	int nLife;
	int forlimit;
	D3DXCOLOR col;
	float speed;
	float minspeed;
	float gravity;
}PARTICLE;

void InitParticle();
void UpdateParticle(bool bLimit);
void SetParticle(D3DXVECTOR3 pos,
	D3DXVECTOR3 fAngle, 
	D3DXCOLOR col, 
	PARTICLETYPE ntype,
	D3DXVECTOR3 scale,
	int nLife,
	int forlimit,
	float speed,
	float minspeed,
	float gravity,
	EFFECTTYPE nType);
void SetParticleInfo(PARTICLE Particle);
#endif // !PARTICLE_H_
