#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "main.h"
#include "Object.h"
#include "effect.h"

#define MAX_PARTICLE (514)
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
	bool bUse;
	int nLife;
	int forlimit;
	D3DXCOLOR col;
	float speed;
}PARTICLE;

void InitParticle();
void UpdateParticle(bool bLimit);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 fAngle, D3DXCOLOR col, PARTICLETYPE ntype, D3DXVECTOR3 scale,int nLife,int forlimit);
void SetParticleInfo(PARTICLE Particle);
#endif // !PARTICLE_H_
