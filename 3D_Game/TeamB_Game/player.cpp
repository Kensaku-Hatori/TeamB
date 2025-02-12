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
#include "fade.h"
#include "light.h"
#include "Item.h"
#include "circle.h"
#include "arrow.h"
#include "invisiblewall.h"

//�O���[�o���ϐ�
Player g_player;
D3DXVECTOR3 g_vtxMinPlayer;//�v���C���[�̍ŏ��l
D3DXVECTOR3 g_vtxMaxPlayer;//�v���C���[�̍ő�l

int g_nCntHealMP;
bool bfirst = true;
bool g_bAbolition = false;//�S�Ńt���O

//=====================
// �v���C���[�̏�����
//=====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (bfirst == false)
	{
		g_player.pos = g_player.NextPosition;
	}
	else
	{
		bfirst = false;
		g_player.pos = D3DXVECTOR3(0.0f,0.0f,100.0f);
	}
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot, 20.0f);//�e�̐ݒ�
	g_player.nIndxCircle = 0;
	g_player.nJump = PLAYER_JUMP;
	g_player.bJump = false;		//�W�����v
	//g_player.bLanding = true;

	//���[�V�����֘A
	g_player.bLoopMotion = true;//���[�v
	g_player.PlayerMotion.bBlendMotion = true;
	g_player.nNumKey = 2;		//�L�[�̑���
	g_player.nCntMotion = 0;	//���[�V�����J�E���^�[
	g_player.nKey = 0;			//���݂̃L�[No
	g_player.nNumModel = 13;	//�p�[�c�̑���

	//��b�X�e�[�^�X
	g_player.Status.fHP = PLAYER_HP;
	g_player.Status.nMP = PLAYER_MP;
	g_player.Status.fPower = PLAYER_MP;
	g_player.Status.fSpeed = PLAYER_SPEED;

	//���b�N�I���֘A
	g_player.bLockOn = false;
	g_player.fSightRange = 200.0f;					// ���E����
	g_player.fSightAngle = D3DXToRadian(110.0f);	// ���E�̗t��
	g_player.fDistance = g_player.fSightRange / 2;
	g_player.nLockOnEnemy = 0;

	//�S�Ńt���O
	g_bAbolition = false;				//�S�ł��Ă��Ȃ����

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
	Camera *pCamera = GetCamera();				//�J�����̏��擾
	ENEMY* pEnemy = GetEnemy();					//�G�̏��擾
	int* NumEnemy = GetNumEnemy();				//�G�̐��擾

	if (g_player.bUse == true)
	{
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_ACTION)
		{
			//�v���C���[�ړ�
			PlayerMove();
		}

		//���b�N�I����ԂȂ�
		if (g_player.bLockOn == true)
		{
			pCamera->rot.y = g_player.rot.y + D3DX_PI;
			
			//�v���C���[�̌���
			float fMathDistance, fMathDistance1;
			fMathDistance = pEnemy[g_player.nLockOnEnemy].Object.Pos.x - g_player.pos.x;
			fMathDistance1 = pEnemy[g_player.nLockOnEnemy].Object.Pos.z - g_player.pos.z;
			g_player.rotDest.y = atan2f(fMathDistance, fMathDistance1) + D3DX_PI;
			

			//�����ɂ�����
			float Dis = ((g_player.pos.x - pEnemy[g_player.nLockOnEnemy].Object.Pos.x) * (g_player.pos.x - pEnemy[g_player.nLockOnEnemy].Object.Pos.x))
				   	  + ((g_player.pos.y - pEnemy[g_player.nLockOnEnemy].Object.Pos.y) * (g_player.pos.y - pEnemy[g_player.nLockOnEnemy].Object.Pos.y))
				      + ((g_player.pos.z - pEnemy[g_player.nLockOnEnemy].Object.Pos.z) * (g_player.pos.z - pEnemy[g_player.nLockOnEnemy].Object.Pos.z));
			if (Dis >= g_player.fSightRange * g_player.fSightRange * 2)
			{
				g_player.bLockOn = false;
				pCamera->rot.y = 0.0f; //�J�����߂�
			}
		}

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
		if ((KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_B) == true) && g_player.PlayerMotion.motionType != MOTIONTYPE_ACTION)
		{// MP���T�O�ȏ�̎�
			SetMotion(MOTIONTYPE_ACTION, &g_player.PlayerMotion);
			if (g_player.Status.nMP >= 50)
			{
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[0].bActionStart = false;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[0].bFirst = false;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[0].nStartKey = 3;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[0].nEndKey = 3;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[0].nStartFrame = 23;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[0].nEndFrame = 24;

				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[1].bActionStart = false;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[1].bFirst = false;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[1].nStartKey = 3;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[1].nEndKey = 3;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[1].nStartFrame = 20;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[1].nEndFrame = 24;

				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[2].bActionStart = false;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[2].bFirst = false;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[2].nStartKey = 0;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[2].nEndKey = 0;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[2].nStartFrame = 1;
				g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[2].nEndFrame = 2;

				g_player.Status.nMP -= 50; //MP����
			}
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

				g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_LANDING].ActionFrameInfo[0].bActionStart = false;
				g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_LANDING].ActionFrameInfo[0].bFirst = false;
				g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_LANDING].ActionFrameInfo[0].nStartKey = 0;
				g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_LANDING].ActionFrameInfo[0].nEndKey = 0;
				g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_LANDING].ActionFrameInfo[0].nStartFrame = 1;
				g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_LANDING].ActionFrameInfo[0].nEndFrame = 2;

				g_player.bJump = true;
				g_player.move.y += g_player.nJump;
			}
		}

		if (g_player.bJump == true)
		{
			g_player.bLanding = false;
		}
		if (g_player.bLanding == false)
		{
			g_player.move.y -= GRAVITY; //�d�͉��Z	
		}

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
			if (g_player.bLockOn == true)
			{
				g_player.bLockOn = g_player.bLockOn ? false : true;
				pCamera->rot.y = 0.0f; //�J�����߂�
			}
			else if(g_player.bLockOn == false)
			{
				g_player.bLockOn = IsEnemyInsight();
			}
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
		//��
		if (KeyboardTrigger(DIK_8) == true)
		{
			g_player.Status.nMP = PLAYER_MP;
			g_player.Status.fHP = PLAYER_HP;
		}
		//�X�e�[�W�ړ�
		if (KeyboardTrigger(DIK_DELETE) && GetKeyboardPress(DIK_5))
		{
			SetFade(MODE_STAGEONE);
		}
		else if (KeyboardTrigger(DIK_DELETE) && GetKeyboardPress(DIK_6))
		{
			SetFade(MODE_STAGETWO);
		}
		else if (KeyboardTrigger(DIK_DELETE) && GetKeyboardPress(DIK_7))
		{
			SetFade(MODE_STAGETHREE);
		}
		else if (KeyboardTrigger(DIK_DELETE) && GetKeyboardPress(DIK_8))
		{
			SetFade(MODE_STAGEFOUR);
		}
		if (KeyboardTrigger(DIK_3) == true)
		{
			SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 100.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetEnemy(D3DXVECTOR3(100.0f, 0.0f, 100.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (KeyboardTrigger(DIK_4) == true)
		{
			SetItem(D3DXVECTOR3(0.0f, 0.0f, -100.0f), ITEMTYPE_HP);
			SetItem(D3DXVECTOR3(100.0f, 0.0f, -100.0f), ITEMTYPE_MP);
			SetItem(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), ITEMTYPE_SPEED);
		}

#endif

		//�G��S�ē|���Ă���Ȃ�
		if (*(NumEnemy) <= 0)
		{
			if (g_bAbolition != true)
			{
				//�G���A�ړ��ʒu�̎擾
				D3DXVECTOR3 Destpos = GetBottom();

				//�T�[�N���̐ݒ菈��
				g_player.nIndxCircle = SetCircle(g_player.pos, g_player.rot, D3DCOLOR_RGBA(255, 255, 100, 204), 12, 0, 10.0f, 25.0f, true, false);

				//���̐ݒ菈��
				SetArrow(Destpos, g_player.pos, 40.0f, 20.0f, 26.0f);

				//�S�ł��Ă����Ԃɂ���
				g_bAbolition = true;
			}
		}

		//�G���S�ł��Ă���Ȃ�
		if (g_bAbolition == true)
		{
			//�T�[�N���̈ʒu�̍X�V����
			SetPositionCircle(g_player.nIndxCircle, g_player.pos, g_player.rot);

			//���̈ʒu�X�V
			SetPositonArrow(g_player.pos);
		}

		//�e�̑傫���̍X�V����
		SetSizeShadow(g_player.pos, g_player.nIdxShadow);

		//�e�̈ʒu�̍X�V����
		SetPositionShadow(g_player.nIdxShadow, g_player.pos, g_player.bUse);//�e

		//���[�V�����̍X�V����
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
			D3DXMATRIX mtxRotModel, mtxTransModel,mtxShadow;
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
			if (nCntModel == 12)
			{
				MatrixWand();
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

	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[0].bActionStart = false;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[0].bFirst = false;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[0].nStartKey = 1;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[0].nEndKey = 1;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[0].nStartFrame = 1;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[0].nEndFrame = 2;

	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[1].bActionStart = false;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[1].bFirst = false;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[1].nStartKey = 3;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[1].nEndKey = 3;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[1].nStartFrame = 1;
	g_player.PlayerMotion.aMotionInfo[MOTIONTYPE_MOVE].ActionFrameInfo[1].nEndFrame = 2;

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
	if (g_player.pos.x <= -STAGE_SIZE)
	{
		g_player.pos.x = -STAGE_SIZE;
	}
	if (g_player.pos.x >= STAGE_SIZE)
	{
		g_player.pos.x = STAGE_SIZE;
	}
	if (g_player.pos.z <= -STAGE_SIZE)
	{
		g_player.pos.z = -STAGE_SIZE;
	}
	if (g_player.pos.z >= STAGE_SIZE)
	{
		g_player.pos.z = STAGE_SIZE;
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

//===================
// �p�[�c���̐ݒ�
//===================
void SetPartsInfo(LoadInfo PartsInfo)
{
	g_player.PlayerMotion.nNumModel = PartsInfo.nNumParts;
	g_player.nNumModel = PartsInfo.nNumParts;
	for (int PartsCount = 0; PartsCount < g_player.PlayerMotion.nNumModel; PartsCount++)
	{
		g_player.PlayerMotion.aModel[PartsCount].nIndx = PartsInfo.PartsInfo[PartsCount].nIndx;
		g_player.PlayerMotion.aModel[PartsCount].Parent = PartsInfo.PartsInfo[PartsCount].Parent;
		g_player.PlayerMotion.aModel[PartsCount].pos = PartsInfo.PartsInfo[PartsCount].pos;
		g_player.PlayerMotion.aModel[PartsCount].OffSetPos = PartsInfo.PartsInfo[PartsCount].OffSetPos;
		g_player.PlayerMotion.aModel[PartsCount].rot = PartsInfo.PartsInfo[PartsCount].rot;
		g_player.PlayerMotion.aModel[PartsCount].OffSetRot = PartsInfo.PartsInfo[PartsCount].OffSetRot;

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
//=========================
// �G�����E�ɂ��邩�ǂ���
//=========================
bool IsEnemyInsight(void)
{
	ENEMY* pEnemy = GetEnemy();

	D3DXVECTOR3 playerFront;

	playerFront.x = -sinf(g_player.rot.y);
	playerFront.y = 0.0f;
	playerFront.z = -cosf(g_player.rot.y);

	D3DXVECTOR3 toEnemy;

	for (int EnemyCount = 0; EnemyCount < MAX_ENEMY; EnemyCount++)
	{
		if (pEnemy[EnemyCount].bUse == true)
		{
			toEnemy.x = pEnemy[EnemyCount].Object.Pos.x - g_player.pos.x;
			toEnemy.y = 0.0f;
			toEnemy.z = pEnemy[EnemyCount].Object.Pos.z - g_player.pos.z;

			D3DXVec3Normalize(&playerFront, &playerFront);

			D3DXVec3Normalize(&toEnemy, &toEnemy);

			float dotProduct = D3DXVec3Dot(&playerFront, &toEnemy);

			if (dotProduct > cosf(g_player.fSightAngle * 0.5f))
			{
				float distanceSquared =
					(g_player.pos.x - pEnemy[EnemyCount].Object.Pos.x) * (g_player.pos.x - pEnemy[EnemyCount].Object.Pos.x) +
					(g_player.pos.y - pEnemy[EnemyCount].Object.Pos.y) * (g_player.pos.y - pEnemy[EnemyCount].Object.Pos.y) +
					(g_player.pos.z - pEnemy[EnemyCount].Object.Pos.z) * (g_player.pos.z - pEnemy[EnemyCount].Object.Pos.z);

				if (distanceSquared <= g_player.fSightRange * g_player.fSightRange)
				{
					EnemyDistanceSort(EnemyCount);
					return true;
				}
			}
		}
	}
	return false;
}

//=====================
// ��ԋ߂��G�𔻕�
//=====================
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
		g_player.nLockOnEnemy = EnemyCount;
	}
}

void MatrixWand(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRotPlayer, mtxTransPlayer;
	D3DXMATRIX mtxParent;
	D3DXMatrixIdentity(&g_player.mtxWand);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRotPlayer, g_player.PlayerMotion.aModel[12].rot.y, g_player.PlayerMotion.aModel[12].rot.x, g_player.PlayerMotion.aModel[12].rot.z);
	D3DXMatrixMultiply(&g_player.mtxWand, &g_player.mtxWand, &mtxRotPlayer);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransPlayer, 0.0f, 25.0f, 0.0f);
	D3DXMatrixMultiply(&g_player.mtxWand, &g_player.mtxWand, &mtxTransPlayer);

	mtxParent = g_player.PlayerMotion.aModel[12].mtxWorld;

	D3DXMatrixMultiply(&g_player.mtxWand,
		&g_player.mtxWand,
		&mtxParent);

	pDevice->SetTransform(D3DTS_WORLD,
		&g_player.mtxWand);
}