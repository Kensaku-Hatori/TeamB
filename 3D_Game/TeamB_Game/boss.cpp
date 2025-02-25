//*********************************************************
// 
// boss[boss.cpp]
// Author:Hatori
// 
//*********************************************************

//*************
// �C���N���[�h
///************
#include "boss.h"
#include "camera.h"
#include "particle.h"
#include "wall.h"
#include "loadmotion.h"
#include "shadow.h"
#include "animation.h"
#include "player.h"
#include "skill.h"
#include "collision.h"
#include "lockon.h"
#include "resultinfo.h"
#include "fade.h"

//*******************
// �O���[�o���ϐ��錾
//*******************
BOSS g_Boss;

//***************
// �{�X�̏���������
//***************
void InitBoss(void)
{
	g_Boss.state = BOSSSTATE_NORMAL;								// �G�̏��
	g_Boss.ActionType = BOSSACTION_WELL;							// ���[�V�����̎��
	g_Boss.Status.fPower = BOSS_AP;									// �U����
	g_Boss.Status.fSpeed = BOSS_SPEED;								// �X�s�[�h
	g_Boss.Status.fHP = BOSS_HP;									// HP
	g_Boss.BossMotion.motionType = MOTIONTYPE_NEUTRAL;				// ���[�V�����̎��
	g_Boss.BossMotion.nKey = 0;										// ���[�V�����̃L�[
	g_Boss.BossMotion.NextKey = 1;									// ���[�V�����̎��̃L�[
	g_Boss.BossMotion.bBlendMotion = true;							// ���[�V�����u�����h�����邩�ǂ���
	g_Boss.Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);			// �ʒu
	g_Boss.Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	g_Boss.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����(�ڕW)
	g_Boss.bUse = false;											// �g�p���Ă��邩�ǂ���
	g_Boss.nActionCount = 0;										// �A�N�V�����J�E���^�[
	g_Boss.nActionCounter = 0;										// �A�N�V�����J�E���^�[
	g_Boss.Action = BOSSACTION_WELL;								// �s���̎��
	g_Boss.Radius = 4.4f;											// ���a
}
//*************
// �{�X�̏I������
//*************
void UninitBoss(void)
{
	for (int PartsCount = 0; PartsCount < MAX_PARTS; PartsCount++)
	{ 
		// ���b�V���̔j��
		if (g_Boss.BossMotion.aModel[PartsCount].pMesh != NULL)
		{
			g_Boss.BossMotion.aModel[PartsCount].pMesh->Release();
			g_Boss.BossMotion.aModel[PartsCount].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (g_Boss.BossMotion.aModel[PartsCount].pBuffMat != NULL)
		{
			g_Boss.BossMotion.aModel[PartsCount].pBuffMat->Release();
			g_Boss.BossMotion.aModel[PartsCount].pBuffMat = NULL;
		}

		for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
		{//�e�N�X�`���̔j��
			if (g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount] != NULL)
			{
				g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount]->Release();
				g_Boss.BossMotion.aModel[PartsCount].pTexture[TexCount] = NULL;
			}
		}
	}
}

//*************
// �{�X�̍X�V����
//*************
void UpdateBoss(void)
{
	Player* pPlayer = GetPlayer();
	Skill* pSkill = GetSkill();

	if (g_Boss.bUse == true)
	{
		// �s���̍X�V
		UpdateBossAction();

		// ���@�Ƃ̓����蔻��
		for (int SkillCount = 0; SkillCount < MAX_SKILL; SkillCount++)
		{
			if (pSkill[SkillCount].bUse == true)
			{
				// �����蔻��
				if (collisioncircle(g_Boss.Object.Pos, g_Boss.Radius, pSkill[SkillCount].pos, SKILL_SIZE) == true)
				{
					pSkill[SkillCount].nLife = 1;
					pSkill[SkillCount].bHit = true;
					HitBoss(pPlayer->Status.fPower);
				}
			}
		}

		if (g_Boss.BossMotion.motionType == MOTIONTYPE_ACTION)
		{
			CollisionBossAction();
		}

		//���b�N�I��
		if (pPlayer->bWantLockOn == true)
		{
			if (IsEnemyInsight(g_Boss.Object.Pos, 1) == true)
			{
				pPlayer->bLockOn = true;
			}
		}

		// �p�x�̋ߓ�
		if (g_Boss.rotDest.y - g_Boss.Object.Rot.y >= D3DX_PI)
		{
			g_Boss.Object.Rot.y += D3DX_PI * 2.0f;
		}
		else if (g_Boss.rotDest.y - g_Boss.Object.Rot.y <= -D3DX_PI)
		{
			g_Boss.Object.Rot.y -= D3DX_PI * 2.0f;
		}

		if (g_Boss.statecount <= 0)
		{
			g_Boss.state = BOSSSTATE_NORMAL;
			g_Boss.statecount = 0;
		}
		g_Boss.statecount--;

		// �ړ��ʂ̍X�V(����)
		g_Boss.move.x = (0.0f - g_Boss.move.x) * 0.1f;
		g_Boss.move.y = (0.0f - g_Boss.move.y) * 0.1f;
		g_Boss.move.z = (0.0f - g_Boss.move.z) * 0.1f;

		// �ʒu�̍X�V
		g_Boss.Object.Pos += g_Boss.move;

		// ������
		if (g_Boss.Object.Pos.y < 0)
		{
			g_Boss.Object.Pos.y = 0;
		}

		g_Boss.Object.Rot.y += (g_Boss.rotDest.y - g_Boss.Object.Rot.y) * 0.05f;

		// �e�̍X�V
		SetPositionShadow(g_Boss.IndxShadow, g_Boss.Object.Pos, g_Boss.bUse);
		SetSizeShadow(g_Boss.Object.Pos, g_Boss.IndxShadow);

		// ���[�V�����̍X�V
		UpdateMotion(&g_Boss.BossMotion);
	}
}

