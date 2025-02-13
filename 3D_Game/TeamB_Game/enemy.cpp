//*********************************************************
// 
// enemy[enemy.cpp]
// Author:Hatori
// 
//*********************************************************

//*************
// �C���N���[�h
///************
#include "enemy.h"
#include "camera.h"
#include "particle.h"
#include "wall.h"
#include "loadmotion.h"
#include "shadow.h"
#include "animation.h"
#include "player.h"

//*******************
// �O���[�o���ϐ��錾
//*******************
ENEMY g_Enemy[MAX_ENEMY];
EnemyOrigin g_EnemyOrigin[ENEMYTYPE_MAX];
int g_nNumEnemy;
float g_fDistance[MAX_ENEMY];//�f�o�b�N�t�H���g�p

//***************
// �G�̏���������
//***************
void InitEnemy(void)
{
	//�G�̐��̏�����
	g_nNumEnemy = 0;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].state = ENEMYSTATE_NORMAL;								// �G�̏��
		g_Enemy[i].ActionType = ENEMYACTION_WELL;							// ���[�V�����̎��
		g_Enemy[i].Status.fPower = ENEMY_AP;								// �U����
		g_Enemy[i].Status.fSpeed = ENEMY_SPEED;								// �X�s�[�h
		g_Enemy[i].Status.fHP = ENEMY_HP;									// HP
		g_Enemy[i].EnemyMotion.motionType = MOTIONTYPE_NEUTRAL;				// ���[�V�����̎��
		g_Enemy[i].EnemyMotion.nKey = 0;									// ���[�V�����̃L�[
		g_Enemy[i].EnemyMotion.NextKey = 1;									// ���[�V�����̎��̃L�[
		g_Enemy[i].EnemyMotion.bBlendMotion = true;
		g_Enemy[i].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);			// �ʒu
		g_Enemy[i].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
		g_Enemy[i].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����(�ڕW)
		g_Enemy[i].bUse = false;											// �g�p���Ă��邩�ǂ���
		g_Enemy[i].nActionCount = 0;										// �A�N�V�����J�E���^�[
		g_Enemy[i].nActionCounter = 0;										// �A�N�V�����J�E���^�[
		g_Enemy[i].Action = ENEMYACTION_WELL;								// �s���̎��
		g_Enemy[i].Radius = 4.4f;											// ���a

		g_fDistance[i] = 0.0f;
	}
}
//*************
// �G�̏I������
//*************
void UninitEnemy(void)
{
	for (int OriginCount = 0; OriginCount < ENEMYTYPE_MAX; OriginCount++)
	{
		for (int PartsCount = 0; PartsCount < MAX_PARTS; PartsCount++)
		{
			//���b�V���̔j��
			if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh->Release();
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat->Release();
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat = NULL;
			}

			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
				//�e�N�X�`���̔j��
				if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pTexture[TexCount] != NULL)
				{
					g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pTexture[TexCount]->Release();
					g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pTexture[TexCount] = NULL;
				}
			}
		}
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		for (int i1 = 0; i1 < MAX_ENEMYPARTS; i1++)
		{
			// ���b�V���̔j��
			if (g_Enemy[i].EnemyMotion.aModel[i1].pMesh != NULL)
			{
				g_Enemy[i].EnemyMotion.aModel[i1].pMesh = NULL;
			}

			// �}�e���A���̔j��
			if (g_Enemy[i].EnemyMotion.aModel[i1].pBuffMat != NULL)
			{
				g_Enemy[i].EnemyMotion.aModel[i1].pBuffMat = NULL;
			}

			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
				//�e�N�X�`���̔j��
				if (g_Enemy[i].EnemyMotion.aModel[i1].pTexture[TexCount] != NULL)
				{
					g_Enemy[i].EnemyMotion.aModel[i1].pTexture[TexCount] = NULL;
				}
			}
		}
	}
}

