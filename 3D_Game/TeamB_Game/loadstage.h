//*************************************************
// 
// ���f���r���[���ǂݍ��ݏ���[loadstage.h]
// Author Kensaku Hatori
// 
//*************************************************
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"

void LoadModelViewer();				// �X�N���v�g�ȑO��ǂݍ��ޏ���
void SkipComment(FILE* pFile);		// �V���[�v�ȍ~���΂��֐�
void LoadStart(FILE* pFile);		// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���
void SkipEqual(FILE* pFile);		//  = ��ǂݔ�΂�����
void LoadTextureNum(FILE* pFile);	// �e�N�X�`���̎�ނ�ǂݍ��ޏ���
void LoadTexturePath(FILE* pFile);	// �e�N�X�`���̃p�X��ǂݍ��ޏ���
void LoadModelNum(FILE* pFile);		// ���f���̎�ނ�ǂݍ��ޏ���
void LoadModelPath(FILE* pFile);	// ���f���̃p�X��ǂݍ��ޏ���
int LoadInt(FILE* pFile);
char *LoadPath(FILE* pFile);
#endif // !LOADSTAGE_H_