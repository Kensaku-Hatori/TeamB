//=================================
//
// �v���C���[�\������[player.cpp]
// Author:kaiti
//
//=================================

#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "wall.h"
#include "timer.h"
#include "polygon.h"
#include "sound.h"
#include "skill.h"
#include "animation.h"
#include "enemy.h"
#include "game.h"
#include"impact.h"

//�O���[�o���ϐ�
Player g_player;
D3DXVECTOR3 g_vtxMinPlayer;//�v���C���[�̍ŏ��l
D3DXVECTOR3 g_vtxMaxPlayer;//�v���C���[�̍ő�l

int g_nCntHealMP;
//=====================
// �v���C���[�̏�����
//=====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot, 20.0f);//�e�̐ݒ�
	g_player.nJump = PLAYER_JUMP;

	//���[�V�����֘A
	g_player.bLoopMotion = true;//���[�v
	g_player.nNumKey = 2;//�L�[�̑���
	g_player.nCntMotion = 0;//���[�V�����J�E���^�[
	g_player.nKey = 0;//���݂̃L�[No
	g_player.nNumModel = 13;//�p�[�c�̑���

	g_player.bJump = false;//�W�����v

	//��b�X�e�[�^�X
	g_player.Status.fHP = PLAYER_HP;
	g_player.Status.nMP = PLAYER_MP;
	g_player.Status.fPower = PLAYER_MP;
	g_player.Status.fSpeed = PLAYER_SPEED;

	g_player.fDistance = PLAYER_RADIUS / 2;
	g_player.bLockOn = false;

	g_player.sightAngle = 0;
	g_player.sightRange = 0;

	g_nCntHealMP = 0;
}
//=======================
// �v���C���[�̏I������
//=======================
void UninitPlayer(void)
{
	//�v���C���[�̔j��
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		//���b�V���̔j��
		if (g_player.PlayerMotion.aModel[nCnt].pMesh != NULL)
		{
			g_player.PlayerMotion.aModel[nCnt].pMesh->Release();
			g_player.PlayerMotion.aModel[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_player.PlayerMotion.aModel[nCnt].pBuffMat != NULL)
		{
			g_player.PlayerMotion.aModel[nCnt].pBuffMat->Release();
			g_player.PlayerMotion.aModel[nCnt].pBuffMat = NULL;
		}
	}
}
//=======================
// �v���C���[�̍X�V����
//=======================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	if (g_player.bUse == true)
	{
		SetPositionShadow(g_player.nIdxShadow, g_player.pos, g_player.bUse);//�e
		SetSizeShadow(g_player.pos, g_player.nIdxShadow, g_player.bJump);

		PlayerMove();

		// �p�x�̋ߓ�
		if (g_player.rotDest.y - g_player.rot.y >= D3DX_PI)
		{
			g_player.rot.y += D3DX_PI * 2.0f;
		}
		else if (g_player.rotDest.y - g_player.rot.y <= -D3DX_PI)
		{
			g_player.rot.y -= D3DX_PI * 2.0f;
		}

		g_player.rot += (g_player.rotDest - g_player.rot) * 0.5f;


		//���@����
		if ((KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_B) == true))
		{// MP���T�O�ȏ�̎�
			if (g_player.Status.nMP >= 50)
			{
				SetSkill(g_player.pos, g_player.move, g_player.rot);
				g_player.Status.nMP -= 50; //MP����
			}
			SetMotion(MOTIONTYPE_ACTION,&g_player.PlayerMotion);
		}

		//MP��
		if (g_player.Status.nMP < PLAYER_MP)
		{//MP�������Ă�����
			g_nCntHealMP++;
		}
		if (g_nCntHealMP >= 60)
		{
			g_player.Status.nMP += 10;
			g_nCntHealMP = 0;
		}

		//�W�����v
		if ((KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true))
		{// SPACE
			if (g_player.bJump == false)
			{
				SetMotion(MOTIONTYPE_JUMP, &g_player.PlayerMotion);
				g_player.bJump = true;
				g_player.move.y += g_player.nJump;
			}
		}

		g_player.move.y -= 0.3f; //�d�͉��Z

		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//�ʒu���X�V
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
		g_player.pos.z += g_player.move.z;

		CollisionEnemy();

		//���b�N�I��
		if ((KeyboardTrigger(DIK_R) == true || GetJoypadTrigger(JOYKEY_R1) == true))
		{
			g_player.bLockOn = IsEnemyInsight();
		}

		// HP0
		if (g_player.Status.fHP <= 0.0f)
		{
			SetGameState(GAMESTATE_GAMEOVER);
		}

		//�n�ʂƂ̔���
		if (g_player.pos.y <= 0)
		{
			if (g_player.bJump == true)
			{
				g_player.bJump = false;
				if (g_player.PlayerMotion.motionType != MOTIONTYPE_LANDING)
				{
					SetMotion(MOTIONTYPE_LANDING, &g_player.PlayerMotion);
				}
			}
			g_player.pos.y = 0.0;
			g_player.move.y = 0.0;
		}

		//�ړ��ʂ��X�V
		g_player.move.x = 0.0f;
		g_player.move.z = 0.0f;