//*************
// �G�̍X�V����
//*************
void UpdateEnemy(void)
{
	MODE nMode = GetMode();

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == true)
		{
			//�s���̍X�V
			UpdateAction(EnemyCount);

			// �p�x�̋ߓ�
			if (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y >= D3DX_PI)
			{
				g_Enemy[EnemyCount].Object.Rot.y += D3DX_PI * 2.0f;
			}
			else if (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y <= -D3DX_PI)
			{
				g_Enemy[EnemyCount].Object.Rot.y -= D3DX_PI * 2.0f;
			}

			if (g_Enemy[EnemyCount].statecount <= 0)
			{
				g_Enemy[EnemyCount].state = ENEMYSTATE_NORMAL;
				g_Enemy[EnemyCount].statecount = 0;
			}
			g_Enemy[EnemyCount].statecount--;

			//�ړ��ʂ̍X�V(����)
			g_Enemy[EnemyCount].move.x = (0.0f - g_Enemy[EnemyCount].move.x) * 0.1f;
			g_Enemy[EnemyCount].move.y = (0.0f - g_Enemy[EnemyCount].move.y) * 0.1f;
			g_Enemy[EnemyCount].move.z = (0.0f - g_Enemy[EnemyCount].move.z) * 0.1f;

			//������
			if (g_Enemy[EnemyCount].Object.Pos.y < 0)
			{
				g_Enemy[EnemyCount].Object.Pos.y = 0;
			}

			g_Enemy[EnemyCount].Object.Rot.y += (g_Enemy[EnemyCount].rotDest.y - g_Enemy[EnemyCount].Object.Rot.y) * 0.05f;

			//�e�̍X�V
			SetPositionShadow(g_Enemy[EnemyCount].IndxShadow, g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].bUse);
			SetSizeShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].IndxShadow);

			//���[�V�����̍X�V
			UpdateMotion(&g_Enemy[EnemyCount].EnemyMotion);
		}
	}
}

//*************
// �G�̕`�揈��
//*************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���ւ̃|�C���^


	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[EnemyCount].Object.mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[EnemyCount].Object.Rot.y, g_Enemy[EnemyCount].Object.Rot.x, g_Enemy[EnemyCount].Object.Rot.z);
			D3DXMatrixMultiply(&g_Enemy[EnemyCount].Object.mtxWorld, &g_Enemy[EnemyCount].Object.mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[EnemyCount].Object.Pos.x, g_Enemy[EnemyCount].Object.Pos.y, g_Enemy[EnemyCount].Object.Pos.z);
			D3DXMatrixMultiply(&g_Enemy[EnemyCount].Object.mtxWorld, &g_Enemy[EnemyCount].Object.mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[EnemyCount].Object.mtxWorld);

			// ���݂̃}�e���A���̎擾
			pDevice->GetMaterial(&matDef);


			for (int EnemyPartsCount = 0; EnemyPartsCount < g_EnemyOrigin[g_Enemy[EnemyCount].nType].nNumParts; EnemyPartsCount++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;
				D3DXMATRIX mtxParent;
				D3DXMatrixIdentity(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld);

				// �����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot.y, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot.x, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].rot.z);
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &mtxRotModel);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos.x, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos.y, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pos.z);
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld, &mtxTransModel);


				if (g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].Parent != -1)
				{
					mtxParent = g_Enemy[EnemyCount].EnemyMotion.aModel[g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].Parent].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[EnemyCount].Object.mtxWorld;
				}
				D3DXMatrixMultiply(&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld,
					&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld,
					&mtxParent);

				pDevice->SetTransform(D3DTS_WORLD,
					&g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].mtxWorld);

				// �}�e���A���f�[�^�ւ̃|�C���^
				pMat = (D3DXMATERIAL*)g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].dwNumMat; nCntMat++)
				{
					switch (g_Enemy[EnemyCount].state)
					{
					case ENEMYSTATE_NORMAL:
						// �}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
						break;
					case ENEMYSTATE_KNOCKUP:
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
					pDevice->SetTexture(0, g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pTexture[nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_Enemy[EnemyCount].EnemyMotion.aModel[EnemyPartsCount].pMesh->DrawSubset(nCntMat);
				}
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//*************
// �G�̎擾����
//*************
ENEMY* GetEnemy()
{
	return &g_Enemy[0];
}

//***************
// �G�̃q�b�g����
//***************
void HitEnemy(float Atack,int Indx)
{
	Camera* pCamera = GetCamera();

	g_Enemy[Indx].Status.fHP -= (int)Atack;

	g_Enemy[Indx].Action = ENEMYACTION_WELL;
	g_Enemy[Indx].state = ENEMYSTATE_KNOCKUP;

	if (Atack >= 10)
	{// �_���[�W���ŏ��l�ȏ�Ȃ�
		//g_Enemy[Indx].statecount = (int)Atack * 3;
		g_Enemy[Indx].statecount = 30;

	}
	else
	{// �_���[�W���ŏ��l�ȉ��Ȃ�
		g_Enemy[Indx].statecount = 30;
	}

	if (g_Enemy[Indx].Status.fHP <= 0.0f && g_Enemy[Indx].bUse == true)
	{// �g���Ă��đ̗͂��O�ȉ��Ȃ�
		DeadEnemy(Indx);
	}
}

//*************
// �G�̐ݒ菈��
//*************
void SetEnemy(D3DXVECTOR3 pos, int nType,D3DXVECTOR3 rot)
{
	MODE nMode = GetMode();

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (g_Enemy[EnemyCount].bUse == false)
		{
			g_nNumEnemy++;
			g_Enemy[EnemyCount].bUse = true;
			g_Enemy[EnemyCount].Object.Pos = pos;
			g_Enemy[EnemyCount].Object.Rot = rot;
			g_Enemy[EnemyCount].state = ENEMYSTATE_NORMAL;
			g_Enemy[EnemyCount].nType = nType;
			g_Enemy[EnemyCount].nNumModel = g_EnemyOrigin[nType].nNumParts;
			g_Enemy[EnemyCount].EnemyMotion.nNumModel = g_EnemyOrigin[nType].nNumParts;
			for (int PartsCount = 0; PartsCount < g_EnemyOrigin[nType].nNumParts; PartsCount++)
			{
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].nIndx = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].nIndx;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].Parent = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].Parent;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pos = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pos;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].OffSetPos = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetPos;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].rot = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].rot;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].OffSetRot = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetRot;

				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].dwNumMat = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pBuffMat = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pMesh = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh;

				for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
				{
					g_Enemy[EnemyCount].EnemyMotion.aMotionInfo[MotionCount] = g_EnemyOrigin[nType].EnemyMotion.aMotionInfo[MotionCount];
				}
			}
			g_Enemy[EnemyCount].IndxShadow = SetShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].Object.Rot,20.0f);
			g_Enemy[EnemyCount].nActionCount = rand() % 180 + 120;

			break;
		}
	}
}

