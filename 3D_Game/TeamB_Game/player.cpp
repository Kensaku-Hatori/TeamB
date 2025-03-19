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
#include "impact.h"
#include "fade.h"
#include "light.h"
#include "Item.h"
#include "circle.h"
#include "arrow.h"
#include "invisiblewall.h"
#include "lockon.h"
#include "boss.h"
#include "mission.h"
#include "score.h"
#include "mouse.h"
#include "itemui.h"
#include "particle.h"
#include <cassert>

//�O���[�o���ϐ�
Player g_player;
D3DXVECTOR3 g_vtxMinPlayer;	//�v���C���[�̍ŏ��l
D3DXVECTOR3 g_vtxMaxPlayer;	//�v���C���[�̍ő�l

int g_nCntHealMP;			//MP�񕜎���

// �������̊֐���
bool isGreaterCount(int Counter,int Max);
bool isLockOn();
bool isRolling();
bool isLanding();
bool isSkillType(SKILLTYPE SkillType);
bool isStateType(PLAYERSTATE State);
bool isMotionType(MOTIONTYPE MotionType);
bool isMotionAction();
bool isMotionRoll();
bool isActionCondition();

// ����Ƃ̊֐���
float Speed();
void UpdateMp();
void UpdatePosition();
void ShotSkill();
void AddGravity();
void UpdateStateCount(int &StateCount);
void RollingState();
void LockOnInput();
void LockOnRot();
void SetState(PLAYERSTATE State);
void SetActionFlame(int ActionIndx,int StartKey, int EndKey, int StartFlame, int EndFlame);

//=====================
// �v���C���[�̏�����
//=====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	if (g_player.bfirst == false)
	{//�X�e�[�W�ړ����Ă���Ȃ�
		g_player.pos = g_player.NextPosition;
		//g_player.Status.nMP += PLAYER_MP / 3;
		g_player.Status.fSpeed = PLAYER_SPEED;
	}
	else
	{//�ŏ��Ȃ�
		g_player.bfirst = false;
		g_player.pos = D3DXVECTOR3(350.0f,0.0f,950.0f);
		//��b�X�e�[�^�X
		g_player.Status.fHP = PLAYER_HP;
		g_player.Status.nMP = PLAYER_MP;
		g_player.Status.fPower = PLAYER_AP;
		g_player.Status.fSpeed = PLAYER_SPEED;
		g_player.Skilltype = SKILLTYPE_NONE;
		g_player.ItemType = ITEMTYPE_HP;
		g_player.nScore = 0;
	}	

	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.rot, 20.0f);//�e�̐ݒ�
	g_player.nIndxCircle = 0;
	g_player.bHit = false;
	g_player.state = PLAYERSTATE_NORMAL;	// �v���C���[�̏��
	g_player.nCntState = 0;					// �v���C���[�̏�Ԏ���
	g_player.nCntRollingState = 0;			// ���[�����O�̃J�E���g
	g_player.bRolling = false;				// ���[�����O���g�p���Ă��邩�ǂ���
	g_player.bSkillUse = false;
	//g_player.bLanding = true;

	//���[�V�����֘A
	g_player.bLoopMotion = true;			//���[�v
	g_player.PlayerMotion.bBlendMotion = true;
	g_player.nNumKey = 2;					//�L�[�̑���
	g_player.nCntMotion = 0;				//���[�V�����J�E���^�[
	g_player.nKey = 0;						//���݂̃L�[No
	g_player.nNumModel = 13;				//�p�[�c�̑���

	//���b�N�I���֘A
	g_player.bLockOn = false;
	g_player.fSightRange = 200.0f;					// ���E����
	g_player.fSightAngle = D3DXToRadian(110.0f);	// ���E�̗t��
	g_player.fDistance = g_player.fSightRange / 2;
	g_player.nLockOnEnemy = 0;
	g_player.bWantLockOn = false;

	//�S�Ńt���O
	g_player.bAbolition = false;				// �S�ł��Ă��Ȃ����

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
		UninitMesh(g_player.PlayerMotion.aModel[nCnt].pMesh);
		UninitBuffMat(g_player.PlayerMotion.aModel[nCnt].pBuffMat);
		for (int TexCount = 0; TexCount < MAX_TEX; TexCount++)
		{
			UninitTexture(g_player.PlayerMotion.aModel[nCnt].pTexture[TexCount]);
		}
	}
}

