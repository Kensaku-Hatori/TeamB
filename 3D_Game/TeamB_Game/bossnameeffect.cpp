//*********************************************************
// 
// �{�X�̃��[�r�[�̖��O[bossnameeffect.cpp]
// Author:Hatori
// 
//*********************************************************

#include "bossnameeffect.h"
#include <cassert>

#define BACESIZEX (float)(10)
#define BACESIZEY (float)(10)

BOSSNAMEEFFECT g_BossName;

bool isReVerse(float V);
bool isFade(NAMEFADE FadeType);
bool isSetCondition();
bool isUseNameEffect();
bool CreatNameBuffer();
bool isGreaterLife(int Count);
bool isGreaterFade();

void UpdateTexUV(float U,float V);
void UpdateSizeAnim(float U, float V);
void UpdateAlphaAnim();

void InitBossNameEffect()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossname1.png", &g_BossName.Tex);

	g_BossName.fAngle = atan2f(BACESIZEX,BACESIZEY);
	g_BossName.Length = sqrtf(BACESIZEX + BACESIZEY);
}
void UninitBossNameEffect()
{
	UninitBuffer(g_BossName.Buff);
	UninitTexture(g_BossName.Tex);
}
void UpdateBossNameEffect()
{
	static float U = 0.0f;
	static float V = 0.0f;
	if (isUseNameEffect() == true)
	{
		UpdateTexUV(U,V);

		UpdateSizeAnim(U,V);

		UpdateAlphaAnim();

		if (isReVerse(V) == true)
		{
			g_BossName.FadeCounter++;
			if (isGreaterFade() == true)
			{
				g_BossName.FadeCounter = 0;
				g_BossName.Fade = NAMEFADE_OUT;
			}
		}
		if (isFade(NAMEFADE_IN) == true)
		{
			g_BossName.Col.a += (1.1f - g_BossName.Col.a) * 0.05f;
			U += (1.0f - U) * 0.1f;
			V += (1.0f - V) * 0.1f;
		}
		else if (isFade(NAMEFADE_OUT) == true)
		{
			g_BossName.Col.a += (-0.1f - g_BossName.Col.a) * 0.05f;
			U += (-0.1f - U) * 0.1f;
			V += (-0.1f - V) * 0.1f;
		}

		g_BossName.nLife--;
		if (isGreaterLife(0) == false)
		{
			g_BossName.bUse = false;
			U = 0.0f;
			V = 0.0f;
		}
	}
}
void DrawBossNameEffect()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (isUseNameEffect() == true)
	{
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_BossName.Buff, 0, sizeof(VERTEX_2D));
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_BossName.Tex);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
void SetBossNameEffect(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR2 Scale, D3DXCOLOR Col,int nLife)
{
	if (isSetCondition() == true)
	{
		g_BossName.bUse = true;
		g_BossName.Pos = Pos;
		g_BossName.Rot = Rot;
		g_BossName.Scale = Scale;
		g_BossName.Col = Col;
		g_BossName.nLife = nLife;
		g_BossName.Fade = NAMEFADE_IN;
		g_BossName.FadeCounter = 0;

		//���_�o�b�t�@�̐����E���_���̐ݒ�
		VERTEX_2D* pVtx;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

		////��ڂ̃|���S��
		//pVtx[0].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.y - 25.0f;
		//pVtx[0].pos.y = Pos.y - cosf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.x - 150.0f;
		//pVtx[0].pos.z = 0.0f;//0.0f;

		//pVtx[1].pos.x = Pos.x - sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x + 150.0f;
		//pVtx[1].pos.y = Pos.y - cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y - 25.0f;
		//pVtx[1].pos.z = 0.0f;//0.0f;

		//pVtx[2].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x - 150.0f;
		//pVtx[2].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y + 25.0f;
		//pVtx[2].pos.z = 0.0f;//0.0f;

		//pVtx[3].pos.x = Pos.x + sinf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x + 150.0f;
		//pVtx[3].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y + 25.0f;
		//pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		////�e�N�X�`�����W�̐ݒ�
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_BossName.Buff->Unlock();
	}
	else
	{
		assert(false);
	}
}

bool isSetCondition()
{
	return isUseNameEffect() == false && CreatNameBuffer() == true;
}
bool isUseNameEffect()
{
	return g_BossName.bUse;
}
bool CreatNameBuffer()
{
	HRESULT hresult;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	hresult = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_BossName.Buff,
		NULL);
	if (FAILED(hresult)) return false;
	else return true;
}
bool isGreaterLife(int Count)
{
	return g_BossName.nLife > Count;
}

void UpdateTexUV(float U,float V)
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, V);
	pVtx[3].tex = D3DXVECTOR2(U, V);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_BossName.Buff->Unlock();
}
void UpdateSizeAnim(float U, float V)
{
	D3DXVECTOR3 Pos = g_BossName.Pos;
	D3DXVECTOR3 Rot = g_BossName.Rot;
	D3DXVECTOR2 Scale = g_BossName.Scale;
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

	//��ڂ̃|���S��
	pVtx[0].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.y - 25.0f;
	pVtx[0].pos.y = Pos.y - cosf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.x - 150.0f;
	pVtx[0].pos.z = 0.0f;//0.0f;

	pVtx[1].pos.x = Pos.x - sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x * U;//pos.x + 150.0f;
	pVtx[1].pos.y = Pos.y - cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y;//pos.y - 25.0f;
	pVtx[1].pos.z = 0.0f;//0.0f;

	pVtx[2].pos.x = Pos.x + sinf(Rot.z - g_BossName.fAngle) * g_BossName.Length * Scale.x;//pos.x - 150.0f;
	pVtx[2].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y * V;//pos.y + 25.0f;
	pVtx[2].pos.z = 0.0f;//0.0f;

	pVtx[3].pos.x = Pos.x + sinf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.x * U;//pos.x + 150.0f;
	pVtx[3].pos.y = Pos.y + cosf(Rot.z + g_BossName.fAngle) * g_BossName.Length * Scale.y * V;//pos.y + 25.0f;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_BossName.Buff->Unlock();
}
void UpdateAlphaAnim()
{
	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_BossName.Buff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(g_BossName.Col);
	pVtx[1].col = D3DXCOLOR(g_BossName.Col);
	pVtx[2].col = D3DXCOLOR(g_BossName.Col);
	pVtx[3].col = D3DXCOLOR(g_BossName.Col);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_BossName.Buff->Unlock();
}
bool isFade(NAMEFADE FadeType)
{
	return g_BossName.Fade == FadeType;
}
bool isReVerse(float V)
{
	return V >= 0.8f;
}
bool isGreaterFade()
{
	return g_BossName.FadeCounter >= FADE_TIME;
}