#ifdef _DEBUG
		//�ʒu���O��
		if (KeyboardTrigger(DIK_0) == true)
		{
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
			g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 400.0f);
		}
		//HP���炷
		if (KeyboardTrigger(DIK_9) == true)
		{
			g_player.Status.fHP -= 100;
			if (g_player.Status.fHP <= 0)
			{
				g_player.Status.fHP = 0;
			}
		}
		if (KeyboardTrigger(DIK_8) == true)
		{
			g_player.Status.nMP = PLAYER_MP;
			g_player.Status.fHP = PLAYER_HP;
		}
#endif
		UpdateMotion(&g_player.PlayerMotion);
	}
}
//===================
// �v���C���[�̕`��
//===================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bUse == true)
	{
		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;
		//���݂̃}�e���A���ۑ��p
		D3DMATERIAL9 matDef;
		//�}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATERIAL* pMat;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.mtxWorld);

		//�����𔽓]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�S�p�[�c�̕`��
		for (int nCntModel = 0; nCntModel < g_player.PlayerMotion.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;

			//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.PlayerMotion.aModel[nCntModel].rot.y, g_player.PlayerMotion.aModel[nCntModel].rot.x, g_player.PlayerMotion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_player.PlayerMotion.aModel[nCntModel].pos.x, g_player.PlayerMotion.aModel[nCntModel].pos.y, g_player.PlayerMotion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &g_player.PlayerMotion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
			if (g_player.PlayerMotion.aModel[nCntModel].Parent != -1)
			{
				mtxParent = g_player.PlayerMotion.aModel[g_player.PlayerMotion.aModel[nCntModel].Parent].mtxWorld;
			}
			else
			{
				mtxParent = g_player.mtxWorld;
			}

			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			D3DXMatrixMultiply(&g_player.PlayerMotion.aModel[nCntModel].mtxWorld,
				&g_player.PlayerMotion.aModel[nCntModel].mtxWorld,
				&mtxParent);
			
			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player.PlayerMotion.aModel[nCntModel].mtxWorld);
			
			//�p�[�c�̕`��
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player.PlayerMotion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player.PlayerMotion.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_player.PlayerMotion.aModel[nCntModel].pTexture[nCntMat]);
				//�v���C���[�̕`��
				g_player.PlayerMotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}
//======================
// �v���C���[�̈ړ�
//======================
void PlayerMove(void)
{
	Camera* pCamera;
	pCamera = GetCamera();

	//�ړ�
	//��
	if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}
		//�O
		if (GetKeyboardPress(DIK_W)|| GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		//��
		else if (GetKeyboardPress(DIK_S)|| GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		else
		{
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
		}
	}
	//�E
	else if (GetKeyboardPress(DIK_D)|| GetJoypadPress(JOYKEY_RIGET))
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}

		//�O
		if (GetKeyboardPress(DIK_W)|| GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		//��
		else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
		}
	}
	//�O
	else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_DOWN) == true)
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}

		//��
		if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		//�E
		else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		else
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
		}
	}
	//��
	else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_UP))
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE && g_player.PlayerMotion.motionType != MOTIONTYPE_JUMP)
		{
			SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
		}

		//��
		if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_DOWN))
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		//�E
		else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_UP))
		{
			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		else
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * g_player.Status.fSpeed;
			g_player.rotDest.y = pCamera->rot.y;
		}
	}
	//
	else
	{
		if (g_player.PlayerMotion.motionType == MOTIONTYPE_MOVE)
		{
			SetMotion(MOTIONTYPE_NEUTRAL, &g_player.PlayerMotion);
		}
	}

	//�ړ�����
	if (g_player.pos.x <= -945.0f)
	{
		g_player.pos.x = -945.0f;
	}
	if (g_player.pos.x >= 945.0f)
	{
		g_player.pos.x = 945.0f;
	}
	if (g_player.pos.z <= -945.0f)
	{
		g_player.pos.z = -945.0f;
	}
	if (g_player.pos.z >= 945.0f)
	{
		g_player.pos.z = 945.0f;
	}
}
//===================
// �v���C���[�̎擾
//===================
Player* GetPlayer(void)
{
	return &g_player;
}
void SetMesh(char* pFilePath, int Indx)
{

}

