//============================
//
// モデル表示処理[Block.h]
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

//構造体
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス

	D3DXVECTOR3 vtxMinBlock[BLOCKTYPE_MAX];//モデルの最小値
	D3DXVECTOR3 vtxMaxBlock[BLOCKTYPE_MAX];//モデルの最大値
	MODELINFO aModel[BLOCKTYPE_MAX];
	BLOCKTYPE type;
	bool bUse;
}Block;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE type);
bool CollisionBlock(void);
void CollisionBlockEnemy(int nCntEnemy);

#endif
