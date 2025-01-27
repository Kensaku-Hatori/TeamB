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
#include "block.h"
#include "wall.h"
#include "enemy.h"
#include "timer.h"
#include "polygon.h"
#include "sound.h"
#include "skill.h"
#include "animation.h"

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

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	g_player.Status.nHP = PLAYER_HP;
	g_player.Status.nMP = PLAYER_MP;
	g_player.Status.fSpeed = PLAYER_SPEED;


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

		//�ړ�
		//��
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{// A
			if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_UP) == true)
			{//����
				g_player.move.x -= sinf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
				g_player.move.z += cosf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			}
			else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{//���O
				g_player.move.x -= sinf(D3DX_PI * 0.25f) * g_player.Status.fSpeed;
				g_player.move.z += cosf(D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			}
			else
			{//��
				g_player.move.x -= g_player.Status.fSpeed;
			}
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
		}
		//�E
		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
		{// D
			if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_UP) == true)
			{//�E��
				g_player.move.x += sinf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
				g_player.move.z += cosf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			}
			else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{//�E�O
				g_player.move.x += sinf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
				g_player.move.z -= cosf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			}
			else
			{//�E
				g_player.move.x += g_player.Status.fSpeed;
			}
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
		}
		//�O
		else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{// S
			if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
			{//���O
				g_player.move.x -= sinf(D3DX_PI * 0.25f) * g_player.Status.fSpeed;
				g_player.move.z += cosf(D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
			{//�E�O
				g_player.move.x += sinf(D3DX_PI * 0.25f) * g_player.Status.fSpeed;
				g_player.move.z -= cosf(D3DX_PI * 0.25f) * g_player.Status.fSpeed;
			}
			else
			{//�O
				g_player.move.z += g_player.Status.fSpeed;
			}
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
		}
		//��
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_UP) == true)
		{// W
			if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
			{//����
				g_player.move.x -= sinf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
				g_player.move.z += cosf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
			{//�E��
				g_player.move.x += sinf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
				g_player.move.z += cosf(D3DX_PI * 0.75f) * g_player.Status.fSpeed;
			}
			else
			{//��
				g_player.move.z -= g_player.Status.fSpeed;
			}
			g_player.rotDest.y = pCamera->rot.y;
		}
		////�p�x�̐��K��
		//if (g_player.rotDest.y > D3DX_PI / 2)
		//{
		//	g_player.rot.y -= D3DX_PI;
		//}
		//if (g_player.rotDest.y < -g_player.rot.y)
		//{
		//	g_player.rot.y += D3DX_PI;
		//}

		g_player.rot += (g_player.rotDest - g_player.rot) * 0.5f;

		//���@����
		if (((KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)) && g_player.Status.nMP >= 50)
		{// MP���T�O�ȏ�̎�
			SetMotion(MOTIONTYPE_ACTION,&g_player.PlayerMotion);
			SetSkill(g_player.pos, g_player.move, g_player.rot);
			g_player.Status.nMP -= 50; //MP����
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
		if (KeyboardTrigger(DIK_SPACE) == true)
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

		//�����蔻��
		g_player.bJump = !CollisionBlock();
		CollisionEnemy();

		//�n�ʂƂ̔���
		if (g_player.pos.y <= 0)
		{
			if (g_player.bJump == true)
			{
				//SetMotion(MOTIONTYPE_LANDING, &g_player.PlayerMotion);
				g_player.bJump = false;
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
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		//HP���炷
		if (KeyboardTrigger(DIK_9) == true)
		{
			g_player.Status.nHP -= 100;
			if (g_player.Status.nHP <= 0)
			{
				g_player.Status.nHP = 0;
			}
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
				pDevice->SetTexture(0, g_player.PlayerMotion.aModel[nCntModel].pTexture[nCntModel]);
				//�v���C���[�̕`��
				g_player.PlayerMotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXLoadMeshFromX(pFilePath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.PlayerMotion.aModel[Indx].pBuffMat,
		NULL,
		&g_player.PlayerMotion.aModel[Indx].dwNumMat,
		&g_player.PlayerMotion.aModel[Indx].pMesh);

		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		//���_���擾
		nNumVtx = g_player.PlayerMotion.aModel[Indx].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.PlayerMotion.aModel[Indx].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_player.PlayerMotion.aModel[Indx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
	g_player.PlayerMotion.aModel[Indx].pMesh->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	pMat = (D3DXMATERIAL*)g_player.PlayerMotion.aModel[Indx].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_player.PlayerMotion.aModel[Indx].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_player.PlayerMotion.aModel[Indx].pTexture[Indx]); //1
		}
	}
	g_player.bUse = true;
}
void SetPartsInfo(MODELINFO ModelInfo,int Indx)
{
	g_player.PlayerMotion.aModel[Indx].nIndx = ModelInfo.nIndx;
	g_player.PlayerMotion.aModel[Indx].Parent = ModelInfo.Parent;
	g_player.PlayerMotion.aModel[Indx].pos = ModelInfo.pos;
	g_player.PlayerMotion.aModel[Indx].rot = ModelInfo.rot;
	g_player.PlayerMotion.aModel[Indx].size = ModelInfo.size;
	g_player.PlayerMotion.aModel[Indx].OffSet = ModelInfo.pos;
	int i = 0;
}
void PlayerMotion(MOTIONINFO *pMotionInfo)
{
	for (int MotionCount = 0; MotionCount < MOTIONTYPE_MAX; MotionCount++, pMotionInfo++)
	{
		g_player.PlayerMotion.aMotionInfo[MotionCount] = *pMotionInfo;
	}
}