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
int g_nTypeCountMotion = 0;
int g_PartsNum = 0;

//***************
// �G�̏���������
//***************
void InitEnemy(void)
{
	g_nNumEnemy = 0;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_nTypeCountMotion = 0;
		g_Enemy[i].Object.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
		g_Enemy[i].Object.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].bUse = false;
		g_Enemy[i].pMotion = MOTIONTYPE_NEUTRAL;
		g_Enemy[i].nActionCount = 0;
		g_Enemy[i].nActionCounter = 0;
		g_Enemy[i].Action = ENEMYACTION_WELL;
		g_Enemy[i].Status.fPower = ENEMY_AP;
		g_Enemy[i].Status.fSpeed = ENEMY_SPEED;
		g_Enemy[i].Status.fHP = ENEMY_HP;
		g_Enemy[i].state = ENEMYSTATE_NORMAL;
		g_Enemy[i].Radius = 4.4f;
		g_Enemy[i].pMotion = MOTIONTYPE_NEUTRAL;
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
			if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh->Release();
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pMesh = NULL;
			}
			if (g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat != NULL)
			{
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat->Release();
				g_EnemyOrigin[OriginCount].EnemyMotion.aModel[PartsCount].pBuffMat = NULL;
			}
			for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
			{
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
	D3DXMATRIX mtxRot, mtxTrans, mtxSize;				// �v�Z�p�}�g���b�N�X
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
		g_Enemy[Indx].statecount = (int)Atack * 3;
	}
	else
	{// �_���[�W���ŏ��l�ȉ��Ȃ�
		g_Enemy[Indx].statecount = 10;
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
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].OffSet = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSet;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].rot = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].rot;

				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].dwNumMat = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].dwNumMat;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pBuffMat = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pBuffMat;
				g_Enemy[EnemyCount].EnemyMotion.aModel[PartsCount].pMesh = g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].pMesh;

				for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
				{
					g_Enemy[EnemyCount].EnemyMotion.aMotionInfo[MotionCount] = g_EnemyOrigin[nType].EnemyMotion.aMotionInfo[MotionCount];
				}
			}
			g_Enemy[EnemyCount].IndxShadow = SetShadow(g_Enemy[EnemyCount].Object.Pos, g_Enemy[EnemyCount].Object.Rot,g_Enemy[EnemyCount].Radius);
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
// �G�̎��b����
//*************
void DeadEnemy(int Indx)
{
	MODE nMode = GetMode();
	Player* pPlayer = GetPlayer();

	g_Enemy[Indx].bUse = false;
	g_nNumEnemy--;
	SetPositionShadow(g_Enemy[Indx].IndxShadow,g_Enemy[Indx].Object.Pos,g_Enemy[Indx].bUse);
	SetParticle(g_Enemy[Indx].Object.Pos, D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PARTICLE_NONE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100, 50);	
	//���b�N�I������
	if (pPlayer->bLockOn == true)
	{
		if (pPlayer->nLockOnEnemy == Indx)
		{
			pPlayer->bLockOn = false;
		}
	}
}

//***************
// �G�̍s�����X�V
//***************
void UpdateAction(int nCount)
{

}

//*****************
// �G�̏�ԑJ�ڏ���
//*****************
void EnemyState(int Indx)
{

}
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
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].OffSet = PartsInfo.PartsInfo[PartsCount].OffSet;
		g_EnemyOrigin[nType].EnemyMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;

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