//=======================
// �v���C���[�̍X�V����
//=======================
void UpdatePlayer(void)
{
	MODE Mode = GetMode();
	Camera *pCamera = GetCamera();				//�J�����̏��擾
	Mission* pMission = GetMission();
	int* NumEnemy = GetNumEnemy();				//�G�̐��擾

	if (isUse() == true)
	{
		if (Mode != MODE_BOSSMOVIE)
		{
			//�v���C���[�ړ�
			PlayerMove();

			//���b�N�I����ԂȂ�
			if (isLockOn() == true)
			{
				LockOnRot();
			}

			NearPlayerRot();

			if (isStateType(PLAYERSTATE_NORMAL) == true || isStateType(PLAYERSTATE_ROLL) == true)
			{
				//���@����
				if (isActionCondition() == true)
				{
					ShotSkill();
				}
			}

			//�A�C�e����
			if (KeyboardTrigger(DIK_R) || GetJoypadTrigger(JOYKEY_X))
			{
				UseItem(g_player.ItemType);
			}

			SkillChange(0);

			LockOnInput();

			RollingState();

			UpdateMp();
			//MP��
			if (isGreaterCount(g_player.Status.nMP, PLAYER_MP) == true)
			{
				g_player.Status.nMP = PLAYER_MP;
			}
			else if (isGreaterCount(g_player.Status.nMP, PLAYER_MP) == true)
			{
				g_player.Status.fHP = PLAYER_HP;
			}

			AddGravity();
			CollisionEnemy();
			CollisionBoss();

			//�O��̈ʒu��ۑ�
			g_player.posOld = g_player.pos;

			UpdatePosition();

			//�n�ʂƂ̔���
			if (g_player.pos.y <= 0)
			{
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
				g_player.Status.nMP = 0;
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
				SetFade(MODE_BOSSMOVIE);
			}
			else if (KeyboardTrigger(DIK_DELETE) && GetKeyboardPress(DIK_9))
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
				SetItem(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), ITEMTYPE_POWER);
			}

#endif

			//�G��S�ē|���Ă���Ȃ�
			if (*(NumEnemy) <= 0)
			{
				if (g_player.bAbolition != true)
				{
					//�G���A�ړ��ʒu�̎擾
					D3DXVECTOR3 Destpos = GetBottom();
					MODE mode = GetMode();

					if (mode != MODE_STAGEFOUR)
					{
						PlaySound(SOUND_LABEL_ZENMETU);
						//�T�[�N���̐ݒ菈��
						g_player.nIndxCircle = SetCircle(g_player.pos, g_player.rot, D3DCOLOR_RGBA(255, 255, 50, 204), 12, 0, 10.0f, 20.0f, true, false, 0);

						//���̐ݒ菈��
						SetArrow(Destpos, g_player.pos, D3DCOLOR_RGBA(255, 200, 0, 200), 35.0f, 15.0f, 21.0f, true, false);

					}
					//�{�X�����񂾂Ȃ�
					else if ((DethBoss()) == false)
					{
						//�T�[�N���̐ݒ菈��
						g_player.nIndxCircle = SetCircle(g_player.pos, g_player.rot, D3DCOLOR_RGBA(255, 255, 50, 204), 12, 0, 10.0f, 20.0f, true, false, 0);
					}

					else
					{
						pMission->mission = MISSION_BOSS;
					}
					TimeScore();
					//�S�ł��Ă����Ԃɂ���
					g_player.bAbolition = true;
				}
			}

			//�G���S�ł��Ă���Ȃ�
			if (g_player.bAbolition == true)
			{
				MODE mode = GetMode();

				//�T�[�N���̈ʒu�̍X�V����
				SetPositionCircle(g_player.nIndxCircle, g_player.pos, g_player.rot);

				if (mode != MODE_STAGEFOUR)
				{
					pMission->mission = MISSION_IDOU;
					//���̈ʒu�X�V
					SetPositonArrow(g_player.nIdxArrow, g_player.pos);

					g_player.Status.fSpeed = PLAYER_SPEED * 1.5f;
				}
			}

			//�e�̑傫���̍X�V����
			SetSizeShadow(g_player.pos, g_player.nIdxShadow);

			//�e�̈ʒu�̍X�V����
			SetPositionShadow(g_player.nIdxShadow, g_player.pos, g_player.bUse);//�e

			g_player.nScore = GetScore();
		}
		if (isStateType(PLAYERSTATE_KNOCKUP) == false)
		{
			UpdateRotation();
			//���[�V�����̍X�V����
			UpdateMotion(&g_player.PlayerMotion);
		}
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
				if (isStateType(PLAYERSTATE_KNOCKUP) == true)
				{
					D3DXMATERIAL DamageColor = pMat[nCntMat];
					DamageColor.MatD3D.Diffuse.r = 255;
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&DamageColor.MatD3D);
				}
				else
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				}
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_player.PlayerMotion.aModel[nCntModel].pTexture[nCntMat]);
				//�v���C���[�̕`��
				g_player.PlayerMotion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			DrawPlayerShadow(g_player.PlayerMotion.aModel[nCntModel].mtxWorld,
				g_player.PlayerMotion.aModel[nCntModel].pBuffMat,
				g_player.PlayerMotion.aModel[nCntModel].pMesh,
				(int)g_player.PlayerMotion.aModel[nCntModel].dwNumMat,
				g_player.PlayerMotion.aModel[nCntModel].rot,
				g_player.PlayerMotion.aModel[nCntModel].pos);

			if (nCntModel == 12)
			{
				MatrixWand();
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//*************************************
// �V���h�E�}�g���b�N�X���g�����e�̕`��
//*************************************
void DrawPlayerShadow(D3DXMATRIX mtxWorld, LPD3DXBUFFER pBuffer, LPD3DXMESH pMesh, int NumMat,D3DXVECTOR3 Rot,D3DXVECTOR3 OffSet)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRotModel, mtxTransModel;
	D3DXMATRIX mtxParent, mtxShadow,mtxOut;

	D3DXVECTOR4 LightPos = D3DXVECTOR4(0.0f, 10.0f, 0.0f, 0.0f);
	D3DXPLANE Plane = D3DXPLANE(0.0f, 1.0f, 0.0f, -1.0f);

	//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxOut);
	mtxOut = mtxWorld;

	D3DXMatrixShadow(&mtxShadow, &LightPos, &Plane);
	D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxShadow);

	//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&mtxOut);

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffer->GetBufferPointer();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntMat = 0; nCntMat < (int)NumMat; nCntMat++)
	{
		D3DXMATERIAL test = pMat[nCntMat];
		test.MatD3D.Diffuse.r = 255;
		test.MatD3D.Diffuse.g = 255;
		test.MatD3D.Diffuse.b = 255;
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&test.MatD3D);
		//�v���C���[�̕`��
		pMesh->DrawSubset(nCntMat);
	}

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//====================
// �v���C���[�̈ړ�
//====================
void PlayerMove(void)
{
	Camera* pCamera;
	pCamera = GetCamera();

	float Speed1 = Speed();
	
	if ((KeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A)) && isRolling() == false && isStateType(PLAYERSTATE_KNOCKUP) == false)
	{
		PlaySound(SOUND_LABEL_ROLLING);
		g_player.bSkillUse = false;
		g_player.bRolling = true;
		g_player.state = PLAYERSTATE_ROLL;
	}

	if (g_player.state == PLAYERSTATE_NORMAL || g_player.state == PLAYERSTATE_ROLL)
	{
		//�ړ�
		//��
		if (GetKeyboardPress(DIK_A))
		{
			//���[�V����
			if (g_player.bRolling == false)
			{
				if (g_player.bLockOn == false && isMotionType(MOTIONTYPE_MOVE) == false)
				{
					SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
					SetActionFlame(0, 1, 1, 1, 2);
					SetActionFlame(1, 3, 3, 1, 2);
				}
				else if (g_player.bLockOn == true && isMotionType(MOTIONTYPE_LOCKON_L_MOVE) == false)
				{
					SetMotion(MOTIONTYPE_LOCKON_L_MOVE, &g_player.PlayerMotion);
				}
			}
			else
			{
				if (g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MAE && g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_HIDARI)
				{
					if (g_player.bLockOn == false)
					{
						SetMotion(MOTIONTYPE_KAIHI_MAE, &g_player.PlayerMotion);
					}
					else if (g_player.bLockOn == true)
					{
						SetMotion(MOTIONTYPE_KAIHI_HIDARI, &g_player.PlayerMotion);
					}
				}
			}

			//�O
			if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_DOWN))
			{
				g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
				g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
			}
			//��
			else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_UP))
			{
				g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
				g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
			}
			else
			{
				g_player.move.x += cosf(pCamera->rot.y - D3DX_PI) * Speed1;
				g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI) * Speed1;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2;
			}
		}
		//�E
		else if (GetKeyboardPress(DIK_D))
			{
				//���[�V����
				if (g_player.bRolling == false)
				{
					if (g_player.bLockOn == false && isMotionType(MOTIONTYPE_MOVE) == false)
					{
						SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
						SetActionFlame(0, 1, 1, 1, 2);
						SetActionFlame(1, 3, 3, 1, 2);
					}
					else if (g_player.bLockOn == true && isMotionType(MOTIONTYPE_LOCKON_R_MOVE) == false)
					{
						SetMotion(MOTIONTYPE_LOCKON_R_MOVE, &g_player.PlayerMotion);
					}
				}
				else
				{
					if (g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MAE && g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MIGI)
					{
						if (g_player.bLockOn == false)
						{
							SetMotion(MOTIONTYPE_KAIHI_MAE, &g_player.PlayerMotion);
						}
						else if (g_player.bLockOn == true)
						{
							SetMotion(MOTIONTYPE_KAIHI_MIGI, &g_player.PlayerMotion);
						}
					}
				}

				//�O
				if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_DOWN))
				{
					g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
					g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
				}
				//��
				else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_UP))
				{
					g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
					g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
				}
				else
				{
					g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI) * Speed1;
					g_player.move.z += sinf(pCamera->rot.y - D3DX_PI) * Speed1;
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2;
				}
			}
		//�O
		else if (GetKeyboardPress(DIK_W) == true)
			{
				//���[�V����
				if (g_player.bRolling == false)
				{
					if (g_player.bLockOn == false && isMotionType(MOTIONTYPE_MOVE) == false)
					{
						SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
						SetActionFlame(0, 1, 1, 1, 2);
						SetActionFlame(1, 3, 3, 1, 2);
					}
					else if (g_player.bLockOn == true && isMotionType(MOTIONTYPE_LOCKON_F_MOVE) == false)
					{
						SetMotion(MOTIONTYPE_LOCKON_F_MOVE, &g_player.PlayerMotion);
					}
				}
				else
				{
					if (g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MAE)
					{
						SetMotion(MOTIONTYPE_KAIHI_MAE, &g_player.PlayerMotion);
					}
				}


				//��
				if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_DOWN))
				{
					g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
					g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
				}
				//�E
				else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_UP))
				{
					g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
					g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
				}
				else
				{
					g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI) * Speed1;
					g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * Speed1;
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI;
				}
			}
		//��
		else if (GetKeyboardPress(DIK_S))
			{
				//���[�V����
				if (g_player.bRolling == false)
				{
					if (g_player.bLockOn == false && isMotionType(MOTIONTYPE_MOVE) == false)
					{
						SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
						SetActionFlame(0, 1, 1, 1, 2);
						SetActionFlame(1, 3, 3, 1, 2);
					}
					else if (g_player.bLockOn == true && isMotionType(MOTIONTYPE_LOCKON_F_MOVE) == false)
					{
						SetMotion(MOTIONTYPE_LOCKON_F_MOVE, &g_player.PlayerMotion);
					}
				}
				else
				{
					if (g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MAE && g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_USIRO)
					{
						if (g_player.bLockOn == false)
						{
							SetMotion(MOTIONTYPE_KAIHI_MAE, &g_player.PlayerMotion);
						}
						else if (g_player.bLockOn == true)
						{
							SetMotion(MOTIONTYPE_KAIHI_USIRO, &g_player.PlayerMotion);
						}
					}
				}

				//��
				if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_DOWN))
				{
					g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
					g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * Speed1;
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
				}
				//�E
				else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_UP))
				{
					g_player.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
					g_player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * Speed1;
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
				}
				else
				{
					g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * Speed1;
					g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * Speed1;
					g_player.rotDest.y = pCamera->rot.y;
				}
			}
		//
		else if (GetJoyStickL() == true)
		{
			PlayerMoveJoyPad(Speed1);
		}
		//
		else
		{
			if (g_player.PlayerMotion.motionType == MOTIONTYPE_MOVE || g_player.PlayerMotion.motionType == MOTIONTYPE_LOCKON_R_MOVE
				|| g_player.PlayerMotion.motionType == MOTIONTYPE_LOCKON_L_MOVE || g_player.PlayerMotion.motionType == MOTIONTYPE_LOCKON_F_MOVE
				|| isMotionRoll() == true
				|| isMotionAction() == true)
			{
				SetMotion(MOTIONTYPE_NEUTRAL, &g_player.PlayerMotion);
				SetState(PLAYERSTATE_NORMAL);
			}
		}
	}
	else if(g_player.state == PLAYERSTATE_KNOCKUP)
	{//�_�E�����
		if (g_player.PlayerMotion.motionType != MOTIONTYPE_DOWN)
		{
			SetMotion(MOTIONTYPE_DOWN, &g_player.PlayerMotion);
		}
		g_player.bSkillUse = false;
		g_player.nCntState++;
		if (g_player.nCntState >= PLAYER_DOWNTIME)
		{
			g_player.nCntState = 0;
			g_player.state = PLAYERSTATE_NORMAL;
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
//==========================
// �R���g���[���[�ł̈ړ�
//==========================
void PlayerMoveJoyPad(float Speed)
{
	Camera* pCamera = GetCamera();
	XINPUT_STATE* pStick = GetJoyStickAngle();

	float fStickAngleX = (float)pStick->Gamepad.sThumbLX * pStick->Gamepad.sThumbLX;
	float fStickAngleY = (float)pStick->Gamepad.sThumbLY * pStick->Gamepad.sThumbLY;

	float DeadZone = 10920.0f;
	float fMag = sqrtf(fStickAngleX + fStickAngleY);

	if (fMag > DeadZone)
	{
		float fAngle = atan2f(pStick->Gamepad.sThumbLX, pStick->Gamepad.sThumbLY);
		g_player.move.x = sinf(pCamera->rot.y + fAngle) * Speed;
		g_player.move.z = cosf(pCamera->rot.y + fAngle) * Speed;
		g_player.rotDest.y = pCamera->rot.y + fAngle + D3DX_PI;

		// ���[�V����
		if (g_player.bRolling == false)
		{
			if (g_player.bLockOn == false && g_player.PlayerMotion.motionType != MOTIONTYPE_MOVE)
			{
				SetMotion(MOTIONTYPE_MOVE, &g_player.PlayerMotion);
			}
			else if (g_player.bLockOn == true)
			{
				if (pStick->Gamepad.sThumbLX < 0 && g_player.PlayerMotion.motionType != MOTIONTYPE_LOCKON_L_MOVE)
				{
					SetMotion(MOTIONTYPE_LOCKON_L_MOVE, &g_player.PlayerMotion);
				}
				else if (pStick->Gamepad.sThumbLX > 0 && g_player.PlayerMotion.motionType != MOTIONTYPE_LOCKON_R_MOVE)
				{
					SetMotion(MOTIONTYPE_LOCKON_R_MOVE, &g_player.PlayerMotion);
				}
				else if (pStick->Gamepad.sThumbLY < 0 && pStick->Gamepad.sThumbLY > 0 && g_player.PlayerMotion.motionType != MOTIONTYPE_LOCKON_F_MOVE)
				{
					SetMotion(MOTIONTYPE_LOCKON_F_MOVE, &g_player.PlayerMotion);
				}
			}
		}
		else if(g_player.bRolling == true)
		{
			if (g_player.bLockOn == false && g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MAE)
			{
				SetMotion(MOTIONTYPE_KAIHI_MAE, &g_player.PlayerMotion);
			}
			else if (g_player.bLockOn == true)
			{
				if (   g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MAE && g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_USIRO
					&& g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_HIDARI && g_player.PlayerMotion.motionType != MOTIONTYPE_KAIHI_MIGI)
				{
					if (pStick->Gamepad.sThumbLX < 0)
					{
						SetMotion(MOTIONTYPE_KAIHI_HIDARI, &g_player.PlayerMotion);
					}
					else if (pStick->Gamepad.sThumbLX > 0)
					{
						SetMotion(MOTIONTYPE_KAIHI_MIGI, &g_player.PlayerMotion);
					}
					else if (pStick->Gamepad.sThumbLY > 0)
					{
						SetMotion(MOTIONTYPE_KAIHI_MAE, &g_player.PlayerMotion);
					}
					else if (pStick->Gamepad.sThumbLY < 0)
					{
						SetMotion(MOTIONTYPE_KAIHI_USIRO, &g_player.PlayerMotion);
					}
				}
			}
		}	
	}
}
//===============
// ���[�����O
//===============
void PlayerRolling(void)
{

}

//==========================
// �g�p���閂�@�̎�ޕύX
//==========================
void SkillChange(int zDelta)
{
	if (KeyboardTrigger(DIK_LEFT) || GetJoypadTrigger(JOYKEY_LEFT) ||
		zDelta < 0)
	{
		switch (g_player.Skilltype)
		{
		case SKILLTYPE_NONE:
			g_player.Skilltype = SKILLTYPE_EXPLOSION;
			break;

		case SKILLTYPE_HORMING:
			g_player.Skilltype = SKILLTYPE_NONE;
			break;

		case SKILLTYPE_EXPLOSION:
			g_player.Skilltype = SKILLTYPE_HORMING;
			break;
		default:
			break;
		}
	}
	else if (KeyboardTrigger(DIK_RIGHT) || GetJoypadTrigger(JOYKEY_RIGHT) ||
			 zDelta > 0)
	{
		switch (g_player.Skilltype)
		{
		case SKILLTYPE_NONE:
			g_player.Skilltype = SKILLTYPE_HORMING;
			break;

		case SKILLTYPE_HORMING:
			g_player.Skilltype = SKILLTYPE_EXPLOSION;
			break;

		case SKILLTYPE_EXPLOSION:
			g_player.Skilltype = SKILLTYPE_NONE;
			break;
		default:
			break;
		}
	}

}

//===================
// �v���C���[�̎擾
//===================
Player* GetPlayer(void)
{
	return &g_player;
}

//=======================
// �v���C���[�̃q�b�g����
//=======================
void HitPlayer(float Atack,D3DXVECTOR3 Pos)
{
	if (g_player.state != PLAYERSTATE_KNOCKUP)
	{
		if (g_player.bRolling == false)
		{
			g_player.Status.fHP -= (int)Atack;
			float move = 5.0f + (Atack / 10);

			D3DXVECTOR3 Vec = g_player.pos - Pos;
			D3DXVec3Normalize(&Vec, &Vec);
			g_player.move = Vec * move;
			g_player.bHit = true;
			g_player.state = PLAYERSTATE_KNOCKUP;

			if (g_player.Status.fHP <= 0.0f && g_player.bUse == true)
			{// �g���Ă��đ̗͂��O�ȉ��Ȃ�
				g_player.bUse = false;
				SetParticle(g_player.pos,
					D3DXVECTOR3(162, 1, 1),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					PARTICLE_NONE,
					D3DXVECTOR3(1.0f, 1.0f, 1.0f),
					100,
					50,
					500.0f,
					500.0f,
					0.0f,
					EFFECT_NONE);
				SetGameState(GAMESTATE_GAMEOVER);
			}
			SetShake(10);
			SetVibRation(50000, 50000, 30);
		}
	}
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

//***********************************
// �����������������傫��������
//***********************************
bool isGreaterCount(int Counter, int Max)
{
	if(Counter != NULL) return Counter >= Max;
	return false;
}

//*********************
// �g���Ă��邩�ǂ���
//*********************
bool isUse()
{
	return g_player.bUse;
}

//*********************
// ���b�N�I�������ǂ���
//*********************
bool isLockOn()
{
	return g_player.bLockOn;
}

//***********************
// �n�ʂɑ������Ă��邩
//***********************
bool isLanding()
{
	return g_player.bLanding;
}

//*******************************************************
// �������ƃv���C���[�̃X�L���^�C�v�������Ă��邩�ǂ���
//*******************************************************
bool isSkillType(SKILLTYPE SkillType)
{
	if(SkillType >= 0 && SkillType <= SKILLTYPE_MAX) return g_player.Skilltype == SkillType;
	return false;
}
//*********************
// ���[�����O�����ǂ���
//*********************
bool isRolling()
{
	return g_player.bRolling;
}

//***************************************************
// �������ƃv���C���[�̃X�e�[�g�������Ă��邩�ǂ���
//***************************************************
bool isStateType(PLAYERSTATE State)
{
	if(State >= PLAYERSTATE_NORMAL && State <= PLAYERSTATE_MAX) return g_player.state == State;
	return false;
}

//***************************************************
// �������ƃv���C���[�̃��[�V�����������Ă��邩�ǂ���
//***************************************************
bool isMotionType(MOTIONTYPE MotionType)
{
	if(MotionType >= MOTIONTYPE_NEUTRAL && MotionType <= MOTIONTYPE_MAX) return g_player.PlayerMotion.motionType == MotionType;
	return false;
}

//*************************
// �U�����[�V���������ǂ���
//*************************
bool isMotionAction()
{
	return isMotionType(MOTIONTYPE_ACTION) == true
		|| isMotionType(MOTIONTYPE_ACTION_HORMING) == true
		|| isMotionType(MOTIONTYPE_ACTION_EXPLOSION) == true;
}

//*************************
// ������[�V���������ǂ���
//*************************
bool isMotionRoll()
{
	return isMotionType(MOTIONTYPE_KAIHI_HIDARI) == true
		|| isMotionType(MOTIONTYPE_KAIHI_MIGI) == true
		|| isMotionType(MOTIONTYPE_KAIHI_MAE) == true
		|| isMotionType(MOTIONTYPE_KAIHI_USIRO) == true;
}

//***********************
// �U���ł���󋵉��ǂ���
//***********************
bool isActionCondition()
{
	return OnMouseDown(0) == true || GetJoypadTrigger(JOYKEY_B) == true
		&& isMotionAction() == false
		&& isMotionRoll() == false
		&& isStateType(PLAYERSTATE_NORMAL) == true
		&& g_player.PlayerMotion.bBlendMotion == false;
}

//***********************
// �󋵂ɉ�����������ݒ�
//***********************
float Speed()
{
	if((KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A))&& isRolling() == false) return g_player.Status.fSpeed * 20;
	if (isLockOn() == true) return g_player.Status.fSpeed * 0.5f;
	return g_player.Status.fSpeed;
}

//***********************
// �v���C���[�̃|�X���ړ�
//***********************
void UpdatePosition()
{
	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;
}
//*******************************
// �v���C���[��Mp�Ɋւ���X�V����
//*******************************
void UpdateMp()
{
	if (isGreaterCount(PLAYER_MP, g_player.Status.nMP) == true)
	{
		UpdateStateCount(g_nCntHealMP);
		if (isGreaterCount(g_nCntHealMP,180) == true)
		{
			g_player.Status.nMP += 10;
			g_nCntHealMP = 0;
		}
	}
}

//*************************
// �󋵂ɉ������X�L���𔭎�
//*************************
void ShotSkill()
{
	if (isMotionRoll() == false)
	{
		if (isSkillType(SKILLTYPE_NONE) == true)
		{
			SetState(PLAYERSTATE_ACTION);

			SetMotion(MOTIONTYPE_ACTION, &g_player.PlayerMotion);

			SetActionFlame(0, 3, 3, 18, 19);
			SetActionFlame(1, 3, 3, 15, 19);
			SetActionFlame(2, 0, 0, 1, 2);
		}
		else if (isSkillType(SKILLTYPE_HORMING) == true)
		{
			if (g_player.bSkillUse == false)
			{
				SetState(PLAYERSTATE_ACTION);

				g_player.bSkillUse = true;
				SetMotion(MOTIONTYPE_ACTION_HORMING, &g_player.PlayerMotion);

				SetActionFlame(0, 2, 2, 23, 24);
				SetActionFlame(2, 0, 0, 1, 2);
			}
		}
		else if (isSkillType(SKILLTYPE_EXPLOSION) == true)
		{
			SetState(PLAYERSTATE_ACTION);

			SetMotion(MOTIONTYPE_ACTION_EXPLOSION, &g_player.PlayerMotion);

			SetActionFlame(0, 0, 0, 15, 16);
			SetActionFlame(1, 0, 0, 15, 16);
		}
	}
}
//***********
// �d�͂����Z
//***********
void AddGravity()
{
	if (isLanding() == false)
	{
		g_player.move.y -= GRAVITY; //�d�͉��Z	
	}
}

//***************
// �����������Z
//***************
void UpdateStateCount(int &StateCount)
{
	StateCount++;
}

//*************************************
// ���[�����O���̂���m�[�}���ɖ߂�����
//*************************************
void RollingState()
{
	//���[�����O
	if (isRolling() == true)
	{
		UpdateStateCount(g_player.nCntRollingState);
		if (isGreaterCount(g_player.nCntRollingState, 40) == true)
		{
			g_player.bRolling = false;
			g_player.nCntRollingState = 0;
			SetState(PLAYERSTATE_NORMAL);
		}
	}
}

//*****************************
// ���b�N�I���ł���󋵂��ǂ���
//*****************************
void LockOnInput()
{
	//���b�N�I��
	if ((GetJoypadTrigger(JOYKEY_R1) == true) ||
		OnMouseDown(1))
	{
		if (isLockOn() == false)
		{
			g_player.bWantLockOn = true;
			PlaySound(SOUND_LABEL_LOCKON);
		}
		else if (isLockOn() == true)
		{
			g_player.bLockOn = false;
			g_player.bWantLockOn = false;
		}
	}
}

//*************************************
// ���b�N�I�����̃v���C���[�̌����̏���
//*************************************
void LockOnRot()
{
	Lockon* pLockon = GetLockOn();

	//�v���C���[�̌���
	float fMathDistance = Vector(g_player.pos.x, pLockon->pos.x);
	float fMathDistance1 = Vector(g_player.pos.z, pLockon->pos.z);
	float fAngle = Angle(D3DXVECTOR2(fMathDistance, fMathDistance1));
	SetAngle(fAngle + D3DX_PI,g_player.rotDest.y);

	SetCameraRotY(fAngle);
}

//***********************************
// �v���C���[�̌������߂��ق������
//***********************************
void NearPlayerRot()
{
	NearRot(g_player.rotDest.y - g_player.rot.y,g_player.rot.y);
}

//*******************************
// ������ڕW�̌����ɏ��X�Ɍ�����
//*******************************
void UpdateRotation()
{
	g_player.rot += (g_player.rotDest - g_player.rot) * 0.5f;
}

//***************************
// �v���C���[�̃X�e�[�g��ݒ�
//***************************
void SetState(PLAYERSTATE State)
{
	g_player.state = State;
}

//*************************
// �A�N�V�����t���[����ݒ�
//*************************
void SetActionFlame(int ActionIndx, int StartKey, int EndKey, int StartFlame, int EndFlame)
{
#ifdef DEBUG
	assert(ActionIndx <= MAX_ACTION || StartKey <= 0 || EndKey <= g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].nNumKey);
#endif // DEBUG

	g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[ActionIndx].bActionStart = false;
	g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[ActionIndx].bFirst = false;
	g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[ActionIndx].nStartKey = StartKey;
	g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[ActionIndx].nEndKey = EndKey;
	g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[ActionIndx].nStartFrame = StartFlame;
	g_player.PlayerMotion.aMotionInfo[g_player.PlayerMotion.motionType].ActionFrameInfo[ActionIndx].nEndFrame = EndFlame;
}

void SetRotDest(D3DXVECTOR3 Rot)
{
	g_player.rotDest = Rot;
}