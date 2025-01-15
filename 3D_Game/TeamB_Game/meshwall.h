//===================================
//
// ���b�V���Ǖ\������[meshWall.h]
// Author:kaiti
//
//===================================
#ifndef _MESHWALL_H
#define _MESHWALL_H_

#include "main.h"

//�}�N����`
#define WALLMESHVTX_X (50)//��
#define WALLMESHVTX_Y (50)//�c

#define WALLMAX_VTX ((WALLMESHVTX_X + 1) * (WALLMESHVTX_Y + 1))//���_��

#define WALLPOLYGON_NO (WALLMESHVTX_X * WALLMESHVTX_Y * 2 + (WALLMESHVTX_Y - 1) * 4)//�|���S����

#define WALLINDEX_NO ((WALLMESHVTX_X + 1) * 2 * WALLMESHVTX_Y + (WALLMESHVTX_Y - 1) * 2)//�C���f�b�N�X��

#define WALLMESH_SIZE (150.0f)

#define MAX_MESHWALL (4)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;
}MeshWall;

//�v���g�^�C�v�錾
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif