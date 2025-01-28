//============================================================
//
//�A�C�e��[Item.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//�}�N����`
#define MAX_ITEM (5)									//�ő�A�C�e����
#define NUM_ITEMTYPE (3)								//�A�C�e���̎�ނ̐�
#define ITEM_RADIUS (10.0f)								//�A�C�e��(�r���{�[�h)�̔��a
#define ITEM_TIME_DEL (240)								//�A�C�e����������܂ł̃t���[��

//�e�N�X�`��
static const char* ITEM_TEXTURE[NUM_ITEMTYPE] =
{

};

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//����
	D3DXVECTOR3 size;									//���a
	D3DXMATRIX mtxWorld;								//���[���h�}�g���b�N�X
	int type;											//���
	int nCntTime;										//������܂ł̃t���[���J�E���^
	int nIndexShadow;									//�e�̃C���f�b�N�X�i�[�p
	bool bUse;											//�g�p���Ă��邩�ǂ���
	bool bDesp;											//�`�悷�邩�ǂ���
}Item;

//�v���g�^�C�v�錾
void InitItem();										//����������
void UninitItem();										//�I������
void UpdateItem();										//�X�V����
void DrawItemBillboard();								//�`�揈��(�r���{�[�h)
void SetItem(D3DXVECTOR3 pos, int type);				//�ݒ菈��
void CollisionItem(int nIndexItem);						//�擾����

#endif // !_MODEL_H_