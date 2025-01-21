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
#define MESH_NUM_MAX (1)//���b�V���t�B�[���h�̐�
#define MAX_TEX (64)//�e�N�X�`���̍ő吔

//�|���S��(��)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int textype;							//�e�N�X�`���̃^�C�v
	int nDiviX;								//������x
	int nDiviY;								//������y
	int nDiviZ;								//������z
	int fWidth;								//��
	int fHeight;							//����
	bool bUse;								//�g�p���Ă��邩�ǂ���
}MeshField;

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetMeshfield(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int textype,int nDiviX,int nDiviY,int nDiviZ,int fWidth,int fHeight);//�ʒu�A�����A�e�N�X�`���A������x�A������y�A������z�A���A����
void SetTexture(char texfileName[32]);		//�e�N�X�`���ݒ�

#endif