//*************
// �G�̎擾����
//*************
int* GetNumEnemy(void)
{
	return &g_nNumEnemy;
}

//*************
// �G�̎��S����
//*************
void DeadEnemy(int Indx)
{
	MODE nMode = GetMode();
	Player* pPlayer = GetPlayer();
	Camera* pCamera = GetCamera();

	g_Enemy[Indx].bUse = false;
	g_nNumEnemy--;
	SetPositionShadow(g_Enemy[Indx].IndxShadow,g_Enemy[Indx].Object.Pos,g_Enemy[Indx].bUse);

	SetParticle(g_Enemy[Indx].Object.Pos, 
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
		if (pPlayer->nLockOnEnemy == Indx)
		{
			pPlayer->bLockOn = false;
			pCamera->rot.y = 0.0f; //�J�����߂�
		}
	}
}

//***************
// �G�̍s�����X�V
//***************
void UpdateAction(int nCount)
{
	Player* pPlayer = GetPlayer();				//�v���C���[�̏��擾

	//�G�ƃv���C���[�̋����v�Z
	D3DXVECTOR3 vec = pPlayer->pos - g_Enemy[nCount].Object.Pos;
	float fDistance = (vec.x) * (vec.x) + (vec.z) * (vec.z);
	float fAngle = 0.0f;

	fDistance = (float)sqrt(fDistance);				//�G�ƃv���C���[�̋���
	g_fDistance[nCount] = fDistance;

	//�p�x�̎擾
	fAngle = (float)atan2(vec.x, vec.z);

	//�ڕW�̈ړ������i�p�x�j�̕␳
	if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	else if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}

	//�U��
	if (fDistance <= ATTACK_DIST)
	{
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			//���[�V�����̎�ސݒ�
			g_Enemy[nCount].ActionType = ENEMYACTION_ATTACK;
			//g_Enemy[nCount].EnemyMotion.motionType = MOTIONTYPE_ACTION;//�������ꂵ���@�\���Ă��Ȃ�
			//g_Enemy[nCount].EnemyMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
			//g_Enemy[nCount].EnemyMotion.nFrameBlend = 10.0f;
			//g_Enemy[nCount].EnemyMotion.nKey = 0;
			//g_Enemy[nCount].EnemyMotion.NextKey = 1;
			SetMotion(MOTIONTYPE_ACTION, &g_Enemy[nCount].EnemyMotion);
		}
	}
	//�ǂ�������
	else if (fDistance <= HOMING_DIST)
	{
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			//���[�V�����̎�ސݒ�
			g_Enemy[nCount].ActionType = ENEMYACTION_RUN;
			//g_Enemy[nCount].EnemyMotion.motionType = MOTIONTYPE_MOVE;//�������ꂵ���@�\���Ă��Ȃ�
			//g_Enemy[nCount].EnemyMotion.motionTypeBlend = MOTIONTYPE_NEUTRAL;
			//g_Enemy[nCount].EnemyMotion.nFrameBlend = 10.0f;

			//�ړ��ʂ̐ݒ�
			g_Enemy[nCount].move.x = sinf(fAngle) * HOMING_MOVE;
			g_Enemy[nCount].move.z = cosf(fAngle) * HOMING_MOVE;

			//�ʒu�̍X�V
			g_Enemy[nCount].Object.Pos += g_Enemy[nCount].move;

			//�p�x�̖ڕW�ݒ�
			g_Enemy[nCount].rotDest.y = fAngle + D3DX_PI;

			if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_MOVE)
			{
				SetMotion(MOTIONTYPE_MOVE, &g_Enemy[nCount].EnemyMotion);
			}

		}
	}
	//�l�q��
	else
	{
		g_Enemy[nCount].ActionType = ENEMYACTION_WELL;
		//g_Enemy[nCount].EnemyMotion.motionType = MOTIONTYPE_NEUTRAL;
		//g_Enemy[nCount].pMotion = MOTIONTYPE_NEUTRAL;
		if (g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_NEUTRAL && g_Enemy[nCount].EnemyMotion.motionType != MOTIONTYPE_ACTION)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_Enemy[nCount].EnemyMotion);
		}
	}
}

