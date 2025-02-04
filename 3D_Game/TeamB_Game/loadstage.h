//*************************************************
// 
// ���f���r���[���ǂݍ��ݏ���[loadstage.h]
// Author Kensaku Hatori
// 
//*************************************************
#ifndef LOADSTAGE_H_
#define LOADSTAGE_H_

#include "main.h"

#define MAX_PATHNUM (15)
#define MAX_FILEPATH (15)
#define MAX_PATHTYPE (2)

// �p�X�̎��
typedef struct
{
	int nPolygoneType;
	int nModelType;
}NTYPE;

void LoadModelViewer(MODE Mode);					// �X�N���v�g�ȑO��ǂݍ��ޏ���
void SkipComment(FILE* pFile);						// �V���[�v�ȍ~���΂��֐�
void LoadStart(FILE* pFile);						// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���
void SkipEqual(FILE* pFile);						//  = ��ǂݔ�΂�����
int LoadInt(FILE* pFile);							// ������ǂݍ��ޏ���
float LoadFloat(FILE* pFile);						// �����_��ǂݍ��ޏ���
char *LoadPath(FILE* pFile,char *cData2);			// �������ǂݍ��ޏ���

void LoadCameraInfo(FILE* pFile);					// �J��������ǂݍ��ޏ���
void LoadLightInfo(FILE* pFile);					// ���C�g����ǂݍ��ޏ���
void LoadSkyInfo(FILE* pFile);						// �����ǂݍ��ޏ���
void LoadMountInfo(FILE* pFile);					// �R����ǂݍ��ޏ���
void LoadFieldInfo(FILE* pFile);					// �n�ʏ���ǂݍ��ޏ���
void LoadWallInfo(FILE* pFile);						// �Ǐ���ǂݍ��ޏ���
void LoadModelInfo(FILE* pFile);					// ���f������ǂݍ��ޏ���
void LoadBillBoardInfo(FILE* pFile);				// �r���{�[�h����ǂݍ��ޏ���
void LoadPlayerInfo(FILE* pFile);					// �v���C���[����ǂݍ��ޏ���
#endif // !LOADSTAGE_H_