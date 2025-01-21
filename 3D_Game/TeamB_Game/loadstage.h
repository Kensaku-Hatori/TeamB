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
#define MAX_PATHNUM 10
#define MAX_FILEPATH 32
#define MAX_PATHTYPE 2

typedef struct
{
	int nPolygoneType;
	int nModelType;
}NTYPE;

void LoadModelViewer();					// �X�N���v�g�ȑO��ǂݍ��ޏ���
void SkipComment(FILE* pFile);			// �V���[�v�ȍ~���΂��֐�
void LoadStart(FILE* pFile);			// �X�N���v�g�ȍ~�̓ǂݍ��ݏ���
void SkipEqual(FILE* pFile);			//  = ��ǂݔ�΂�����
int LoadInt(FILE* pFile);				// ������ǂݍ��ޏ���
float LoadFloat(FILE* pFile);			// �����_��ǂݍ��ޏ���
char *LoadPath(FILE* pFile);			// �������ǂݍ��ޏ���

char* LoadCameraInfo(FILE* pFile);		// �J��������ǂݍ��ޏ���
char* LoadLightInfo(FILE* pFile);		// ���C�g����ǂݍ��ޏ���
char* LoadSkyInfo(FILE* pFile);			// �����ǂݍ��ޏ���
char* LoadMountInfo(FILE* pFile);		// �R����ǂݍ��ޏ���
char* LoadFieldInfo(FILE* pFile);		// �n�ʏ���ǂݍ��ޏ���
char* LoadWallInfo(FILE* pFile);		// �Ǐ���ǂݍ��ޏ���
char* LoadModelInfo(FILE* pFile);		// ���f������ǂݍ��ޏ���
char* LoadBillBoardInfo(FILE* pFile);	// �r���{�[�h����ǂݍ��ޏ���
#endif // !LOADSTAGE_H_