void SetPartsInfo(LoadInfo PartsInfo)
{
	g_player.PlayerMotion.nNumModel = PartsInfo.nNumParts;
	g_player.nNumModel = PartsInfo.nNumParts;
	for (int PartsCount = 0; PartsCount < g_player.PlayerMotion.nNumModel; PartsCount++)
	{
		g_player.PlayerMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_player.PlayerMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_player.PlayerMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_player.PlayerMotion.aModel[PartsCount].OffSet = PartsInfo.PartsInfo[PartsCount].OffSet;
		g_player.PlayerMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		HRESULT hresult = D3DXLoadMeshFromX(PartsInfo.cPartsPath[PartsCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.PlayerMotion.aModel[PartsCount].pBuffMat,
			NULL,
			&g_player.PlayerMotion.aModel[PartsCount].dwNumMat,
			&g_player.PlayerMotion.aModel[PartsCount].pMesh);

		if (FAILED(hresult))
		{
			return;
		}
		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		//���_���擾
		nNumVtx = g_player.PlayerMotion.aModel[PartsCount].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.PlayerMotion.aModel[PartsCount].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_player.PlayerMotion.aModel[PartsCount].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ăv���C���[�̍ŏ��l�A�ő�l���擾
			//�ŏ��l
			if (vtx.x < g_vtxMinPlayer.x)
			{
				g_vtxMinPlayer.x = vtx.x;
			}
			if (vtx.y < g_vtxMinPlayer.y)
			{
				g_vtxMinPlayer.y = vtx.y;
			}
			if (vtx.z < g_vtxMinPlayer.z)
			{
				g_vtxMinPlayer.z = vtx.z;
			}
			//�ő�l
			if (vtx.x > g_vtxMaxPlayer.x)
			{
				g_vtxMaxPlayer.x = vtx.x;
			}
			if (vtx.y > g_vtxMaxPlayer.y)
			{
				g_vtxMaxPlayer.y = vtx.y;
			}
			if (vtx.z > g_vtxMaxPlayer.z)
			{
				g_vtxMaxPlayer.z = vtx.z;
			}
			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		g_player.size = D3DXVECTOR3(g_vtxMaxPlayer.x - g_vtxMinPlayer.x, g_vtxMaxPlayer.y - g_vtxMinPlayer.y, g_vtxMaxPlayer.z - g_vtxMinPlayer.z);

		//���_�o�b�t�@�̃A�����b�N
		g_player.PlayerMotion.aModel[PartsCount].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
		pMat = (D3DXMATERIAL*)g_player.PlayerMotion.aModel[PartsCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.PlayerMotion.aModel[PartsCount].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_player.PlayerMotion.aModel[PartsCount].pTexture[nCntMat]); //1
			}
		}
	}
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++)
	{
		g_player.PlayerMotion.aMotionInfo[MotionCount] = PartsInfo.MotionInfo[MotionCount];
	}
	g_player.bUse = true;
}

void PlayerMotion(MOTIONINFO *pMotionInfo)
{
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++, pMotionInfo++)
	{
		g_player.PlayerMotion.aMotionInfo[MotionCount] = *pMotionInfo;
	}
	g_player.bUse = true;
}
//
//
//
bool IsEnemyInsight(void)
{
	ENEMY* pEnemy = GetEnemy();

	D3DXVECTOR3 playerFront;

	playerFront.x = -sinf(g_player.rot.y);
	playerFront.y = 0.0f;
	playerFront.z = -cosf(g_player.rot.y);

	D3DXVECTOR3 toEnemy;

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			toEnemy.x = pEnemy->Object.Pos.x - g_player.pos.x;
			toEnemy.y = 0.0f;
			toEnemy.z = pEnemy->Object.Pos.z - g_player.pos.z;

			D3DXVec3Normalize(&playerFront, &playerFront);

			D3DXVec3Normalize(&toEnemy, &toEnemy);

			float dotProduct = D3DXVec3Dot(&playerFront, &toEnemy);

			if (dotProduct > cosf(g_player.sightAngle * 0.5f))
			{
				float distanceSquared =
					(g_player.pos.x - pEnemy->Object.Pos.x) * (g_player.pos.x - pEnemy->Object.Pos.x) +
					(g_player.pos.y - pEnemy->Object.Pos.y) * (g_player.pos.y - pEnemy->Object.Pos.y) +
					(g_player.pos.z - pEnemy->Object.Pos.z) * (g_player.pos.z - pEnemy->Object.Pos.z);

				if (distanceSquared <= g_player.sightRange * g_player.sightRange)
				{
					EnemyDistanceSort(EnemyCount);
					return true;
				}
			}
		}
	}
	return false;
}
//
//
//
void EnemyDistanceSort(int EnemyCount)
{
	ENEMY* pEnemy = GetEnemy();

	//�G�Ƃ̋���
	pEnemy[EnemyCount].fDistance = sqrtf(((pEnemy[EnemyCount].Object.Pos.x - g_player.pos.x) * (pEnemy[EnemyCount].Object.Pos.x - g_player.pos.x))
									   + ((pEnemy[EnemyCount].Object.Pos.y - g_player.pos.y) * (pEnemy[EnemyCount].Object.Pos.y - g_player.pos.y))
									   + ((pEnemy[EnemyCount].Object.Pos.z - g_player.pos.z) * (pEnemy[EnemyCount].Object.Pos.z - g_player.pos.z)));

	float RADIUS = (g_player.fDistance + pEnemy[EnemyCount].Radius) * (g_player.fDistance + pEnemy[EnemyCount].Radius);

	if (pEnemy[EnemyCount].fDistance <= RADIUS)
	{

	}
}
