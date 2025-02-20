//=========================================================
// 
// �G��HP�Q�[�W[HPgauge.h]
// Aothor:Rio Ohno
// 
//=========================================================

#ifndef HPGAUGE_H_
#define HPGAUGE_H_

#include "main.h"

//�}�N����`
#define MAX_HPGAUGE (32)															// �Q�[�W�̍ő�̐�
#define MAX_POLY (3)																// �P�̃Q�[�W�Ɏg���|���S����

//�^�C�v
typedef enum
{
	HPGAUGETYPE_NORMAL=0,															// �ʏ�
	HPGAUGETYPE_RED,																// ��
	HPGAUGETYPE_NONE,																// �g
	HPGAUGETYPE_MAX										
}HPGAUGETYPE;

//�e�N�X�`��
static const char* HPGAUGETEX[HPGAUGETYPE_MAX] =
{
	"data\\TEXTURE\\GUAGE.png",														// �ʏ�Q�[�W�̃p�X
	"data\\TEXTURE\\GUAGE.png",														// �ԃQ�[�W�̃p�X
	"data\\TEXTURE\\GUAGEEDGE.png",													// �g�Q�[�W
};

//�|���S���̍\����
typedef struct
{
	D3DXCOLOR col;																	// �F
	HPGAUGETYPE type;																// ���
	D3DXMATRIX mtxWorld;															// ���[���h�}�g���b�N�X
	float fWidth;																	// ���ۑ�
	float fMaxGauge;																// �ő啝�ۑ�
}POLY;

//HP�Q�[�W�\����
typedef struct
{
	POLY poly[MAX_POLY];															//�|���S���̏��
	D3DXVECTOR3 pos;																// �ʒu
	D3DXVECTOR3 rot;																// ����
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;												// ���_���
	float fNowHP;																	// ���݂�HP
	float fMaxHP;																	// �ő��HP
	bool bUse;																		// �g�p���Ă��邩�ǂ���
}HPgauge;

//�v���g�^�C�v�錾
void InitHPgauge();																	// ����������
void UninitHPgauge();																// �I������
void UpdateHPgauge();																// �X�V����
void DrawHPgauge();																	// �`�揈��
int SetHPgauge(D3DXVECTOR3 pos, D3DXVECTOR2 scale, float MaxHP);					// �ݒ菈��
void SetPositionHPgauge(int Indx,D3DXVECTOR3 pos);									// �ʒu�̐ݒ菈��
void HPgaugeDeff(int Indx,float NowHP);												// �Q�[�W�̌�������
void RedgaugeDeff(int Indx, float NowHP);											// �ԃQ�[�W�̌�������
void DeleteGuage(int Indx);															// HP�Q�[�W������

#endif // !HPGAUGE_H_
