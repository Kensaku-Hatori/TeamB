//================================
//
// �v���C���[�\������[player.h]
// Author:kaiti
//
//================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"
#include "status.h"
#include "key.h"
#include "loadmotion.h"

#define PLAYER_JUMP (5)			//�W�����v��
#define PLAYER_RADIUS (3)		//�v���C���[�̔��a

#define PLAYER_MP (500)		//MP
#define PLAYER_HP (1000)	//HP
#define PLAYER_SPEED (4)	//���x
#define PLAYER_AP (10)	//���x

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ʒu
	D3DXVECTOR3 size;	//�T�C�Y
	D3DXVECTOR3 move;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 rotDest;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	OBJECTINFO PlayerMotion;
	int nIdxShadow;		//�e
	int nJump;			//�W�����v��
	bool bJump;			//�W�����v�ł��邩�ǂ���
	bool bUse;
	PlayerStatus Status;//�X�e�[�^�X
	int nNumModel;
	int nNumMotion;							//���[�V�����̑���
	MOTIONTYPE motionType;					//���[�V�����̎��
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[�̑���
	int nKey;								//���݂̃L�[No
	int nCntMotion;							//���[�V�����̃J�E���^�[

	bool bFinishMotion;				//���݂̃��[�V�������I�����Ă��邩�ǂ���
	bool bBlendMotion;				//�u�����h���[�V���������邩�ǂ���
	MOTIONTYPE motionTypeBlend;		//�u�����h���[�V�����̎��
	int nNumKeyBlend;				//�u�����h���[�V�����̃L�[�̑���
	int nKeyBlend;					//�u�����h���[�V�����̂̃L�[No
	int nCntMotionBlend;			//�u�����h���[�V�����̃J�E���^�[
	int nFrameBlend;
	int nCntBlend;
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void SetMesh(char* pFilePath, int Indx);
void SetPartsInfo(LoadInfo PartsInfo);
void PlayerMotion(MOTIONINFO *pMotionInfo);
#endif