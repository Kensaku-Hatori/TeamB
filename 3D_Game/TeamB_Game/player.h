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

#define PLAYER_HITOSPEED (2)		//�l�^�̑��x
#define PLAYER_BALLSPEED (4)		//�{�[���̑��x
#define PLAYER_SUPERBALLSPEED (7)	//�X�[�p�[�{�[���̑��x
#define PLAYER_HITOJUMP (10)		//�l�^�̃W�����v��
#define PLAYER_BALLJUMP (5)			//�{�[���̃W�����v��
#define PLAYER_RADIUS (3)			//�v���C���[�̔��a
#define MAX_BALLTIME (200)			//�{�[���ł����鎞��
#define PIN_CONDITION (10)			//�X�[�p�[�{�[���ɂȂ����
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

	MOTIONTYPE_BALLNEUTRAL,
	MOTIONTYPE_BALLMOVE,
	MOTIONTYPE_BALLACTION,
	MOTIONTYPE_BALLJUMP,
	MOTIONTYPE_BALLLANDING,

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
	int nBallTime;		//�{�[���ł����鎞��
	int nCntKill;		//���̓|������
	int nCntPin;		//�X�[�p�[�{�[���ɂȂ�����p�J�E���^�\
	float fSpeed;		//���x
	bool bBall;			//�{�[���ɂȂ�邩�ǂ���
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