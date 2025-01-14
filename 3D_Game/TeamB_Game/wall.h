//============================
//
// �|���S���\������[Wall.h]
// Author:kaiti
//
//============================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

#define MAX_WALL (4)
#define WALL_HEIGHT (75)
#define WALL_WIDTH (75)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float a);
void CollisionWall(void);
Wall* GetWall(void);

#endif