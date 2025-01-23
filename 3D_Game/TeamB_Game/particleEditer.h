#ifndef PARTICLEEDITER_H_
#define PARTICLEEDITER_H_

#include "main.h"
#include "particle.h"

typedef struct
{
	PARTICLE ParticleInfo;
	int ParticleLimit;
}PARTICLEEDITER;

void InitParticleEditer();
void UpdateParticleEditer();
PARTICLEEDITER* GetParticleInfo();

#endif // !PARTICLEEDITER_H_