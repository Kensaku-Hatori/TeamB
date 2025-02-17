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
	D3DXVECTOR3 pos;								// �ʒu
	D3DXVECTOR3 rot;								// ����
	LPDIRECT3DVERTEXBUFFER9 pVtxHPgaugeBuff;		// ���[���h�}�g���b�N�X
	float fNowHP;									// ���݂�HP
	float fMaxHP;									// �ő��HP
	float fWidth;									// ��
	float fHeight;									// ����
	bool bUse;										// �g�p���Ă��邩�ǂ���
}HPgauge;

//�v���g�^�C�v�錾
void InitHPgauge();									// ����������
void UninitHPgauge();								// �I������
void UpdateHPgauge();								// �X�V����
void DrawHPgauge();									// �`�揈��
void SetHPgauge(D3DXVECTOR3 pos);					// �ݒ菈��

#endif // !HPGAUGE_H_
