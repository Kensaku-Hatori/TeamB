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

#define PLAYER_JUMP (5)			//�W�����v��
#define PLAYER_RADIUS (3)		//�v���C���[�̔��a
#define MOTIONFILE_PLAYER  ("data\\MOTION\\motion00.txt")//�v���C���[�̃��[�V�����t�@�C��

#define PLAYER_MP (500)		//MP
#define PLAYER_HP (1000)	//HP
#define PLAYER_SPEED (4)	//���x

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
	int nIdxShadow;		//�e
	int nJump;			//�W�����v��
	bool bJump;			//�W�����v�ł��邩�ǂ���
	bool bUse;
	PlayerStatus Status;//�X�e�[�^�X
	//���f��
	MODELINFO aModel[MAX_PARTS];
	int nNumModel;
	//���[�V����
	MOTIONINFO aMotionInfo[MOTIONTYPE_MAX];//���[�V�������
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
void SetMesh(char* pFilePath, int Indx);
void SetPartsInfo(MODELINFO ModelInfo,int Indx);
void PlayerMotion(MOTIONINFO *pMotionInfo);
#endif