//*************
// �C���N���[�h
//*************
#include "particle.h"

//*******************
// �O���[�o���ϐ��錾
//*******************
PARTICLE g_particle[MAX_PARTICLE] = {	};

//*************************
// �p�[�e�B�N���̏���������
//*************************
void InitParticle()
{
	for (int particlecount = 0; particlecount < MAX_PARTICLE; particlecount++)
	{
		g_particle[particlecount].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_particle[particlecount].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_particle[particlecount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_particle[particlecount].bUse = false;
		g_particle[particlecount].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//***********************
// �p�[�e�B�N���̍X�V����
//***********************
void UpdateParticle(bool bLimit)
{
	for (int particlecount = 0; particlecount < MAX_PARTICLE;particlecount++)
	{
		if (g_particle[particlecount].bUse == true)
		{
			for (int nEffect = 0; nEffect < g_particle[particlecount].forlimit; nEffect++)
			{
				g_particle[particlecount].dir *= 100.0f;
				D3DXVECTOR3 dir;
				int speed;
				int nLife;
				dir.x = rand() %(int)g_particle[particlecount].dir.x + 1.0f;
				dir.y = rand() %(int)g_particle[particlecount].dir.y + 1.0f;

				dir.z = rand() %(int)g_particle[particlecount].dir.z + 1.0f;
				dir *= 0.01f;
				nLife = rand() % g_particle[particlecount].nLife + 1;
				speed = rand() % 10 + 1;
				SetEffect(g_particle[particlecount].Object.Pos,dir,nLife,speed,D3DXVECTOR3(1.0f,1.0f,1.0f),g_particle[particlecount].col,EFFECT_NONE);
			}
			if (bLimit == true)
			{
				g_particle[particlecount].bUse = false;
			}
		}
	}
}
//***********************
// �p�[�e�B�N���̐ݒ菈��
//***********************
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 fAngle, D3DXCOLOR col, PARTICLETYPE ntype, D3DXVECTOR3 scale,int nLife,int forlimit)
{
	for (int particlecount = 0; particlecount < MAX_PARTICLE; particlecount++)
	{
		if (g_particle[particlecount].bUse == false)
		{
			g_particle[particlecount].bUse = true;
			g_particle[particlecount].Object.Pos = pos;
			g_particle[particlecount].ntype = ntype;
			g_particle[particlecount].dir = fAngle;
			g_particle[particlecount].col = col;
			g_particle[particlecount].Scale = scale;
			g_particle[particlecount].nLife = nLife;
			g_particle[particlecount].forlimit = forlimit;

			break;
		}
	}
}
void SetParticleInfo(PARTICLE Particle)
{
	for (int ParticleCount = 0; ParticleCount < MAX_PARTICLE; ParticleCount++)
	{
		if (g_particle[ParticleCount].bUse == true)
		{
			g_particle[ParticleCount] = Particle;
			break;
		}
	}
}