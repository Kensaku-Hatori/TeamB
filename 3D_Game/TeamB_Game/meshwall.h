//===================================
//
// メッシュ壁表示処理[meshWall.h]
// Author:kaiti
//
//===================================

#ifndef _MESHWALL_H
#define _MESHWALL_H_

#include "main.h"

//マクロ定義
#define MAX_MESHWALL (4)
#define MAX_TEX_WALL (16)

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int textype;							//テクスチャのタイプ
	int nDiviX;								//分割数x
	int nDiviY;								//分割数y
	int nDiviZ;								//分割数z
	int nWidth;								//幅
	int nHeight;							//高さ
	int nIndex;								//インテックス保存用
	bool bUse;								//使用しているかどうか
}MeshWall;

//プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int textype, int nDiviX, int nDiviY, int nDiviZ, int fWidth, int fHeight);
void SetwallTexture(char texfileName[32]);		//テクスチャ設定

#endif