//*************
// �{�X�̕`�揈��
//*************
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���ւ̃|�C���^


	if (g_Boss.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Boss.Object.mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Boss.Object.Rot.y, g_Boss.Object.Rot.x, g_Boss.Object.Rot.z);
		D3DXMatrixMultiply(&g_Boss.Object.mtxWorld, &g_Boss.Object.mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Boss.Object.Pos.x, g_Boss.Object.Pos.y, g_Boss.Object.Pos.z);
		D3DXMatrixMultiply(&g_Boss.Object.mtxWorld, &g_Boss.Object.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Boss.Object.mtxWorld);

		// ���݂̃}�e���A���̎擾
		pDevice->GetMaterial(&matDef);


		for (int EnemyPartsCount = 0; EnemyPartsCount < g_Boss.BossMotion.nNumModel; EnemyPartsCount++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;
			D3DXMatrixIdentity(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Boss.BossMotion.aModel[EnemyPartsCount].rot.y, g_Boss.BossMotion.aModel[EnemyPartsCount].rot.x, g_Boss.BossMotion.aModel[EnemyPartsCount].rot.z);
			D3DXMatrixMultiply(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &mtxRotModel);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_Boss.BossMotion.aModel[EnemyPartsCount].pos.x, g_Boss.BossMotion.aModel[EnemyPartsCount].pos.y, g_Boss.BossMotion.aModel[EnemyPartsCount].pos.z);
			D3DXMatrixMultiply(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld, &mtxTransModel);


			if (g_Boss.BossMotion.aModel[EnemyPartsCount].Parent != -1)
			{
				mtxParent = g_Boss.BossMotion.aModel[g_Boss.BossMotion.aModel[EnemyPartsCount].Parent].mtxWorld;
			}
			else
			{
				mtxParent = g_Boss.Object.mtxWorld;
			}
			D3DXMatrixMultiply(&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld,
				&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld,
				&mtxParent);

			pDevice->SetTransform(D3DTS_WORLD,
				&g_Boss.BossMotion.aModel[EnemyPartsCount].mtxWorld);

			// �}�e���A���f�[�^�ւ̃|�C���^
			pMat = (D3DXMATERIAL*)g_Boss.BossMotion.aModel[EnemyPartsCount].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Boss.BossMotion.aModel[EnemyPartsCount].dwNumMat; nCntMat++)
			{
				switch (g_Boss.state)
				{
				case BOSSSTATE_NORMAL:
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					break;
				case BOSSSTATE_KNOCKUP:
					D3DXMATERIAL Damage;
					Damage = pMat[nCntMat];

					Damage.MatD3D.Diffuse.r = 255;
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&Damage.MatD3D);
					break;
				default:
					break;
				}
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Boss.BossMotion.aModel[EnemyPartsCount].pTexture[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_Boss.BossMotion.aModel[EnemyPartsCount].pMesh->DrawSubset(nCntMat);
			}
		}
		pDevice->SetMaterial(&matDef);
	}
}

//*************
// �{�X�̎擾����
//*************
BOSS* GetBoss()
{
	return &g_Boss;
}

