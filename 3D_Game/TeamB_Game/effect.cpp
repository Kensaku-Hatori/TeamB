//**********************
// 
// Author: HATORI
// �r���{�[�h�`�揈��
// 
//**********************


//*************
// �C���N���[�h
//*************
#include "effect.h"
#include "particle.h"
#include "player.h"


//***************
// �O���[�o���ϐ�
//***************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_MAX] = { NULL };
EFFECT g_effect[MAX_EFFECT];


//***********
// ����������
//***********
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾����


	for (int TexCount = 0; TexCount < EFFECT_MAX; TexCount++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			EFFECTTEX[TexCount],
			&g_pTextureEffect[TexCount]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect, NULL);


	VERTEX_3D* pVtx = NULL;
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect ->Lock(0, 0, (void**)&pVtx, 0);


	for (int effectcount = 0; effectcount < MAX_EFFECT; effectcount++)
	{
		g_effect[effectcount].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_effect[effectcount].Object.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_effect[effectcount].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_effect[effectcount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_effect[effectcount].dir = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_effect[effectcount].bUse = false;
		g_effect[effectcount].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_effect[effectcount].nLife = 0;
		g_effect[effectcount].Anim = 0;
		g_effect[effectcount].AnimCount = 0;
		g_effect[effectcount].AnimSpeed = 0;

		// �e���_�̖@���̐ݒ�i��ȏ�j
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �e���_�̐F�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e���_�̃e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0f);

		// ���_���W�̍X�V
		pVtx[0].pos.x = -5.0f;
		pVtx[0].pos.y = 5.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 5.0f;
		pVtx[1].pos.y = 5.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -5.0f;
		pVtx[2].pos.y = -5.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 5.0f;
		pVtx[3].pos.y = -5.0f;
		pVtx[3].pos.z = 0.0f;

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//*********
// �I�����u
//*********
void UninitEffect(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
	for (int texcount = 0; texcount < EFFECT_MAX; texcount++)
	{
		if (g_pTextureEffect[texcount] != NULL)
		{
			g_pTextureEffect[texcount]->Release();
			g_pTextureEffect[texcount] = NULL;
		}
	}
}
//*********
// �X�V����
//*********
void UpdateEffect(void)
{
	VERTEX_3D* pVtx = NULL;
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int effectcount = 0; effectcount < MAX_EFFECT; effectcount++)
	{
		if (g_effect[effectcount].bUse == true)
		{
			if (g_effect[effectcount].ntype != EFFECT_MAGICCIRCLE)
			{
				g_effect[effectcount].col -= g_effect[effectcount].colordiff;
			}
			if (g_effect[effectcount].ntype == EFFECT_SMOKE)
			{
				g_effect[effectcount].AnimCount++;
				if (g_effect[effectcount].AnimCount >= g_effect[effectcount].AnimSpeed)
				{
					g_effect[effectcount].AnimCount = 0;
					g_effect[effectcount].Anim++;

					if (g_effect[effectcount].Anim >= MAX_SMOKEANIM)
					{
						g_effect[effectcount].Anim = 0;
					}
				}
				// �e���_�̃e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_effect[effectcount].Anim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_effect[effectcount].Anim * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_effect[effectcount].Anim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_effect[effectcount].Anim * 0.125f, 1.0f);
			}
			else if (g_effect[effectcount].ntype == EFFECT_MAGICCIRCLE)
			{
				Player* pPLayer = GetPlayer();
				if (g_effect[effectcount].Object.Rot.y - pPLayer->rot.y <= D3DX_PI * 2.0f)
				{
					g_effect[effectcount].Object.Rot.y += 0.1f;
				}
				else
				{
					g_effect[effectcount].colordiff.a = 1.0f / g_effect[effectcount].nLife;
					g_effect[effectcount].col -= g_effect[effectcount].colordiff;
				}
				if (g_effect[effectcount].Scale.x <= 7.0f)
				{
					g_effect[effectcount].Scale.x += 0.1f;
					g_effect[effectcount].Scale.y += 0.1f;
				}
				else
				{

				}
			}
			else
			{

			}

			// �e���_�̐F�̐ݒ�
			pVtx[0].col = g_effect[effectcount].col;
			pVtx[1].col = g_effect[effectcount].col;
			pVtx[2].col = g_effect[effectcount].col;
			pVtx[3].col = g_effect[effectcount].col;

			if (g_effect[effectcount].ntype == EFFECT_EXPROSION && g_effect[effectcount].Scale.x <= 10.0f && g_effect[effectcount].bExprosion == true)
			{
				g_effect[effectcount].Scale.x += g_effect[effectcount].LengthValue;
				g_effect[effectcount].Scale.y += g_effect[effectcount].LengthValue;
				g_effect[effectcount].Scale.z += g_effect[effectcount].LengthValue;
			}
			else if (g_effect[effectcount].ntype == EFFECT_EXPROSION && g_effect[effectcount].Scale.x >= 5.0f)
			{
				g_effect[effectcount].bExprosion = false;
				g_effect[effectcount].Scale.x -= g_effect[effectcount].LengthValue;
				g_effect[effectcount].Scale.y -= g_effect[effectcount].LengthValue;
				g_effect[effectcount].Scale.z -= g_effect[effectcount].LengthValue;
			}

			g_effect[effectcount].nLife--;
			if (g_effect[effectcount].nLife <= 0 && g_effect[effectcount].ntype != EFFECT_SKILL)
			{
				g_effect[effectcount].bUse = false;
			}
			g_effect[effectcount].move.y -= g_effect[effectcount].gravity;
			g_effect[effectcount].Object.Pos += g_effect[effectcount].move;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//*********
// �`�揈��
//*********
void DrawEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxScale;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ALPHA�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Z�o�b�t�@�ɂ͏������܂Ȃ�

	for (int effectcount = 0; effectcount < MAX_EFFECT; effectcount++)
	{
		if (g_effect[effectcount].bUse == true)
		{
			if (g_effect[effectcount].ntype != EFFECT_SMOKE && g_effect[effectcount].ntype != EFFECT_MAGICCIRCLE)
			{
				// ���Z������ݒ肷��
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_effect[effectcount].Object.mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			if (g_effect[effectcount].ntype != EFFECT_SKILLFLASH && g_effect[effectcount].ntype != EFFECT_MAGICCIRCLE)
			{
				// �J�����̋t�s���ݒ�
				g_effect[effectcount].Object.mtxWorld._11 = mtxView._11;
				g_effect[effectcount].Object.mtxWorld._12 = mtxView._21;
				g_effect[effectcount].Object.mtxWorld._13 = mtxView._31;
				g_effect[effectcount].Object.mtxWorld._21 = mtxView._12;
				g_effect[effectcount].Object.mtxWorld._22 = mtxView._22;
				g_effect[effectcount].Object.mtxWorld._23 = mtxView._32;
				g_effect[effectcount].Object.mtxWorld._31 = mtxView._13;
				g_effect[effectcount].Object.mtxWorld._32 = mtxView._23;
				g_effect[effectcount].Object.mtxWorld._33 = mtxView._33;
			}

			// �g�嗦�𔽉f
			D3DXMatrixScaling(&mtxScale, g_effect[effectcount].Scale.x, g_effect[effectcount].Scale.y, g_effect[effectcount].Scale.z);
			D3DXMatrixMultiply(&g_effect[effectcount].Object.mtxWorld, &g_effect[effectcount].Object.mtxWorld, &mtxScale);

			if (g_effect[effectcount].ntype == EFFECT_SKILLFLASH || g_effect[effectcount].ntype == EFFECT_MAGICCIRCLE)
			{
				// �����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_effect[effectcount].Object.Rot.y, g_effect[effectcount].Object.Rot.x, g_effect[effectcount].Object.Rot.z);
				D3DXMatrixMultiply(&g_effect[effectcount].Object.mtxWorld, &g_effect[effectcount].Object.mtxWorld, &mtxRot);

				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_effect[effectcount].Object.Pos.x, g_effect[effectcount].Object.Pos.y, g_effect[effectcount].Object.Pos.z);
			D3DXMatrixMultiply(&g_effect[effectcount].Object.mtxWorld, &g_effect[effectcount].Object.mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_effect[effectcount].Object.mtxWorld);
			// ���_�o�b�t�@���f�o�C�X����f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_effect[effectcount].ntype]);
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * effectcount, 2);

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
	// �ݒ�����ɖ߂�
	 pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	 pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, float speed,D3DXVECTOR3 scale,D3DCOLOR col,EFFECTTYPE nType,int Indx,float gravity,D3DXVECTOR3 Rot)
{
	VERTEX_3D* pVtx = NULL;
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int effectcount = 0; effectcount < MAX_EFFECT; effectcount++)
	{
		if (g_effect[effectcount].bUse == false)
		{
			g_effect[effectcount].nLife = nLife;
			g_effect[effectcount].Object.Pos = pos;
			g_effect[effectcount].bUse = true;
			g_effect[effectcount].Object.Pos = pos;
			g_effect[effectcount].dir = dir;
			g_effect[effectcount].Object.Rot = Rot;
			g_effect[effectcount].move.x = sinf(g_effect[effectcount].dir.x) * speed;
			g_effect[effectcount].move.y = sinf(g_effect[effectcount].dir.y) * speed;
			g_effect[effectcount].move.z = sinf(g_effect[effectcount].dir.z) * speed;
			g_effect[effectcount].col = col;
			g_effect[effectcount].Scale = scale;
			g_effect[effectcount].ntype = nType;
			g_effect[effectcount].Anim = 0;
			g_effect[effectcount].AnimCount = 0;
			g_effect[effectcount].AnimSpeed = 0;
			g_effect[effectcount].colordiff.a = g_effect[effectcount].col.a / nLife;
			g_effect[effectcount].Indx = Indx;
			g_effect[effectcount].gravity = gravity;
			g_effect[effectcount].LengthValue = 0.0f;
			g_effect[effectcount].bExprosion = true;

			if (nType == EFFECT_EXPROSION)
			{
				g_effect[effectcount].LengthValue = 3.0f;
			}

			// �e���_�̐F�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_effect[effectcount].col);
			pVtx[1].col = D3DXCOLOR(g_effect[effectcount].col);
			pVtx[2].col = D3DXCOLOR(g_effect[effectcount].col);
			pVtx[3].col = D3DXCOLOR(g_effect[effectcount].col);

			// �e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			if (nType == EFFECT_SMOKE)
			{
				g_effect[effectcount].AnimSpeed = nLife / MAX_SMOKEANIM;
				g_effect[effectcount].LengthValue = MAX_SMOKELENGTH / (float)nLife;
				g_effect[effectcount].colordiff.a = g_effect[effectcount].col.a / nLife;
				// �e���_�̃e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
			}
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//***************************
// �G�t�F�N�g����C�ɏ����֐�
//***************************
void DeleteEffect(EFFECTTYPE nType, int Indx)
{
	for (int EffectCount = 0; EffectCount < MAX_EFFECT; EffectCount++)
	{
		if (g_effect[EffectCount].ntype == nType && g_effect[EffectCount].Indx == Indx)
		{
			g_effect[EffectCount].bUse = false;
		}
	}
}

void SetSkillParticle(EFFECTTYPE nType, int Indx, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, int Limit)
{
	for (int EffectCount = 0; EffectCount < Limit; EffectCount++)
	{
		D3DXVECTOR3 EffectPos = EndPos - StartPos;
		EffectPos = EffectPos / (float)Limit * (float)EffectCount;

		SetParticle(StartPos + EffectPos,
			D3DXVECTOR3(628.0f, 628.0f, 628.0f),
			D3DXCOLOR(0.25f, 0.45f, 1.0f, 1.0f),
			PARTICLE_NONE,
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),
			100,
			5,
			50.0f,
			40.0f,
			0.01f,
			EFFECT_NONE);
	}
	SetParticle(EndPos,
		D3DXVECTOR3(628.0f, 628.0f, 628.0f),
		D3DXCOLOR(0.05f, 0.25f, 1.0f, 1.0f),
		PARTICLE_NONE,
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		100,
		300,
		100.0f,
		100.0f,
		0.0f,
		EFFECT_NONE);
}