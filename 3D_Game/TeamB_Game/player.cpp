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
#include "balltimer.h"
#include "motion.h"
#include "timer.h"
#include "polygon.h"
#include "sound.h"

//�O���[�o���ϐ�
Player g_player;
D3DXVECTOR3 g_vtxMinPlayer;//�v���C���[�̍ŏ��l
D3DXVECTOR3 g_vtxMaxPlayer;//�v���C���[�̍ő�l

////�j���[�g�������[�V����
//static KEY_INFO g_aKeyNeutral[] =
//{
//	//�L�[�O
//	{40,
//		{
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c0
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.85f},	//�p�[�c1
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.60f},	//�p�[�c2
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c3
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.85f},	//�p�[�c4
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.60f},	//�p�[�c5
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c6
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c7
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c8
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.10f},	//�p�[�c9
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c10
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c11
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}		//�p�[�c12
//		}
//	},
//	//�L�[�P
//	{40,
//		{
//			{0.0f,0.0f,0.0f,0.13f,0.0f,0.0f},	//�p�[�c�O
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.66f},	//�p�[�c�P
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.44f},	//�p�[�c2
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c3
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.66f},	//�p�[�c4
//			{0.0f,0.0f,0.0f,0.0f,0.0f,-0.44f},	//�p�[�c5
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c6
//			{0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f},	//�p�[�c7
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c8
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.10f},	//�p�[�c9
//			{0.0f,0.0f,0.0f,-0.13f,0.0f,0.0f},	//�p�[�c10
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f},	//�p�[�c11
//			{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}		//�p�[�c12
//		}
//	}
//};

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
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot);//�e
	g_player.type = PLAYERTYPE_HITO;
	g_player.fSpeed = PLAYER_HITOSPEED;
	g_player.nJump = PLAYER_HITOJUMP;
	g_player.nBallTime = MAX_BALLTIME;
	g_player.nCntKill = 0;
	g_player.nCntPin = 0;
	//���[�V�����֘A
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = true;//���[�v
	g_player.nNumKey = 2;//�L�[�̑���
	g_player.nCntMotion = 0;//���[�V�����J�E���^�[
	g_player.nKey = 0;//���݂̃L�[No
	g_player.nNumModel = 13;//�p�[�c�̑���

	g_player.bBall = true;
	g_player.bJump = false;//�W�����v
	g_player.bUse = true;

	LoadPlayer();

#if 0
	//X�t�@�C���̓ǂݍ���
	{
		D3DXLoadMeshFromX("data\\MODEL\\00_body02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[0].pBuffMat,
			NULL,
			&g_player.aModel[0].dwNumMat,
			&g_player.aModel[0].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\02_armUR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[1].pBuffMat,
			NULL,
			&g_player.aModel[1].dwNumMat,
			&g_player.aModel[1].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\02_armFR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[2].pBuffMat,
			NULL,
			&g_player.aModel[2].dwNumMat,
			&g_player.aModel[2].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\03_handR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[3].pBuffMat,
			NULL,
			&g_player.aModel[3].dwNumMat,
			&g_player.aModel[3].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\04_armUL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[4].pBuffMat,
			NULL,
			&g_player.aModel[4].dwNumMat,
			&g_player.aModel[4].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\04_armFL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[5].pBuffMat,
			NULL,
			&g_player.aModel[5].dwNumMat,
			&g_player.aModel[5].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\05_handL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[6].pBuffMat,
			NULL,
			&g_player.aModel[6].dwNumMat,
			&g_player.aModel[6].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\06_legUR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[7].pBuffMat,
			NULL,
			&g_player.aModel[7].dwNumMat,
			&g_player.aModel[7].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\06_legFR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[8].pBuffMat,
			NULL,
			&g_player.aModel[8].dwNumMat,
			&g_player.aModel[8].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\07_footR02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[9].pBuffMat,
			NULL,
			&g_player.aModel[9].dwNumMat,
			&g_player.aModel[9].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\08_legUL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[10].pBuffMat,
			NULL,
			&g_player.aModel[10].dwNumMat,
			&g_player.aModel[10].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\08_legFL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[11].pBuffMat,
			NULL,
			&g_player.aModel[11].dwNumMat,
			&g_player.aModel[11].pMesh);

		D3DXLoadMeshFromX("data\\MODEL\\09_footL02.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[12].pBuffMat,
			NULL,
			&g_player.aModel[12].dwNumMat,
			&g_player.aModel[12].pMesh);
	}

	//�e�p�[�c�̊K�w�\���ݒ�
	//{
	//	g_player.aModel[0].nIdxModelParent = -1;			   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 11.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[1].nIdxModelParent = 0;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[1].pos = D3DXVECTOR3(-9.0f, 13.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[2].nIdxModelParent = 1;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[2].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[3].nIdxModelParent = 2;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[3].pos = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[4].nIdxModelParent = 0;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[4].pos = D3DXVECTOR3(9.0f, 13.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[5].nIdxModelParent = 4;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[5].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[6].nIdxModelParent = 5;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[6].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[7].nIdxModelParent = 0;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[7].pos = D3DXVECTOR3(-5.0f, 1.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[8].nIdxModelParent = 7;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[8].pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[9].nIdxModelParent = 8;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -5.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[10].nIdxModelParent = 0;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[10].pos = D3DXVECTOR3(5.0f, 1.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[11].nIdxModelParent = 10;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[11].pos = D3DXVECTOR3(0.0f, -3.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�

	//	g_player.aModel[12].nIdxModelParent = 11;				   //�e�v���C���[�̃C���f�b�N�X��ݒ�
	//	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -5.0f, 0.0f);//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	//	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏����ݒ�
	//}