//***************
// �{�X�̃q�b�g����
//***************
void HitBoss(float Atack)
{
	Camera* pCamera = GetCamera();

	g_Boss.Status.fHP -= (int)Atack;

	g_Boss.Action = BOSSACTION_WELL;
	g_Boss.state = BOSSSTATE_KNOCKUP;

	if (Atack >= 10)
	{// �_���[�W���ŏ��l�ȏ�Ȃ�
		g_Boss.statecount = 30;
	}
	else
	{// �_���[�W���ŏ��l�ȉ��Ȃ�
		g_Boss.statecount = 30;
	}

	if (g_Boss.Status.fHP <= 0.0f && g_Boss.bUse == true)
	{// �g���Ă��đ̗͂��O�ȉ��Ȃ�
		DeadBoss();
	}
}

//*************
// �{�X�̐ݒ菈��
//*************
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	MODE nMode = GetMode();

	if (g_Boss.bUse == false)
	{
		g_Boss.bUse = true;
		g_Boss.Object.Pos = pos;
		g_Boss.Object.Rot = rot;
		g_Boss.state = BOSSSTATE_NORMAL;
		g_Boss.IndxShadow = SetShadow(g_Boss.Object.Pos, g_Boss.Object.Rot, 20.0f);
		g_Boss.nActionCount = rand() % 180 + 120;
	}
}

//*************
// �{�X�̎��S����
//*************
void DeadBoss()
{
	MODE nMode = GetMode();
	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	g_Boss.bUse = false;
	SetPositionShadow(g_Boss.IndxShadow, g_Boss.Object.Pos, g_Boss.bUse);

	SetParticle(g_Boss.Object.Pos,
		D3DXVECTOR3(100.0f, 100.0f, 100.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		PARTICLE_NONE,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		100,
		50,
		2.0f,
		2.0f,
		1.0f,
		EFFECT_NONE);

	//���b�N�I������
	if (pPlayer->bLockOn == true)
	{
		if (pPlayer->nLockOnEnemy == 0)
		{
			pPlayer->bLockOn = false;
		}
	}

	SetFade(MODE_RESULT);
	SetResult(RESULT_CLEAR);
}

//***************
// �{�X�̍s�����X�V
//***************
void UpdateBossAction()
{
	Player* pPlayer = GetPlayer();					// �v���C���[�̏��擾

	// �G�ƃv���C���[�̋����v�Z
	D3DXVECTOR3 vec = pPlayer->pos - g_Boss.Object.Pos;
	float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);
	float fAngle = 0.0f;

	fDistance = (float)sqrt(fDistance);				// �G�ƃv���C���[�̋���

	// �p�x�̎擾
	fAngle = (float)atan2(vec.x, vec.z);

	// �ڕW�̈ړ������i�p�x�j�̕␳
	if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	else if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}

	// �U��
	if (fDistance <= BOSSATTACK_DIST)
	{
		if (pPlayer->state != PLAYERSTATE_KNOCKUP)
		{
			if (g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
			{// ���[�V�����̎�ސݒ�
				g_Boss.ActionType = BOSSACTION_ATTACK;
				//g_Boss[nCount].BossMotion.motionType = MOTIONTYPE_ACTION;//�������ꂵ���@�\���Ă��Ȃ�
				//g_Boss[nCount].BossMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
				//g_Boss[nCount].BossMotion.nFrameBlend = 10.0f;
				//g_Boss[nCount].BossMotion.nKey = 0;
				//g_Boss[nCount].BossMotion.NextKey = 1;
				SetMotion(MOTIONTYPE_ACTION, &g_Boss.BossMotion);
			}
		}
	}
	// �ǂ�������
	else if (fDistance <= BOSSHORMING_DIST)
	{
		if (g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
		{//���[�V�����̎�ސݒ�
			g_Boss.ActionType = BOSSACTION_RUN;
			//g_Boss[nCount].BossMotion.motionType = MOTIONTYPE_MOVE;//�������ꂵ���@�\���Ă��Ȃ�
			//g_Boss[nCount].BossMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
			//g_Boss[nCount].BossMotion.nFrameBlend = 10.0f;

			// �ړ��ʂ̐ݒ�
			g_Boss.move.x = sinf(fAngle) * BOSSHORMING_MOVE;
			g_Boss.move.z = cosf(fAngle) * BOSSHORMING_MOVE;

			// �p�x�̖ڕW�ݒ�
			g_Boss.rotDest.y = fAngle + D3DX_PI;

			if (g_Boss.BossMotion.motionType != MOTIONTYPE_MOVE)
			{
				SetMotion(MOTIONTYPE_MOVE, &g_Boss.BossMotion);
			}
		}
	}
	// �l�q��
	else
	{
		g_Boss.ActionType = BOSSACTION_WELL;
		//g_Boss[nCount].BossMotion.motionType = MOTIONTYPE_NEUTRAL;
		//g_Boss[nCount].pMotion = MOTIONTYPE_NEUTRAL;
		if (g_Boss.BossMotion.motionType != MOTIONTYPE_NEUTRAL && g_Boss.BossMotion.motionType != MOTIONTYPE_ACTION)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_Boss.BossMotion);
		}
	}
}

