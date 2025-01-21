#ifndef LOADMOTION_H_
#define LOADMOTION_H_

#include "main.h"
#include "loadstage.h"

#define CHARACTOR "END_CHARACTORSET"
#define MOTION "END_MOTIONSET"
#define PARTS "END_PARTSSET"
#define KEY "END_KEYSET"

void LoadMotionViewer(char *cMotionPath);				// �X�N���v�g�ȑO��ǂݍ��ޏ���
void LoadMotionStart(FILE* pFile);			// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���

char* LoadCharactorInfo(FILE* pFile);		// �J��������ǂݍ��ޏ���
char* LoadPartsInfo(FILE* pFile);		// �J��������ǂݍ��ޏ���
char* LoadMotionInfo(FILE* pFile);		// ���C�g����ǂݍ��ޏ���
char* LoadKeyInfo(FILE* pFile);		// ���C�g����ǂݍ��ޏ���
#endif // !LOADMOTION_H_