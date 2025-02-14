//================================
//
// �r���{�[�h����[Biillboard.h]
// Author:kaiti
//
//================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

#define MAX_BILLBOARD (10)								//�r���{�[�h�̐�

//�r���{�[�h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR2 origin;									//���_
	D3DXMATRIX mtxWorld;								//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffBiillboard;			//���_���
	LPDIRECT3DTEXTURE9 pTextureBiillboard;
	int nIndexShadow;									//�e�̃C���f�b�N�X
	int textype;										//�e�N�X�`���̎��
	int nWidth;											//��
	int nHeight;										//����
	bool bShadow;										//�e�����邩�ǂ���
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Biillboard;

//�v���g�^�C�v�錾
void InitBiillboard(void);
void UninitBiillboard(void);
void UpdateBiillboard(void);
void DrawBiillboard(void);
void SetBiillboard(D3DXVECTOR3 pos, int nWidth, int nHeigh, int textype, D3DXVECTOR2 origin, bool bShadow);
void SetBillTexture(int Indx);
#endif