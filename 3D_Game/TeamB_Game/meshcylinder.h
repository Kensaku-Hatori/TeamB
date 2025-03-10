//==============================================
//
// ���b�V���~���\������[MeshCylinder.h]
// Author:kaiti
//
//==============================================
#ifndef _MESHCYLINDER_H
#define _MESHCYLINDER_H_

#include "main.h"

//�}�N����`
#define MESHCYLINDERVTX_X (8)//��
#define MESHCYLINDERVTX_Z (2)//�c

#define MAXCYLINDER_VTX ((MESHCYLINDERVTX_X + 1) * (MESHCYLINDERVTX_Z + 1))//���_��

#define CYLINDERPOLYGON_NO (MESHCYLINDERVTX_X * MESHCYLINDERVTX_Z * 2 + (MESHCYLINDERVTX_Z - 1) * 4)//�|���S����

#define CYLINDERINDEX_NO ((MESHCYLINDERVTX_X + 1) * 2 * MESHCYLINDERVTX_Z + (MESHCYLINDERVTX_Z - 1) * 2)//�C���f�b�N�X��

#define MESHCYLINDER_SIZE (150.0f)

//�v���g�^�C�v�錾
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
#endif