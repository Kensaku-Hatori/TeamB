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
#define MAX_HPGAUGE (32)		//�Q�[�W�̍ő�̐�

//HP�Q�[�W�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	LPDIRECT3DVERTEXBUFFER9 pVtxHPgaugeBuff;
	int nLife;
	bool bUse;
}HPgauge;

//�v���g�^�C�v�錾
void InitHPgauge();
void UninitHPgauge();
void UpdateHPgauge();
void DrawHPgauge();

#endif // !HPGAUGE_H_
