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
#define MESHVTX_X (15)//��
#define MESHVTX_Z (15)//�c

#define MAX_VTX ((MESHVTX_X + 1) * (MESHVTX_Z + 1))//���_��

#define POLYGON_NO (MESHVTX_X * MESHVTX_Z * 2 + (MESHVTX_Z - 1) * 4)//�|���S����

#define INDEX_NO ((MESHVTX_X + 1) * 2 * MESHVTX_Z + (MESHVTX_Z - 1) * 2)//�C���f�b�N�X��

#define MESH_SIZE (150.0f)

#define MESH_NUM_MAX (1)//���b�V���t�B�[���h�̐�


//�e�N�X�`���^�C�v
typedef enum
{
	MESH_TEX_NULL=0,
	MESH_TEX_MAX
}MESH_TEX;

//�t�@�C���i�[
static const char* MESHFIELD_TEXTURE[MESH_TEX_MAX] =
{
	NULL
};

//�|���S��(��)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	MESH_TEX textype;						//�e�N�X�`���̃^�C�v
	int nDiviX;								//������x
	int nDiviY;								//������y
	int nDiviZ;								//������z
	float fWidth;								//��
	float fHeight;							//����
	bool bUse;								//�g�p���Ă��邩�ǂ���
}MeshField;

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetMeshfield(D3DXVECTOR3 pos,D3DXVECTOR3 rot,MESH_TEX textype,int nDiviX,int nDiviY,int nDiviZ,float fWidth,float fHeight);//�ʒu�A�����A�e�N�X�`���A������x�A������y�A������z�A���A����

#endif