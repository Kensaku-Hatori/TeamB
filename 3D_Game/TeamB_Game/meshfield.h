//=====================================
//
// ���b�V�����\������[meshfield.h]
// Author:kaiti
//
//=====================================
#ifndef _MESHFIELD_H
#define _MESHFIELD_H_

#include "main.h"

//�}�N����`
#define MESH_NUM_MAX (16)//���b�V���t�B�[���h�̐�
#define MAX_TEX_FIELD (64)//�e�N�X�`���̍ő吔

//�|���S��(��)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//����
	D3DXMATRIX mtxWorld;								//���[���h�}�g���b�N�X
	LPDIRECT3DINDEXBUFFER9 IdxBuffMeshField;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int textype;										//�e�N�X�`���̃^�C�v
	int nDiviX;											//������x
	int nDiviY;											//������y
	int nDiviZ;											//������z
	int nWidth;											//��
	int nHeight;										//����
	int nIndex;											//�C���e�b�N�X�ۑ��p
	bool bUse;											//�g�p���Ă��邩�ǂ���
}MeshField;

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetMeshfield(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int textype,int nDiviX,int nDiviY,int nDiviZ,int nWidth,int nHeight);//�ʒu�A�����A�e�N�X�`���A������x�A������y�A������z�A���A����
void SetfieldTexture(char *pFileName,int TexIndx);		//�e�N�X�`���ݒ�
#endif