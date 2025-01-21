//=====================================
//
// メッシュ床表示処理[meshfield.h]
// Author:kaiti
//
//=====================================
#ifndef _MESHFIELD_H
#define _MESHFIELD_H_

#include "main.h"

//マクロ定義
#define MESH_NUM_MAX (1)//メッシュフィールドの数
#define MAX_TEX (64)//テクスチャの最大数

//ポリゴン(横)の構造体
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int textype;							//テクスチャのタイプ
	int nDiviX;								//分割数x
	int nDiviY;								//分割数y
	int nDiviZ;								//分割数z
	int fWidth;								//幅
	int fHeight;							//高さ
	bool bUse;								//使用しているかどうか
}MeshField;

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
void SetMeshfield(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int textype,int nDiviX,int nDiviY,int nDiviZ,int fWidth,int fHeight);//位置、向き、テクスチャ、分割数x、分割数y、分割数z、幅、高さ
void SetTexture(char texfileName[32]);		//テクスチャ設定

#endif