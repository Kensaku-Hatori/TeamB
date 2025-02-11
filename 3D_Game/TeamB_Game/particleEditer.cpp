#include "particleEditer.h"
#include "particle.h"
#include "effect.h"
#include "camera.h"
#include "input.h"
#include "player.h"

#define COLSPEED (float)(0.01f)
#define VECSPEED (float)(0.01f)

PARTICLEEDITER g_ParticleEditer;

void InitParticleEditer()
{
	Player* pPlayer = GetPlayer();
	g_ParticleEditer.ParticleInfo.Object.Pos = pPlayer->pos;
	g_ParticleEditer.ParticleInfo.Object.Pos.y = 100.0f;
	g_ParticleEditer.ParticleInfo.dir = D3DXVECTOR3(3.14f,3.14f, 3.14f);
	g_ParticleEditer.ParticleInfo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ParticleEditer.ParticleInfo.ntype = PARTICLE_NONE;
	g_ParticleEditer.ParticleInfo.Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_ParticleEditer.ParticleInfo.nLife = 100;
	g_ParticleEditer.ParticleInfo.forlimit = 10;
	g_ParticleEditer.ParticleInfo.speed = 10.0f;
	g_ParticleEditer.ParticleInfo.minspeed = 1.0f;
	g_ParticleEditer.ParticleInfo.gravity = 0.0f;
	g_ParticleEditer.ParticleInfo.bUse = true;

	SetParticle(g_ParticleEditer.ParticleInfo.Object.Pos,
		g_ParticleEditer.ParticleInfo.dir,
		g_ParticleEditer.ParticleInfo.col,
		g_ParticleEditer.ParticleInfo.ntype,
		g_ParticleEditer.ParticleInfo.Scale,
		g_ParticleEditer.ParticleInfo.nLife,
		g_ParticleEditer.ParticleInfo.forlimit,
		10.0f,
		1.0f,
		1.0f);
}
void UpdateParticleEditer()
{
	UpdateEffect();
	UpdateParticle(false);
	UpdateCamera();

	if (GetKeyboardPress(DIK_LSHIFT))
	{
		if (GetKeyboardPress(DIK_R) && g_ParticleEditer.ParticleInfo.col.r > 0.0f)
		{
			g_ParticleEditer.ParticleInfo.col.r -= COLSPEED;
		}
		else if (GetKeyboardPress(DIK_G) && g_ParticleEditer.ParticleInfo.col.g > 0.0f)
		{
			g_ParticleEditer.ParticleInfo.col.g -= COLSPEED;
		}
		else if (GetKeyboardPress(DIK_B) && g_ParticleEditer.ParticleInfo.col.b > 0.0f)
		{
			g_ParticleEditer.ParticleInfo.col.b -= COLSPEED;
		}
		else if (GetKeyboardPress(DIK_X) && g_ParticleEditer.ParticleInfo.dir.x > 0.1f)
		{
			g_ParticleEditer.ParticleInfo.dir.x -= VECSPEED;
		}
		else if (GetKeyboardPress(DIK_Y) && g_ParticleEditer.ParticleInfo.dir.y > 0.1f)
		{
			g_ParticleEditer.ParticleInfo.dir.y -= VECSPEED;
		}
		else if (GetKeyboardPress(DIK_Z) && g_ParticleEditer.ParticleInfo.dir.z > 0.1f)
		{
			g_ParticleEditer.ParticleInfo.dir.z -= VECSPEED;
		}
		else if (GetKeyboardPress(DIK_L) && g_ParticleEditer.ParticleInfo.forlimit > 0)
		{
			g_ParticleEditer.ParticleInfo.forlimit--;
		}
		else if (GetKeyboardPress(DIK_H) && g_ParticleEditer.ParticleInfo.nLife > 1)
		{
			g_ParticleEditer.ParticleInfo.nLife--;
		}
		else if (GetKeyboardPress(DIK_S) && g_ParticleEditer.ParticleInfo.Scale.x > 1)
		{
			g_ParticleEditer.ParticleInfo.Scale.x-=0.01f;
			g_ParticleEditer.ParticleInfo.Scale.y-=0.01f;
			g_ParticleEditer.ParticleInfo.Scale.z-=0.01f;
		}
	}
	else
	{
		if (GetKeyboardPress(DIK_R) && g_ParticleEditer.ParticleInfo.col.r < 1.0f)
		{
			g_ParticleEditer.ParticleInfo.col.r += COLSPEED;
		}
		else if (GetKeyboardPress(DIK_G) && g_ParticleEditer.ParticleInfo.col.g < 1.0f)
		{
			g_ParticleEditer.ParticleInfo.col.g += COLSPEED;
		}
		else if (GetKeyboardPress(DIK_B) && g_ParticleEditer.ParticleInfo.col.b < 1.0f)
		{
			g_ParticleEditer.ParticleInfo.col.b += COLSPEED;
		}
		else if (GetKeyboardPress(DIK_X) && g_ParticleEditer.ParticleInfo.dir.x < D3DX_PI * 2)
		{
			g_ParticleEditer.ParticleInfo.dir.x += VECSPEED;
		}
		else if (GetKeyboardPress(DIK_Y) && g_ParticleEditer.ParticleInfo.dir.y < D3DX_PI * 2)
		{
			g_ParticleEditer.ParticleInfo.dir.y += VECSPEED;
		}
		else if (GetKeyboardPress(DIK_Z) && g_ParticleEditer.ParticleInfo.dir.z < D3DX_PI * 2)
		{
			g_ParticleEditer.ParticleInfo.dir.z += VECSPEED;
		}
		else if (GetKeyboardPress(DIK_L) && g_ParticleEditer.ParticleInfo.forlimit < 100)
		{
			g_ParticleEditer.ParticleInfo.forlimit++;
		}
		else if (GetKeyboardPress(DIK_H) && g_ParticleEditer.ParticleInfo.nLife < 150)
		{
			g_ParticleEditer.ParticleInfo.nLife++;
		}
		else if (GetKeyboardPress(DIK_S) && g_ParticleEditer.ParticleInfo.Scale.x < 50)
		{
			g_ParticleEditer.ParticleInfo.Scale.x+=0.01f;
			g_ParticleEditer.ParticleInfo.Scale.y+=0.01f;
			g_ParticleEditer.ParticleInfo.Scale.z+=0.01f;
		}
		else if (GetKeyboardPress(DIK_1))
		{
			g_ParticleEditer.ParticleInfo.EffectnType = EFFECT_NONE;
		}
		else if (GetKeyboardPress(DIK_2))
		{
			g_ParticleEditer.ParticleInfo.EffectnType = EFFECT_SMOKE;
		}
	}
	SetParticleInfo(g_ParticleEditer.ParticleInfo);
}
PARTICLEEDITER *GetParticleInfo()
{
	return &g_ParticleEditer;
}