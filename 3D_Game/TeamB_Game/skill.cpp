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
#include "impact.h"
#include "boss.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkill = NULL;
LPDIRECT3DTEXTURE9 g_apTextureSkill = {};
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
		g_Skill[nCnt].fPower = 0.0f;
		g_Skill[nCnt].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureSkill); //1

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
	if (g_apTextureSkill != NULL)
	{
		g_apTextureSkill->Release();
		g_apTextureSkill = NULL;
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
	//�v���C���[�̏��擾
	Player* pPlayer = GetPlayer();
	//�e�̏��擾
	Shadow* pShadow = GetShadow();
	
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == true)
		{
			if (g_Skill[nCnt].ntype == SKILLTYPE_HORMING)
			{
				g_Skill[nCnt].nCounter++;
				UpdateHorming(nCnt);
			}
			// �G�t�F�N�g�̐ݒ�
			SetEffect(g_Skill[nCnt].pos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				30,
				0,
				D3DXVECTOR3(2.0f, 2.0f, 2.0f),
				D3DXCOLOR(0.55f,0.75f,1.0f,1.0f),
				EFFECT_SKILL,
				nCnt,
				0.0f,
				D3DXVECTOR3(0.0f,0.0f,0.0f)
			);

			// �G�t�F�N�g�̐ݒ�
			SetEffect(g_Skill[nCnt].pos,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				30,
				0,
				D3DXVECTOR3(3.0f, 3.0f, 3.0f),
				D3DXCOLOR(0.05f, 0.25f, 1.0f, 1.0f),
				EFFECT_SKILL,
				nCnt,
				0.0f,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f)
			);

			if (g_Skill[nCnt].nLife > 0)
			{
				if ((g_Skill[nCnt].nLife % INTERVAL_IMPACT) == 0 && g_Skill[nCnt].ntype != SKILLTYPE_HORMING)
				{
					//�Ռ��g�̐ݒ�
					SetImpact(IMPACTTYPE_SKILL,				// �^�C�v
						g_Skill[nCnt].pos,					// �ꏊ
						D3DXCOLOR(0.2f, 0.5f, 1.0f, 1.0f),	// �F
						30,									// ����
						5.0f,								// �Ȃ������̑傫��
						10.0f,								// �O�т̑傫��
						2,									// �Q�Œ�
						50,									// ������
						1.0f,								// �L����X�s�[�h
						g_Skill[nCnt].rot.y);				// ����
				}
			}

			if (g_Skill[nCnt].bHit == false && g_Skill[nCnt].ntype != SKILLTYPE_HORMING)
			{
				g_Skill[nCnt].move.x += sinf(g_Skill[nCnt].rot.y - D3DX_PI) * g_Skill[nCnt].Speed;
				g_Skill[nCnt].move.z += cosf(g_Skill[nCnt].rot.y - D3DX_PI) * g_Skill[nCnt].Speed;

				g_Skill[nCnt].pos += g_Skill[nCnt].move;
			}

			g_Skill[nCnt].nLife--;

			if (g_Skill[nCnt].nLife <= 0)
			{
				g_Skill[nCnt].bUse = false;
				DeleteEffect(EFFECT_SKILL, nCnt);
				if (g_Skill[nCnt].ntype != SKILLTYPE_HORMING)
				{
					SetSkillParticle(EFFECT_SKILL, nCnt, g_Skill[nCnt].StartPos, g_Skill[nCnt].pos, 100);
				}
				else
				{
					SetParticle(g_Skill[nCnt].pos,
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
				pShadow[g_Skill[nCnt].nIdxShadow].bUse = false;
				g_Skill[nCnt].AnimCounter = 0;
			}
		}
	}
}
void UpdateHorming(int Indx)
{
	//�v���C���[�̏��擾
	Player* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
	BOSS* pBoss = GetBoss();
	if (g_Skill[Indx].nCounter >= g_Skill[Indx].nCount && g_Skill[Indx].bHorming == false)
	{
		g_Skill[Indx].nCounter = 0;
		for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++,pEnemy++)
		{
			if (pEnemy->bUse == true)
			{
				if (SerchHormingEnemy(Indx, pEnemy->Object.Pos) == true)
				{
					g_Skill[Indx].nIndxHorming = EnemyCount;
					g_Skill[Indx].rot = pPlayer->rot;
					g_Skill[Indx].bHorming = true;
					if (pPlayer->bLockOn != true)
					{
						pEnemy += g_Skill[Indx].nIndxHorming;
					}
					else
					{
						pEnemy += pPlayer->nLockOnEnemy;
					}
					if (pEnemy->bUse == true)
					{
						D3DXVECTOR3 fMoveVec = pEnemy->Object.Pos - g_Skill[Indx].pos;
						D3DXVec3Normalize(&fMoveVec, &fMoveVec);
						g_Skill[Indx].moveDest = fMoveVec * 10.0f;
						//g_Skill[nCnt].move = fMoveVec;
					}
					else
					{
						g_Skill[Indx].moveDest = D3DXVECTOR3(0.0, 0.0f, 0.0f);
					}
					break;
				}
			}
		}
		if (pBoss->bUse == true)
		{
			if (SerchHormingEnemy(Indx, pBoss->Object.Pos) == true)
			{
				g_Skill[Indx].rot = pPlayer->rot;
				g_Skill[Indx].bHorming = true;
				D3DXVECTOR3 fMoveVec = pBoss->Object.Pos - g_Skill[Indx].pos;
				D3DXVec3Normalize(&fMoveVec, &fMoveVec);
				g_Skill[Indx].moveDest = fMoveVec * 10.0f;
			}
		}
	}
	if (g_Skill[Indx].bHorming == true && g_Skill[Indx].bHit == false)
	{
		D3DXVECTOR3 fMove;
		fMove.x = cosf(g_Skill[Indx].fRotRatio) * sinf(pPlayer->rot.y + D3DX_PI * 0.5f) * 1.0f;
		fMove.y = sinf(g_Skill[Indx].fRotRatio) * 1.0f;
		fMove.z = cosf(g_Skill[Indx].fRotRatio) * cosf(pPlayer->rot.y + D3DX_PI * 0.5f) * 1.0f;

		g_Skill[Indx].move = fMove;

		g_Skill[Indx].AnimCounter++;
		if (g_Skill[Indx].AnimCounter >= 30)
		{
			D3DXVECTOR3 moveDiff = g_Skill[Indx].moveDest - g_Skill[Indx].move;
			g_Skill[Indx].move = moveDiff / g_Skill[Indx].AnimCounter * 20.0f;
		}
		else if (g_Skill[Indx].AnimCounter >= 20)
		{
			PlaySound(SOUND_LABEL_MAGIC);
		}
		else
		{
			g_Skill[Indx].nLife = 100;
		}
		//if(g_Skill[nCnt].AnimCounter >= )
	}
	else
	{
		UpdateHormingPosition(Indx);
	}
	g_Skill[Indx].pos += g_Skill[Indx].move;
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
			pDevice->SetTexture(0, g_apTextureSkill);

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
void SetSkill(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, SKILLTYPE ntype, float fRotRatio)
{
	//�v���C���[�̏��擾
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (g_Skill[nCnt].bUse == false)
		{
			g_Skill[nCnt].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
			g_Skill[nCnt].StartPos = g_Skill[nCnt].pos;
			g_Skill[nCnt].move = move;
			g_Skill[nCnt].Speed = 0.5f;
			g_Skill[nCnt].rot = rot;
			g_Skill[nCnt].ntype = ntype;
			g_Skill[nCnt].nLife = SKILL_LIFE;

			// �ʏ햂�@
			if (ntype == SKILLTYPE_NONE)
			{
				g_Skill[nCnt].fPower = pPlayer->Status.fPower;
			}
			// �z�[�~���O���@
			else if (ntype == SKILLTYPE_HORMING)
			{
				g_Skill[nCnt].fRotRatio = fRotRatio;
				g_Skill[nCnt].nCounter = 0;
				g_Skill[nCnt].nCount = 120;
				g_Skill[nCnt].nIndxHorming = 0;
				g_Skill[nCnt].bHorming = false;
				g_Skill[nCnt].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
				g_Skill[nCnt].Speed = 0.0f;
				g_Skill[nCnt].fDistance = 0.0f;
				g_Skill[nCnt].nLife = 300;
				g_Skill[nCnt].AnimCounter = 0;
				g_Skill[nCnt].fPower = pPlayer->Status.fPower / 5;
			}
			// �������@
			else if (ntype == SKILLTYPE_EXPLOSION)
			{
				g_Skill[nCnt].fPower = pPlayer->Status.fPower * 1.25f;
			}
			g_Skill[nCnt].bHit = false;
			g_Skill[nCnt].bUse = true;
			break;
		}
	}
}
//***************************************
// �z�[�~���O�͈͂ɓG�����邩��������֐�
//***************************************
bool SerchHormingEnemy(int Indx, D3DXVECTOR3 Pos)
{
	Player* pPLayer = GetPlayer();
	D3DXVECTOR3 fDistance = pPLayer->pos - Pos;
	if (sqrtf((fDistance.x * fDistance.x) + (fDistance.y + fDistance.y) + (fDistance.z * fDistance.z)) <= DISTANCE_HORMING)
	{
		if (g_Skill[Indx].fDistance <= sqrtf((fDistance.x * fDistance.x) + (fDistance.y + fDistance.y) + (fDistance.z * fDistance.z)))
		{
			g_Skill[Indx].fDistance = sqrtf((fDistance.x * fDistance.x) + (fDistance.y + fDistance.y) + (fDistance.z * fDistance.z));
		}
		return true;
		g_Skill[Indx].nCount = INTERVAL_HORMING;
	}
	return false;
}
//***********************************
// �z�[�~���O�̋��̈ʒu���X�V����֐�
//***********************************
void UpdateHormingPosition(int Indx)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 fDistance;
	fDistance.x = cosf(g_Skill[Indx].fRotRatio) * sinf(pPlayer->rot.y + D3DX_PI * 0.5f) * 50.0f;
	fDistance.y = sinf(g_Skill[Indx].fRotRatio) * 50.0f;
	fDistance.z = cosf(g_Skill[Indx].fRotRatio) * cosf(pPlayer->rot.y + D3DX_PI * 0.5f) * 50.0f;

	g_Skill[Indx].pos = D3DXVECTOR3(pPlayer->PlayerMotion.aModel[1].mtxWorld._41,
		pPlayer->PlayerMotion.aModel[1].mtxWorld._42,
		pPlayer->PlayerMotion.aModel[1].mtxWorld._43) + fDistance;
	g_Skill[Indx].StartPos = g_Skill[Indx].pos;
}
void UpdateHormingAnim(int Indx)
{

}
//==============
// ���@�̎擾
//==============
Skill* GetSkill()
{
	return &g_Skill[0];
}
//===============
// MP�����炷
//===============
void SubMP(SKILLTYPE type)
{
	Player* pPlayer = GetPlayer();

	switch (type)
	{
	case SKILLTYPE_NONE:
		pPlayer->Status.nMP -= 50;
		break;

	case SKILLTYPE_HORMING:
		pPlayer->Status.nMP -= 100;
		break;

	case SKILLTYPE_EXPLOSION:
		pPlayer->Status.nMP -= 10;
		break;
	default:
		break;
	}
}