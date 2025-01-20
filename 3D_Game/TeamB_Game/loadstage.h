//*************************************************
// 
// ���f���r���[���ǂݍ��ݏ���[loadstage.h]
// Author Kensaku Hatori
// 
//*************************************************
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"

#define CAMERA "END_CAMERASET"
#define LIGHT "END_LIGHTSET"
#define SKY "END_SKYSET"
#define MOUNTAIN "END_MOUNTAINSET"
#define FIELD "END_FIELDSET"
#define WALL "END_WALLSET"
#define MODEL "END_MODELSET"
#define BILLBOARD "END_BILLBOARDSET"

void LoadModelViewer();				// �X�N���v�g�ȑO��ǂݍ��ޏ���
void SkipComment(FILE* pFile);		// �V���[�v�ȍ~���΂��֐�
void LoadStart(FILE* pFile);		// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���
void SkipEqual(FILE* pFile);		//  = ��ǂݔ�΂�����
int LoadInt(FILE* pFile);			// ������ǂݍ��ޏ���
float LoadFloat(FILE* pFile);		// �����_��ǂݍ��ޏ���
char *LoadPath(FILE* pFile);		// �������ǂݍ��ޏ���
char* LoadDecision(FILE* pFile);		// ������𔻒f���鏈��
#endif // !LOADSTAGE_H_