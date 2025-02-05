#ifndef KEY_H_
#define KEY_H_

#define MAX_KEY (10)
#define MAX_MOTION (5)

#include "main.h"
#include "model.h"

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_DOWN,
	MOTIONTYPE_DOWNNUTORAL,
	MOTIONTYPE_NANDE,
	MOTIONTYPE_MAX
}MOTIONTYPE;

typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

typedef struct
{
	int nFrame;
	KEY aKey[MAX_PARTS];
}KEYINFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEYINFO aKeyInfo[MAX_KEY];
}MOTIONINFO;

//�v���C���[�̍\����
typedef struct
{
	//���f��
	MODELINFO aModel[MAX_PARTS];
	int nNumModel;
	//���[�V����
	MOTIONINFO aMotionInfo[MOTIONTYPE_MAX];	//���[�V�������
	int nNumMotion;							//���[�V�����̑���
	MOTIONTYPE motionType;					//���[�V�����̎��
	bool bLoopMotion;						//���[�v���邩�ǂ���
	int nNumKey;							//�L�[�̑���
	int nKey;								//���݂̃L�[No
	int NextKey;
	int nCntMotion;							//���[�V�����̃J�E���^�[

	bool bFinish;							// ���݂̃��[�V�������I�����Ă��邩�ǂ���
	bool bBlendMotion;						// �u�����h���[�V���������邩�ǂ���
	MOTIONTYPE motionTypeBlend;				// �u�����h���[�V�����̎��
	int nNumKeyBlend;						// �u�����h���[�V�����̃L�[�̑���
	int nKeyBlend;							// �u�����h���[�V�����̂̃L�[No
	int nCntMotionBlend;					// �u�����h���[�V�����̃J�E���^�[
	int nFrameBlend;						// �u�����h�t���[��
	int nCntBlend;							// �u�����h�t���[���J�E���g
	int nNextKeyBlend;
	bool bLoopBlend;						//���[�v���邩�ǂ���

}OBJECTINFO;

#endif // !KEY_H_