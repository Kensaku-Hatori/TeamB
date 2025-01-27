//================================
//
// �e����[skill.cpp]
// Author:kaiti
//
//================================
#include "skill.h"
#include "shadow.h"
#include "explosion.h"
#include "player.h"
#include "effect.h"
#include "wall.h"
#include "particle.h"
#include "enemy.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkill = NULL;
LPDIRECT3DTEXTURE9 g_apTextureSkill[1] = {};
Skill g_Skill[MAX_SKILL];
//=========================
// �e�̏���������
//=========================
void InitSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		g_Skill[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Skill[nCnt].nLife = SKILL_LIFE;
		g_Skill[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureSkill[0]); //1

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SKILL,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffSkill,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSkill->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x - SKILL_SIZE, g_Skill[nCnt].pos.y + SKILL_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x + SKILL_SIZE, g_Skill[nCnt].pos.y + SKILL_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x - SKILL_SIZE, g_Skill[nCnt].pos.y - SKILL_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Skill[nCnt].pos.x + SKILL_SIZE, g_Skill[nCnt].pos.y - SKILL_SIZE, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSkill->Unlock();
}
//=======================
// �e�̏I������
//=======================
void UninitSkill(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureSkill[0] != NULL)
	{
		g_apTextureSkill[0]->Release();
		g_apTextureSkill[0] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSkill != NULL)
	{
		g_pVtxBuffSkill->Release();
		g_pVtxBuffSkill = NULL;
	}
}
//=======================
// �e�̍X�V����
//=======================
void UpdateSkill(void)
{
	Player* pPlayer;
	pPlayer = GetPlayer();

	Shadow* pShadow;
	pShadow = GetShadow();
	
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			SkillCollision(nCnt);

			SetEffect(g_Skill[nCnt].pos,
					  D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					  10.0f,
					  0.0f, 
					  D3DXVECTOR3(3.0f, 3.0f, 3.0f), 
					  D3DXCOLOR(0.80f, 1.00f, 0.00f,1.0f),
					  EFFECT_NONE);

			g_Skill[nCnt].pos += g_Skill[nCnt].move;

			g_Skill[nCnt].move.x += sinf(g_Skill[nCnt].rot.y - D3DX_PI) * 0.5f;
			g_Skill[nCnt].move.z += cosf(g_Skill[nCnt].rot.y - D3DX_PI) * 0.5f;

			g_Skill[nCnt].nLife -= 1;

			if (g_Skill[nCnt].nLife <= 0)
			{
				g_Skill[nCnt].bUse = false;
				pShadow[g_Skill[nCnt].nIdxShadow].bUse = false;
			}
		}
	}
}
//=======================
// �e�̕`�揈��
//=======================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Skill[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_Skill[nCnt].mtxWorld._11 = mtxView._11;
			g_Skill[nCnt].mtxWorld._12 = mtxView._21;
			g_Skill[nCnt].mtxWorld._13 = mtxView._31;
			g_Skill[nCnt].mtxWorld._21 = mtxView._12;
			g_Skill[nCnt].mtxWorld._22 = mtxView._22;
			g_Skill[nCnt].mtxWorld._23 = mtxView._32;
			g_Skill[nCnt].mtxWorld._31 = mtxView._13;
			g_Skill[nCnt].mtxWorld._32 = mtxView._23;
			g_Skill[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Skill[nCnt].pos.x, g_Skill[nCnt].pos.y, g_Skill[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Skill[nCnt].mtxWorld, &g_Skill[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Skill[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSkill, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureSkill[0]);

			//�|���S����`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===================
// �e�̐ݒ�
//===================
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == false)
		{
			g_Skill[nCnt].pos = D3DXVECTOR3(pos.x, pos.y + 30, pos.z);
			g_Skill[nCnt].move = move;
			g_Skill[nCnt].rot = rot;
			g_Skill[nCnt].nLife = SKILL_LIFE;
			g_Skill[nCnt].bUse = true;
			break;
		}
	}
}
//
// �G�Ɩ��@�̓����蔻��
//
void SkillCollision(int nIdx)
{
	ENEMY* pEnemy = GetEnemy();
	Player* pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].bUse == true)
		{
			g_Skill[nIdx].fDistance = sqrtf(((g_Skill[nIdx].pos.x - pEnemy->Object.Pos.x) * (g_Skill[nIdx].pos.x - pEnemy->Object.Pos.x))
										  + ((g_Skill[nIdx].pos.y - pEnemy->Object.Pos.y) * (g_Skill[nIdx].pos.y - pEnemy->Object.Pos.y))
										  + ((g_Skill[nIdx].pos.z - pEnemy->Object.Pos.z) * (g_Skill[nIdx].pos.z - pEnemy->Object.Pos.z)));

			float RADIUS = (pEnemy->Radius + SKILL_SIZE) * (pEnemy->Radius + SKILL_SIZE);

			if (g_Skill[nIdx].fDistance <= RADIUS)
			{
				HitEnemy(pPlayer->Status.fPower,nCntEnemy);
			}
		}
	}
}