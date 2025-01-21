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

#define PLAYER_SPEED (4)		//�{�[���̑��x
#define PLAYER_JUMP (5)			//�{�[���̃W�����v��
#define PLAYER_RADIUS (3)			//�v���C���[�̔��a
#define MOTIONFILE_PLAYER  ("data\\MOTION\\motionBallMan.txt")//�v���C���[�̃��[�V�����t�@�C��

//�v���C���[�̏��
typedef enum
{
	PLAYERTYPE_HITO = 0,
	PLAYERTYPE_BALL,
	PLAYERTYPE_SUPERBALL,
	PLAYERTYPE_MAX
}PLAYERTYPE;

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_MAX
}MOTIONTYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;

	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;
	KEY aKey[MAX_PARTS];
}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[MAX_KEY];
}MOTION_INFO;

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
	PLAYERTYPE type;
	int nIdxShadow;		//�e
	int nJump;			//�W�����v��
	float fSpeed;		//���x
	bool bJump;			//�W�����v�ł��邩�ǂ���
	bool bUse;
	//���f��
	Model aModel[MAX_PARTS];
	int nNumModel;
	//���[�V����
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];//���[�V�������
	int nNumMotion;							//���[�V�����̑���
	MOTIONTYPE motionType;					//���[�V�����̎��
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[�̑���
	int nKey;								//���݂̃L�[No
	int nCntMotion;							//���[�V�����̃J�E���^�[
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void SetPlayerMotion(void);
void LoadPlayer(void);

#endif