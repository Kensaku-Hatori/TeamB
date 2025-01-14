//=================================
//
//  �p�[�e�B�N������[particle.h]
//  Author:kaiti
//
//=================================
#include "particle.h"
#include "effect.h"
#define MAX_PARTICLE (256)
//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	float fRadius;
	int nLife;
	bool bUse;
}Particle;
//�O���[�o���ϐ�
Particle g_aParticle[MAX_PARTICLE];
//=============
// ����������
//=============
void InitParticle(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_aParticle[nCnt].fRadius = 0.0f;
		g_aParticle[nCnt].nLife = 0;
		g_aParticle[nCnt].bUse = false;
	}
}
//===========
// �I������
//===========
void UninitParticle(void)
{
}
//==========
// �X�V����
//==========
void UpdateParticle(void)
{
	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	int nLife;

	float fAngle;
	float fLength;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			for (nCntAppear = 0; nCntAppear < 15; nCntAppear++)
			{
				pos = g_aParticle[nCntParticle].pos;

				fAngle = (float)(rand() % 629 - 314) / 100.0f;
				fLength = (float)(rand() % 100) / 100 + 5.0f;

				move.x = sinf(fAngle) * fLength;
				move.y = cosf(fAngle) * fLength;

				col = g_aParticle[nCntParticle].col;

				fRadius = g_aParticle[nCntParticle].fRadius;
				nLife = 30;

				//fRadius = (float)(rand() % 20) / 150 + 1.0f;
				//nLife = (float)(rand() % 120) / 140 + 1.0f;

				SetEffect(pos, move, col, nLife, fRadius);
			}
			g_aParticle[nCntParticle].nLife -= 1;
			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}
//============
// �`�揈��
//============
void DrawParticle(void)
{

}
//=====================
// �p�[�e�B�N���̐ݒ�
//=====================
void SetParticle(D3DXVECTOR3 pos)
{
	int nCntParticle;
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 0.15f, 0.01f, 0.5f);
			g_aParticle[nCntParticle].fRadius = 30.0f;
			g_aParticle[nCntParticle].nLife = 30;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
	}
}