//*****************
// �G�̏�ԑJ�ڏ���
//*****************
void EnemyState(int Indx)
{

}

//******************
// �G�̃I�t�Z�b�g?
//******************
void SetEnemyPartsInfo(LoadInfo PartsInfo, int nType)
{
	nType -= 1;
	g_EnemyOrigin[nType].nNumParts = PartsInfo.nNumParts;
	g_EnemyOrigin[nType].EnemyMotion.nNumModel = PartsInfo.nNumParts;
	for (int PartsCount = 0; PartsCount < g_EnemyOrigin[nType].nNumParts; PartsCount++)
	{
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetPos = PartsInfo.PartsInfo[PartsCount].OffSetPos;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSetRot = PartsInfo.PartsInfo[PartsCount].OffSetRot;

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		HRESULT hresult = D3DXLoadMeshFromX(PartsInfo.cPartsPath[PartsCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat,
			NULL,
			&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat,
			&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh);

		if (FAILED(hresult))
		{
			return;
		}

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y

		//���_���擾
		nNumVtx = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh->GetFVF());

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
		pMat = (D3DXMATERIAL*)g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename, 
					&g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pTexture[nCntMat]); //1
			}
		}
	}
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
	{
		g_EnemyOrigin[nType].EnemyMotion.aMotionInfo[MotionCount] = PartsInfo.MotionInfo[MotionCount];
	}
}

//==============================
// �G�ƃv���C���[�̓����蔻��
//==============================
void CollisionEnemy(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//�G�Ƃ̋���
			g_Enemy[nCntEnemy].fDistance = sqrtf(((g_Enemy[nCntEnemy].Object.Pos.x - pPlayer->pos.x) * (g_Enemy[nCntEnemy].Object.Pos.x - pPlayer->pos.x))
											   + ((g_Enemy[nCntEnemy].Object.Pos.y - pPlayer->pos.y) * (g_Enemy[nCntEnemy].Object.Pos.y - pPlayer->pos.y))
											   + ((g_Enemy[nCntEnemy].Object.Pos.z - pPlayer->pos.z) * (g_Enemy[nCntEnemy].Object.Pos.z - pPlayer->pos.z)));

			float RADIUS = ((PLAYER_RADIUS / 2) + g_Enemy[nCntEnemy].Radius) * ((PLAYER_RADIUS / 2) + g_Enemy[nCntEnemy].Radius);

			if (g_Enemy[nCntEnemy].fDistance <= RADIUS)
			{
				pPlayer->Status.fHP -= g_Enemy[nCntEnemy].Status.fPower;
			}
		}
	}
}

//========================
// �����̎擾
//========================
float GetfDistance()
{
	return g_fDistance[0];
}