#endif

	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		int nNumVtx;   //���_��
		DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		//���_���擾
		nNumVtx = g_player.aModel[nCnt].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y�擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCnt].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_player.aModel[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
		g_player.aModel[nCnt].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
		pMat = (D3DXMATERIAL*)g_player.aModel[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_player.aModel[nCnt].pTexture[nCnt]); //1
			}
		}
	}
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
		if (g_player.aModel[nCnt].pMesh != NULL)
		{
			g_player.aModel[nCnt].pMesh->Release();
			g_player.aModel[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_player.aModel[nCnt].pBuffMat != NULL)
		{
			g_player.aModel[nCnt].pBuffMat->Release();
			g_player.aModel[nCnt].pBuffMat = NULL;
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

		//SetEffect(g_player.pos,g_player.move, g_player.rot);

		if (g_player.bJump == true)
		{
			g_player.fSpeed /= 1.5;
		}
		//�ړ�
		if (GetKeyboardPress(DIK_D) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
		}
		if (GetKeyboardPress(DIK_W) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			//if (g_player.type == PLAYERTYPE_HITO)
			//{
			//	g_player.motionType = MOTIONTYPE_MOVE;
			//}
			//else
			//{
			//	g_player.motionType = MOTIONTYPE_BALLMOVE;
			//}
			//g_player.motionType = MOTIONTYPE_MOVE;

			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * g_player.fSpeed;
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

		//���[�h�ύX
		if (KeyboardTrigger(DIK_RETURN) == true)
		{
			//g_player.motionType = MOTIONTYPE_ACTION;

			if (g_player.type == PLAYERTYPE_HITO)
			{//�l�̎�
				if (g_player.bBall == true && g_player.nBallTime > 0)
				{//�{�[���g�p�\��
					g_player.type = PLAYERTYPE_BALL;
				}
			}
			else if (g_player.type == PLAYERTYPE_BALL)
			{//�{�[���̎�
				g_player.type = PLAYERTYPE_HITO;
			}
		}

		//�W�����v
		if (KeyboardTrigger(DIK_SPACE) == true)
		{// SPACE
			if (g_player.bJump == false)
			{
				//if (g_player.type == PLAYERTYPE_HITO)
				//{
				//	g_player.motionType = MOTIONTYPE_JUMP;
				//}
				//else
				//{
				//	g_player.motionType = MOTIONTYPE_BALLJUMP;
				//}
				//g_player.motionType = MOTIONTYPE_JUMP;

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
		//CollisionWall();
		CollisionEnemy();
		//CollisionPolygon();

		//�n�ʂƂ̔���
		if (g_player.pos.y <= 0)
		{
			if (g_player.bJump == true)
			{
				//if (g_player.type == PLAYERTYPE_HITO)
				//{
				//	g_player.motionType = MOTIONTYPE_LANDING;
				//}
				//else
				//{
				//	g_player.motionType = MOTIONTYPE_BALLLANDING;
				//}
				g_player.bJump = false;
			}
			g_player.pos.y = 0.0;
			g_player.move.y = 0.0;
		}

		//�ړ��ʂ��X�V
		g_player.move.x = 0.0f;
		g_player.move.z = 0.0f;

		//�{�[����ԂȂ�
		if (g_player.type == PLAYERTYPE_BALL)
		{
			SetEffect(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 10.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), EFFECT_LIFE, EFFECT_SIZE);
			g_player.fSpeed = PLAYER_BALLSPEED;
			g_player.nJump = PLAYER_BALLJUMP;
		}
		//�l�^�Ȃ�
		else if (g_player.type == PLAYERTYPE_HITO)
		{
			g_player.fSpeed = PLAYER_HITOSPEED;
			g_player.nJump = PLAYER_HITOJUMP;
		}
		//�X�[�p�[�{�[���Ȃ�
		else if (g_player.type == PLAYERTYPE_SUPERBALL)
		{
			SetEffect(D3DXVECTOR3(g_player.pos.x + 10.0f, g_player.pos.y + 5.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.8f, 0.0f, 1.0f, 1.0f), EFFECT_LIFE, EFFECT_SIZE);
			SetEffect(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 5.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f), EFFECT_LIFE, EFFECT_SIZE);
			SetEffect(D3DXVECTOR3(g_player.pos.x - 10.0f, g_player.pos.y + 5.0f, g_player.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.8f, 0.0f, 1.0f, 1.0f), EFFECT_LIFE, EFFECT_SIZE);
			g_player.fSpeed = PLAYER_SUPERBALLSPEED;
			g_player.nJump = PLAYER_HITOJUMP;
		}

		//�P�O�̓|������
		if (g_player.nCntPin >= PIN_CONDITION && g_player.type != PLAYERTYPE_SUPERBALL)
		{
			g_player.type = PLAYERTYPE_SUPERBALL;
			SetBallTimer(MAX_BALLTIME + 100);
			//PlaySound(SOUND_LABEL_BALL);
		}

		//�����{�[�����Ԃ��O�ɂȂ�����
		if (g_player.nBallTime <= 0)
		{
			if (g_player.type == PLAYERTYPE_SUPERBALL)
			{
				SetBallTimer(0);
				g_player.nCntPin = 0;
				StopSound(SOUND_LABEL_BALL);
			}
			g_player.type = PLAYERTYPE_HITO;
			g_player.bBall = false;
		}

#ifdef _DEBUG

		//�ʒu���O��
		if (KeyboardTrigger(DIK_0) == true)
		{
			g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
#endif

		//�ړ�����
		if (g_player.pos.x <= -POLYGON_X)
		{
			g_player.pos.x = -POLYGON_X;
		}
		if (g_player.pos.x >= POLYGON_X)
		{
			g_player.pos.x = POLYGON_X;
		}
		if (g_player.pos.z <= -POLYGON_Y)
		{
			g_player.pos.z = -POLYGON_Y;
		}
		if (g_player.pos.z >= POLYGON_Y)
		{
			g_player.pos.z = POLYGON_Y;
		}

		//���[�V����
		SetPlayerMotion();
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
		for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;

			//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
			if (g_player.aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player.mtxWorld;
			}

			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
				&g_player.aModel[nCntModel].mtxWorld,
				&mtxParent);
			
			//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player.aModel[nCntModel].mtxWorld);
			
			//�p�[�c�̕`��
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_player.aModel[nCntModel].pTexture[nCntModel]);
				//�v���C���[�̕`��
				g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
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
//=================
// ���[�V�����ݒ�
//=================
void SetPlayerMotion(void)
{
	//�S���f���̍X�V
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		//���̃L�[
		int nNext = (g_player.nKey + 1) % g_player.aMotionInfo[g_player.motionType].nNumKey;
		//�L�[����߂�
		if (g_player.nKey >= g_player.aMotionInfo[g_player.motionType].nNumKey || nNext >= g_player.aMotionInfo[g_player.motionType].nNumKey)
		{
			g_player.nKey = 0;
		}

		D3DXVECTOR3 posMotion, rotMotion, posSabun, rotSabun;

		//�����v�Z
		//pos
		posSabun.x = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fPosX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX;
		posSabun.y = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fPosY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY;
		posSabun.z = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fPosZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ;
		//rot
		rotSabun.x = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fRotX - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX;
		rotSabun.y = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fRotY - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY;
		rotSabun.z = g_player.aMotionInfo[g_player.motionType].aKeyInfo[nNext].aKey[nCnt].fRotZ - g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ;

		float fDis = (float)g_player.nCntMotion / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;

		//�p�[�c�̈ʒu�E�������Z�o
		posMotion.x = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosX + posSabun.x * fDis);
		posMotion.y = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosY + posSabun.y * fDis);
		posMotion.z = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fPosZ + posSabun.z * fDis);

		rotMotion.x = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotX + rotSabun.x * fDis);
		rotMotion.y = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotY + rotSabun.y * fDis);
		rotMotion.z = (g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCnt].fRotZ + rotSabun.z * fDis);

		////���̃L�[
		//int nNext = (g_player.nKey + 1) % g_player.nNumKey;
		////�L�[����߂�
		//if (g_player.nKey >= g_player.nNumKey || nNext >= g_player.nNumKey)
		//{
		//	g_player.nKey = 0;
		//}
		//
		//D3DXVECTOR3 posMotion, rotMotion, posSabun, rotSabun;
		//
		////�����v�Z
		////pos
		//posSabun.x = g_aKeyNeutral[nNext].aKey[nCnt].fPosX - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosX;
		//posSabun.y = g_aKeyNeutral[nNext].aKey[nCnt].fPosY - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosY;
		//posSabun.z = g_aKeyNeutral[nNext].aKey[nCnt].fPosZ - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosZ;
		////rot
		//rotSabun.x = g_aKeyNeutral[nNext].aKey[nCnt].fRotX - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotX;
		//rotSabun.y = g_aKeyNeutral[nNext].aKey[nCnt].fRotY - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotY;
		//rotSabun.z = g_aKeyNeutral[nNext].aKey[nCnt].fRotZ - g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotZ;
		//
		//float fDis = (float)g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame;
		//
		////�p�[�c�̈ʒu�E�������Z�o
		//posMotion.x = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosX + posSabun.x * fDis);
		//posMotion.y = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosY + posSabun.y * fDis);
		//posMotion.z = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosZ + posSabun.z * fDis);
		//
		//rotMotion.x = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotX + rotSabun.x * fDis);
		//rotMotion.y = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotY + rotSabun.y * fDis);
		//rotMotion.z = (g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotZ + rotSabun.z * fDis);

		////�J�N�J�N
		////�p�[�c�̈ʒu�E�������Z�o
		//posMotion.x = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosX + posSabun.x * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//posMotion.y = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosY + posSabun.y * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//posMotion.z = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fPosZ + posSabun.z * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//
		//rotMotion.x = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotX + rotSabun.x * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//rotMotion.y = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotY + rotSabun.y * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);
		//rotMotion.z = g_aKeyNeutral[g_player.nKey].aKey[nCnt].fRotZ + rotSabun.z * (g_player.nCntMotion / g_aKeyNeutral[g_player.nKey].nFrame);

		g_player.aModel[nCnt].pos += posMotion;
		g_player.aModel[nCnt].rot = rotMotion;
	}

	g_player.nCntMotion++;

	if (g_player.nCntMotion >= g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame)
	{
		g_player.nCntMotion = 0;

		g_player.nKey++;

		//g_player.motionType = MOTIONTYPE_NEUTRAL;
	}
}
//=================================
// �v���C���[�̃t�@�C���ǂݍ���
//=================================
void LoadPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	int Index;
	int nNum_Parts;
	int nCntModel = 0;
	int nLoop;
	int nCntMotion = 0;
	int nCntParts = 0;
	int nCntKey = 0;

	FILE* pFile;
	pFile = fopen(MOTIONFILE_PLAYER, "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];

		fscanf(pFile, "%s", &aString[0]);
		if (strcmp(aString, "SCRIPT") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);

				//���f����
				if (strcmp(aString, "NUM_MODEL") == 0)
				{
					fscanf(pFile, "%d", &g_player.nNumModel);
				}
				//���f���t�@�C����
				else if (strcmp(aString, "MODEL_FILENAME") == 0)
				{
					fscanf(pFile, "%s", &aString[0]);

					const char* ModelName = {};
					ModelName = aString;

					D3DXLoadMeshFromX(ModelName,
									  D3DXMESH_SYSTEMMEM,
									  pDevice,
									  NULL,
									  &g_player.aModel[nCntModel].pBuffMat,
									  NULL,
									  &g_player.aModel[nCntModel].dwNumMat,
									  &g_player.aModel[nCntModel].pMesh);
					nCntModel++;
				}
				//�L�����N�^�[���
				else if (strcmp(aString, "CHARACTERSET") == 0)
				{
					while (1)
					{
						fscanf(pFile, "%s", &aString[0]);

						//�p�[�c��
						if (strcmp(aString, "NUM_PARTS") == 0)
						{
							fscanf(pFile, "%d", &nNum_Parts);
						}
						//�p�[�c�ݒ�
						else if (strcmp(aString, "PARTSSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aString[0]);

								//�C���f�b�N�X
								if (strcmp(aString, "INDEX") == 0)
								{
									fscanf(pFile, "%d", &Index);
								}
								//�e���f���̃C���f�b�N�X
								else if (strcmp(aString, "PARENT") == 0)
								{
									fscanf(pFile, "%d", &g_player.aModel[Index].nIdxModelParent);
								}
								//�ʒu
								else if (strcmp(aString, "POS") == 0)
								{
									fscanf(pFile, "%f", &g_player.aModel[Index].pos.x);
									fscanf(pFile, "%f", &g_player.aModel[Index].pos.y);
									fscanf(pFile, "%f", &g_player.aModel[Index].pos.z);
								}
								//����
								else if (strcmp(aString, "ROT") == 0)
								{
									fscanf(pFile, "%f", &g_player.aModel[Index].rot.x);
									fscanf(pFile, "%f", &g_player.aModel[Index].rot.y);
									fscanf(pFile, "%f", &g_player.aModel[Index].rot.z);
								}
								else if (strcmp(aString, "END_PARTSSET") == 0)
								{
									break;
								}
							}
						}
						else if (strcmp(aString, "END_CHARACTERSET") == 0)
						{
							break;
						}
					}
				}
				//���[�V����
				else if (strcmp(aString, "MOTIONSET") == 0)
				{
					while (1)
					{
						fscanf(pFile, "%s", &aString[0]);
						//���[�v			
						if (strcmp(aString, "LOOP") == 0)
						{
							fscanf(pFile, "%d", &nLoop);
						}
						//�L�[��
						else if (strcmp(aString, "NUM_KEY") == 0)
						{
							fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].nNumKey);
						}
						//�L�[���
						else if (strcmp(aString, "KEYSET") == 0)
						{
							while (1)
							{
								fscanf(pFile, "%s", &aString[0]);
								//�t���[����
								if (strcmp(aString, "FRAME") == 0)
								{
									fscanf(pFile, "%d", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);								
								}
								//�L�[
								else if (strcmp(aString, "KEY") == 0)
								{
									while (1)
									{
										fscanf(pFile, "%s", &aString[0]);
										//�ʒu
										if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
										}
										//����
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
											fscanf(pFile, "%f", &g_player.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
										}
										else if (strcmp(aString, "END_KEY") == 0)
										{
											nCntParts++;
											break;
										}
									}
								}
								else if (strcmp(aString, "END_KEYSET") == 0)
								{
									nCntKey++;
									nCntParts = 0;
									break;
								}
							}
						}
						else if (strcmp(aString, "END_MOTIONSET") == 0)
						{
							nCntMotion++;
							nCntKey = 0;
							break;
						}
					}
				}
				else if (strcmp(aString, "END_SCRIPT") == 0)
				{
					break;
				}
			}
		}		
		fclose(pFile);//�t�@�C�������
	}
	else
	{
		return;
	}
}