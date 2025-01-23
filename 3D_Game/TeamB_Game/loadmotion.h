#ifndef LOADMOTION_H_
#define LOADMOTION_H_

#include "main.h"
#include "loadstage.h"
#include "key.h"
#include "model.h"

#define CHARACTOR "END_CHARACTERSET"
#define MOTION "END_MOTIONSET"
#define PARTS "END_PARTSSET"
#define KEYPARTS "END_KEY"
#define KEY "END_KEYSET"

void LoadMotionViewer(char *cMotionPath);	// �X�N���v�g�ȑO��ǂݍ��ޏ���
void LoadMotionStart(FILE* pFile);			// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���

char* LoadCharactorInfo(FILE* pFile,int *nCharactor, int* nParts, MODELINFO*Model);				// �L�����N�^�[����ǂݍ��ޏ���
char* LoadPartsInfo(FILE* pFile,int *nParts);									// �p�[�c����ǂݍ��ޏ���
char* LoadMotionInfo(FILE* pFile,int *nMotion, int* nKey, int* nKeyParts,MOTIONINFO *Motion);	// ���[�V��������ǂݍ��ޏ���
char* LoadKeyInfo(FILE* pFile, int* nKey, int* nKeyParts, MOTIONINFO* Motion);					// �L�[����ǂݍ��ޏ���
char* LoadKeyPartsInfo(FILE* pFile,int *nKey,int *nKeyParts, MOTIONINFO* Motion);				// �p�[�c���Ƃ̃L�[����ǂݍ��ޏ���
#endif // !LOADMOTION_H_