//*****************
// �{�X�̏�ԑJ�ڏ���
//*****************
void BossState(int Indx)
{

}

//******************
// �G�̃I�t�Z�b�g?
//******************
void SetBossPartsInfo(LoadInfo PartsInfo)
{
	g_Boss.nNumModel = PartsInfo.nNumParts;
	g_Boss.BossMotion.nNumModel = PartsInfo.nNumParts;

	for (int PartsCount = 0; PartsCount < g_Boss.nNumModel; PartsCount++)
	{
		g_Boss.BossMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_Boss.BossMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_Boss.BossMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_Boss.BossMotion.aModel[PartsCount].OffSetPos = PartsInfo.PartsInfo[PartsCount].OffSetPos;
		g_Boss.BossMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;
		g_Boss.BossMotion.aModel[PartsCount].OffSetRot = PartsInfo.PartsInfo[PartsCount].OffSetRot;

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		HRESULT hresult = D3DXLoadMeshFromX(PartsInfo.cPartsPath[PartsCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Boss.BossMotion.aModel[PartsCount].pBuffMat,
			NULL,
			&g_Boss.BossMotion.aModel[PartsCount].dwNumMat,
			&g_Boss.BossMotion.aModel[PartsCount].pMesh);

		if (FAILED(hresult))
		{
			return;
		}

		int nNumVtx;   // ���_��
		DWORD sizeFVF; // ���_�t�H�[�}�b�g�̃T�C�Y

		// ���_���擾
		nNumVtx = g_Boss.BossMotion.aModel[PartsCount].pMesh->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_Boss.BossMotion.aModel[PartsCount].pMesh->GetFVF());

		D3DXMATERIAL* pMat;		// �}�e���A���ւ̃|�C���^
		pMat = (D3DXMATERIAL*)g_Boss.BossMotion.aModel[PartsCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Boss.BossMotion.aModel[PartsCount].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Boss.BossMotion.aModel[PartsCount].pTexture[nCntMat]); //1
			}
		}
	}
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
	{
		g_Boss.BossMotion.aMotionInfo[MotionCount] = PartsInfo.MotionInfo[MotionCount];
	}
}

//==============================
// �{�X�ƃv���C���[�̓����蔻��
//==============================
void CollisionBoss(void)
{
	Player* pPlayer = GetPlayer();

	if (g_Boss.bUse == true)
	{
		//�G�Ƃ̋���
		g_Boss.fDistance = sqrtf(((g_Boss.Object.Pos.x - pPlayer->pos.x) * (g_Boss.Object.Pos.x - pPlayer->pos.x))
							   + ((g_Boss.Object.Pos.y - pPlayer->pos.y) * (g_Boss.Object.Pos.y - pPlayer->pos.y))
							   + ((g_Boss.Object.Pos.z - pPlayer->pos.z) * (g_Boss.Object.Pos.z - pPlayer->pos.z)));

		float RADIUS = ((PLAYER_RADIUS / 2) + g_Boss.Radius) * ((PLAYER_RADIUS / 2) + g_Boss.Radius);

		if (g_Boss.fDistance <= RADIUS)
		{
			HitPlayer(g_Boss.Status.fPower,g_Boss.Object.Pos);
		}
	}
}
//===================================
// �G�̃A�N�V�������̓����蔻�菈��
//===================================
void CollisionBossAction(void)
{
	Player* pPlayer = GetPlayer();

	if (collisioncircle(g_Boss.BossMotion.aModel[12].pos, g_Boss.Radius * 1.5f, pPlayer->pos, PLAYER_RADIUS) == true)
	{
		HitPlayer(g_Boss.Status.fPower,g_Boss.Object.Pos);
	}
}

//===================================
//�{�X�̎��S�t���O�擾����
//===================================
bool DethBoss(void)
{
	return g_Boss.bUse;
}