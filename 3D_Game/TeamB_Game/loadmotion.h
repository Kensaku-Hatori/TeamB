#ifndef LOADMOTION_H_
#define LOADMOTION_H_

#include "main.h"
#include "loadstage.h"
#include "key.h"
#include "model.h"

#define MOTIONFILE_PLAYER  ("data\\MOTION\\motion00.txt")//�v���C���[�̃��[�V�����t�@�C��
#define MOTIONFILE_ENEMYONE  ("data\\MOTION\\Enemymotion00.txt")//�v���C���[�̃��[�V�����t�@�C��

#define CHARACTOR "END_CHARACTERSET"
#define MOTION "END_MOTIONSET"
#define PARTS "END_PARTSSET"
#define KEYPARTS "END_KEY"
#define KEY "END_KEYSET"

typedef enum
{
	LOADTYPE_PLAYER = 0,
	LOADTYPE_ENEMYONE,
	LOADTYPE_ENEMYTWO,
	LOADTYPE_ENEMYTHREE,
	LOADTYPE_ENEMYFOUR,
	LOADTYPE_MAX
}LoadType;

typedef struct
{
	MODELINFO PartsInfo[MAX_PARTS];
	MOTIONINFO MotionInfo[MOTIONTYPE_MAX];
	char cPartsPath[MAX_PARTS][62];
	int nNumParts;
	int PathCount,PartsCount,MotionCount,KeyCount,KeyPartsCount;
}LoadInfo;

void InitMotion();
void LoadMotionViewer(char *cMotionPath);	// �X�N���v�g�ȑO��ǂݍ��ޏ���
void LoadMotionStart(FILE* pFile);			// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���

char* LoadCharactorInfo(FILE* pFile,int *nCharactor, int* nParts, MODELINFO*Model);				// �L�����N�^�[����ǂݍ��ޏ���
char* LoadPartsInfo(FILE* pFile,int *nParts);									// �p�[�c����ǂݍ��ޏ���
char* LoadMotionInfo(FILE* pFile,int *nMotion, int* nKey, int* nKeyParts,MOTIONINFO *Motion);	// ���[�V��������ǂݍ��ޏ���
char* LoadKeyInfo(FILE* pFile, int* nKey, int* nKeyParts, MOTIONINFO* Motion);					// �L�[����ǂݍ��ޏ���
char* LoadKeyPartsInfo(FILE* pFile,int *nKey,int *nKeyParts, MOTIONINFO* Motion);				// �p�[�c���Ƃ̃L�[����ǂݍ��ޏ���
#endif // !LOADMOTION_H_