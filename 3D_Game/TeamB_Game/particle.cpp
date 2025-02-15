//*************
// インクルード
//*************
#include "particle.h"

//*******************
// グローバル変数宣言
//*******************
PARTICLE g_particle[MAX_PARTICLE] = {	};

//*************************
// パーティクルの初期化処理
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
// パーティクルの更新処理
//***********************
void UpdateParticle(bool bLimit)
{
	for (int particlecount = 0; particlecount < MAX_PARTICLE;particlecount++)
	{
		if (g_particle[particlecount].bUse == true)
		{
			for (int nEffect = 0; nEffect < g_particle[particlecount].forlimit; nEffect++)
			{
				D3DXVECTOR3 dir;
				D3DXVECTOR3 dir1;
				dir1 = g_particle[particlecount].dir * 100;
				float speed;
				int nLife;
				dir.x = (float)(rand() %(int)dir1.x - 314) / 100.0f;
				dir.y = (float)(rand() %(int)dir1.y - 314) / 100.0f;
				dir.z = (float)(rand() %(int)dir1.z - 314) / 100.0f;
				nLife = rand() % g_particle[particlecount].nLife + 1;
				speed = (float)(rand() % (int)g_particle[particlecount].speed - (int)g_particle[particlecount].minspeed) / 100.0f;

				SetEffect(g_particle[particlecount].Object.Pos,
					dir,
					nLife,
					speed,
					g_particle[particlecount].Scale,
					g_particle[particlecount].col,
					g_particle[particlecount].EffectnType,
					0,
					g_particle[particlecount].gravity,
					D3DXVECTOR3(0.0f,0.0f,0.0f));
			}
			if (bLimit == true)
			{
				g_particle[particlecount].bUse = false;
			}
		}
	}
}
//***********************
// パーティクルの設定処理
//***********************
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 fAngle, D3DXCOLOR col, PARTICLETYPE ntype, D3DXVECTOR3 scale,int nLife,int forlimit,float speed,float minspeed,float gravity,EFFECTTYPE nType)
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
			g_particle[particlecount].speed = speed;
			g_particle[particlecount].minspeed = minspeed;
			g_particle[particlecount].gravity = gravity;
			g_particle[particlecount].EffectnType = nType;

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