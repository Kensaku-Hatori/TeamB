//============================
//
// ���f���\������[Block.h]
// Author:kaiti
//
//============================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include "model.h"

#define MAX_BLOCK (50)

typedef enum
{
	BLOCKTYPE_NORMAL = 0,
	BLOCKTYPE_WALL,
	BLOCKTYPE_PILLAR,
	BLOCKTYPE_MAX,
}BLOCKTYPE;

//�\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

	D3DXVECTOR3 vtxMinBlock[BLOCKTYPE_MAX];//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxBlock[BLOCKTYPE_MAX];//���f���̍ő�l
	MODELINFO aModel[BLOCKTYPE_MAX];
	BLOCKTYPE type;
	bool bUse;
}Block;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE type);
bool CollisionBlock(void);
void CollisionBlockEnemy(int nCntEnemy);

#endif
